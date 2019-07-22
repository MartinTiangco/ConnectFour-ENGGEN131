/* ENGGEN131 Project - C Project - 2018 */
/* Connect Four */

#include "connect4.h"

/*
*** Please replace this comment with your name and ID number ***
This is the file that you will be submitting for marking
Complete the definitions of the functions in this file
DO NOT REMOVE ANY FUNCTION DEFINITIONS - they all must be present when you submit this file
*/

int SecondPlacePrize(int prize1, int prize2, int prize3)
{
	//finds the middle value of a three element array
	int temp = 0;
	int values[3] = {0};
	values[0] = prize1;
	values[1] = prize2;
	values[2] = prize3;
	
	for (int i = 0; i < 3; i++) {
		for (int j = i + 1; j < 3; j++) {
			if (values[i] > values[j]) {
				temp = values[i];
				values[i] = values[j];
				values[j] = temp;
			}
		}
	}
	
	return values[1];
}

int FourInARow(int values[], int length)
{
	//Checks a 1D array for four values in a row
	values[length] = '\0';
	
	//checks if a value at one point has 3 of the same values preceding it
	for (int i = 0; i < length; i++) {
		if ((values[i] == values[i+1]) && (values[i] == values[i+2]) && (values[i] == values[i+3])) {
			return i;
		}
	}
	return -1;
}

int PowerOfValue(int result, int exponent)
{
	//helper for BinaryToDecimal
	
	//calculates power of integer
	result = 1;

	for (int i = 1; i < exponent + 1; i++) {
		result = result * 2;
	}
	return result;
}
	
int BinaryToDecimal(int binary)
{
	//Converts Binary to Decimal
	
	int i = 0;
	int digits = 0;
	int remainder = 0;
	int result = 0;
	int temp = 0;
	int array[100] = {0};
	
	//find length of binary
	//algorithm is modified from
	//https://www.programiz.com/c-programming/examples/digits-count
	while (binary != 0) {
		remainder = binary % 10;
		binary = binary/10;
		
		if (remainder == 0) {
			array[i] = 0;
		} else {
			array[i] = 1;
		}
		
		digits++;
		i++;
	}
	
	//convert binary to decimal
	for (int j = 0; j < digits; j++) {
		temp = 0;
		if (array[j] != 0) {
			temp = PowerOfValue(array[j], j);
		}
		result = result + temp;
	}		
	
	return result;	
}

double MedianAbility(double abilities[], int length)
{
	//Finds the median value of a given 1D array
	
	//rearranges array
	double temp;
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {
			if (abilities[i] > abilities[j]) {
			temp = abilities[i];
			abilities[i] = abilities[j];
			abilities[j] = temp;
			}
		}
	}	
	//finds median value
	if (length % 2 != 0) {
		return (abilities[length/2]);
	} else {
		return (abilities[length/2] + abilities[length/2 -1]) / 2;
	}
}
void RemoveCharacter(char *name, int index)
{
	//helper function for RemoveSpaces
	
	//loops through the array and moves all elements rightwards
	//of the current index to the left
	int length = strlen(name);
	for (int i = index; i < length; i++) {
		name[i] = name[i + 1];
	}
}

void RemoveSpaces(char *name)
{
	//Removes all redundant spaces (only leaves one space)
	int i = 0;
	int j = i + 1;
	
	//compares a space character (i) with the next character (j)
	//in array and will remove j if j is a space
	while (name[i] != '\0') {
		while ((name[i] == ' ') && (name[i] == name[j])) {
			RemoveCharacter(name, j);
		}
		i++;
		j = i + 1;
	}
}

