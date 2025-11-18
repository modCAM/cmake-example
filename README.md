# ModCAM example project

This example project shows you how to incorporate [modCAM](https://github.com/modCAM/modcam) into your CMake project using [`FetchContent`](https://cmake.org/cmake/help/latest/module/FetchContent.html). It includes an executable and a library example.

## Dependencies

ModCAM depends on [Eigen](https://libeigen.gitlab.io/) and [libigl](https://libigl.github.io/). This example project is set up to fetch those dependencies with [vcpkg](https://vcpkg.io/).

## Compile and run the example

This example project has a CMake preset you can use to install the dependencies with vcpkg:

```
cmake -S . -D CMAKE_BUILD_TYPE=Release --preset vcpkg
cmake --build build/
```

Once it's built, you can run the executable:

```
./build/modcam-cmake-example
```

If you want to install the library:

```
cmake --install build/ --prefix build/cmake-example
```

## Point to a local copy of modCAM

### [`FetchContent`](https://cmake.org/cmake/help/latest/module/FetchContent.html) mode

If you want to edit modCAM and then use those changes in your project immediately, you can point `FetchContent` to your local copy of modCAM using [`FETCHCONTENT_SOURCE_DIR_MODCAM`](https://cmake.org/cmake/help/latest/module/FetchContent.html#variable:FETCHCONTENT_SOURCE_DIR_%3CuppercaseName%3E). This can be helpful for iterating quickly on your ideas.

```
cmake -S . -D FETCHCONTENT_SOURCE_DIR_MODCAM=</path/to/your/local/modcam> -D CMAKE_BUILD_TYPE=Release --preset vcpkg
```

Be sure to clear `build/CMakeCache.txt` before changing the value of `FETCHCONTENT_SOURCE_DIR_MODCAM`.

### [`find_package`](https://cmake.org/cmake/help/latest/command/find_package.html) mode

For library developers, if you install the library as shown above, then you'll get the following output when using FetchContent:

```
build/
|__ cmake-example/
    |__ include/
    |   |__ modcam/  <-- modCAM is installed here...
    |   |__ max_curvature.h
    |   |__ VERSION
    |__ share/
        |__ cmake/
            |__ modCAM/  <-- and here
            |__ modCAM-cmake-example/
```

ModCAM is installed next to your library, which you might not want if you are trying to package up your library. In that case, you can install modCAM separately and supply CMake with its package config location so that CMake uses `find_package()` instead of `FetchContent`. To do this, you can either clone the modCAM repo and install it:

```
git clone https://github.com/modCAM/modcam.git
cd modcam
# Make whatever code changes you want.
cmake -S . -D CMAKE_BUILD_TYPE=Release --preset build-minimal
cmake --build build/
cmake --install build/ --prefix build/modcam    # Install it wherever you want it
```

or you can download a [release package](https://github.com/modCAM/modcam/releases), which contains the necessary files.

Once you have installed modCAM, direct CMake to the package config location by supplying the path in `modCAM_DIR`. This variable needs to point to the directory that contains `modCAMConfig.cmake` and `modCAMConfigVersion.cmake`, which are in `share/cmake/modCAM` by default.

```
cmake -S . -D modCAM_DIR=</path/to/share/cmake/modCAM> -D CMAKE_BUILD_TYPE=Release --preset vcpkg
```

For example, if you installed modCAM in `/home/user/modcam/build/modcam`, then the CMake command would be 

```
cmake -S . -D modCAM_DIR=/home/user/modcam/build/modcam/share/cmake/modCAM -D CMAKE_BUILD_TYPE=Release --preset vcpkg
```
