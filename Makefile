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
# TARGET is the name of the output
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# INCLUDES is a list of directories containing extra header files
#---------------------------------------------------------------------------------
TARGET		:=	ManaGunZ
BUILD		:=	build
SOURCES		:=	source
DATA		:=	data
INCLUDES	:=	include
PKGFILES	:=	$(CURDIR)/pkgfiles
SFOXML		:=	sfo.xml

VERSION		:=  1.26

TITLE		:=	$(TARGET) v$(VERSION)
APPID		:=	MANAGUNZ0
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
	@$(MAKE) -C MGZ --no-print-directory
	@cp -f MGZ/MGZ.self pkgfiles/USRDIR/$(TARGET).self
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile
	
#---------------------------------------------------------------------------------
clean:
	@echo clean ...
	@rm -fr $(BUILD) *.elf *.self *.pkg
	@$(MAKE) clean -C MGZ --no-print-directory
	@$(MAKE) clean -C MGZ/lib/cobralib --no-print-directory
	@$(MAKE) clean -C MGZ/lib/ImageMagick --no-print-directory
	@$(MAKE) clean -C MGZ/lib/libapputil --no-print-directory
	@$(MAKE) clean -C MGZ/lib/libgtfconv --no-print-directory
	@$(MAKE) clean -C MGZ/lib/libiconv --no-print-directory
	@$(MAKE) clean -C MGZ/lib/libntfs_ext --no-print-directory
	@$(MAKE) clean -C payloads/MAMBA --no-print-directory
	@$(MAKE) clean -C payloads/MAMBA_LOADER --no-print-directory
	
