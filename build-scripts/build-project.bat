cd ../
set working_dir=%cd%
set library_binaries=%working_dir%/library_binaries
set cmake="cmake"
set generator="-G Visual Studio 17 2022"
set test="-DTESTS=OFF"

CALL :InstallLibs ail-1.0.0 Release %library_binaries%
CALL :InstallLibs ail-1.0.0 Debug %library_binaries%/Debug
CALL :InstallProject Release %library_binaries%
CALL :InstallProject Debug %library_binaries%/Debug

pause 
EXIT /B %ERRORLEVEL%

:InstallProject
if not exist "build" mkdir build
cd build
%cmake% %generator% -A x64 -DCMAKE_BUILD_TYPE=%~1 -S ./../ -DCMAKE_PREFIX_PATH=%~2 %test%
%cmake% --build . --config %~1 --parallel
%cmake% --install %working_dir%/build --prefix %~2 --config %~1
cd ../
echo Project built successfully
EXIT /B 0

:InstallLibs
echo Installing %~1
cd external\%~1
if not exist "build" mkdir build
cd build
%cmake% %generator% -A x64 -DCMAKE_BUILD_TYPE=%~2 -S %working_dir%/external/%~1 -B %working_dir%/external/%~1/build -DCMAKE_PREFIX_PATH=%~3
%cmake% --build . --config %~2 --parallel
%cmake% --install . --prefix %~3 --config %~2 
cd ../../..
echo %~1 Installed
EXIT /B 0