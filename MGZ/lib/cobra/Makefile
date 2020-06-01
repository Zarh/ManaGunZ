#---------------------------------------------------------------------------------
# Clear the implicit built in rules
#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------

ifeq ($(strip $(PSL1GHT)),)
$(error "Please set PSL1GHT in your environment. export PSL1GHT=<path>")
endif

include	$(PSL1GHT)/ppu_rules



#---------------------------------------------------------------------------------
ifeq ($(strip $(PLATFORM)),)
#---------------------------------------------------------------------------------
export BASEDIR		:= $(CURDIR)
export DEPS			:= $(BASEDIR)/deps
export LIBS			:=	$(BASEDIR)/lib

#---------------------------------------------------------------------------------
else
#---------------------------------------------------------------------------------

export LIBDIR		:= $(LIBS)/$(PLATFORM)
export DEPSDIR		:=	$(DEPS)/$(PLATFORM)

#---------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------

TARGET		:=	libcobra
BUILD		:=	build
SOURCE		:=	source 
INCLUDE		:=	include
DATA		:=	data
LIBS		:=	

MACHDEP		:= -DBIGENDIAN 
CFLAGS		+= -O2 -Wall -std=gnu99 -Wno-char-subscripts -mcpu=cell $(MACHDEP) -fno-strict-aliasing $(INCLUDES) 
LD			:=	ppu-ld

ifneq ($(BUILD),$(notdir $(CURDIR)))

export OUTPUT	:=	$(CURDIR)/$(TARGET)
export VPATH	:=	$(foreach dir,$(SOURCE),$(CURDIR)/$(dir)) \
					$(foreach dir,$(DATA),$(CURDIR)/$(dir))
export BUILDDIR	:=	$(CURDIR)/$(BUILD)
export DEPSDIR	:=	$(BUILDDIR)

CFILES		:= $(foreach dir,$(SOURCE),$(notdir $(wildcard $(dir)/*.c)))
CXXFILES	:= $(foreach dir,$(SOURCE),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES		:= $(foreach dir,$(SOURCE),$(notdir $(wildcard $(dir)/*.S)))
BINFILES	:= $(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.bin)))
VCGFILES	:= $(foreach dir,$(SOURCE),$(notdir $(wildcard $(dir)/*.vcg)))
VSAFILES	:= $(foreach dir,$(SOURCE),$(notdir $(wildcard $(dir)/*.vsa)))


export OFILES	:=	$(CFILES:.c=.o) \
					$(CXXFILES:.cpp=.o) \
					$(SFILES:.S=.o) \
					$(BINFILES:.bin=.bin.o) \
					$(VCGFILES:.vcg=.vcg.o) \
					$(VSAFILES:.vsa=.vsa.o)

export BINFILES	:=	$(BINFILES:.bin=.bin.h)
export VCGFILES	:=	$(VCGFILES:.vcg=.vcg.h)
export VSAFILES	:=	$(VSAFILES:.vsa=.vsa.h)

export INCLUDES	=	$(foreach dir,$(INCLUDE),-I$(CURDIR)/$(dir)) \
					-I$(CURDIR)/$(BUILD) -I$(PSL1GHT)/ppu/include -I$(PORTLIBS)/include

.PHONY: $(BUILD) install clean shader

$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@make --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

shader:
	@echo "[VPCOMP] $(notdir $<)"
	@vpcomp shader/vshader_text_normal.vcg shader/vshader_text_normal.rvp
	@raw2h.exe  shader/vshader_text_normal.rvp source/vshader_text_normal.vcg.h source/vshader_text_normal.vcg.S vshader_text_normal_bin
install: $(BUILD)
	@echo Copying...
	@cp include/*.h $(PORTLIBS)/include
	@cp *.a $(PORTLIBS)/lib
	@echo Done!

clean:
	@echo Clean...
	@rm -rf $(BUILD) $(OUTPUT).elf $(OUTPUT).self $(OUTPUT).a

else

DEPENDS	:= $(OFILES:.o=.d)

$(OUTPUT).a: $(OFILES)
$(OFILES): $(BINFILES) $(VCGFILES) $(VSAFILES)

-include $(DEPENDS)

endif
