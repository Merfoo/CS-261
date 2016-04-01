CXX = gcc
CFLAGS = 
EXE = printPrimes

SRCS = PrintPrime.c
OBJS = $(SRCS: .c = .o)

$(EXE): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $@

$(OBJS): $(SRCS)
	$(CXX) $(CXXFLAGS) -c $(@:.c=.o)

clean:
	rm -f *.o $(EXE)
