TARGET = main
LIBS = -lm
CC = gcc
CFLAGS = -g -Wall

.PHONY: default all clean

default: $(TARGET)
all: default

run: default
	./main

render: clean_imgs run wait convert

wait:
	sleep 3

clean_imgs:
	-rm pngs/*.png
	-rm ppms/*.ppm

IMAGES = $(patsubst ppms/%.ppm, pngs/%.png, $(wildcard ppms/*.ppm))

convert: $(IMAGES)
	ffmpeg -framerate 30 -pattern_type glob -i "pngs/*.png" -c:v libx264 -pix_fmt yuv420p out.mp4 -y

pngs/%.png: ppms/%.ppm
	ffmpeg -i $< $@ -y


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