void InitialiseBoard(int board[MAX_SIZE][MAX_SIZE], int size)
{
	//creates a connect 4 board with 2D arrays
	
	//clears all board spaces first
	for (int i = 0; i < MAX_SIZE; i++) {
		for (int j = 0; j < MAX_SIZE; j++) {
			board[i][j] = -1;
		}
	}
	
	//places 3 (fixed space) in the middle
	if (size % 2 == 1) { //for odd sizes, only one fixed piece is placed
		board[size/2][size/2] = 3;
	} else { //for even sizes, 4 fixed pieces are placed
		board[size/2 - 1][size/2 - 1] = 3;
		board[size/2][size/2 - 1] = 3;
		board[size/2 - 1][size/2] = 3;
		board[size/2][size/2] = 3;
	}
	
	//places 0 (empty space) everywhere else
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (board[i][j] != 3) {
				board[i][j] = 0;
			}
		}
	}
}

void AddMoveToBoard(int board[MAX_SIZE][MAX_SIZE], int size, char side, int move, int player, int *lastRow, int *lastCol)
{
	//Places tokens of player 1 and player 2 on connect 4 board
	int i = 0;
	
	if (side == 'N') { //north -> goes down
		//checks if move is valid
		if (board[0][move] == 0) {
			for (i = 0; i < size; i++) { //loops through entire column
				if (board[i][move] != 0) {
					board[i-1][move] = player; //places token one above the existing non-zero piece
					*lastRow = i - 1;
					*lastCol = move;
					i = size; //stops loop
				} else if (i == size - 1) {
					//if loop doesn't run into any non-zero pieces, place token at the end
					//same as other directions
					board[size-1][move] = player;
					*lastRow = size - 1;
					*lastCol = move;
				}
			}
		} else { //move is invalid (and is the same code as other directions)
			*lastRow = -1;
			*lastCol = -1;
		}
	} else if (side == 'W') { //west -> goes right
		//checks if move is valid
		if (board[move][0] == 0) {
			for (i = 0; i < size; i++) { //loops through the entire row
				if (board[move][i] != 0) {
					board[move][i-1] = player; //places token one to the left of existing non-zero piece
					*lastRow = move;
					*lastCol = i - 1;
					i = size; //stops loop
				} else if (i == size - 1) {
					board[move][size-1] = player;
					*lastRow = move;
					*lastCol = size - 1;
				}
			}
		} else {
			*lastRow = -1;
			*lastCol = -1;
		}
	} else if (side == 'E') { //east -> goes left
		//checks if move is valid
		if (board[move][size-1] == 0) {
			for (i = size-1; i >= 0; i--) { //loops through entire row
				if (board[move][i] != 0) {
					board[move][i+1] = player; //places token one to the right of existing non-zero piece
					*lastRow = move;
					*lastCol = i + 1;
					i = -1; 
				} else if (i == 0) {
					board[move][0] = player;
					*lastRow = move;
					*lastCol = 0;
				}
			}
		} else {
			*lastRow = -1;
			*lastCol = -1;
		}
	} else if (side == 'S') { //north -> goes up
		//checks if move is valid
		if (board[size-1][move] == 0) {
			for (i = size-1; i >= 0; i--) { //loops through entire column
				if (board[i][move] != 0) {
					board[i+1][move] = player; //places token one below the non-zero piece
					*lastRow = i + 1;
					*lastCol = move;
					i = -1;
				} else if (i == 0) { 
					board[0][move] = player;
					*lastRow = 0;
					*lastCol = move;
				}
			}
		} else { 
			*lastRow = -1;
			*lastCol = -1;
		}
	}
}

