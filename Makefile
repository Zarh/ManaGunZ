#---------------------------------------------------------------------------------
# Clear the implicit built in rules
#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------
ifeq ($(strip $(PSL1GHT)),)
$(error "Please set PSL1GHT in your environment. export PSL1GHT=<path>")
endif

include $(PSL1GHT)/ppu_rules


#---------------------------------------------------------------------------------
# ManaGunZ : "make pkg"
# ManaGunZ for rpcs3 : "RPCS3=1 make pkg"
# FileManger : "FILEMANAGER=1 make pkg"
# FileManager for rpcs3 : "FILEMANAGER=1 RPCS3=1 make pkg"
# 
# Note : RPCS3 doesn't support "opendir" on system root : "/"
#---------------------------------------------------------------------------------

#---------------------------------------------------------------------------------
# TARGET is the name of the output
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# INCLUDES is a list of directories containing extra header files
#---------------------------------------------------------------------------------

BUILD		:=	build
SOURCES		:=	source
DATA		:=	data
INCLUDES	:=	include
PKGFILES1	:=	$(CURDIR)/pkgfiles
PKGFILES2	:=	$(CURDIR)/pkgfiles2
SFOXML		:=	sfo.xml

VERSION		:=  1.37

ifeq ($(FILEMANAGER), 1)
PKGFILES	:=	$(PKGFILES2)
MACHDEP		+= -DFILEMANAGER
TARGET		:=	FileManager
TITLE		:=	File Manager v$(VERSION)
APPID		:=	FILEMANAG
else
PKGFILES	:=	$(PKGFILES1)
TARGET		:=	ManaGunZ
TITLE		:=	$(TARGET) v$(VERSION)
APPID		:=	MANAGUNZ0
endif
CONTENTID	:=	EP0001-$(APPID)_00-0000000000000000

SCETOOL_FLAGS	+=	--self-ctrl-flags 4000000000000000000000000000000000000000000000000000000000000002
SCETOOL_FLAGS	+=	--self-cap-flags 00000000000000000000000000000000000000000000007B0000000100000000

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------

CFLAGS		=	-O2 -Wall -mcpu=cell $(MACHDEP) $(INCLUDE)
CXXFLAGS	=	$(CFLAGS)

LDFLAGS		=	$(MACHDEP) -Wl,-Map,$(notdir $@).map

#---------------------------------------------------------------------------------
# any extra libraries we wish to link with the project
#---------------------------------------------------------------------------------
LIBS	:= 

#---------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level containing
# include and lib
#---------------------------------------------------------------------------------
LIBDIRS	:= $(PORTLIBS)

#---------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# rules for different file extensions
#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------

export OUTPUT	:=	$(CURDIR)/$(TARGET)_v$(VERSION)

export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
					$(foreach dir,$(DATA),$(CURDIR)/$(dir))

export DEPSDIR	:=	$(CURDIR)/$(BUILD)

export BUILDDIR	:=	$(CURDIR)/$(BUILD)

