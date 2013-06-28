SRC_PATH=./object
DRIVER_PATH=./python

CXX=g++
CXXFLAGS=-Wall
CPPFLAGS=-I./include

main : dictobject.o intobject.o stringobject.o typeobject.o driver.o
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o :  
	$(CXX) -c $(CPPFLAGS) $(SRC_PATH)/$(subst .o,.C,$@)

driver.o : 
	$(CXX) -c $(CPPFLAGS) $(DRIVER_PATH)/driver.C

.PHONY:
	clean

clean:
	-rm main *.o
