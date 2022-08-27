//Authors: Gino Nicosia and Ethan Ben-Rey
//Date: 7/19/2022
//Purpose: Project 7 Build a tic tac toe game that sends top 10 leaderboard to file
//Name: tictactoe.c

#include <stdio.h>
#define SIZE_BOARD 4
#define AMOUNT 9
#define SIZE_NAME 15

int menu();
void play(char winNames[], int[]);
void setBoard(char array[][SIZE_BOARD]);
void displayBoard(char array[][SIZE_BOARD], int, int, char);
_Bool check(char array[][SIZE_BOARD], char[], char[], int, int[]);
void send(char fileNames[][SIZE_NAME], int[], FILE*, char[]);
void score(FILE*);

int main() {
    FILE* txt;
    int userChoice, wins[AMOUNT + 1];
    char winName[SIZE_NAME], fileNames[AMOUNT][SIZE_NAME];
    for(int ind = 0; ind < AMOUNT; ind++) {
        wins[ind] = 0;
    }
    do {
        userChoice = menu();
        switch (userChoice) {
            case 0: break;
            case 1: play(winName, wins);
                    if((txt=fopen("scores.txt", "r")) != NULL) {
                        for(int row = 0; fscanf(txt, "%s %d\n", fileNames[row], &wins[row]) == 2; row++);
                        fclose(txt);
                        txt = fopen("scores.txt", "w");
                        send(fileNames, wins, txt, winName);
                        fclose(txt);
                    }else{
                        txt = fopen("scores.txt", "w");
                        send(fileNames, wins, txt, winName);
                        fclose(txt);
                    }
                    break;
            case 2: printf("**HIGH SCORES**\n");
                    if((txt = fopen("scores.txt", "r")) != NULL) {
                    score(txt);
                    fclose(txt);
                    }
                    printf("\n");
                    break;
            default: printf("Please enter a valid option!\n");
                     break;
        }
    }while(userChoice != 0);
}

int menu() {
    int input;
    printf("***TIC TAC TOE***\n");
    printf("1. Play Game\n");
    printf("2. Show Scores\n");
    printf("0. EXIT\n");
    printf("Enter your choice: ");
    scanf("%d", &input);
    return input;
}

void play(char winNames[], int wins[]) {
    int row, col, moves = 0, tieCount = 0, replay, winXO[AMOUNT];
    char move[SIZE_BOARD][SIZE_BOARD], name1[SIZE_NAME + 1], name2[SIZE_NAME + 1], piece;
    _Bool winner = 0;
    winXO[1] = 0;
    winXO[2] = 0;
    printf("Player 1, enter your name: ");
    scanf("%s", name1);
    printf("Player 2, enter your name: ");
    scanf("%s", name2);
    printf("*********\n");
    printf("%s, you'll be X's\n", name1);
    printf("%s, you'll be O's\n", name2);
    printf("------------\n");
    do {
        setBoard(move);
            do {
                if(moves % 2 == 0) {
                    printf("%s - Enter your move (row col): ", name1);
                    scanf("%d %d", &row, &col);
                    piece = 'X';
                    displayBoard(move, row, col, piece);
                }else{
                    printf("%s - Enter your move (row col): ", name2);
                    scanf("%d %d", &row, &col);
                    piece = 'O';
                    displayBoard(move, row, col, piece);
                }
                moves++;
                tieCount++;
                winner = check(move, name1, name2, tieCount, winXO);
                if(winner == 1){
                    tieCount = 0;
                }
            }while(winner == 0);
        printf("\nPlay again? 0 - no: ");
        scanf("%d", &replay);
    }while(replay != 0);
    if(winXO[1] > winXO[2]) {
        for(col = 0; col < SIZE_NAME; col++) {
            winNames[col] = name1[col];
            wins[9] = winXO[1];
        }
    }else {
        for(col = 0; col < SIZE_NAME; col++) {
            winNames[col] = name2[col];
            wins[9] = winXO[2];
        }
    }
}

