cd ../
set working_dir=%cd%
set library_binaries=%working_dir%/library_binaries
set generator="-G Visual Studio 17 2022"

CALL :InstallProject Release %library_binaries%
CALL :InstallProject Debug %library_binaries%/Debug

pause 
EXIT /B %ERRORLEVEL%

:InstallProject
if not exist "build" mkdir build
cd build
cmake %generator% -A x64 -DCMAKE_BUILD_TYPE=%~1 -S ./../ -DCMAKE_PREFIX_PATH=%~2 -D MY_VARIABLE=%~1
cmake --build . --config %~1 --parallel
cmake --install %working_dir%/build --prefix %~2 --config %~1
cd ../
echo Project built successfully
EXIT /B 0