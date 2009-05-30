
CC      = gcc
CP	= g++
CFLAGS  = -g -Wall -c
OFLAGS  = -g 
LFLAGS  = -liniparser
RM      = rm -f
OBJS	= Barrel.o BarrelException.o BarrelsList.o InclinedPlane.o dictionary.o iniparser.o IniFileData.o main.o 


all: AALBarrels

AALBarrels: $(OBJS)
	$(CP) $(OFLAGS) -o AALBarrels $(OBJS) $(LFLAGS)
main.o: main.cpp 
	$(CP) $(CFLAGS) -o main.o main.cpp 
IniFileData.o: IniFileData.cpp
	$(CP) $(CFLAGS) -o IniFileData.o IniFileData.cpp $(LFLAGS)	
iniparser.o:
	$(CP) $(CFLAGS) -o iniparser.o iniparser.cpp
dictionary.o:
	$(CP) $(CFLAGS) -o dictionary.o dictionary.cpp
InclinedPlane.o: InclinedPlane.cpp
	$(CP) $(CFLAGS) -o InclinedPlane.o InclinedPlane.cpp 
BarrelsList.o: BarrelsList.cpp
	$(CP) $(CFLAGS) -o BarrelsList.o  BarrelsList.cpp
BarrelException.o: BarrelException.cpp
	$(CP) $(CFLAGS) -o BarrelException.o BarrelException.cpp
Barrel.o: Barrel.cpp
	$(CP) $(CFLAGS) -o Barrel.o Barrel.cpp

clean:
	$(RM) $(OBJS)

