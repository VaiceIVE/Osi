@echo Hello from LR_10!
set VAR=%cd%
set /p name=Enter new name for catalog :
mkdir %name%
set path=%VAR%\%name%
@echo %path%
copy *.txt %path%

@pause