#---------------------------------------------------------------------------------
# automatically build a list of object files for our project
#---------------------------------------------------------------------------------
CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
sFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.S)))
BINFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.bin)))
PNGFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.png)))
JPGFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.jpg)))
TTFFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.ttf)))
VCGFILES	:=	$(foreach dir,$(SHADERS),$(notdir $(wildcard $(dir)/*.vcg)))
FCGFILES	:=	$(foreach dir,$(SHADERS),$(notdir $(wildcard $(dir)/*.fcg)))

#---------------------------------------------------------------------------------
# use CXX for linking C++ projects, CC for standard C
#---------------------------------------------------------------------------------
ifeq ($(strip $(CPPFILES)),)
	export LD	:=	$(CC)
else
	export LD	:=	$(CXX)
endif

export OFILES	:=	$(addsuffix .o,$(BINFILES)) \
			$(addsuffix .o,$(TTFFILES)) \
			$(addsuffix .o,$(VPOFILES)) \
			$(addsuffix .o,$(FPOFILES)) \
			$(addsuffix .o,$(PNGFILES)) \
			$(addsuffix .o,$(JPGFILES)) \
					$(CPPFILES:.cpp=.o) $(CFILES:.c=.o) \
					$(sFILES:.s=.o) $(SFILES:.S=.o)

#---------------------------------------------------------------------------------
# build a list of include paths
#---------------------------------------------------------------------------------
export INCLUDE	:=	-I$(PORTLIBS)/include/freetype2 \
			$(foreach dir,$(INCLUDES), -I$(CURDIR)/$(dir)) \
					$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
					$(LIBPSL1GHT_INC) \
					-I$(CURDIR)/$(BUILD)

#---------------------------------------------------------------------------------
# build a list of library paths
#---------------------------------------------------------------------------------
export LIBPATHS	:=	$(foreach dir,$(LIBDIRS),-L$(dir)/lib) \
					$(LIBPSL1GHT_LIB)

export OUTPUT	:=	$(CURDIR)/$(TARGET)_v$(VERSION)
.PHONY: $(BUILD) clean

#---------------------------------------------------------------------------------
$(BUILD):
	@$(MAKE) small_clean --no-print-directory
	@$(MAKE) -C MGZ --no-print-directory
	@cp -f MGZ/MGZ.self $(PKGFILES)/USRDIR/$(TARGET).self
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile
ifeq ($(FILEMANAGER), 1)
	@cp -fr $(PKGFILES1)/USRDIR/GUI/common $(PKGFILES2)/USRDIR/GUI
	@cp -fr $(PKGFILES1)/USRDIR/GUI/colorset.ini $(PKGFILES2)/USRDIR/GUI
	@cp -fr $(PKGFILES1)/USRDIR/sys/data $(PKGFILES2)/USRDIR/sys
	@cp -fr $(PKGFILES1)/USRDIR/sys/loc $(PKGFILES2)/USRDIR/sys
	@cp -fr $(PKGFILES1)/USRDIR/sys/RCO $(PKGFILES2)/USRDIR/sys
	@cp -fr $(PKGFILES1)/USRDIR/sys/Check.zip $(PKGFILES2)/USRDIR/sys
	@cp -fr $(PKGFILES1)/USRDIR/sys/sprx_iso $(PKGFILES2)/USRDIR/sys
	@cp -fr $(PKGFILES1)/USRDIR/sys/PSP_CRC.txt $(PKGFILES2)/USRDIR/sys
endif
	
#---------------------------------------------------------------------------------
# To compile filemanager and managunz without recompiling everything,
# it'll recompile files where the "FILEMANAGER" and "RPCS3" are used
#---------------------------------------------------------------------------------

small_clean:
	@rm -fr $(BUILD) *.elf *.self *.pkg
	@rm -fr MGZ/build/main.o

#---------------------------------------------------------------------------------
clean:
	@echo clean ...
	@rm -fr $(BUILD) *.elf *.self *.pkg
	@$(MAKE) clean -C MGZ --no-print-directory
	@$(MAKE) clean -C MGZ/lib/cobra --no-print-directory
	@$(MAKE) clean -C MGZ/lib/ImageMagick --no-print-directory
	@$(MAKE) clean -C MGZ/lib/libapputil --no-print-directory
	@$(MAKE) clean -C MGZ/lib/libgtfconv --no-print-directory
	@$(MAKE) clean -C MGZ/lib/libiconv --no-print-directory
	@$(MAKE) clean -C MGZ/lib/libntfs_ext --no-print-directory
	@$(MAKE) clean -C payloads/MAMBA --no-print-directory
	@$(MAKE) clean -C payloads/PS2_EMU --no-print-directory
	@$(MAKE) clean -C payloads/rawseciso --no-print-directory
	@rm -fr $(PKGFILES1)/USRDIR/$(TARGET).self
	@rm -fr $(PKGFILES2)/USRDIR
	
#---------------------------------------------------------------------------------
update:
	cd OffsetFinder; ./OffsetFinder.exe	search
	cd OffsetFinder; ./OffsetFinder.exe	move
	@$(MAKE) -C payloads/SKY --no-print-directory
	@$(MAKE) clean -C payloads/MAMBA --no-print-directory
	@$(MAKE) all -C payloads/MAMBA --no-print-directory
	@$(MAKE) loader -C payloads/MAMBA --no-print-directory
	@mv -f payloads/MAMBA/mamba_*.lz.bin  MGZ/data
	@mv -f payloads/MAMBA/mamba_loader_*.bin  MGZ/data
	@$(MAKE) all -C payloads/PS2_EMU --no-print-directory
	@mv -f payloads/PS2_EMU/BIN/*.bin  MGZ/data
	@$(MAKE) -C payloads/rawseciso --no-print-directory
	@mv -f payloads/rawseciso/rawseciso.sprx $(PKGFILES)/USRDIR/sys/sprx_iso
	@$(MAKE) -C payloads/erk_dumper/spu --no-print-directory
	@$(MAKE) -C payloads/erk_dumper/source --no-print-directory
	@mv -f payloads/erk_dumper/bin/*.bin  MGZ/data
	
#---------------------------------------------------------------------------------
lib:
	$(MAKE) -C MGZ/lib/cobra --no-print-directory
	@mv -f MGZ/lib/cobra/libcobra.a MGZ/lib/libcobra.a
	$(MAKE) -C MGZ/lib/libntfs_ext --no-print-directory
	@mv -f MGZ/lib/libntfs_ext/libntfs_ext.a MGZ/lib/libntfs_ext.a
	$(MAKE) -C MGZ/lib/OpenSSL --no-print-directory
	@mv -f MGZ/lib/OpenSSL/libcrypto.a MGZ/lib/libcrypto.a
	@mv -f MGZ/lib/OpenSSL/libssl.a MGZ/lib/libssl.a
#---------------------------------------------------------------------------------
run:
	ps3load $(OUTPUT).self

#---------------------------------------------------------------------------------
pkg: $(BUILD) $(OUTPUT).pkg

#---------------------------------------------------------------------------------
else

DEPENDS	:=	$(OFILES:.o=.d)

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------
$(OUTPUT).self: $(OUTPUT).elf
$(OUTPUT).elf:	$(OFILES)

#---------------------------------------------------------------------------------
# This rule links in binary data with the .bin extension
#---------------------------------------------------------------------------------
%.bin.o	:	%.bin
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

#---------------------------------------------------------------------------------
%.ttf.o	:	%.ttf
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

#---------------------------------------------------------------------------------
%.vpo.o	:	%.vpo
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

#---------------------------------------------------------------------------------
%.fpo.o	:	%.fpo
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

#---------------------------------------------------------------------------------
%.jpg.o	:	%.jpg
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)
#---------------------------------------------------------------------------------
%.png.o	:	%.png
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

-include $(DEPENDS)

#---------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------
