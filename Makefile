CC = g++
CFLAGS = -Weverything
BIN = land-server

$(BIN): driver.o
	$(CC) $^ -o $@
%.o: %.cpp *.h
	$(CC) -c $< -o $@ $(CFLAGS)
format:
	clang-format -i -style=file *.[ch]
clean:
	rm *.o $(BIN)
