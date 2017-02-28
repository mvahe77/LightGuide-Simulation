# $Id: GNUmakefile,v 1.1 1999/01/07 16:05:42 gunter Exp $
# --------------------------------------------------------------
# GNUmakefile for examples module.  Gabriele Cosmo, 06/04/98.
# --------------------------------------------------------------

LBITS := $(shell getconf LONG_BIT)
ifeq ($(LBITS),64)
name := lg_3piece_withlip_cylinder
else 
name := lg_3piece_withlip_cylinder
endif


G4TARGET := $(name)
G4EXLIB := true

ifndef G4INSTALL
  G4INSTALL = ../../..
endif

.PHONY: all
all: lib bin

include $(G4INSTALL)/config/binmake.gmk

ifdef ROOTSYS
ifdef G4UI_USE_ROOT
CPPFLAGS += $(shell $(ROOTSYS)/bin/root-config --cflags)
CPPFLAGS += -ggdb

ROOTLIBS = $(shell $(ROOTSYS)/bin/root-config --libs) -lMinuit -lHtml
ROOTLIBS := $(filter-out -lNew,$(ROOTLIBS))
ROOTLIBS := $(filter-out -lpthread,$(ROOTLIBS))
LDLIBS += $(ROOTLIBS)
LDLIBS += $(MPICHLIBS)

endif
endif
