set(TEST_TARGET_NAME "${PROJECT_NAME}_test")

file(GLOB_RECURSE TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cc")

add_executable(${TEST_TARGET_NAME} ${TEST_SOURCES})

target_include_directories(${TEST_TARGET_NAME} PRIVATE ${PROJECT_INCLUDE_DIR})

target_link_libraries(${TEST_TARGET_NAME}
  PRIVATE GTest::gtest GTest::gtest_main)

enable_testing()
add_test(NAME CaitlynTests COMMAND $<TARGET_FILE:${TEST_TARGET_NAME}>)
