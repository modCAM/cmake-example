cmake_minimum_required(VERSION 4.0)

project(
    modCAM-cmake-example
    DESCRIPTION "An example of how to use modCAM in your project with CMake"
	VERSION 0.1.0
    LANGUAGES CXX
)

set(MODCAM_CMAKE_EXAMPLE_MIN_CXX_STANDARD 20)
if(DEFINED CMAKE_CXX_STANDARD)
	if(CMAKE_CXX_STANDARD EQUAL 98 OR CMAKE_CXX_STANDARD LESS MODCAM_CMAKE_EXAMPLE_MIN_CXX_STANDARD)
		message(FATAL_ERROR "modCAM-cmake-example requires at least C++${MODCAM_CMAKE_EXAMPLE_MIN_CXX_STANDARD}")
	endif()
else()
	set(CMAKE_CXX_STANDARD ${MODCAM_CMAKE_EXAMPLE_MIN_CXX_STANDARD})
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Eigen3 REQUIRED NO_MODULE)
find_package(libigl CONFIG REQUIRED)

include(FetchContent)
FetchContent_Declare(
    modCAM
    URL ${CMAKE_CURRENT_LIST_DIR}/../modcam # TODO: Replace placeholder URL with git repo
	FIND_PACKAGE_ARGS
)
FetchContent_MakeAvailable(modCAM)

# Executable ===================================================================

add_executable(modcam-cmake-example src/main.cpp)
target_link_libraries(
	modcam-cmake-example PRIVATE
		Eigen3::Eigen
		modCAM::mesh
)

# Library ======================================================================

add_library(modcam-cmake-exampe-lib INTERFACE)
add_library(modcam-cmake-example::lib ALIAS modcam-cmake-exampe-lib)
target_link_libraries(
    modcam-cmake-exampe-lib INTERFACE
		Eigen3::Eigen
		modCAM::mesh
)
set_target_properties(
	modcam-cmake-exampe-lib PROPERTIES
	EXPORT_NAME lib
)

target_sources(
	modcam-cmake-exampe-lib INTERFACE
		FILE_SET HEADERS
		BASE_DIRS "${modCAM-cmake-example_SOURCE_DIR}/include"
		FILES
			"${modCAM-cmake-example_SOURCE_DIR}/include/max_curvature.h"
)

install(
    TARGETS modcam-cmake-exampe-lib
    EXPORT modCAM-cmake-example-Targets
    FILE_SET HEADERS
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

set(MODCAM_CMAKE_EXAMPLE_INSTALL_CMAKEDIR "share/cmake/modCAM-cmake-example"
	CACHE PATH "CMake package config location"
)
mark_as_advanced(MODCAM_CMAKE_EXAMPLE_INSTALL_CMAKEDIR)

install(
    EXPORT modCAM-cmake-example-Targets
    DESTINATION "${MODCAM_CMAKE_EXAMPLE_INSTALL_CMAKEDIR}"
    NAMESPACE modCAM-cmake-example::
    FILE modCAM-cmake-example-Targets.cmake
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
	modcam-cmake-example-config-version.cmake
	COMPATIBILITY SameMajorVersion
	ARCH_INDEPENDENT
)

install(
	FILES
	    tools/cmake/modcam-cmake-example-config.cmake
		"${CMAKE_CURRENT_BINARY_DIR}/modcam-cmake-example-config-version.cmake"
	DESTINATION "${MODCAM_CMAKE_EXAMPLE_INSTALL_CMAKEDIR}"
)
