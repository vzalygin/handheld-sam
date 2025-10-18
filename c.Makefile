OBJS = reciter.o sam.o render.o main-x86.o debug.o
CC = gcc
CFLAGS = -Wall -Werror -Os -fsanitize=address,undefined
LFLAGS = -fsanitize=address,undefined

sam: $(OBJS)
	$(CC) -o sam.bin $(OBJS) $(LFLAGS)
%.o: src/%.c
	$(CC) -o $@ $(CFLAGS) -c $<

clean:
	rm -f *.o
