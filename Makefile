# makefile for MPDMM
# by Patrick Gleeson

TEST=test
LIBRARY=mmpdmm.a
CPP_SRC=src/Album.cpp src/Artist.cpp src/Connection.cpp src/FileSystemEntry.cpp src/Error.cpp src/OutputDevice.cpp src/Stats.cpp src/Status.cpp src/Song.cpp src/test.cpp
CPP_OBJ=$(CPP_SRC:.cpp=.o)
#TEST_OBJ=src/plugin_setup.o
#MAIN_OBJ=src/main.o
RM=rm -f
HEADERS= -I headers -lstdc++ -lsocket


all: $(CPP_OBJ)
	
	gcc $(HEADERS) -o $(TEST) $(CPP_OBJ)

%.o: %.cpp
	gcc $(HEADERS) -o $@ -c $<
	
%.o: %.c
	gcc $(HEADERS) -o $@ -c $<

clean:
	-$(RM) src/*.o
	-$(RM) src/*~
	-$(RM) *\#
	-$(RM) *.core

fclean: clean
	-$(RM) $(TEST)
	-$(RM) $(LIBRARY)
	-$(RM) headers/*~
	-$(RM) *~

redo: clean all

sudo: all
	
commit: sudo fclean
	hg commit -A