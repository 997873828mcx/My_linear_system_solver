#This makefile was written based on Professor.Zingale's course website
SOURCE := $(wildcard *.cpp)
HEADERS := $(wildcard *.h)
OBJECTS := $(SOURCE:.cpp=.o)
MAINS := main.o test_MyLinearSystemSolver.o
OBJECTS := $(filter-out $(MAINS), $(OBJECTS))

DEBUG ?= FALSE

CXXFLAGS := -Wall -Wextra -Wpedantic -Wshadow -g

ifeq (${DEBUG}, TRUE)
   CXXFLAGS += -g
else
   CXXFLAGS += -DNDEBUG -O3
endif


%.o : %.cpp ${HEADERS}
	g++ ${CXXFLAGS} --std=c++17 -c $<

main: main.o ${OBJECTS}
	g++ -o $@ main.o ${OBJECTS}

clean:
	rm -f *.o main test_MyLinearSystemSolver

test_MyLinearSystemSolver:test_MyLinearSystemSolver.o ${OBJECTS}
	g++ -o $@ test_MyLinearSystemSolver.o ${OBJECTS}

testing: test_MyLinearSystemSolver
	./test_MyLinearSystemSolver > /dev/null
	@if [ $$? == 0 ]; then echo "tests passed"; fi