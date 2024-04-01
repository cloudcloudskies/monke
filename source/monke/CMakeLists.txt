set(MONKE_SOURCE_FILES
    main.cc
    pack.cc)

set(MONKE_INCLUDE_DIRECTORIES
    ${CMAKE_SOURCE_DIR}/include/monke
    ${CMAKE_SOURCE_DIR}/third_party
    ${PROJECT_BINARY_DIR}/source/monke)

set(MONKE_LINK_LIBRARIES
    cryptopp)

set(MONKE_COMPILE_DEFINITIONS
    NDEBUG)

configure_file(
    ${CMAKE_SOURCE_DIR}/include/monke/config.hh.in
    ${CMAKE_BINARY_DIR}/include/monke/config.hh)

add_executable(monke ${MONKE_SOURCE_FILES})

target_include_directories(monke PUBLIC ${MONKE_INCLUDE_DIRECTORIES})
target_link_libraries(monke PUBLIC ${MONKE_LINK_LIBRARIES})
target_compile_definitions(monke PUBLIC ${MONKE_COMPILE_DEFINITIONS})
