#include <GLFW/glfw3.h>
#include "Alphabet.h"
#include "Shapes.h"
#include "Main.h"
#include <string>
#include <array>
#include <iostream>

bool enter{};



double xPos{}, yPos{};

int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(windowwidth, windowheight, "Connect Four", NULL, NULL);

    glfwSetCursorPosCallback(window, cursorPositonCallback);
    glfwSetCursorEnterCallback(window, cursorEnterCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, 1);

    glfwSetKeyCallback(window, KeyCallback);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
	

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glOrtho(0, windowwidth, 0, windowheight, 0, 1);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        if (enter) {
			glfwGetCursorPos(window, &xPos, &yPos);
        }
		
		runGame();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);


        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}






std::array<Value, 42> board{};


bool running{ true };
bool turn{};


void runGame() {
	printBoard();

	int scaleText = 2;
	// checks if the winning condition is met
	if (win()) {
		running = false;
		printWin(scaleText);
		printEndGameMessages(scaleText);
	}
	else if (tie()) {
		running = false;
		printTie(scaleText);
		printEndGameMessages(scaleText);
	}

}

bool tie() {
	int count{};
	for (int i = 0; i < 7; i++) {
		if (board[i] != Value::empty) {
			count++;
		}
	}
	if (count == 7) {
		return true;
	}
	else {
		return false;
	}
}

bool win() {
	if (verticalWin() ||
		horizontalWin() ||
		positiveDiagonalWin() ||
		negativeDiagonalWin()) {
		return true;
	}
	else {
		return false;
	}
}

// check negative diagonal
bool negativeDiagonalWin() {
	for (int i = 0; i < 21; i++) {
		if ((i % 7) <= 3) {
			if ((board[i] == board[i + 8]) &&
				(board[i] == board[i + 16]) &&
				(board[i] == board[i + 24]) &&
				(board[i] != Value::empty)) {
				return true;
			}
		}
	}
	return false;
}

// check positive diagonal
bool positiveDiagonalWin() {
	for (int i = 0; i < 21; i++) {
		if ((i % 7) >= 3) {
			if ((board[i] == board[i + 6]) &&
				(board[i] == board[i + 12]) &&
				(board[i] == board[i + 18]) &&
				(board[i] != Value::empty)) {
				return true;
			}
		}
	}
	return false;
}

// check vertical (top to bottom)
bool verticalWin() {
	for (int i = 0; i < 21; i++) {
		if ((board[i] == board[i + 7]) &&
			(board[i] == board[i + 14]) &&
			(board[i] == board[i + 21]) &&
			(board[i] != Value::empty)) {
			return true;
		}
	}
	return false;
}

// check horizontal (left to right)
bool horizontalWin() {
	for (int i = 0; i < 42; i++) {
		if ((i % 7) <= 3) {
			if ((board[i] == board[i + 1]) &&
				(board[i] == board[i + 2]) &&
				(board[i] == board[i + 3]) &&
				(board[i] != Value::empty)) {
				return true;
			}
		}
	}
	return false;
}


void fillBoard(int col) {
	col--;
	Value piece{};
	if (turn) {
		piece = Value::yellow;
	}
	else {
		piece = Value::red;
	}
	if (board[col] == Value::empty) {
		for (int i = 5; i >= 0; i--) {
			int pos{ 7 * i + col };
			if (board[pos] == Value::empty) {
				board[pos] = piece;

				turn = not(turn);
				break;
			}
		}
	}
}

void reset() {
	running = true;
	turn = false;
	for (int i = 0; i < 42; i++) {
		board[i] = Value::empty;
	}
}


int pixel = 100;
int width = pixel * 7;
int height = pixel * 6;
int radius = pixel * 2 / 5;


void printBoard() {
	// highlights a column if the cursor is over it, if not displays normally
	for (int i = 1; i < 8; i++) {
		if ((xPos >= ((windowwidth - width) / 2 + (i - 1) * pixel)) &&
			(xPos <= ((windowwidth - width) / 2 + i * pixel)) &&
			(yPos >= ((windowheight - height) / 2)) &&
			(yPos <= ((windowheight + height) / 2))) {
			Rect((windowwidth - width) / 2 + (i - 1) * pixel, (windowheight - height) / 2, 0, pixel, height, 0, 0, 127);
		}
		else {
			Rect((windowwidth - width) / 2 + (i - 1) * pixel, (windowheight - height) / 2, 0, pixel, height, 0, 0, 64);
		}
	}

	// displays column numbers
	int scaleCol = 3;
	printColumns(scaleCol);

	// displays each entry of the board as a circle with colour corresponding to its Value
	for (int i = 0; i < 42; i++) {
		int row = i / 7;
		int col = i % 7;
		switch (board[i]) {
		case Value::empty:
			Circ((windowwidth - width) / 2 + col * pixel + pixel / 2, (windowheight + height) / 2 - row * pixel - pixel / 2, radius, 0, 360, 0, 0, 0);
			break;
		case Value::red:
			Circ((windowwidth - width) / 2 + col * pixel + pixel / 2, (windowheight + height) / 2 - row * pixel - pixel / 2, radius, 0, 360, 127, 0, 0);
			break;
		case Value::yellow:
			Circ((windowwidth - width) / 2 + col * pixel + pixel / 2, (windowheight + height) / 2 - row * pixel - pixel / 2, radius, 0, 360, 127, 127, 0);
			break;
		}
	}
}

