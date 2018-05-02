include C:/1218_Alibaba/Build/GRANTLEY/RELEASE_MYTOOLS/IfrList.mak
.PHONY : all
all : 
	C:/1218_Alibaba/AmiTsePkg\Core\em\AMITSE/UefiHpkTool.exe $(IFR_DIR_LIST) -fC:/1218_Alibaba/AmiTsePkg\Core\em\AMITSE/Uefisetup.ini -doC:/1218_Alibaba/Build/GRANTLEY/Defaults.bin -oC:/1218_Alibaba\Build/tmp.asm -r -dn0 -de1 -vs0x20028 -dlen-US -dp0 -dg4599D26F-1A11-49b8-B91F-858745CFF824 -h -RT 
	C:/1218_Alibaba/AmiTsePkg\Core\em\AMITSE/UefiHpkTool.exe $(IFR_DIR_LIST) -fC:/1218_Alibaba/AmiTsePkg\Core\em\AMITSE/Uefisetup.ini -doC:/1218_Alibaba/Build/GRANTLEY/Nvram.bin -oC:/1218_Alibaba\Build/setupdata_asm.asm -dlen-US -dp0 -ds262048 -dn0 -de1 -vs0x20028 -h -RT 
	ml /c /nologo /FoC:/1218_Alibaba\Build/ C:/1218_Alibaba\Build/setupdata_asm.asm 
	"C:/WinDDK_7600.16385.1/WinDDk/WinDDK/7600.16385.1/bin/x86/x86/link" /NOENTRY /FIXED /DLL C:/1218_Alibaba\Build/setupdata_asm.obj /OUT:C:/1218_Alibaba\Build/setupdata.dll 
	genfw --exe2bin C:/1218_Alibaba\Build/setupdata.dll -o C:/1218_Alibaba\Build/setupdata.bin
