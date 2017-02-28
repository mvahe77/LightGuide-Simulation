   ROOTLIBS      = $(shell root-config --glibs) 
   ROOTGLIBS     = -lGpad -lGui -lGX11 -lX3d 
   XLIB          = -L/usr/X11R6/lib
   CXX           = g++
   CFFLAGS       = -lgfortran
   CXXFLAGS      = -DLINUXVERS -DVISUALIZATION -g -Wall -I$(ROOTSYS)/include 


   LIBS = $(ROOTLIBS)  \
	$(XLIB) -lXt -lX11 -lXpm 

all :	pmt_pulse

clean:
	rm -f *.o pmt_pulse pmt_pulse.o core* core*~

OBJS =	pmt_pulse.o

SRC =	pmt_pulse.C 

HEAD =  

pmt_pulse	:	$(SRC) $(OBJS)
	rm -f $@
	$(CXX) $(FCFLAGS) -o pmt_pulse $(OBJS) $(LIBS) $(CFFLAGS)

pmt_pulse.o:	pmt_pulse.C $(HEAD)
	$(CXX) -c $(CXXFLAGS) pmt_pulse.C
