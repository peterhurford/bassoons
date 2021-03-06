# A sample Makefile for building Google Test and using it in user
# tests.  Please tweak it to suit your environment and project.  You
# may want to move it to your project's root directory.
#
# SYNOPSIS:
#
#   make [all]  - makes everything.
#   make TARGET - makes the given target.
#   make clean  - removes all files generated by make.

# Please tweak the following variable definitions as needed by your
# project, except GTEST_HEADERS, which you can use in your own targets
# but shouldn't modify.

# Points to the root of Google Test, relative to where this file is.
# Remember to tweak this if you move this file.
GTEST_DIR = /Volumes/Data/home/cs173/gtest-1.7.0

# Where to find user code.
USER_DIR = .

# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS += -isystem $(GTEST_DIR)/include

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra -pthread -std=c++0x

# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
TESTS = testDLList testCustomer testEvent testOrderedSet testQueue testSimulator bassoons

# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

# House-keeping build targets.

all : $(TESTS)


clean :
	rm -f $(TESTS) *.o *.a *~

# Builds gtest.a and gtest_main.a.

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

# Builds two Rational test executables.  A test should link with either gtest.a or
# gtest_main.a, depending on whether it defines its own main()
# function.
#------------------------Event------------------------------------
Event.o : $(USER_DIR)/Event.cpp $(USER_DIR)/Event.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/Event.cpp

testEvent.o : $(USER_DIR)/testEvent.cpp \
                     $(USER_DIR)/Event.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/testEvent.cpp

testEvent : Event.o testEvent.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@
	
#------------------------------------------------------------------
#------------------------Customer----------------------------------

Customer.o : $(USER_DIR)/Customer.cpp $(USER_DIR)/Customer.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/Customer.cpp

testCustomer.o : $(USER_DIR)/testCustomer.cpp \
                     $(USER_DIR)/Customer.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/testCustomer.cpp

testCustomer : Customer.o testCustomer.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@
	
#-------------------------------------------------------------------
#-------------------------Server------------------------------------
Server.o : $(USER_DIR)/Server.cpp $(USER_DIR)/Server.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/Server.cpp
	
#-------------------------------------------------------------------
#-------------------------CustomerArrival---------------------------

CustomerArrival.o : $(USER_DIR)/CustomerArrival.cpp $(USER_DIR)/CustomerArrival.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/CustomerArrival.cpp

#-------------------------------------------------------------------
#--------------------------OrderedSet-------------------------------
testOrderedSet.o : $(USER_DIR)/testOrderedSet.cpp \
                    $(USER_DIR)/OrderedSet.h $(USER_DIR)/OrderedSet.hpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/testOrderedSet.cpp

testOrderedSet : Event.o testOrderedSet.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@
	
#--------------------------------------------------------------------
#-------------------------Queue--------------------------------------
testQueue.o : $(USER_DIR)/testQueue.cpp \
                     $(USER_DIR)/Queue.h $(USER_DIR)/Queue.hpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/testQueue.cpp	
	
testQueue : Customer.o testQueue.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@


#--------------------------------------------------------------------
#-------------------------DLListInt----------------------------------
	
DLListInt.o : $(USER_DIR)/DLListInt.h $(USER_DIR)/DLListInt.cpp 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/DLListInt.cpp

testDLListInt.o : $(USER_DIR)/testDLListInt.cpp \
                     $(USER_DIR)/DLListInt.h $(USER_DIR)/DLListInt.cpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/testDLListInt.cpp
	
testDLListInt : DLListInt.o testDLListInt.o gtest_main.a 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@


#--------------------------------------------------------------------
#-------------------------DLList-------------------------------------
	
testDLList.o : $(USER_DIR)/testDLList.cpp \
                     $(USER_DIR)/DLList.h $(USER_DIR)/DLList.hpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/testDLList.cpp

testDLList : testDLList.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@

#---------------------------------------------------------------------

#------------------------------------------------------------------
#-------------------------Simulator--------------------------------

Simulator.o : $(USER_DIR)/Simulator.cpp $(USER_DIR)/Simulator.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/Simulator.cpp

testSimulator.o : $(USER_DIR)/testSimulator.cpp \
                     $(USER_DIR)/Simulator.h $(USER_DIR)/OrderedSet.hpp $(USER_DIR)/Queue.hpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/testSimulator.cpp

testSimulator : Customer.o Simulator.o Event.o CustomerArrival.o Server.o testSimulator.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@
	
#------------------------------------------------------------------
#-------------------------Bassoons---------------------------------

bassoons.o : $(USER_DIR)/bassoons.cpp \
                     $(USER_DIR)/Simulator.h $(USER_DIR)/OrderedSet.hpp $(USER_DIR)/Queue.hpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/bassoons.cpp

bassoons : Customer.o Simulator.o Event.o CustomerArrival.o Server.o bassoons.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@