int CheckGameOver(int board[MAX_SIZE][MAX_SIZE], int size, int player, int row, int col)
{
	//Checks the game if a player has won by either placing the last token on the board or
	//by placing a token that completes the four in a row win condition
	int zeroCount = 0; //number of 0's on the boundaries of the board
	
	if ((row == -1) && (col == -1)) {
		return 0; //if a player makes an invalid move, the game keeps going
	} else {
		//checks all outer columns and rows for empty spaces
		for (int i = 0; i < size; i++) {
			if (board[i][0] == 0) {
				zeroCount++;
			}
			if (board[i][size-1] == 0) {
				zeroCount++;
			}
			if (board[0][i] == 0) {
				zeroCount++;
			}
			if (board[size-1][i] == 0) {
				zeroCount++;
			}
		}
		if (zeroCount == 0) {
			//Player has placed their token on the last available position in the board and wins
			return player;
		} else { //checks for four in a row
		
			/* --- horizontal --- */
			for (int i = 0; i < size; i++) {
				if ((board[row][i] == board[row][i+1]) && (board[row][i] == board[row][i+2]) && (board[row][i] == board[row][i+3]) && (board[row][i] == player)) {
					printf("Horizontal Win\n");
					return player;
				}
			}
			
			/* --- vertical --- */
			for (int i = 0; i < size; i++) {
			if ((board[i][col] == board[i+1][col]) && (board[i][col] == board[i+2][col]) && (board[i][col] == board[i+3][col]) && (board[i][col] == player)) {
					printf("Vertical Win\n");
					return player;
				}
			}
			
			/* --- diagonal --> top left to bottom right --- */
			
			//sets up integers i and j as lastRow and lastCol for diagonal checks
			int i = row;
			int j = col;
			while (board[i-1][j-1] == player) {
				//move up to the top leftmost corner (stops at board boundaries, set pieces (3),
				//tokens from the other player and 0's)
				i--;
				j--;
			}
			//scans diagonally from top left 
			while (board[i][j] == player) {
				if ((board[i][j] == board[i+1][j+1]) && (board[i][j] == board[i+2][j+2]) && (board[i][j] == board[i+3][j+3]) && (board[i][j] == player)) {
					printf("Diagonal Top Left Win\n");
					return player;
				}
				i++;
				j++;
			}
			
			//resets i and j to current position
			i = row;
			j = col;
			
			/* --- diagonal --> top right to bottom left --- */
			while (board[i-1][j+1] == player) {
				//move up to the top rightmost corner (stops at 0's, 3's, board boundaries and
				//tokens from the other player)
				i--;
				j++;
			}
			//scans diagonally from top right
			while (board[i][j] == player) {
				if ((board[i][j] == board[i+1][j-1]) && (board[i][j] == board[i+2][j-2]) && (board[i][j] == board[i+3][j-3]) && (board[i][j] == player)) {
					printf("Diagonal Top Right Win\n");
					return player;
				}
				i++;
				j--;
			}
			return 0; //keep playing
			
		}
	}
}

