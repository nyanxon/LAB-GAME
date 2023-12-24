#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10
#define MINES 15

void papan(char board[][SIZE], int showMines); // Mendisplay papan
void bom(char board[][SIZE]); // Memasang bom
int penunjukbom(char board[][SIZE], int row, int col); // Menghitung bom yang berada di dekat sel yang dipilih (Penunjuk bom)

int main() {
    char board[SIZE][SIZE];
    int row, col;
    int i,j;
    int minesLeft = MINES;

    srand(time(NULL));

    for (i = 0; i < SIZE; i++) { // Membuat papan 10 x 10 (SIZE = 10)
        for (j = 0; j < SIZE; j++) {
            board[i][j] = '#';
        }
    }

    bom(board); /// Memasang bom

    while (minesLeft > 0) {
        papan(board, 0);
        printf("Masukkan input (Contoh : 0 0): "); 
        scanf("%d %d", &row, &col); // Input baris dan kolom yang ingin dipilih

        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
            printf("Input yang dimasukkan salah, silahkan memasukkan input kembali\n");
            continue; // Bila format input yang dipilih salah maka akan diminta untuk memasukkan input kembali
        }

        if (board[row][col] == 'X') {
            printf("Game Over! Kamu menyentuh bom\n");
            papan(board, 1); 
            break; // Bila menyentuh bom maka akan game over dan menampilkan letak bom yang tersisa
        }

        int penunjuk = penunjukbom(board, row, col); // Memanggil fungsi dan dimasukkan ke variabel adjacentMines
        board[row][col] = (char)(penunjuk + '0');  // Memasukkan jumlah bom yang ada di sekitar (penunjuk bom)

        if (penunjuk == 0) {
            for (i = row - 1; i <= row + 1; i++) {
                for (j = col - 1; j <= col + 1; j++) {
                    if (i >= 0 && i < SIZE && j >= 0 && j < SIZE && board[i][j] == '#') {
                        int adj = penunjukbom(board, i, j);
                        board[i][j] = (adj == 0) ? ' ' : (char)(adj + '0');
                    }
                }
            }
        } // Bila penunjuk bom menunjukkan 0 yang berdekatan akan menunjukkan sel kosong

        minesLeft--; // Mengurangi counter bom yang tersisa

        if (minesLeft == 0) {
            printf("Selamat kamu menang\n");
            papan(board, 1);
            break; //Bila semua bom telah ditemukan, maka game telah dimenangkan
        }
    }

    return 0;
}

void papan(char board[][SIZE], int showMines) {
    printf("\n  ");
    int i,j;
    for (i = 0; i < SIZE; i++) {
        printf("%d ", i);
    }
    printf("\n");

    for (i = 0; i < SIZE; i++) {
        printf("%d ", i);
        for (j = 0; j < SIZE; j++) {
            if (board[i][j] == 'X' && !showMines) {
                printf("# ");
            } else {
                printf("%c ", board[i][j]);
            }
        }
        printf("\n");
    }
}

void bom(char board[][SIZE]) {
	int i;
    for (i = 0; i < MINES; i++) {
        int row, col;
        do {
            row = rand() % SIZE;
            col = rand() % SIZE;
        } while (board[row][col] == 'X');
        board[row][col] = 'X';
    }
}

int penunjukbom(char board[][SIZE], int row, int col) {
    int count = 0;
    int i,j;
    for (i = row - 1; i <= row + 1; i++) {
        for (j = col - 1; j <= col + 1; j++) {
            if (i >= 0 && i < SIZE && j >= 0 && j < SIZE && board[i][j] == 'X') {
                count++;
            }
        }
    }
    return count;
}


