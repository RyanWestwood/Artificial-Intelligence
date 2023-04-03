cd ../
set working_dir=%cd%
set library_binaries=%working_dir%/library_binaries
set cmake="cmake"
set generator="-G Ninja"

if not exist "library_binaries" mkdir library_binaries

CALL :InstallAll Release %library_binaries%
CALL :InstallAll Debug %library_binaries%/Debug
CALL :InstallProject Release %library_binaries%
CALL :InstallProject Debug %library_binaries%/Debug

pause 
EXIT /B %ERRORLEVEL%

:InstallAll
CALL :InstallLibs sdl-2.24.2 %~1 %~2
CALL :InstallLibs sdl-image-2.6.2 %~1 %~2
CALL :InstallLibs sdl-mixer-2.6.2 %~1 %~2
CALL :InstallLibs sdl-ttf-2.20.1 %~1 %~2
CALL :InstallLibs ai-library %~1 %~2
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

:InstallProject
if not exist "build" mkdir build
cd build
%cmake% %generator% -A x64 -DCMAKE_BUILD_TYPE=%~1 -S ./../ -DCMAKE_PREFIX_PATH=%~2
%cmake% --build . --config %~1 --parallel
%cmake% --install %working_dir%/build --prefix %~2 --config %~1
cd ../
echo Project built successfully
EXIT /B 0