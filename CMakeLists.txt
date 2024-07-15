cmake_minimum_required(VERSION 3.10)

option(DEVELOPMENT "Development mode" ON)
option(BUILD_TESTS "Build tests" OFF)
option(INSTALL "Install library" OFF)

if (INSTALL)
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

if(INSTALL)
  set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})

  set(LIB_TARGET_NAME ${PROJECT_NAME})
  set(LIB_TARGET_NAMESPACE "${PROJECT_NAME}::")
  set(LIB_INSTALL_PATH "lib/cmake/caitlyn")

  set(LIB_EXPORT_NAME "${PROJECT_NAME}Targets")

  set(LIB_ROOT_CONFIG "${PROJECT_NAME}Config.cmake.in")
  set(LIB_CONFIG "${PROJECT_NAME}Config.cmake")
  set(LIB_CONFIG_VERSION "${PROJECT_NAME}ConfigVersion.cmake")
  set(LIB_TARGETS "${PROJECT_NAME}Targets.cmake")

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
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/${LIB_ROOT_CONFIG}"
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

  export(
    EXPORT ${LIB_EXPORT_NAME}
    FILE "${CMAKE_CURRENT_BINARY_DIR}/${LIB_TARGETS}"
    NAMESPACE ${LIB_TARGET_NAMESPACE}
  )
endif()
