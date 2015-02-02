ODIR = ./objects
SDIR = ./src
IDIR = ./include
MAIN = ObjectRemover.cpp
EXECUTABLE = $(patsubst %.cpp,%, $(MAIN))

MAKEFLAGS = -j$(shell nproc)
FLAGS := $(shell root-config --cflags)
FLAGS += -I. -I$(IDIR)
FLAGS += -I$(BOOST_PATH)
OPTFLAG = $(FLAGS) -Wall -Wextra -O3

LIBS :=  $(shell root-config --libs)
LIBS += -lrt
LIBS += -L$(BOOST_PATH)/build/lib -lboost_filesystem -lboost_system

OBJS = $(patsubst %.cpp,%.o,$(addprefix $(ODIR)/,$(wildcard *.cpp)))
OBJS += $(patsubst $(SDIR)/%.cpp,$(ODIR)/%.o,$(wildcard $(SDIR)/*.cpp))

.PHONY: clean

all: $(EXECUTABLE)

debug:OPTFLAG = $(FLAGS) -Wall -Wextra -O0 -g
debug:$(EXECUTABLE)

$(OBJS): | $(ODIR)
$(ODIR):
	mkdir -p $(ODIR)

$(ODIR)/$(MAIN:.cpp=.o): $(MAIN)
	$(CXX) $(OPTFLAG) -c -o $@ $<

$(ODIR)/%.o:$(SDIR)/%.cpp $(IDIR)/%.hpp
	$(CXX) $(OPTFLAG) -c -o $@ $<


$(EXECUTABLE): $(OBJS)
	$(CXX) $(OPTFLAG) -o $@  $^ $(LIBS)

clean:
	rm -f $(ODIR)/*.o $(SDIR)/*~ $(IDIR)/*~ $(EXECUTABLE) *~

