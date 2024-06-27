CC = gcc
MAIN = main.c
EXEC = exec
LIB_NAME = libmymemory.so
LIB_MAIN = mymemory.c
LIB_OBJ = $(LIB_MAIN:.c=.o)
CFLAGS = -I. -fPIC
LDFLAGS = -shared

all: $(EXEC)

$(EXEC): $(MAIN) $(LIB_NAME)
	$(CC) $(MAIN) -o $(EXEC) -L. -lmymemory

$(LIB_NAME): $(LIB_OBJ)
	$(CC) $(LDFLAGS) -o $(LIB_NAME) $(LIB_OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXEC) $(LIB_NAME) $(LIB_OBJ)
