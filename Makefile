# Makefile
#vpath %.h /home/xunzhang/桌面/SPython/include

CXX = g++
CXXFLAGS = -Wall
CPPFLAGS = -I./include

objects = dictobject.o intobject.o stringobject.o typeobject.o

main : driver.o $(objects)
	$(CXX) -o main driver.o $(objects)

driver.o : 
	$(CXX) -c $(CPPFLAGS) ./python/driver.C

dictobject.o : 
	$(CXX) -c $(CPPFLAGS) ./object/dictobject.C

intobject.o : 
	$(CXX) -c $(CPPFLAGS) ./object/intobject.C

stringobject.o : 
	$(CXX) -c $(CPPFLAGS) ./object/stringobject.C

typeobject.o : 
	$(CXX) -c $(CPPFLAGS) ./object/typeobject.C

.PHONY:
	clean

clean : 
	-rm main driver.o $(objects) 
