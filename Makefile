# Copyright 2018 ikhatri@umass.edu
# College of Information and Computer Sciences,
# University of Massachusetts Amherst
# Based on a guide by Scott McPeak
#
# This software is free: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License Version 3,
# as published by the Free Software Foundation.
#
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# Version 3 in the file COPYING that came with this distribution.
# If not, see <http://www.gnu.org/licenses/>.
# ========================================================================

# Reference http://scottmcpeak.com/autodepend/autodepend.html

#Compiler and Linker
CC          := clang++

#The Target Binary Program
TARGET      := reader

#The Directories, Source, Includes, Objects, Binary and Resources
SRCDIR      := ../ConfigurationReader
INCDIR      := config_types
BUILDDIR    := obj
TARGETDIR   := bin
# RESDIR      := res
SRCEXT      := cc
DEPEXT      := d
OBJEXT      := o

#Flags, Libraries and Includes
CFLAGS      := -std=c++11 -fsanitize=thread -g
LIB         := -llua -ldl -lpthread
INC         := -I$(INCDIR) -I/usr/local/include
INCDEP      := -I$(INCDIR)

#---------------------------------------------------------------------------------
#DO NOT EDIT BELOW THIS LINE
#---------------------------------------------------------------------------------
SOURCES     := $(shell find $(SRCDIR) -type f -name '*.$(SRCEXT)')
OBJECTS     := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))

#Defauilt Make
all: resources main $(TARGET)

print-%  : ; @echo $* = $($*)

main: main.cpp
	$(CC) $(CFLAGS) $(INC) -c -o obj/main.o ../ConfigurationReader/main.cpp

#Remake
remake: cleaner all

#Copy Resources from Resources Directory to Target Directory
resources: directories
	# @cp $(RESDIR)/* $(TARGETDIR)/

#Make the Directories
directories:
	@mkdir -p $(TARGETDIR)
	@mkdir -p $(BUILDDIR)

#Clean only Objecst
clean:
	@$(RM) -rf $(BUILDDIR)

#Full Clean, Objects and Binaries
cleaner: clean
	@$(RM) -rf $(TARGETDIR)

#Pull in dependency info for *existing* .o files
-include $(OBJECTS:.$(OBJEXT)=.$(DEPEXT))

#Link
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGETDIR)/$(TARGET) $^ obj/main.o $(LIB)

#Compile
$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<
	@$(CC) $(CFLAGS) $(INCDEP) -MM $(SRCDIR)/$*.$(SRCEXT) > $(BUILDDIR)/$*.$(DEPEXT)
	@cp -f $(BUILDDIR)/$*.$(DEPEXT) $(BUILDDIR)/$*.$(DEPEXT).tmp
	@sed -e 's|.*:|$(BUILDDIR)/$*.$(OBJEXT):|' < $(BUILDDIR)/$*.$(DEPEXT).tmp > $(BUILDDIR)/$*.$(DEPEXT)
	@sed -e 's/.*://' -e 's/\\$$//' < $(BUILDDIR)/$*.$(DEPEXT).tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILDDIR)/$*.$(DEPEXT)
	@rm -f $(BUILDDIR)/$*.$(DEPEXT).tmp

#Non-File Targets
.PHONY: all remake clean cleaner resources