# mechanismsynthesis
Create a mechanism from specified inputs

The current Visusl Studio Code configuration supports build and debug on Mac and Windows. Linux is not supported as of now.

How to compile
## On macOS
### Using Visual Studio Code
Reference - https://code.visualstudio.com/docs/cpp/config-clang-mac
1. Install Visual Studio Code
2. Install C/C++ extension by Microsoft (see extensions.json)
4. Install clang compiler (should be installed by Xcode)
5. If clang is not installed (check by running "clang --version" in terminal), install by running "xcode-select --install" in terminal
6. Run the project from Visual Studio Code

## On Windows
### Using Visual Studio Code
Reference - https://code.visualstudio.com/docs/cpp/config-msvc
1. Install Visual Studio Code
2. Install C++ development tools for Visual Studio
3. Install C/C++ extension by Microsoft (see extensions.json)
5. Launch VSCode by typing "code ." in Developer Command Prompt for VS 2022 from the project directory. This is required to add cl.exe in the path
6. Run the project from Visual Studio Code

## Externam Dependencies
### Eigen
Eigen is a C++ template library for linear algebra: matrices, vectors, numerical solvers, and related algorithms.  
Wiki - https://eigen.tuxfamily.org/  
Source Code - https://gitlab.com/libeigen/eigen  
Releases - https://gitlab.com/libeigen/eigen/-/releases  
Version included - 3.4.0  

### doctest
doctest is a new C++ testing framework but is by far the fastest both in compile times (by orders of magnitude) and runtime compared to other feature-rich alternatives. It is a header only framework and included as a single header doctest.h.
Wiki - https://github.com/doctest/doctest/blob/master/README.md  
Source Code - https://github.com/doctest/doctest  
Releases - https://github.com/doctest/doctest/releases  
Version included - 2.4.11  
