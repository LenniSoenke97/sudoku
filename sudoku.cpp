#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include<iostream>
#include<fstream>
#include"sudoku.h"
#include<cmath>

using namespace std;


/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in)
    cout << "Failed!" << '\n';
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << '\n';
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3))
    cout << "  +===========+===========+===========+" << '\n';
  else
    cout << "  +---+---+---+---+---+---+---+---+---+" << '\n';
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << '\n';
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) 
    cout << (char) ('1'+r) << "   ";
  cout << '\n';
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* add your functions here */


// Task 1
/*
Type: Main Function 
Description: this function checks if the board is complete, that is, it had a digit in every position. This function does not verify the correctness of the board.
Input: board which you want to check
Output: true if the board is complete; false if it is not
*/
bool is_complete(const char board[ROW_NUMBER][COLUMN_NUMBER]) {
  for(int row=0; row<ROW_NUMBER; row++) {
    for(int col=0; col<COLUMN_NUMBER; col++) {
      if (!(board[row][col] >= '1' && board[row][col] <= '9'))
	return false;
    }
  }
  return true;
}
  
// Task 2
/*
Type: Helper Function
Description: This helper funtion checks if a certain digit is allowed to be placed within a certain column
Input: the position, the digit to place, the board
Output: true if digit fits in the row; false if it does not
*/
bool is_allowed_in_row(const int row, const char digit, const char board[ROW_NUMBER][COLUMN_NUMBER]) {
  for(int col=0; col<COLUMN_NUMBER; col++) {
    if (board[row][col] == digit) {
      return false;
    }
  }
  return true;
}

/* 
Type: Helper Function
Description: This helper funtion checks if a certain digit is allowed to be placed within a certain row
Input: the position, the digit to place, the board
Output: true if digit fits in the column; false if it does not
*/
bool is_allowed_in_col(const int col, const char digit, const char board[ROW_NUMBER][COLUMN_NUMBER]) {
  for(int row=0; row<ROW_NUMBER; row++) {
    if (board[row][col] == digit) {
      return false;
    }
  }
  return true;
}

/* 
Type: Helper Function
Description: This helper funtion checks if a certain digit is allowed to be placed within the box
Input: the position, the digit to place, the board
Output: true if digit fits in the box; false if it does not
*/
bool is_allowed_in_box(const int position[2], const char digit, const char board[ROW_NUMBER][COLUMN_NUMBER]) {
  int row_lower_bound = floor(position[0]/3.0)*3, col_lower_bound = floor(position[1]/3.0)*3;
  for(int row=0; row<3; row++) {
    for(int col = 0; col<3; col++) {
      if (board[row+row_lower_bound][col+col_lower_bound] == digit) {
	return false;
      }
    }
  }  
  return true;
}

/* 
Type: Helper Function
Description: Helper function converting char board positions to numerical board positions (eg. {'A','2'} goes to {0,1} 
Input: the character position you want converted, the number array you want the converted numbers to be inserted into
Output: true if the position was successfully converted; false if not
*/
bool char_position_to_numerical_position(const char char_position[], int num_position[]) {
  if('a'<= char_position[0] &&  char_position[0]<='z') {
    num_position[0] = char_position[0] - 97;
  }
  else if('A'<= char_position[0] &&  char_position[0]<='Z') {
    num_position[0] = char_position[0] - 65;
  }
  else {
    return false;
  }

  if ('0'<=char_position[1] && char_position[1]<='9') {
    num_position[1] = char_position[1] - 49;
  }
  else {
    return false;
  }

  return true;
}

/*
Type: Main Function
Description: This function checks whether a certain digit may be placed in a certain position given the current board without a row, column or box conflict
Input: the position where the digit should be placed, the digit, the board
Output: true if the file was successfully saved; false if there was an error.
*/
bool make_move(const char position[2], const char digit, const char board[ROW_NUMBER][COLUMN_NUMBER]) {
  int numerical_position[2];
  if (!('1'<=digit && digit<='9'))
    return false;
  
  if (!char_position_to_numerical_position(position, numerical_position)) {
    return false;
  }
  if(numerical_position[0] >= ROW_NUMBER || numerical_position[1] >= COLUMN_NUMBER)
    return false;

  return (is_allowed_in_row(numerical_position[0], digit, board) && \
	  is_allowed_in_col(numerical_position[1], digit, board) && \
	  is_allowed_in_box(numerical_position, digit, board));
  
}

// Task 3
/* 
Type: Main Function
Description: This function saves a given board to a file with a given filename.
Input: the filename under which you want to save the board, the board you want to save
Output: true if the file was successfully saved; false if there was an error.
*/
bool save_board(const char filename[], const char board[ROW_NUMBER][COLUMN_NUMBER]) {
  ofstream save_to_file(filename);
  if (!save_to_file) {
    cout << "Failed!" << '\n';
    return false;
  }
  
  for(int row=0; row<ROW_NUMBER; row++) {
    for(int col=0; col<COLUMN_NUMBER; col++) {
      save_to_file << board[row][col];
    }
    save_to_file << endl;
  }
  return true;
}

// Task 4
/* 
Type: Main Function
Description: This function tries to recursively solve the board, placing eligible digits at all the positions (if possible).
Input: the board you want to solve, the current row and column (default 0 for both)
Output: True if the board can be solved; False if not
*/
bool solve_board(char board[ROW_NUMBER][COLUMN_NUMBER], int row, int col) {

  if (row == ROW_NUMBER)
    return true; 

  if (board[row][col] != '.') {
    if(col == (COLUMN_NUMBER-1)) {
      if (solve_board(board, row+1, 0)) 
	return true;
    }
    else {
      if (solve_board(board, row,col+1))
	return true;
    }
    return false;
  }

  for(char digit='1'; digit<='9'; digit++) {
    char char_position[2] = {static_cast<char>(row+65),static_cast<char>(col+49)};
    if (make_move(char_position, digit, board)) {
      board[row][col] = digit;
      if(col == (COLUMN_NUMBER-1)) {
	if (solve_board(board, row+1, 0)) {
	  return true;
	}
      }
      else {
	if (solve_board(board, row, col+1)) {
	  return true;
	}
      }
       
      board[row][col] = '.';
    }
  }

  return false;
}
