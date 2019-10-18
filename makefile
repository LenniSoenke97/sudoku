sudoku: sudoku.o main.o
	g++ sudoku.o main.o -o sudoku

main.o: main.cpp sudoku.h
	g++ -g -Wall -c main.cpp

soduko.o: sudoku.cpp sudoku.h
	g++ -g -Wall -c sudoko.cpp

clean:
	rm -f *.o
