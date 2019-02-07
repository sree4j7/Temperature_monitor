DIR_GAURD= @mkdir -p $(@D)

OBJDIR=obj

DESTDIR=

TARGET=Binary

CXX = g++ -g -std=c++0x

CXXFLAGS=-c -Wall -Wextra -W -O0

LDFLAGS= -L/usr/lib \
     
INCLUDE=-I/usr/include 


LIBS=	-pthread

SOURCES=	./main.cpp ./acmonitor.cpp ./temperaturemonitor.cpp ./temperaturesensor.cpp ./maincontroller.cpp

OBJECTS:= $(SOURCES:%.cpp=$(OBJDIR)/%.o)

all: $(TARGET)

$(OBJDIR)/%.o: %.cpp 
	$(DIR_GAURD)
	$(CXX) $(LDFLAGS) $(CXXFLAGS) $(LIBS) $(INCLUDE) -c $? -o $@

$(TARGET): $(OBJECTS) 
	$(DIR_GAURD)
	$(CXX) $(INCLUDE) $(LDFLAGS) -o $@ $(OBJECTS) $(LIBS)

install: $(TARGET)
.PHONY: all clean install

clean:
	-rm -rf $(OBJDIR) $(TARGET) \
	rm final.txt 

