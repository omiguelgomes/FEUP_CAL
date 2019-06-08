# Change to executable name.
PROG := app

# Add whatever compiler flags you want.
CXXFLAGS := -std=c++14
CXXFLAGS += -Wall

# You MUST keep this for auto-dependency generation.
CXXFLAGS += -MMD

# Can change depending on project
LDLIBS :=

# Not sure when you will really need this. Can leave blank usually.
LDFLAGS :=

# Change 'src/' to where ever you hold src files relative to Makefile.
SRCS := $(wildcard ./src/*.cpp)

# Generate .o and .d filenames for each .cpp file.
# Doesn't generate the ACTUAL files (compiler does).
# Just generates the lists.
OBJS := $(SRCS:.cpp=.o)
DEPS := $(OBJS:.o=.d)

# GNUMake feature, in case you have files called 'all' or 'clean'.
.PHONY: all clean

# Called when you run 'make'. This calls the line below.
all: $(PROG)

# Calls the compiler with flags to link all object files together.
$(PROG): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDLIBS) $(OBJS) -o $(PROG)

# Includes the dependency lists (.d files).
-include $(DEPS)

# Removes exectuable, object files, and dependency files.
clean:
	rm -f $(PROG)
	rm -f $(DEPS) $(OBJS)
	rm -f app.xml

run: all
	./$(PROG)
