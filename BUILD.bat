mkdir build
cd build
cmake ..  -DCMAKE_BUILD_TYPE=Release
cmake --build . -j --config Release
cmake ..  -DCMAKE_BUILD_TYPE=Debug
cmake --build . -j --config Debug
pause