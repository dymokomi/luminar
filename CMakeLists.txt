cmake_minimum_required(VERSION 3.12)
project(luminar VERSION 0.1.0 LANGUAGES CXX DESCRIPTION "Luminar")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
include(GNUInstallDirs)

# Add wavelette as a subdirectory
add_subdirectory(external/wavelette)
if(WIN32)  
    set(CMAKE_PREFIX_PATH "C:/Qt/6.8.0/msvc2022_64/lib/cmake")
endif()
set(CMAKE_AUTOMOC ON)

find_package(Qt6 COMPONENTS Core Widgets OpenGLWidgets REQUIRED)

set(LUMINAR_SOURCES
    src/main.cpp
    src/viewer.cpp
    include/viewer.h
)

# Create executable target
add_executable(luminar ${LUMINAR_SOURCES})

# Set output directories
set_target_properties(luminar PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/Debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/Release"
)

target_include_directories(luminar 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/external/spdi/include
)

# Link against wavelette
target_link_libraries(luminar 
    PRIVATE 
        wavelette
        Qt6::Core
        Qt6::Widgets
        Qt6::OpenGLWidgets
)

# Installation rules
install(TARGETS luminar
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Create bin directory if it doesn't exist
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Add post-build commands to copy files
add_custom_command(TARGET luminar POST_BUILD
    # Copy the executable
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:luminar>
        ${CMAKE_SOURCE_DIR}/bin/

    # Copy spdi DLL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:wavelette>
        ${CMAKE_SOURCE_DIR}/bin/

    # Copy colorama DLL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:colorama>
        ${CMAKE_SOURCE_DIR}/bin/

    # Copy spacely DLL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:spacely>
        ${CMAKE_SOURCE_DIR}/bin/

    COMMENT "Copying executables and DLLs to bin directory"
)