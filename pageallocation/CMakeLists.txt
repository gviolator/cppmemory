cmake_minimum_required(VERSION 3.17)

set(TargetName pageallocation)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

file (GLOB_RECURSE Sources "*.cpp" "*.h")

add_executable(${TargetName} ${Sources})

target_link_libraries(${TargetName}
	PRIVATE
		commonlib
)

target_precompile_headers(${TargetName} PRIVATE pch.h)
