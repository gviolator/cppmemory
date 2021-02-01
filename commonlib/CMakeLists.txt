cmake_minimum_required(VERSION 3.17)

set(TargetName commonlib)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

file (GLOB_RECURSE Sources "*.cpp" "*.h")
# auto_group_files("${Sources}" "test_runtime")

add_library(${TargetName} STATIC ${Sources})

target_include_directories(${TargetName}
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
)


target_precompile_headers(${TargetName} PRIVATE pch.h)
