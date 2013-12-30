CC = g++
SRC = $(wildcard *.cpp)
OBJS = $(addsuffix .o, $(basename $(SRC)))
APP = rd
CFLAGS = -g -c 
OFLAGS = -g
$(APP): $(OBJS)
	$(CC) $(OFLAGS)  -o $@ $^
%.o:%.cpp
	$(CC) $(CFLAGS) -o $@  $<
clean:
	-rm *.o $(APP) >/dev/null 2>1& 
