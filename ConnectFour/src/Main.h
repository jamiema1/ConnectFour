#pragma once

void cursorPositonCallback(GLFWwindow* window, double xPos, double yPos);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void cursorEnterCallback(GLFWwindow* window, int entered);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);


enum class Value {
	empty,
	yellow,
	red
};


// main function
void runGame();

// returns true if a tie or win
bool tie();
bool win();

// resets the board
void reset();

// checks all possible winning conditions
bool verticalWin();
bool horizontalWin();
bool positiveDiagonalWin();
bool negativeDiagonalWin();

// fills a given column of the board with a piece
void fillBoard(int col);

// prints various components of the game
void printBoard();
void printWin(int scale);
void printTie(int scale);
void printColumns(int scale);
void printEndGameMessages(int scale);