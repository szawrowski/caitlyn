cmake_minimum_required(VERSION 3.10)

option(CAITLYN_DEV "Development mode" ON)
option(CAITLYN_INSTALL "Install library" OFF)

if (CAITLYN_INSTALL)
  set(CAITLYN_DEV OFF)
endif()

if(CAITLYN_DEV)
  if(UNIX)
    set(TOOLCHAIN_PATH "$ENV{HOME}/vcpkg/scripts/buildsystems/vcpkg.cmake")
  elseif(WIN32)
    set(TOOLCHAIN_PATH "$ENV{HOMEPATH}/vcpkg/scripts/buildsystems/vcpkg.cmake")
  endif()
  set(CMAKE_TOOLCHAIN_FILE ${TOOLCHAIN_PATH} CACHE STRING "Vcpkg toolchain file")
endif()

set(CAITLYN_MAJOR_VERSION 1)
set(CAITLYN_MINOR_VERSION 0)
set(CAITLYN_PATCH_VERSION 0)

set(CAITLYN_VERSION_STRING
    "${CAITLYN_MAJOR_VERSION}.${CAITLYN_MINOR_VERSION}.${CAITLYN_PATCH_VERSION}")

project(caitlyn VERSION ${CAITLYN_VERSION_STRING} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CAITLYN_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

if(CAITLYN_DEV)
  if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Wall /W3 /permissive")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
  endif()

  find_package(GTest CONFIG REQUIRED)

  add_subdirectory(test)
endif()

if(CAITLYN_INSTALL)
  set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})

  set(CAITLYN_TARGET_NAME cait)
  set(CAITLYN_TARGET_NAMESPACE "${PROJECT_NAME}::")
  set(CAITLYN_INSTALL_PATH "lib/cmake/caitlyn")

  add_library(${CAITLYN_TARGET_NAME} INTERFACE)

  target_include_directories(
    ${CAITLYN_TARGET_NAME} INTERFACE
    $<BUILD_INTERFACE:${CAITLYN_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:include>
  )

  include(CMakePackageConfigHelpers)
  write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${CAITLYN_VERSION_STRING}
    COMPATIBILITY AnyNewerVersion
  )

  configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION ${CAITLYN_INSTALL_PATH}
  )

  install(
    TARGETS ${CAITLYN_TARGET_NAME}
    EXPORT "${PROJECT_NAME}Targets"
    INCLUDES DESTINATION include
  )

  install(
    EXPORT "${PROJECT_NAME}Targets"
    FILE "${PROJECT_NAME}Targets.cmake"
    NAMESPACE ${CAITLYN_TARGET_NAMESPACE}
    DESTINATION ${CAITLYN_INSTALL_PATH}
  )

  install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
          "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION ${CAITLYN_INSTALL_PATH}
  )

  export(
    EXPORT "${PROJECT_NAME}Targets"
    FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake"
    NAMESPACE ${CAITLYN_TARGET_NAMESPACE}
  )
endif()
