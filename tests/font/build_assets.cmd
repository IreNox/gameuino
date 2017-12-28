@echo off

..\..\bin\asset_builder.exe ..\..\assets\font_test .

IF NOT ERRORLEVEL 1 GOTO end

pause

:end