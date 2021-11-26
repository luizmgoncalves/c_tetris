#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define COLUMNS 30
#define LINES 10
#define PL 4
#define PC 5
#define BG 'z'+54
#define CL 'z'+97

struct piece_model {
    int x;
    int y;
    char piece[PL][PC];
};

void fill_square(char piece[PL][PC]){
    int i, j;
    for (i=0; i<PL; i++){
        for(j=0; j<PC-1; j++) piece[i][j] = BG;
        piece[i][j] = '\n';
    }
    piece[--i][j] = '\0';

    piece[0][0] = CL;
    piece[0][1] = CL;
    piece[1][0] = CL;
    piece[1][1] = CL;
}

void fill_line(char piece[PL][PC]){
    int i, j;
    for (i=0; i<PL; i++){
        for(j=0; j<PC-1; j++) piece[i][j] = BG;
        piece[i][j] = '\n';
    }
    piece[--i][j] = '\0';

    piece[0][0] = CL;
    piece[1][0] = CL;
    piece[2][0] = CL;
    piece[3][0] = CL;
}

void fill_l(char piece[PL][PC]){
    int i, j;
    for (i=0; i<PL; i++){
        for(j=0; j<PC-1; j++) piece[i][j] = BG;
        piece[i][j] = '\n';
    }
    piece[--i][j] = '\0';

    piece[0][0] = CL;
    piece[1][0] = CL;
    piece[2][0] = CL;
    piece[2][1] = CL;
}

void fill_p_triangle(char piece[PL][PC]){
    int i, j;
    for (i=0; i<PL; i++){
        for(j=0; j<PC-1; j++) piece[i][j] = BG;
        piece[i][j] = '\n';
    }
    piece[--i][j] = '\0';

    piece[0][0] = CL;
    piece[1][0] = CL;
    piece[1][1] = CL;
    piece[2][0] = CL;
}

void fill_p_stair(char piece[PL][PC]){
    int i, j;
    for (i=0; i<PL; i++){
        for(j=0; j<PC-1; j++) piece[i][j] = BG;
        piece[i][j] = '\n';
    }
    piece[--i][j] = '\0';

    piece[0][0] = CL;
    piece[1][0] = CL;
    piece[1][1] = CL;
    piece[2][1] = CL;
}

struct piece_model* aloc_memory(){
    struct piece_model *memory = (struct piece_model*) malloc(sizeof(struct piece_model)*8);
    fill_square(memory->piece);
    fill_line((memory+1)->piece);
    fill_l((memory+2)->piece);
    fill_p_triangle((memory+3)->piece);
    fill_p_stair((memory+4)->piece);

    return memory;
};

void fill_board(char matrix[LINES][COLUMNS+1], char value){
    int i, j;

    for (i=0; i < LINES; i++){
        for (j=0; j < COLUMNS ; j++){
            matrix[i][j] = 'z'+54;
        }
        matrix[i][j] = '\n';
    }
    matrix[--i][j] = '\0';
}

void rotate(char piece[PL][PC]){
    char prov[PL][PC];
    int i, j;

    for(i=0; i<PL; i++){
        for (j=0; j<PC-1; j++) 
            prov[j][i] = piece[i][j];
    }

    for(i=0; i<PL; i++){
        for (j=0; j<PC-1; j++)
            piece[i][j] = prov[i][j];
    }
}

void blit(char matrix[LINES][COLUMNS+1], char piece[PL][PC], int x, int y){
    int i, j;

    for (i=0; i < LINES; i++){
        for (j=0; j < COLUMNS ; j++){
            if(i>=y && i< y+PL && j >= x && j < x+PC-1) 
                matrix[i][j] = piece[i-y][j-x];
        }
    }
}

int main(){
    char matrix[LINES][COLUMNS+1];
    struct piece_model *pieces, piece1;

    fill_board(matrix, 'z'+54);

    pieces = aloc_memory();

    piece1 = pieces[3];

    rotate(piece1.piece);
    rotate(piece1.piece);
    rotate(piece1.piece);

    blit(matrix, piece1.piece, 0, 0);

    printf("%s\n", matrix);

    printf("%s\n\n", pieces->piece);
    printf("%s\n\n", pieces[1].piece);
    printf("%s\n\n", pieces[2].piece);
    printf("%s\n\n", pieces[3].piece);
    printf("%s\n\n", pieces[4].piece);

    return 0;
}