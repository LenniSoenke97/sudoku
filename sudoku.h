void load_board(const char* filename, char board[9][9]);
void display_board(const char board[9][9]);

const int ROW_NUMBER=9, COLUMN_NUMBER=9;

// Task 1
/*
Description: this function checks if the board is complete, that is, it had a digit in every position. This function does not verify the correctness of the board.
Input: the board you want to check
Output: true if the board is complete; false if it is not
*/
bool is_complete(const char  board[ROW_NUMBER][COLUMN_NUMBER]);

// Task 2
/*
Description: This function checks whether a certain digit may be placed in a certain position given the current board without a row, column or box conflict
Input: the position where the digit should be placed, the digit, the board
Output: true if the file was successfully saved; false if there was an error.
*/
bool make_move(const char position[2], const char digit, const char board[ROW_NUMBER][COLUMN_NUMBER]);
// Task 3
/*
Description: This function saves a given board to a file with a given filename.
Input: the filename you want to save the board to, the board to save
Output: true if the file was successfully saved; false if there was an error.
*/
bool save_board(const char filename[], const char board[9][9]);

// Task 4
/* 
Description: This function tries to recursively solve the board, placing eligible digits at all the positions (if possible).
Input: the board you want to solve, the current row and column (default 0 for both)
Output: True if the board can be solved; False if not
*/
bool solve_board(char board[ROW_NUMBER][COLUMN_NUMBER], int row=0, int col=0);
