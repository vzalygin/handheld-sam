OBJS=reciter.o sam.o render.o main.o debug_sam.o ReciterTabs.o RenderTabs.o SamTabs.o
CC=gcc
CFLAGS=-Wall -Istub_h -g -O0 -pedantic -Wno-format-security
LFLAGS=

sam: $(OBJS)
	$(CC) -o sam $(OBJS) $(LFLAGS)
%.o: src/%.c
	$(CC) -o $@ $(CFLAGS) -c $<

clean:
	rm -f *.o
