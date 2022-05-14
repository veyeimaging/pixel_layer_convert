
all: pixel_layer_convert.o
	gcc -o pixel_layer_convert pixel_layer_convert.o

pixel_layer_convert.o : pixel_layer_convert.c
	gcc -c pixel_layer_convert.c

clean : 
	rm pixel_layer_convert.o
