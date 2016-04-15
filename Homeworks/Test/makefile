CC = gcc
CFLAGS = 
EXE = printPrimes

HDRS = dynArray.h
SRCS = PrintPrime.c dynArray.c
OBJS := $(SRCS:.c=.o)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.cpp $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
	 
clean:
	rm -f *.o $(EXE)
