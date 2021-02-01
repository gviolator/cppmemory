call env_vc142x64.cmd
call env_cmake.cmd
cmake -G"Visual Studio 16 2019" -Ax64 -S .. -B ./.target/x64_Debug