# Find CryptoPro CSP CAPILite 2.0

find_path(CAPILite_INCLUDE_DIR
  NAMES capiextern.h
  PATHS /opt/cprocsp/include
)

find_library(CAPILite_LIBRARY_10
  NAMES capi10
  PATHS /opt/cprocsp/lib/amd64
)

find_library(CAPILite_LIBRARY_20
  NAMES capi20
  PATHS /opt/cprocsp/lib/amd64
)

find_library(CAPILite_LIBRARY_RDRSUP
    NAMES rdrsup
    PATHS /opt/cprocsp/lib/amd64
)

set(CAPILite_LIBRARIES ${CAPILite_LIBRARY_10} ${CAPILite_LIBRARY_20} ${CAPILite_LIBRARY_RDRSUP})

set(CAPILite_VERSION 2.0)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CAPILite
  FOUND_VAR CAPILite_FOUND
  REQUIRED_VARS
    CAPILite_LIBRARY_10
    CAPILite_LIBRARY_20
    CAPILite_LIBRARY_RDRSUP
    CAPILite_LIBRARIES
    CAPILite_INCLUDE_DIR
  VERSION_VAR CAPILite_VERSION
)
