cmake_minimum_required(VERSION 3.14...3.22)

include(CMakePrintHelpers) # Debug printing variables
# ---- Project ----

# Note: update this to your new project's name and version
project(
  BeanBackend
  VERSION 1.0
  LANGUAGES CXX
)

# ---- Include guards ----

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
endif()

# ---- Add dependencies via CPM ----
# see https://github.com/TheLartians/CPM.cmake for more info

include(cmake/CPM.cmake)

# PackageProject.cmake will be used to make our target installable
CPMAddPackage("gh:TheLartians/PackageProject.cmake@1.8.0")
CPMAddPackage("gh:oatpp/oatpp#1.3.0-latest")
if(oatpp_ADDED)
  add_library(oatpp::oatpp ALIAS oatpp)
  add_library(oatpp::oatpp-test ALIAS oatpp-test)
endif()

CPMAddPackage("gh:oatpp/oatpp-swagger#1.3.0-latest")
# cmake_print_variables(oatpp-swagger_SOURCE_DIR) cmake_print_variables(oatpp-swagger_BINARY_DIR)
CPMAddPackage(
  NAME fmt
  GIT_TAG 11.0.2
  GITHUB_REPOSITORY fmtlib/fmt
  OPTIONS "FMT_INSTALL YES" # create an installable target
)

# ---- Add source files ----

# Note: globbing sources is considered bad practice as CMake's generators may not detect new files
# automatically. Keep that in mind when changing files, or explicitly mention them here.
file(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")

# ---- Create library ----

# Note: for header-only libraries change all PUBLIC flags to INTERFACE and create an interface
# target: add_library(${PROJECT_NAME} INTERFACE)
include(cmake/tools.static-analyzers.cmake)

add_library(${PROJECT_NAME} ${headers} ${sources})
include(cmake/tools.static-analyzers.disable.cmake)
set_target_properties(
  ${PROJECT_NAME} PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS OFF
)

# Link dependencies
target_link_libraries(
  ${PROJECT_NAME}
  PUBLIC oatpp
  PUBLIC fmt::fmt
  PUBLIC oatpp-swagger
)

target_include_directories(
  ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                         $<INSTALL_INTERFACE:include/${PROJECT_NAME}-${PROJECT_VERSION}>
)
target_compile_definitions(
  ${PROJECT_NAME} PUBLIC OATPP_SWAGGER_RES_PATH="${oatpp-swagger_SOURCE_DIR}/res"
)

# ---- Create an installable target ----
# this allows users to install and find the library via `find_package()`.

# the location where the project's version header will be placed should match the project's regular
# header paths
string(TOLOWER ${PROJECT_NAME}/version.h VERSION_HEADER_LOCATION)

# packageProject( NAME ${PROJECT_NAME} VERSION ${PROJECT_VERSION} NAMESPACE ${PROJECT_NAME}
# BINARY_DIR ${PROJECT_BINARY_DIR} INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include INCLUDE_DESTINATION
# include/${PROJECT_NAME}-${PROJECT_VERSION} VERSION_HEADER "${VERSION_HEADER_LOCATION}"
# COMPATIBILITY SameMajorVersion )
