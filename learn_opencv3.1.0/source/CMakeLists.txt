cmake_minimum_required(VERSION 3.10)

project(opencv_demo)

add_definitions(-std=c++11)

include(tools/helper.cmake)

# include_directories(/usr/local/include)
# link_directories(/usr/lib)

set(ENV{PKG_CONFIG_PATH} /usr/local/lib/pkgconfig)

message(STATUS "[pkg_config] PKG_CONFIG_PATH: $ENV{PKG_CONFIG_PATH}")

find_package(PkgConfig)#必须安装pkg-config可执行程序
message(STATUS "[pkg_config] PKG_CONFIG_EXECUTABLE: ${PKG_CONFIG_EXECUTABLE}")

pkg_search_module(CV REQUIRED opencv)

message(STATUS "[opencv] FOUND: ${CV_FOUND}")        
message(STATUS "[opencv] LIBRARYIES: ${CV_LIBRARIES}")    
message(STATUS "[opencv] LIBARY_DIRS: ${CV_LIBRARY_DIRS}") 
message(STATUS "[opencv] LDFLAGS: ${CV_LDFLAGS}")      
message(STATUS "[opencv] LDFLAGS_OTHER: ${CV_LDFLAGS_OTHER}")
message(STATUS "[opencv] INCLUDE_DIRS: ${CV_INCLUDE_DIRS}") 
message(STATUS "[opencv] CFLAGS: ${CV_CFLAGS}")       
message(STATUS "[opencv] CFLAGS_OTHER: ${CV_CFLAGS_OTHER}")

INCLUDE_DIRECTORIES(${CV_INCLUDE_DIRS})
LINK_DIRECTORIES(${CV_LIBARIES})

add_subdirectory(chapter)
# add_subdirectory(opencv_util)
# add_subdirectory(other)
