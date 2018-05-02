include AmiPkg/Configuration/utilities.mak
.PHONY : all
all:

.PHONY : FontFile
all: FontFile
FontFile : 
	FontTool -F 2.1 -C C:/Aptio_5.x_TOOLS_29/Tools/Fontcfg.ini -IL drawing en-US -T C:/1218_Alibaba\Build/GRANTLEY/RELEASE_MYTOOLS/font.tmp
	FontTool -F 2.1 -C C:/Aptio_5.x_TOOLS_29/Tools/Fontcfg.ini -O C:/1218_Alibaba/Build/GRANTLEY/RELEASE_MYTOOLS/font.out -T C:/1218_Alibaba\Build/GRANTLEY/RELEASE_MYTOOLS/font.tmp

.PHONY : HpkTool
all: HpkTool
HpkTool :
	gawk -f C:/1218_Alibaba/Build/IfrListScript.txt C:/1218_Alibaba/Build/GRANTLEY/RELEASE_MYTOOLS/IfrDirList.txt> C:/1218_Alibaba/Build/GRANTLEY/RELEASE_MYTOOLS/IfrList.mak
	make --no-print-directory -s -C C:/1218_Alibaba/Build/GRANTLEY/RELEASE_MYTOOLS -f C:/1218_Alibaba/Build/AmiTseGenFds.mak
