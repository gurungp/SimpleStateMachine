
# Specify the minimum CMake version required
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)

# Project name and language (C++)
project(StateMachine VERSION 1.0 LANGUAGES CXX)

# Collect all .cpp and *.h source files in the current directory
file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/../*.cpp" "${CMAKE_SOURCE_DIR}/../*.h")


# Add an executable target
add_executable(StateMachineApp 
../main.cpp
../SSM.cpp
../Spell.cpp
../PlaySound.cpp

)


target_link_libraries(StateMachineApp
    "-framework CoreFoundation"
    "-framework AudioToolbox"
)
