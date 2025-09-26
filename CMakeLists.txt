cmake_minimum_required(VERSION 3.21)
project(uge2 LANGUAGES CXX)
 
set(CMAKE_PREFIX_PATH "C:/Qt/6.9.2/mingw_64/")

# Qt 6 Widgets
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
 
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
 
# Executable
add_executable(uge2 WIN32 mastermind.cpp)
 
# C++ standard
target_compile_features(uge2 PRIVATE cxx_std_17)
 
# Link Qt
target_link_libraries(uge2 PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)