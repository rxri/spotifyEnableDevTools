cmake_minimum_required(VERSION 3.9)
project(spotifyEnableDevTools)

set(CMAKE_CXX_FLAGS "-fpermissive")
set(CMAKE_CXX_FLAGS_RELEASE "-O1 -O2")
set(APP_ICON_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/appIcon.rc")

file(GLOB SOURCES "*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES} ${APP_ICON_WINDOWS})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_link_options(${PROJECT_NAME} PRIVATE -static-libgcc -static-libstdc++ -static)