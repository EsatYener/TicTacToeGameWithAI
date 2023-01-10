// Esat Yener 

// TicTacToe Game

#include <stdio.h>
#include "stdlib.h"
#include "string.h"

char gridChar(int i) {
    switch(i) {
        case -1:
            return 'X';
        case 0:
            return '?';
        case 1:
            return 'O';
    }
}

void RunGame();
void draw(int b[9]);
int win(const int board[9]);
int MiniMax(int board[9], int player);
void computerMove(int board[9]);
void playerMove(int board[9]);

int main() {
    printf("\n\n\t Tic Tac Toe\n\t-------------\n\n");
    printf("   Computer (O)    -    User (X)\n\n\n");
    
    RunGame(); // start the game.
    
	return 0;
}


void draw(int b[9]) {
	printf("\n         |      |      |\n");
    printf("    %4c | %4c | %4c |",gridChar(b[0]),gridChar(b[1]),gridChar(b[2]));
    printf("\n   ______|______|______|\n");
    
	printf("         |      |      |\n");
    printf("    %4c | %4c | %4c |",gridChar(b[3]),gridChar(b[4]),gridChar(b[5]));
    printf("\n   ______|______|______|\n");
    
	printf("         |      |      |\n");
    printf("    %4c | %4c | %4c |",gridChar(b[6]),gridChar(b[7]),gridChar(b[8]));
    printf("\n         |      |      |\n\n");
}

int win(const int board[9]) {
    //determines if a player has won, returns 0 otherwise.
    unsigned wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int i;
    for(i = 0; i < 8; ++i) {
        if( board[wins[i][0]] != 0 &&
            board[wins[i][0]] == board[wins[i][1]] &&
            board[wins[i][0]] == board[wins[i][2]] )
        	return board[wins[i][2]];
    }
    return 0;
}

int MiniMax(int board[9], int player) {
    //How is the position like for player (their turn) on board?
    int winner = win(board);
    if(winner != 0) return winner*player;

    int move = -1;
    int score = -2;//Losing moves are preferred to no move
    int i;
    for(i = 0; i < 9; ++i) {//For all moves,
        if(board[i] == 0) {//If legal,
            board[i] = player;//Try the move
            int thisScore = -MiniMax(board, player*-1);
            if(thisScore > score) {
                score = thisScore;
                move = i;
            }//Pick the one that's worst for the opponent
            board[i] = 0;//Reset board after try
        }
    }
    if(move == -1) return 0;
    return score;
}

void computerMove(int board[9]) {
    int move = -1;
    int score = -2;
    int i;
    for(i = 0; i < 9; ++i) {
        if(board[i] == 0) {
            board[i] = 1;
            int tempScore = -MiniMax(board, -1); //calculates the computer's movement.
            board[i] = 0;
            if(tempScore > score) {
                score = tempScore;
                move = i;
            }
        }
    }
    printf("   AI plays move:%d\n",move+1);
    //returns a score based on minimax tree at a given node.
    board[move] = 1;
}

void playerMove(int board[9]) {
	int move = 0;
	int moveOk = 0;
	do {
	start:
		printf("   Choose where to place (1 to 9): ");
		scanf("%d", &move);
		move--;
		
		if(board[move] != 0) {
		printf("   Its Already Occupied !");
		goto start;
		}
		if( move < 0 || move >= 9) {
			move = -1;
			printf("   Invalid range\n");
			goto start;
		}
		moveOk = 1;
	printf("\n");
	} while (moveOk == 0);
	board[move] = -1;
}

void RunGame() {
	int board[9] = {0,0,0,0,0,0,0,0,0};
	//computer squares are 1, player squares are -1.
	
	printf("   Play (1)st or (2)nd? ");
    int player=0;
    scanf("%d",&player);
    //the order of the player is determined.
    unsigned turn;
    
    for(turn = 0; turn < 9 && win(board) == 0; ++turn) {
        if((turn+player) % 2 == 0){
        	draw(board);
        	computerMove(board); 
		}
            
        else {
            draw(board);
            playerMove(board);
        }
    }
    
    switch(win(board)) {
        case 0:
            printf("   It's a draw\n");
            break;
        case 1:
            draw(board);
            printf("   Computer Wins\n");
            break;
        case -1:
            printf("   Human Wins\n");
            break;
    }
}



