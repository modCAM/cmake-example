include(CMakeFindDependencyMacro)
find_dependency(Eigen3)
find_dependency(modCAM)

include(${CMAKE_CURRENT_LIST_DIR}/modCAM-cmake-example-Targets.cmake)
