CC = g++
SRC = $(wildcard *.cpp)
OBJS = $(addsuffix .o, $(basename $(SRC)))
APP = rd
LIB = libelf.a
CFLAGS = -g -c 
OFLAGS = -g
$(APP): $(OBJS)
	$(CC) $(OFLAGS)  -o $@ $^

lib:$(OBJS)
	ar -rs $(LIB) $(OBJS)
%.o:%.cpp
	$(CC) $(CFLAGS) -o $@  $<
clean:
	-rm  -f *.o $(APP) $(LIB) >/dev/null 2>&1 
