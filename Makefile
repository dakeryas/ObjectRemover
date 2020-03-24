ODIR = ./objects
SDIR = ./src
IDIR = ./include
MAIN = ObjectRemover.cpp
EXECUTABLE = $(patsubst %.cpp,%, $(MAIN))

MAKEFLAGS = -j$(shell nproc)
CPPFLAGS += $(shell root-config --cflags)
CPPFLAGS += -I. -I$(IDIR)
CPPFLAGS += -I$(BOOST_PATH)/include
OPTFLAG = $(CPPFLAGS) -Wall -Wextra -O3 -MMD -MP

LDFLAGS +=  $(shell root-config --libs)
LDFLAGS += -lrt
LDFLAGS += -L$(BOOST_PATH)/lib -lboost_filesystem -lboost_system -lboost_program_options

OBJS = $(patsubst %.cpp,%.o,$(addprefix $(ODIR)/,$(wildcard *.cpp)))
OBJS += $(patsubst $(SDIR)/%.cpp,$(ODIR)/%.o,$(wildcard $(SDIR)/*.cpp))

.PHONY: clean

all: $(EXECUTABLE)

debug:OPTFLAG = $(CPPFLAGS) -Wall -Wextra -O0 -g
debug:$(EXECUTABLE)

$(OBJS): | $(ODIR)
$(ODIR):
	mkdir -p $(ODIR)

$(ODIR)/$(MAIN:.cpp=.o): $(MAIN)
	$(CXX) $(OPTFLAG) -c -o $@ $<

$(ODIR)/%.o:$(SDIR)/%.cpp $(IDIR)/%.hpp
	$(CXX) $(OPTFLAG) -c -o $@ $<


$(EXECUTABLE): $(OBJS)
	$(CXX) -o $@  $^ $(LDFLAGS)

clean:
	rm -f $(ODIR)/*.o $(SDIR)/*~ $(IDIR)/*~ $(EXECUTABLE) *~

