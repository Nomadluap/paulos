
# output directory for objects. 
SRCDIR=src
OBJDIR=obj
DEPDIR=dep

# output file name
BINFILE=paulos.bin

# Target bootable ISO file
ISOFILE=paulos.iso
GRUBIMAGE_DIR=grub_image

# tool prefix
TARGET=i686-elf-

# compile comands
CC=$(TARGET)gcc
CPP=$(TARGET)g++
AS=$(TARGET)as

CFLAGS=-ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
LDFLAGS=-T linker.ld -ffreestanding -O2 -nostdlib -lgcc

# source files
CPPSOURCES=$(wildcard src/*.cpp)
ASSOURCES=$(wildcard src/*.s)

# resultant object files
CPPOBJS=$(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(CPPSOURCES:.cpp=.cpp.o))
ASOBJS=$(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(ASSOURCES:.s=.s.o))

# one dependency file for each cpp file
DEPFILES=$(CPPOBJS:%.o=%.d)


# $@ is the file left-of the :, $^ is the file to the right
# $< denotes first file match

# rule to build ISO file for testing in virtualbox
$(ISOFILE): $(BINFILE)
	cp $(BINFILE) $(GRUBIMAGE_DIR)
	mkisofs -quiet -R \
	    -b boot/grub/i386-pc/eltorito.img \
	    --no-emul-boot -boot-load-size 4 \
	    -boot-info-table -o $(ISOFILE) $(GRUBIMAGE_DIR) \

# rule to generate final output file. 
#

$(BINFILE): $(CPPOBJS) $(ASOBJS)
	$(CC) -o $@ $(LDFLAGS) $^

-include $(DEPFILES)

# Rule for all cpp files. The -MMD file will create a dependency
# file alongside the object file that lists all headers that the 
# cpp file requires. 
$(OBJDIR)/%.cpp.o: $(SRCDIR)/%.cpp
	$(CPP) -c $(CFLAGS) -o $@ -MMD $< 

$(OBJDIR)/%.s.o: $(SRCDIR)/%.s
	$(AS) -o $@ $^



.PHONY: clean
clean:
	rm -f $(CPPOBJS)
	rm -f $(DEPFILES)
	rm -f $(ASOBJS)
	rm -f $(BINFILE)
	rm -f $(ISOFILE)
	rm -f $(GRUBIMAGE_DIR)/$(ISOFILE)

