add_executable(
    gtests
    "")

target_sources(
    gtests
    PRIVATE
      LedDriverTest.cpp
    )

target_link_libraries(
    gtests
    gtest_main
    LedDriver
    )

add_test(
  NAME
    LedDriverTest
  COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/gtests
  )
