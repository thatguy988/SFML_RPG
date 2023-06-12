SRCDIR := src
BUILDDIR := build
INCLUDEDIR := include
LIBDIR := lib

OBJS := $(BUILDDIR)/main.o $(BUILDDIR)/GameWindow.o
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

$(BUILDDIR)/GameWindow.o: $(SRCDIR)/view/GameWindow.cpp
	g++ -c $< -o $@ $(CPPFLAGS)
