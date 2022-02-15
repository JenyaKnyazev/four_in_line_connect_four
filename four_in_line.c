#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
void print_board(char board[6][7]) {
    int i, r;
    for (i = 0; i < 6; i++) {
        putchar('\t');
        for (r = 0; r < 7; r++)
            printf("%c ",board[i][r]);
        putchar('\n');
    }
}
void clean_board(char board[6][7]) {
    int i, r;
    for (i = 0; i < 6; i++)
        for (r = 0; r < 7; r++)
            board[i][r] = '+';
}
char choose() {
    char str[100];
    printf("Player 1 choose X or O, 1 = X, Other = O : ");
    gets(str);
    return (strlen(str) == 1 && str[0] == '1') ? 'X' : 'O';
}
void delay(int mill) {
    clock_t start = clock();
    while (clock() < start + mill);
}
int player_action(char board[6][7]) {
    char str[100];
    printf("Enter column 1-7: ");
    gets(str);
    while (strlen(str) != 1 || !(str[0] >= '1' && str[0] <= '7')||board[0][str[0]-'1']!='+') {
        printf("Invalid move enter col 1-7 :");
        gets(str);
    }
    return str[0] - '1';
}
void clean_screan() {
    int i;
    for (i = 0; i < 200; i++)
        putchar('\n');
}
void move(char board[6][7],char player,int col) {
    int i=1;
    clean_screan();
    board[0][col] = player;
    print_board(board);
    delay(350);
    while (i < 6 && board[i][col] == '+') {
        board[i - 1][col] = '+';
        board[i][col] = player;
        clean_screan();
        print_board(board);
        delay(350);
        i++;
    }
}
int check_win(char board[6][7],char player) {
    int i, r,j,k,m,count;
    for (i = 0; i < 6; i++)
        for (j = 0; j < 3; j++) {
            count = 0;
            for (r = j; r < j + 4; r++)
                if (board[i][r] == player)
                    count++;
            if (count == 4)
                return 1;
        }
    for (i = 0; i < 7; i++)
        for (j = 0; j < 3; j++) {
            count = 0;
            for (r = j; r < j + 4; r++)
                if (board[r][i] == player)
                    count++;
            if (count == 4)
                return 1;
        }
    for (k = 0; k < 4; k++) {
        for (j = 0,r=0,i=k; j + i < 4 && j + r < 3; j++) {
            count = 0;
            r = 0;
            i = k;
            for (i += j, r += j, m = 0; m < 4; r++,m++, i++) {
                if (board[r][i] == player)
                    count++;
            }
            if (count == 4)
                return 1;
            r = 0;
            i = k;
        }
    }
    for (k = 0; k < 3; k++) {
        for (j = 0, r = k, i = 0; j + i < 4 && j + r < 3; j++) {
            count = 0;
            r = k;
            i = 0;
            for (i += j, r += j, m = 0; m < 4; m++, r++, i++)
                if (board[r][i] == player)
                    count++;
            if (count == 4)
                return 1;
            r = k;
            i = 0;
        }
    }
    for (k = 3; k < 7; k++) {
        for (i = k, r = 0, j = 0; i - j > 2 && r + j < 3; j++) {
            count = 0;
            i = k;
            r = 0;
            for (i -= j, r += j, m = 0; m < 4; m++, i--, r++)
                if (board[r][i] == player)
                    count++;
            if (count == 4)
                return 1;
            r = 0;
            i = k;
        }
    }
    for (k = 0; k < 3; k++) {
        for (i = 6, r = k, j = 0; r + j < 3 && i - j>2; j++) {
            count = 0;
            i = 6;
            r = k;
            for (i -= j, r += j, m = 0; m < 4; m++, r++, i--)
                if (board[r][i] == player)
                    count++;
            if (count == 4)
                return 1;
            i = 6;
            r = k;
        }
    }
    return 0;
}
void run() {
    char player1;
    char player2;
    char str[100];
    int count_moves;
    char board[6][7];
    do {
        clean_board(board);
        //clean_screan();
        count_moves = 0;
        player1 = choose();
        player2 = (player1 == 'X') ? 'O' : 'X';
        print_board(board);
        while (1) {
            printf("PLayer 1 %c\n", player1);
            move(board, player1, player_action(board));
            if (check_win(board,player1)) {
                printf("PLayer 1 %c WIN\n", player1);
                break;
            }
            printf("PLayer 2 %c\n", player2);
            move(board, player2, player_action(board));
            if (check_win(board,player2)) {
                printf("PLayer 1 %c WIN\n", player2);
                break;
            }
            count_moves += 2;
            if (count_moves == 42) {
                puts("TIE DRAW");
                break;
            }
        }
        printf("Again = 1, Other = Exit: ");
        gets(str);
        if (strlen(str) != 1)
            break;
        
    } while (str[0]=='1');
    puts("Good Bye");
}
void main(){
    run();
    system("pause");
}
