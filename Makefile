OBJS=reciter.o sam.o render.o main.o debug.o ReciterTabs.o RenderTabs.o SamTabs.o
CC=gcc
CFLAGS=-Wall -Werror -Os -Istub_h
LFLAGS=

sam: $(OBJS)
	$(CC) -o sam.bin $(OBJS) $(LFLAGS)
%.o: src/%.c
	$(CC) -o $@ $(CFLAGS) -c $<

clean:
	rm -f *.o
