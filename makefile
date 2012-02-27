
CC = g++

CFLAGS = -g

LDFLAGS=

LIBOBJECTS = -lgtest

PROGRAMS = unit_all


all: $(PROGRAMS)
	./$(PROGRAMS) 1>unit_all.log 2>unit_all.err &
clean:
	rm -f $(PROGRAMS)

unit_all: 
	$(CC) $(CFLAGS) -o $@ $@.cpp $(LIBOBJECTS) $(LDFLAGS)


