# source files.
SRC = src/sort.c

OBJ = $(SRC:.cpp=.o)

OUT = sort

# include directories
INCLUDES = -I. 
 
# C compiler flags 
CCFLAGS = -O3 -Wall -Wextra -fno-omit-frame-pointer -g -I/share/apps/papi/5.4.1/include -L/share/apps/papi/5.4.1/lib

# compiler
CCC = gcc 

# libraries
LIBS = -fopenmp -lm

.SUFFIXES: .cpp .c 

default: clean $(OUT)

.cpp.o:
	$(CCC) $(CCFLAGS) $(INCLUDES)  -c $< -o $@

.c.o:
	$(CCC) $(CCFLAGS) $(INCLUDES) -c $< -o $@

$(OUT): $(OBJ)
	$(CCC) -o $(OUT) $(CCFLAGS) $(OBJ) $(LIBS) 

depend:  dep

dep:
	makedepend -- $(CFLAGS) -- $(INCLUDES) $(SRC)

clean:
	rm -f src/*.o *~ Makefile.bak $(OUT)
