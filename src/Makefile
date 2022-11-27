FLAGS = -pedantic-errors -std=c++11

userInterface.o: userInterface.cpp userInterface.h
	g++ $(FLAGS) -c $<

scoreStorage.o: scoreStorage.cpp scoreStorage.h
	g++ $(FLAGS) -c $<

boardFunction.o: boardFunction.cpp boardFunction.h
	g++ $(FLAGS) -c $<

gamePlay.o: gamePlay.cpp userInterface.h scoreStorage.h boardFunction.h
	g++ $(FLAGS) -c $<

2048: gamePlay.o userInterface.o scoreStorage.o boardFunction.o
	g++ $(FLAGS) $^ -o $@

clean:
	rm -f gamePlay.o userInterface.o scoreStorage.o boardFunction.o 2048.o 2048 boarddata.txt score.txt

.PHONY: clean