void GetDisplayBoardString(int board[MAX_SIZE][MAX_SIZE], int size, char *boardString)
{
	//Creates a pretty board using a char array
	
	int row = 0;
	int col = 0;
	int i = 0;
	
	//stops the char array by placing '\0' character at the end
	boardString[(size + 4) * (size + 5)] = '\0';
	
	//new line characters at the end of each row
	for (row = 0; row < size + 4; row++) {
		boardString[(size + 4) + row * (size + 5)] = '\n';
	}
	
	//hyphen characters
	for (row = 0; row < size + 4; row++) {
		boardString[row * (size + 5)] = '-';
		boardString[row * (size + 5) + 1] = '-';
		boardString[row * (size + 5) + 1 + size + 1] = '-';
		boardString[row * (size + 5) + 1 + size + 2] = '-';
	}

	//'N' and 'S' characters
	for (col = 2; col <= size + 1; col++) {
		boardString[col] = 'N';
		boardString[(size + 3) * (size + 5) + col] = 'S';
	}
	
	//'W' and 'E' characters
	for (row = 2; row < size + 2; row++) {
		boardString[row * (size + 5)] = 'W'; 
		boardString[row * (size + 5) + (size + 3)] = 'E';
	}
	
	//print out 0 -> size -1 characters on 'N' and 'S' side
	for (col = 2; col <= size + 1; col++) {
		boardString[col + size + 5] = (char)(i+48);
		boardString[(size + 3) * (size + 5) + col - (size + 5)] = (char)(i+48);
		i++;
	}
	
    //reset i = 0;
	i = 0;
	
	//print out 0 -> size -1 characters on 'W' and 'E' side
	for (row = 2; row < size + 2; row++) {
		boardString[row * (size + 5) + 1] = (char)(i + 48); 
		boardString[row * (size + 5) + (size + 3) - 1] = (char)(i + 48);
		i++;
	}

	//prints out the board
	//formula for converting from 2D array --> 1D array
	//12 + 2 * size + col + row * (size + 5)
	for (row = 0; row < size; row++) {
		for (col = 0; col < size; col++) {
			if (board[row][col] == 0) {
				boardString[12 + 2 * size + col + row * (size + 5)] = '.';
			} else if (board[row][col] == 1) {
				boardString[12 + 2 * size + col + row * (size + 5)] = 'X';
			} else if (board[row][col] == 2) {
				boardString[12 + 2 * size + col + row * (size + 5)] = 'O';
			} else { // if board value is 3
				boardString[12 + 2 * size + col + row * (size + 5)] = '#';
			}
		}
	}
}
int ValidChecker(int board[MAX_SIZE][MAX_SIZE], int size, char side, int move)
{
	if (side == 'N') {
			if (board[0][move] == 0) {
				return 1;
			}
		} else if (side == 'W') {
			if (board[move][0] == 0) {
				return 1;
			}
		} else if (side == 'E') {
			if (board[move][size-1] == 0) {
				return 1;
			}
		} else if (side == 'S') {
			if (board[size-1][move] == 0) {
				return 1;
			}
		}
	//if none of the if statements executed, it is an invalid move
	return 0;
}

void GetMoveBot1(int board[MAX_SIZE][MAX_SIZE], int size, int player, char *side, int *move)
{
	//Strategy for Bot 1 (same as Bot 2)
	//variable declarations
	int lastRow;
	int lastCol;
	int isValid = 0;
	char sideSelection[1];
	int tempMove = 0;
	int check4Win = 0;
	int winningPlay = 0;
	int i = 0;
	
	//initialises the random number generator's seed
	srand((unsigned int)time(NULL));     
	
	//scans through board to see if any win conditions exist
	for (i = 0; i < size; i++) {
		//places north
		AddMoveToBoard(board, size, 'N', i, player, &lastRow, &lastCol);
		//checks for win
		check4Win = CheckGameOver(board, size, player, lastRow, lastCol);
		if ((lastRow != -1)) {
			//replaces board with 0 to remove the added token
			board[lastRow][lastCol] = 0;
		}
		if (check4Win == player) {
			//if there is winning condition, winningPlay is set to 1
			sideSelection[0] = 'N';
			tempMove = i;
			winningPlay = 1;
		}
		
		//places south
		AddMoveToBoard(board, size, 'S', i, player, &lastRow, &lastCol);
		check4Win = CheckGameOver(board, size, player, lastRow, lastCol);
		if ((lastRow != -1)) {
			board[lastRow][lastCol] = 0;
		}
		if (check4Win == player) {
			sideSelection[0] = 'S';
			tempMove = i;
			winningPlay = 1;
		}
		
		//places west
		AddMoveToBoard(board, size, 'W', i, player, &lastRow, &lastCol);
		check4Win = CheckGameOver(board, size, player, lastRow, lastCol);
		if ((lastRow != -1)) {
			board[lastRow][lastCol] = 0;
		}
		if (check4Win == player) {
			sideSelection[0] = 'W';
			tempMove = i;
			winningPlay = 1;
		}
		
		//places east
		AddMoveToBoard(board, size, 'E', i, player, &lastRow, &lastCol);
		check4Win = CheckGameOver(board, size, player, lastRow, lastCol);
		if ((lastRow != -1)) {
			board[lastRow][lastCol] = 0;
		}
		if (check4Win == player) {
			sideSelection[0] = 'E';
			tempMove = i;
			winningPlay = 1;
		}
	}


	if (winningPlay == 1) {
		*side = sideSelection[0];
		*move = tempMove;
		
	} else { //if there is no winning play made generate random side and move and check if valid move
		while (isValid != 1) {
			if (rand() % 4 == 0) {
				sideSelection[0] = 'N';
			} else if (rand() % 4 == 1) {
				sideSelection[0] = 'W';
			} else if (rand() % 4 == 2) {
				sideSelection[0] = 'E';
			} else {
				sideSelection[0] = 'S';
			}
			
			tempMove = (rand() % size);
			
			//check if it's valid THEN add move to board
			isValid = ValidChecker(board, size, sideSelection[0], tempMove);
			
			if (isValid == 1) {
				*side = sideSelection[0];
				*move = tempMove;
			}
		}
	}
}

