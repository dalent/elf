CC = g++
SRC = $(wildcard *.cpp)
OBJS = $(addsuffix .o, $(basename $(SRC)))
APP = RD
CFLAGS = -g -c 
OFLAGS = -g
$(APP): $(OBJS)
	$(CC) $(OFLAGS)  -o $@ $^
%.o:%.c
	$(CC) $(CFLAGS) -o $@ $<
clean:
	rm *.o $(APP)
