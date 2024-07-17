cmake_minimum_required(VERSION 3.10)

option(DEVELOPMENT "Development mode" ON)
option(BUILD_TESTS "Build tests" OFF)
option(LIB_INSTALL "Install library" OFF)

if (LIB_INSTALL)
  set(DEVELOPMENT OFF)
endif()

if (DEVELOPMENT)
  set(BUILD_TESTS ON)
endif()

set(LIB_MAJOR_VERSION 1)
set(LIB_MINOR_VERSION 0)
set(LIB_PATCH_VERSION 0)

set(
  LIB_VERSION_STRING
  "${LIB_MAJOR_VERSION}.${LIB_MINOR_VERSION}.${LIB_PATCH_VERSION}"
)

project(Caitlyn VERSION ${LIB_VERSION_STRING} LANGUAGES CXX)

if(DEVELOPMENT)
  set(CMAKE_CXX_STANDARD 11)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)

  if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc /Wall /W3 /permissive")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
  endif()
endif()

set(LIB_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(test)
endif()

if(LIB_INSTALL)
  set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})

  set(LIB_TARGET_NAME ${PROJECT_NAME})
  set(LIB_TARGET_NAMESPACE "${LIB_TARGET_NAME}::")
  set(LIB_EXPORT_NAME "${LIB_TARGET_NAME}Targets")

  set(LIB_INSTALL_PATH "lib/cmake/caitlyn")
  set(LIB_CONFIG_INCLUDE_PATH "${CMAKE_SOURCE_DIR}/cmake")

  set(LIB_CONFIG_INCLUDE "${LIB_TARGET_NAME}Config.cmake.in")
  set(LIB_CONFIG "${LIB_TARGET_NAME}Config.cmake")
  set(LIB_CONFIG_VERSION "${LIB_TARGET_NAME}ConfigVersion.cmake")
  set(LIB_TARGETS "${LIB_TARGET_NAME}Targets.cmake")

  add_library(${LIB_TARGET_NAME} INTERFACE)

  target_include_directories(
    ${LIB_TARGET_NAME} INTERFACE
    $<BUILD_INTERFACE:${LIB_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:include>
  )

  include(CMakePackageConfigHelpers)

  write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${LIB_CONFIG_VERSION}"
    VERSION ${LIB_VERSION_STRING}
    COMPATIBILITY AnyNewerVersion
  )

  configure_package_config_file(
    "${LIB_CONFIG_INCLUDE_PATH}/${LIB_CONFIG_INCLUDE}"
    "${CMAKE_CURRENT_BINARY_DIR}/${LIB_CONFIG}"
    INSTALL_DESTINATION ${LIB_INSTALL_PATH}
  )

  install(
    TARGETS ${LIB_TARGET_NAME}
    EXPORT ${LIB_EXPORT_NAME}
    INCLUDES DESTINATION include
  )

  install(
    EXPORT ${LIB_EXPORT_NAME}
    FILE ${LIB_TARGETS}
    NAMESPACE ${LIB_TARGET_NAMESPACE}
    DESTINATION ${LIB_INSTALL_PATH}
  )

  install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/${LIB_CONFIG}"
          "${CMAKE_CURRENT_BINARY_DIR}/${LIB_CONFIG_VERSION}"
    DESTINATION ${LIB_INSTALL_PATH}
  )
endif()
