cmake_minimum_required(VERSION 3.17)

set(TargetName runtimestack)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

file (GLOB_RECURSE Sources "*.cpp" "*.h")

add_executable(${TargetName} ${Sources})

target_link_libraries(${TargetName}
	PRIVATE
		commonlib
		Rpcrt4.lib
		Ws2_32.lib
		Iphlpapi.lib
)

target_precompile_headers(${TargetName} PRIVATE pch.h)
