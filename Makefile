CC = clang++
CFLAGS = -Weverything
BIN = land-server

$(BIN): driver.o board.o tile.o
	$(CC) $^ -o $@
%.o: %.cpp *.h
	$(CC) -c $< -o $@ $(CFLAGS)
format:
	clang-format -i -style=file *.cpp *.h
clean:
	rm *.o $(BIN)
