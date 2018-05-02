@echo off
for /L %%i in (0, 1, 127) do (@echo #ifdef GPIO%%i_CONFIG >> Build\GPIO.h
@echo { GPIO%%i_CONFIG }, >> Build\GPIO.h
@echo #endif >> Build\GPIO.h)

