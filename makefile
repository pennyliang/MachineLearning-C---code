
CC = g++

CFLAGS = -g

LDFLAGS=

LIBOBJECTS = -lpthread 

PROGRAMS = unit_all


all: $(PROGRAMS)
	./$(PROGRAMS)  2>unit_all.err 
clean:
	rm -f $(PROGRAMS)

unit_all: 
	$(CC) -I./gtest-1.6.0/include $(CFLAGS) -o $@ $@.cpp libgtest.a $(LIBOBJECTS) $(LDFLAGS)


