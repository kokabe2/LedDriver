add_library(
    LedDriver
    "")

target_sources(
    LedDriver
    PRIVATE
        LedDriver.c
        SpyRuntimeError.c
    )

target_include_directories(
    LedDriver
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
    )
