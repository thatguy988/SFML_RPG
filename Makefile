SRCDIR := src
BUILDDIR := build
INCLUDEDIR := include
LIBDIR := lib

# List all the source files here
SRCS := $(wildcard $(SRCDIR)/*.cpp)
SRCS += $(wildcard $(SRCDIR)/states/*.cpp)
SRCS += $(wildcard $(SRCDIR)/entities/*.cpp)
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))
EXE := $(BUILDDIR)/main

CPPFLAGS := -I$(INCLUDEDIR) -DSFML_STATIC
LDFLAGS := -L$(LIBDIR) -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJS)
	g++ $^ -o $@ $(LDFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	g++ -c $< -o $@ $(CPPFLAGS)

clean:
	rm -f $(EXE) $(OBJS)