#---------------------------------------------------------------------------------
payload:
	cd OffsetFinder; ./OffsetFinder.exe	
	@cp -f OffsetFinder/firmware_symbols.h payloads/SKY/firmware_symbols.h;
	@cp -f OffsetFinder/common.h MGZ/source/common.h
	@$(MAKE) -C payloads/SKY --no-print-directory
	@$(MAKE) all -C payloads/MAMBA --no-print-directory
	@$(MAKE) all -C payloads/MAMBA_LOADER --no-print-directory
	mv payloads/MAMBA/mamba_4_21DEX.lz.bin  MGZ/data/mamba_421D.lz.bin
	mv payloads/MAMBA/mamba_4_21.lz.bin  MGZ/data/mamba_421C.lz.bin
	mv payloads/MAMBA/mamba_4_30DEX.lz.bin  MGZ/data/mamba_430D.lz.bin
	mv payloads/MAMBA/mamba_4_30.lz.bin  MGZ/data/mamba_430C.lz.bin
	mv payloads/MAMBA/mamba_4_31.lz.bin  MGZ/data/mamba_431C.lz.bin
	mv payloads/MAMBA/mamba_4_40.lz.bin  MGZ/data/mamba_440C.lz.bin
	mv payloads/MAMBA/mamba_4_41DEX.lz.bin  MGZ/data/mamba_441D.lz.bin
	mv payloads/MAMBA/mamba_4_41.lz.bin  MGZ/data/mamba_441C.lz.bin
	mv payloads/MAMBA/mamba_4_46DEX.lz.bin  MGZ/data/mamba_446D.lz.bin
	mv payloads/MAMBA/mamba_4_46.lz.bin  MGZ/data/mamba_446C.lz.bin
	mv payloads/MAMBA/mamba_4_50DEX.lz.bin  MGZ/data/mamba_450D.lz.bin
	mv payloads/MAMBA/mamba_4_50.lz.bin  MGZ/data/mamba_450C.lz.bin
	mv payloads/MAMBA/mamba_4_53DEX.lz.bin  MGZ/data/mamba_453D.lz.bin
	mv payloads/MAMBA/mamba_4_53.lz.bin  MGZ/data/mamba_453C.lz.bin
	mv payloads/MAMBA/mamba_4_55DEX.lz.bin  MGZ/data/mamba_455D.lz.bin
	mv payloads/MAMBA/mamba_4_55.lz.bin  MGZ/data/mamba_455C.lz.bin
	mv payloads/MAMBA/mamba_4_60DEX.lz.bin  MGZ/data/mamba_460D.lz.bin
	mv payloads/MAMBA/mamba_4_60.lz.bin  MGZ/data/mamba_460C.lz.bin
	mv payloads/MAMBA/mamba_4_65DEX.lz.bin  MGZ/data/mamba_465D.lz.bin
	mv payloads/MAMBA/mamba_4_65.lz.bin  MGZ/data/mamba_465C.lz.bin
	mv payloads/MAMBA/mamba_4_66DEX.lz.bin  MGZ/data/mamba_466D.lz.bin
	mv payloads/MAMBA/mamba_4_66.lz.bin  MGZ/data/mamba_466C.lz.bin
	mv payloads/MAMBA/mamba_4_70DEX.lz.bin  MGZ/data/mamba_470D.lz.bin
	mv payloads/MAMBA/mamba_4_70.lz.bin  MGZ/data/mamba_470C.lz.bin
	mv payloads/MAMBA/mamba_4_75DEX.lz.bin  MGZ/data/mamba_475D.lz.bin
	mv payloads/MAMBA/mamba_4_75.lz.bin  MGZ/data/mamba_475C.lz.bin
	mv payloads/MAMBA/mamba_4_80.lz.bin  MGZ/data/mamba_480C.lz.bin
	mv payloads/MAMBA/mamba_4_80DEX.lz.bin  MGZ/data/mamba_480D.lz.bin
	mv payloads/MAMBA_LOADER/payload_4_21DEX.bin  MGZ/data/mamba_loader_421D.bin
	mv payloads/MAMBA_LOADER/payload_4_21.bin  MGZ/data/mamba_loader_421C.bin
	mv payloads/MAMBA_LOADER/payload_4_30DEX.bin  MGZ/data/mamba_loader_430D.bin
	mv payloads/MAMBA_LOADER/payload_4_30.bin  MGZ/data/mamba_loader_430C.bin
	mv payloads/MAMBA_LOADER/payload_4_31.bin  MGZ/data/mamba_loader_431C.bin
	mv payloads/MAMBA_LOADER/payload_4_40.bin  MGZ/data/mamba_loader_440C.bin
	mv payloads/MAMBA_LOADER/payload_4_41DEX.bin  MGZ/data/mamba_loader_441D.bin
	mv payloads/MAMBA_LOADER/payload_4_41.bin  MGZ/data/mamba_loader_441C.bin
	mv payloads/MAMBA_LOADER/payload_4_46DEX.bin  MGZ/data/mamba_loader_446D.bin
	mv payloads/MAMBA_LOADER/payload_4_46.bin  MGZ/data/mamba_loader_446C.bin
	mv payloads/MAMBA_LOADER/payload_4_50DEX.bin  MGZ/data/mamba_loader_450D.bin
	mv payloads/MAMBA_LOADER/payload_4_50.bin  MGZ/data/mamba_loader_450C.bin
	mv payloads/MAMBA_LOADER/payload_4_53DEX.bin  MGZ/data/mamba_loader_453D.bin
	mv payloads/MAMBA_LOADER/payload_4_53.bin  MGZ/data/mamba_loader_453C.bin
	mv payloads/MAMBA_LOADER/payload_4_55DEX.bin  MGZ/data/mamba_loader_455D.bin
	mv payloads/MAMBA_LOADER/payload_4_55.bin  MGZ/data/mamba_loader_455C.bin
	mv payloads/MAMBA_LOADER/payload_4_60DEX.bin  MGZ/data/mamba_loader_460D.bin
	mv payloads/MAMBA_LOADER/payload_4_60.bin  MGZ/data/mamba_loader_460C.bin
	mv payloads/MAMBA_LOADER/payload_4_65DEX.bin  MGZ/data/mamba_loader_465D.bin
	mv payloads/MAMBA_LOADER/payload_4_65.bin  MGZ/data/mamba_loader_465C.bin
	mv payloads/MAMBA_LOADER/payload_4_66DEX.bin  MGZ/data/mamba_loader_466D.bin
	mv payloads/MAMBA_LOADER/payload_4_66.bin  MGZ/data/mamba_loader_466C.bin
	mv payloads/MAMBA_LOADER/payload_4_70DEX.bin  MGZ/data/mamba_loader_470D.bin
	mv payloads/MAMBA_LOADER/payload_4_70.bin  MGZ/data/mamba_loader_470C.bin
	mv payloads/MAMBA_LOADER/payload_4_75DEX.bin  MGZ/data/mamba_loader_475D.bin
	mv payloads/MAMBA_LOADER/payload_4_75.bin  MGZ/data/mamba_loader_475C.bin
	mv payloads/MAMBA_LOADER/payload_4_80.bin  MGZ/data/mamba_loader_480C.bin
	mv payloads/MAMBA_LOADER/payload_4_80DEX.bin  MGZ/data/mamba_loader_480D.bin
	
#---------------------------------------------------------------------------------
sprx_iso:
	$(MAKE) -C payloads/rawseciso --no-print-directory
	@cp -f payloads/rawseciso/rawseciso.sprx pkgfiles/USRDIR/sys/sprx_iso
#---------------------------------------------------------------------------------
lib:
	$(MAKE) -C MGZ/lib/cobra --no-print-directory
	@mv -f MGZ/lib/cobra/libcobra.a MGZ/lib/libcobra.a
	$(MAKE) -C MGZ/lib/libntfs_ext --no-print-directory
	@mv -f MGZ/lib/libntfs_ext/libntfs_ext.a MGZ/lib/libntfs_ext.a
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
