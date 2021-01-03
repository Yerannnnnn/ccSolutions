include(ExternalProject)

ExternalProject_Add(
    catch2
    URL https://github.com/catchorg/Catch2/archive/v2.13.4.zip
    # SOURCE_DIR        "${CMAKE_CURRENT_BINARY_DIR}/catch2-src"
    # BINARY_DIR        "${CMAKE_CURRENT_BINARY_DIR}/catch2-build"
    PREFIX "${CMAKE_INSTALL_PREFIX}/catch2"
    # Disable install step
    CONFIGURE_COMMAND ""
    BUILD_COMMAND     ""
    UPDATE_COMMAND    ""
    INSTALL_COMMAND   ""
    TEST_COMMAND      ""
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON
)


ExternalProject_Get_Property(catch2 source_dir)