void GetMoveBot2(int board[MAX_SIZE][MAX_SIZE], int size, int player, char *side, int *move)
{
	//variable declarations
	int lastRow;
	int lastCol;
	int isValid = 0;
	char sideSelection[1];
	int tempMove = 0;
	int check4Win = 0;
	int winningPlay = 0;
	int i = 0;
	
	//initialises the random number generator's seed
	srand((unsigned int)time(NULL));     
	
	//scans through board to see if any win conditions exist
	for (i = 0; i < size; i++) {
		//places north
		AddMoveToBoard(board, size, 'N', i, player, &lastRow, &lastCol);
		//checks for win
		check4Win = CheckGameOver(board, size, player, lastRow, lastCol);
		if ((lastRow != -1)) {
			//replaces board with 0 to remove the added token
			board[lastRow][lastCol] = 0;
		}
		if (check4Win == player) {
			//if there is winning condition, winningPlay is set to 1
			sideSelection[0] = 'N';
			tempMove = i;
			winningPlay = 1;
		}
		
		//places south
		AddMoveToBoard(board, size, 'S', i, player, &lastRow, &lastCol);
		check4Win = CheckGameOver(board, size, player, lastRow, lastCol);
		if ((lastRow != -1)) {
			board[lastRow][lastCol] = 0;
		}
		if (check4Win == player) {
			sideSelection[0] = 'S';
			tempMove = i;
			winningPlay = 1;
		}
		
		//places west
		AddMoveToBoard(board, size, 'W', i, player, &lastRow, &lastCol);
		check4Win = CheckGameOver(board, size, player, lastRow, lastCol);
		if ((lastRow != -1)) {
			board[lastRow][lastCol] = 0;
		}
		if (check4Win == player) {
			sideSelection[0] = 'W';
			tempMove = i;
			winningPlay = 1;
		}
		
		//places east
		AddMoveToBoard(board, size, 'E', i, player, &lastRow, &lastCol);
		check4Win = CheckGameOver(board, size, player, lastRow, lastCol);
		if ((lastRow != -1)) {
			board[lastRow][lastCol] = 0;
		}
		if (check4Win == player) {
			sideSelection[0] = 'E';
			tempMove = i;
			winningPlay = 1;
		}
	}


	if (winningPlay == 1) {
		*side = sideSelection[0];
		*move = tempMove;
		
	} else { //if there is no winning play made generate random side and move and check if valid move
		while (isValid != 1) {
			if (rand() % 4 == 0) {
				sideSelection[0] = 'N';
			} else if (rand() % 4 == 1) {
				sideSelection[0] = 'W';
			} else if (rand() % 4 == 2) {
				sideSelection[0] = 'E';
			} else {
				sideSelection[0] = 'S';
			}
			
			tempMove = (rand() % size);
			
			//check if it's valid THEN add move to board
			isValid = ValidChecker(board, size, sideSelection[0], tempMove);
			
			if (isValid == 1) {
				*side = sideSelection[0];
				*move = tempMove;
			}
		}
	}
}
