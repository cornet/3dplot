PREFIX=/usr/local

CC = gcc
CFLAGS =-c -Wall -g

ifeq ($(shell uname -s), Darwin)
	LDFLAGS = -framework OpenGL -framework GLUT -framework Foundation
else
	LDFLAGS = -lglut -lGL -lGLU -lm -lMagick -ljpeg -lpng -lwmflite -ltiff
endif

SOURCES = savegraph.c display.c movie.c config.c convert.c lights.c control.c graph.c file.c main.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = 3dplot

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(FRAMEWORKS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

install:
	cp -f 3dplot $(PREFIX)/bin
	chmod a+x $(PREFIX)/bin/3dplot
	cp -f man/3dplot.1 $(PREFIX)/man/man1
	chmod a+r $(PREFIX)/man/man1/3dplot.1
	mkdir -p $(PREFIX)/share/doc/3dplot-0.1
	cp -rf docs/* $(PREFIX)/share/doc/3dplot-0.1

uninstall:
	rm -f $(PREFIX)/bin/3dplot
	rm -f $(PREFIX)/man/man1/3dplot.1
	rm -rf $(PREFIX)/share/doc/3dplot-0.1

clean:
	rm -f $(OBJECTS)
	rm -f 3dplot
