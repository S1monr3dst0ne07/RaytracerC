TARGET = main
LIBS = -lm
CC = gcc
CFLAGS = -g -Wall

.PHONY: default all clean

default: $(TARGET)
all: default

run: default
	./main

render: run convert


IMAGES = $(patsubst ppms/%.ppm, pngs/%.png, $(wildcard ppms/*.ppm))

convert: $(IMAGES)

pngs/%.png: ppms/%.ppm
	ffmpeg -i $< $@


OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)

re: clean default
