sudoku: sudoku.o main.o
	g++ sudoku.o main.o -o sudoku

main.o: main.cpp sudoku.h
	g++ -g -Wall main.cpp sudoku.h -c

soduko.o: sudoku.cpp sudoku.h
	g++ -g -Wall sudoko.cpp sudoku.h -c

clean:
	rm -f *.o
