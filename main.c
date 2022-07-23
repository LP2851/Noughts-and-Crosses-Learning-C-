#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

void fix_string(char *string) {
    int slen = strlen(string);

    for (int i = 0; i < slen; i++)
        if(string[i] == '\n')
            string[i] = NULL;
}

bool is_valid_move(char board[3][3], int move) {
    int y = (move-1) % 3;
    int x = (move-1) / 3;
    return !isalpha(board[x][y]);
}

void show_board(char board[3][3]) {
    printf("----------------------\n");
    for (int i = 0; i < 3; i++) {
        printf("|     |     |     |\n");
        printf("|  %c  |  %c  |  %c  |\n", board[i][0], board[i][1], board[i][2]);
        printf("|     |     |     |\n");
        printf("----------------------\n");
    }
}

int get_move(char board[3][3]) {
    int move;
    do {
        show_board(board);
        printf("Enter the position you would like to take: ");
        scanf("%d", &move);
    } while(!is_valid_move(board, move));
    return move;
}

void do_move(char board[3][3], int move, char symbol) {
    int y = (move-1) % 3;
    int x = (move-1) / 3;
    board[x][y] = symbol;
}

bool check_is_winner(char board[3][3]) {

    for (int i = 0; i < 3; i++) {
        if(board[i][0] == board[i][1] && board[i][0] == board[i][2]) return true;
        else if(board[0][i] == board[1][i] && board[0][i] == board[2][i]) return true;
    }

    // DIAGONALS
    return (board[0][0] == board[1][1] && board[0][0] == board[2][2] ||
            board[0][2] == board[1][1] && board[0][2] == board[2][0]);

}

void play_game(char player1[], char player2[]) {
    int move;
    char symbol = 'O';
    int numOfMoves = 0;
    bool winner = false;
    char board[3][3] =  {
            {'1', '2', '3'},
            {'4', '5', '6'},
            {'7', '8', '9'}
    };
    printf("%s is 'X' and %s is 'O'.\n", player1, player2);

    printf("%s will go first.\n", player1);

    while (numOfMoves < 9 && !winner) {
        symbol = (symbol == 'X') ? 'O' : 'X';
        printf("It is now %s's move.\n", (symbol == 'X') ? player1 : player2);
        move = get_move(board);
        do_move(board, move, symbol);
        numOfMoves++;
        winner = check_is_winner(board);
    }

    show_board(board);

    if(winner)
        printf("%s WINS!!\n", (symbol == 'X') ? player1 : player2);
    else
        printf("It was a DRAW!!\n");

}

bool check_play_again() {
    char input;
    printf("Would you like to play another game? [y/n]: ");
    scanf(" %c", &input);
    return (input == 'Y' || input == 'y');
}

int main() {

    char player1[64], player2[64];
    bool flipOrdering = false;

    printf("Player 1 enter your name: ");
    fgets(player1, 64, stdin);
    fix_string(player1);
    printf("Welcome %s!!\n\n", player1);

    printf("Player 2 enter your name: ");
    fgets(player2, 64, stdin);
    fix_string(player2);
    printf("Welcome %s!!\n\n", player2);

    do {

        if(flipOrdering)
            play_game(player2, player1);
        else
            play_game(player1, player2);
        flipOrdering = !flipOrdering;
    } while (check_play_again());

    return 0;
}






