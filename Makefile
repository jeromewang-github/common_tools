WORKROOT = .

GXX = g++
CXXFLAGS = -g -O2 -fPIC -Wall -pipe

INCLUDES = -I.

LDFLAGS = -L./

SRC = $(wildcard *.cpp main/*.cpp)
OBJS = $(SRC:%.cpp=%.o)

BASE64TOOL = ./main/base64tool

%.o : %.cpp
	$(GXX) $(CXXFLAGS) -c -o $@ $^ $(INCLUDES) $(LDFLAGS)

default : all
	mkdir -p output/bin
	cp -rf $(BASE64TOOL) output/bin

all : $(BASE64TOOL)

$(BASE64TOOL) : $(OBJS)
	$(GXX) $(CXXFLAGS) -o $@ $^ $(INCLUDES) $(LDFLAGS)

clean:
	rm -rf $(BASE64TOOL)
	rm -rf $(OBJS) *.~
	rm -rf *.o *.~
	rm -rf main/*.o main/*.~
	rm -rf output