void printWin(int scale) {
	if (turn) {
		int length = text(0, 0, "Red Wins!", scale, Setting::length, 0, 0, 0);
		int x = windowwidth / 2 - length / 2;
		int y = (windowheight - height) / 4 - 13 * scale / 2;
		text(x, y, "Red Wins!", scale, Setting::print, 127, 0, 0);
	}
	else {
		int length = text(0, 0, "Yellow Wins!", scale, Setting::length, 0, 0, 0);
		int x = windowwidth / 2 - length / 2;
		int y = (windowheight - height) / 2 - pixel / 2;
		text(x, y, "Yellow Wins!", scale, Setting::print, 127, 127, 0);
	}
}

void printTie(int scale) {
	int length = text(0, 0, "It's a Tie!", scale, Setting::length, 0, 0, 0);
	int x = windowwidth / 2 - length / 2;
	int y = (windowheight - height) / 4 - 13 * scale / 2;
	text(x, y, "It's a Tie!", scale, Setting::print, 0, 127, 0);
}

void printColumns(int scale) {
	for (int i = 1; i < 8; i++) {
		std::string col = std::to_string(i);
		int length = text(0, 0, col, scale, Setting::length, 0, 127, 0);
		int x = (windowwidth - width) / 2 + i * pixel - (pixel + length) / 2;
		int y = windowheight - (windowheight - height) / 4 - 13 * scale / 2;

		text(x, y, col, scale, Setting::print, 0, 127, 0);
	}
}

void printEndGameMessages(int scale) {

	int length1 = text(0, 0, "Press R To", scale, Setting::length, 0, 0, 0);
	int x1 = (int)((windowwidth / 2 - pixel * 3.5) / 2 - length1 / 2);
	int y1 = windowheight / 2;
	text(x1, y1, "Press R To", scale, Setting::print, 0, 127, 0);

	int length2 = text(0, 0, "Play Again", scale, Setting::length, 0, 0, 0);
	int x2 = (int)((windowwidth / 2 - pixel * 3.5) / 2 - length2 / 2);
	int y2 = windowheight / 2 - 14 * 2 * scale;
	text(x2, y2, "Play Again", scale, Setting::print, 0, 127, 0);


	int length3 = text(0, 0, "Press Q", scale, Setting::length, 0, 0, 0);
	int x3 = (int)(windowwidth - (windowwidth / 2 - pixel * 3.5) / 2 - length3 / 2);
	int y3 = y1;
	text(x3, y3, "Press Q", scale, Setting::print, 0, 127, 0);

	int length4 = text(0, 0, "To Quit", scale, Setting::length, 0, 0, 0);
	int x4 = (int)(windowwidth - (windowwidth / 2 - pixel * 3.5) / 2 - length4 / 2);
	int y4 = y2;
	text(x4, y4, "To Quit", scale, Setting::print, 0, 127, 0);
}





void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	if ((action == GLFW_PRESS) && running) {
		switch (key) {
		case GLFW_KEY_1:
			fillBoard(1);
			break;
		case GLFW_KEY_2:
			fillBoard(2);
			break;
		case GLFW_KEY_3:
			fillBoard(3);
			break;
		case GLFW_KEY_4:
			fillBoard(4);
			break;
		case GLFW_KEY_5:
			fillBoard(5);
			break;
		case GLFW_KEY_6:
			fillBoard(6);
			break;
		case GLFW_KEY_7:
			fillBoard(7);
			break;
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, 1);
			break;
		}
	}
	else if ((action == GLFW_PRESS) && not(running)) {
		switch (key) {
		case GLFW_KEY_R:
			reset();
			break;
		case GLFW_KEY_Q:
			glfwSetWindowShouldClose(window, 1);
			break;
		}
	}
}






void cursorEnterCallback(GLFWwindow* window, int entered) {
    if (entered) {
        enter = true;
        std::cout << "entered window" << "\n";
    }
    else {
        std::cout << "left window" << "\n";
        enter = false;
    }
}

void cursorPositonCallback(GLFWwindow* window, double xPos, double yPos) {
    static_cast<int>(xPos);
    static_cast<int>(yPos);
    //std::cout << xPos << ":" << yPos << "\n";
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	if ((action == GLFW_PRESS) && 
		(button == GLFW_MOUSE_BUTTON_LEFT) &&
		running) {
		for (int i = 1; i < 8; i++) {
			if ((xPos >= ((windowwidth - width) / 2 + (i - 1) * pixel)) &&
				(xPos <= ((windowwidth - width) / 2 + i * pixel)) && 
				(yPos >= ((windowheight - height) / 2)) &&
				(yPos <= ((windowheight + height) / 2))) {
				fillBoard(i);
			}
		}
	}
}
