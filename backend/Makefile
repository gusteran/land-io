CC = clang++
CFLAGS = -Wall
BIN = land-server

$(BIN): main.o driver.o board.o tile.o bot.o
	$(CC) -lpthread $^ -o $@
main.o: main.cpp
	$(CC) -c $< -o $@ $(CFLAGS)
%.o: %.cpp %.h
	$(CC) -c $< -o $@ $(CFLAGS)
format:
	clang-format -i -style=file *.cpp *.h
clean:
	rm *.o $(BIN)
