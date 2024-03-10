#include <stdio.h>
#include <string.h>

struct Player {
    char Nume[50];
    char Xor0;
} Player1, Player2, PlayerCurrent;

void NumeJucatori() {
    printf("Introduceti numele primului jucator:\n");
    scanf("%s", Player1.Nume);
    printf("Bun venit, %s!\n", Player1.Nume);
    printf("Introduceti numele celui de-al doilea jucator:\n");
    scanf("%s", Player2.Nume);
    printf("Bun venit, %s!\n", Player2.Nume);
}

void Xsau0Jucatori() {
    printf("%s, alegerea e a ta: X sau 0? Introdu caracterul ales:\n", Player1.Nume);
    scanf(" %c", &Player1.Xor0);
    printf("%s, ai ales %c.\n", Player1.Nume, Player1.Xor0);
    if (Player1.Xor0 == 'X') {
        Player2.Xor0 = '0';
    } else {
        Player2.Xor0 = 'X';
    }
    printf("%s, te lansezi in batalie cu %c.\n", Player2.Nume, Player2.Xor0);
    printf("Sa incepem jocul!\n");
}

void AfisareBoard(char board[3][3]) {
    printf("Retineti: coloanele si randurile incep de la 0!\n");
    printf("\n");
    printf("Tabela arata astfel: \n");
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            printf("%c |", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int ConditiiCastig(char board[3][3], char Xor0) {
    for (int i = 0; i < 3; ++i) {
        if ((board[i][0] == Xor0 && board[i][1] == Xor0 && board[i][2] == Xor0) ||
            (board[0][i] == Xor0 && board[1][i] == Xor0 && board[2][i] == Xor0)) {
            return 1;
        }
    }

    if ((board[0][0] == Xor0 && board[1][1] == Xor0 && board[2][2] == Xor0) ||
        (board[0][2] == Xor0 && board[1][1] == Xor0 && board[2][0] == Xor0)) {
        return 1;
    }

    return 0;
}

int BoardFull(char board[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') {
                return 0;
            }
        }
    }
    return 1;
}

void copiazaPlayerCurent(struct Player player) {
    for (int i = 0; i < 50; i++) {
        PlayerCurrent.Nume[i] = player.Nume[i];
    }
    PlayerCurrent.Xor0 = player.Xor0;
}

int main() {
    NumeJucatori();
    Xsau0Jucatori();

    char board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    int row, col;
    copiazaPlayerCurent(Player1);

    while (!ConditiiCastig(board, 'X') && !ConditiiCastig(board, '0') && !BoardFull(board)) {
        AfisareBoard(board);
        printf("Este randul lui %s (%c). Introdu miscarea dorita (rand si coloana): ", PlayerCurrent.Nume, PlayerCurrent.Xor0);
        scanf("%d %d", &row, &col);

        if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ') {
            printf("Miscare nereusita. Incearca din nou.\n");
        } else {
            board[row][col] = PlayerCurrent.Xor0;
            if (strcmp(PlayerCurrent.Nume, Player1.Nume) == 0) {
                copiazaPlayerCurent(Player2);
            }
            else {
                copiazaPlayerCurent(Player1);
            }
        }
    }

    AfisareBoard(board);

    if (ConditiiCastig(board, 'X')) {
        printf("X a castigat! Felicitari!\n");
    } else if (ConditiiCastig(board, '0')) {
        printf("O a castigat! Felicitari\n");
    } else {
        printf("Egalitate! Incercam din nou?\n");
    }

    return 0;
}

