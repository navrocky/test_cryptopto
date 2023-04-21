#include <fstream>
#include <stdexcept>
#include <vector>

#include <cpcsp/CSP_WinCrypt.h>
#include <cpcsp/CSP_WinDef.h>
#include <cpcsp/WinCryptEx.h>

std::vector<BYTE> readFile(const char* fn)
{
    std::ifstream s(fn);
    return std::vector<BYTE>((std::istreambuf_iterator<char>(s)), std::istreambuf_iterator<char>());
}

void writeFile(const char* fn, const std::vector<BYTE>& buf)
{
    std::ofstream s(fn);
    s.write((const char*)buf.data(), buf.size());
}

void writeHash(HCRYPTHASH hHash, const char* fn)
{
    size_t digestSize;
    DWORD dataLen = sizeof(digestSize);

    if (!CryptGetHashParam(hHash, HP_HASHSIZE, (BYTE*)(&digestSize), &dataLen, 0))
        throw std::runtime_error("CryptGetHashParam");

    std::vector<BYTE> digest(digestSize, 0);
    dataLen = digestSize;
    if (!CryptGetHashParam(hHash, HP_HASHVAL, digest.data(), &dataLen, 0))
        throw std::runtime_error("CryptGetHashParam");

    writeFile(fn, digest);
}

int main(int argc, char* argv[])
{
    // read data
    auto fn = argv[1];
    auto buf = readFile(fn);

    const auto containerName = "\\\\.\\HDIMAGE\\test_gost12_256";

    // init provider context
    HCRYPTPROV hProv;
    if (!CryptAcquireContext(&hProv, containerName, nullptr, PROV_GOST_2012_256, 0))
        throw std::runtime_error("CryptAcquireContext");

    auto pin = "123456";
    if (!CryptSetProvParam(hProv, PP_SIGNATURE_PIN, (const BYTE*)pin, 0))
        throw std::runtime_error("CryptSetProvParam");

    // calc hash
    auto alg = CALG_GR3411_2012_256;

    HCRYPTHASH hHash;
    if (!CryptCreateHash(hProv, CALG_GR3411_2012_256, 0, 0, &hHash))
        throw std::runtime_error("CryptCreateHash");

    if (!CryptHashData(hHash, buf.data(), buf.size(), 0))
        throw std::runtime_error("CryptCreateHash");

    writeHash(hHash, "hash");

    // sign hash
    DWORD dwSigLen = 0;
    if (!CryptSignHash(hHash, AT_SIGNATURE, nullptr, 0, nullptr, &dwSigLen))
        throw std::runtime_error("CryptSignHash");

    std::vector<BYTE> signature(dwSigLen, 0);

    if (!CryptSignHash(hHash, AT_SIGNATURE, nullptr, 0, signature.data(), &dwSigLen))
        throw std::runtime_error("CryptSignHash");

    writeFile("signature", signature);

    return 0;
}
