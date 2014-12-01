# STEMMER IMAGING
# 
# makefile for the ComplexMultiOSConsoleExample
# usage:
# make all
# or 
# make debug 

# Points to the root of Google Test, relative to where this file is.
# Remember to tweak this if you move this file.
GTEST_DIR = /usr/src/gtest
SOURCES = cameraTest.cpp cameraTest.h main.cpp

ifeq "$(MAKECMDGOALS)" "debug"
 CPPFLAGS = -D_DEBUG -ggdb3 -O0
 TGT = ComplexMultiOSConsoleExample_d 
 CONFIGURATION = Debug
else 
 CPPFLAGS = -O3
 TGT = ComplexMultiOSConsoleExample 
 CONFIGURATION = Release
endif

CPPFLAGS += -isystem $(GTEST_DIR)/include -I$(CVB)/include
LDFLAGS = -L$(CVB)/lib
LDLIBS= -lCVCImg -lCVCUtilities -lCVCDriver -lCVGenApi 

# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

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



CXXFLAGS += -g -Wall -Wextra -pthread
CONFIGURATIONPREFIX= ./$(CONFIGURATION)/
DEPENDENCIES= $(addprefix $(CONFIGURATIONPREFIX),$(SOURCES:.cpp=.d) )  

%.o: %.cpp $(GTEST_HEADERS)
	@mkdir -p $(CONFIGURATION)
	@echo Building CXX object $(CONFIGURATION)/$@
	@$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) -o $(CONFIGURATION)/$@ $<

OBJECTS = $(addprefix $(CONFIGURATIONPREFIX),$(SOURCES:.cpp=.o) )

$(TGT): $(SOURCES:.cpp=.o) 
	@echo Linking CXX executable $(CONFIGURATION)/$(TGT)
	@$(CXX) $(LDFLAGS) $(OBJECTS) -o $(CONFIGURATION)/$(TGT) $(LDLIBS)

all: $(TGT)

.PHONY: clean
clean:
	@rm -rf Debug
	@rm -rf Release

debug: $(TGT)