void setBoard(char array[][SIZE_BOARD]) {
    for(int row = 0; row < SIZE_BOARD; row++) {
        for(int col = 0; col < SIZE_BOARD; col++) {
            array[row][col] = ' ';
        }
    }
    printf("[1]:[%c][%c][%c]\n", array[0][0], array[0][1], array[0][2]);
    printf("[2]:[%c][%c][%c]\n", array[1][0], array[1][1], array[1][2]);
    printf("[3]:[%c][%c][%c]\n", array[2][0], array[2][1], array[2][2]);
    printf("------------\n");
    printf("    [1][2][3]\n\n");
}

void displayBoard(char array[][SIZE_BOARD], int row, int col, char piece) {
    row --;
    col --;
    if(array[row][col] != ' ' || row > 2 || col > 2) {
        printf("Please enter a valid move (row col): ");
        scanf("%d %d", &row, &col);
        displayBoard(array, row, col, piece);
    }else{
        array[row][col] = piece;
        printf("[1]:[%c][%c][%c]\n", array[0][0], array[0][1], array[0][2]);
        printf("[2]:[%c][%c][%c]\n", array[1][0], array[1][1], array[1][2]);
        printf("[3]:[%c][%c][%c]\n", array[2][0], array[2][1], array[2][2]);
        printf("------------\n");
        printf("    [1][2][3]\n\n");
    }
}

_Bool check(char array[][SIZE_BOARD], char name1[], char name2[], int tie, int winXO[]) {
    for(int ind = 0; ind < 3; ind++) {
        if(array[ind][0] == array[ind][1] && array[ind][0] == array[ind][2] && array[ind][0] != ' ') {
            if(array[ind][0] == 'X') {
                printf("%s YOU WON!! CONGRATS :D\n", name1);
                winXO[1]++;
            }else{
                printf("%s YOU WON!! CONGRATS :D\n", name2);
                winXO[2]++;
            }
            return 1;
        }
        if(array[0][ind] == array[1][ind] && array[0][ind] == array[2][ind] && array[0][ind] != ' ') {
            if(array[0][ind] == 'X') {
                printf("%s YOU WON!! CONGRATS :D\n", name1);
                winXO[1]++;
                
            }else{
                printf("%s YOU WON!! CONGRATS :D\n", name2);
                winXO[2]++;
            }
            return 1;
        }
    }
    if(array[0][0] == array[1][1] && array[1][1] == array[2][2] && array[0][0] != ' ') {
        if(array[0][0] == 'X') {
                printf("%s YOU WON!! CONGRATS :D\n", name1);
                winXO[1]++;
                
            }else{
                printf("%s YOU WON!! CONGRATS :D\n", name2);
                winXO[2]++;
            }
        return 1;
    }else if(array[0][2] == array[1][1] && array[1][1] == array[2][0] && array[0][2] != ' ') {
        if(array[0][2] == 'X') {
                printf("%s YOU WON!! CONGRATS :D\n", name1);
                winXO[1]++;
                
            }else{
                printf("%s YOU WON!! CONGRATS :D\n", name2);
                winXO[2]++;
            }
        return 1;
    }else if(tie == 9) {
        printf("It's a tie! Try again...\n");
        return 1;
    }else {
        return 0;
    }
}

void send(char fileNames[][SIZE_NAME], int wins[], FILE* txt, char winNames[]) {
    for(int row = 0; row < AMOUNT; row++) {
        if(wins[row] > 0) {
            fprintf(txt, "%s %d\n", fileNames[row], wins[row]);
        }
    }
    fprintf(txt, "%s %d\n", winNames, wins[9]);
    for(int row = 0; row < AMOUNT; row++) {
        for(int col = 0; fileNames[row][col] != '\0'; col++) {
            fileNames[row][col] = '\0';
        }
    }
}

void score(FILE* txt) {
    int win;
    char name[AMOUNT];
    while(fscanf(txt, "%s %d", name, &win) == 2) {
        printf("%s: %d\n", name, win);
    }
}
