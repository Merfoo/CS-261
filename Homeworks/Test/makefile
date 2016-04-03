CC = gcc
CFLAGS = 
EXE = printPrimes

SRCS = PrintPrime.c
OBJS = $(SRCS:.c=.o)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
	 
clean:
	rm -f *.o $(EXE)
