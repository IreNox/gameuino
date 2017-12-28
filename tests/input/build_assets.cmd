@echo off

..\..\bin\asset_builder.exe ..\..\assets\input_test .

IF NOT ERRORLEVEL 1 GOTO end

pause

:end