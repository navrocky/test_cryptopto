set(TARGET test_cryptopro)

project(${TARGET} LANGUAGES CXX)
cmake_minimum_required(VERSION 3.7)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

find_package(CAPILite REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUNIX -DHAVE_LIMITS_H -D_COMPACT -DHAVE_STDINT_H -DSIZEOF_VOID_P=8 -DIGNORE_LEGACY_FORMAT_MESSAGE_MSG")

include_directories(${CAPILite_INCLUDE_DIR})

set(SOURCES
    main.cpp
)

add_executable(${TARGET} ${SOURCES})

target_link_libraries(${TARGET}
    ${CAPILite_LIBRARIES}
)



