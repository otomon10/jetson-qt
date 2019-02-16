SOURCES		= led.cpp
OBJS		= $(SOURCES:.cpp=.o)
TARGET		= libled.so

CXX		= /home/ubuntu/JetPack/64_TX1/gcc-linaro-7.3.1-2018.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-g++
CXXFLAGS	= -Wall -W -fPIC \
		  --sysroot=/home/ubuntu/JetPack/64_TX1/Linux_for_Tegra/rootfs \
		  -g
INCPATH		= -I../gpio
LDFLAGS		= -shared

all: $(OBJS)
	$(CXX) $(LDFLAGS) -o $(TARGET) $(OBJS)
	@echo build \"$(TARGET)\" done.

$(OBJS): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(INCPATH) $(SOURCES) -c

clean:
	rm -rf *.o $(TARGET)

install:
	cp $(TARGET) ../build-example-app-03-TX1-Debug
