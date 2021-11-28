#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define COLUMNS 30
#define LINES 10
#define PL 4
#define PC 5
#define BG -80 // 'z'+54 or backgorund ascii character "░"
#define CL -37 // 'z'+97 or filled block ascii character "█"

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
        for(j=0; j<PC-1; j++){
            piece[i][j] =  BG;
        }
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
            matrix[i][j] = value;
        }
        matrix[i][j] = '\n';
    }
    matrix[--i][j] = '\0';
}

void left_piece(char piece[PL][PC]){
    int i, j;

    for(i=0; i<PL; i++){
        for (j=1; j<PC-1; j++) {
            piece[i][j-1] = piece[i][j];
        }
    }

    j--;

    for (i=0; i<PL; i++) 
        piece[i][j] = BG;
    
}

void up_piece(char piece[PL][PC]){
    int i, j;

    for(i=1; i<PL; i++){
        for (j=0; j<PC-1; j++) {
            piece[i-1][j] = piece[i][j];
        }
    }

    i--;

    for (j=0; j<PC-1; j++) 
        piece[i][j] = BG;
    
}

void normalize(char piece[PL][PC]){
    int to_up, to_left;
    int i, j;


    while (1){
        to_up = 1, to_left = 1;
        for(i=0; i<PL; i++){ 
            if (piece[i][0] != BG) to_left=0;
        }

        for (j=0; j<PC-1; j++){
                if (piece[0][j] != BG){ 
                    to_up=0;
                }
        }

        if (to_up) up_piece(piece);
        if (to_left) left_piece(piece);
        if (!(to_up||to_left)) break;
    }

}

void rotate(char piece[PL][PC]){
    char prov[PL][PC];
    int i, j;

    for(i=0; i<PL; i++){
        for (j=0; j<PC-1; j++) {
            prov[PC-1-1-j][i] = piece[i][j];
        }
    }

    for(i=0; i<PL; i++){
        for (j=0; j<PC-1; j++)
            piece[i][j] = prov[i][j];
    }

    normalize(piece);
}

void blit(char matrix[LINES][COLUMNS+1], char piece[PL][PC], int x, int y){
    int i, j;

    for (i=0; i < PL; i++){
        for (j=0; j < PC-1 ; j++){
            matrix[y+i][x+j] = piece[i][j];
        }
    }
}

int main(){
    char matrix[LINES][COLUMNS+1];
    struct piece_model *pieces, piece1;

    fill_board(matrix, BG);

    pieces = aloc_memory();


    printf("%s\n", matrix);

    printf("%s\n\n", pieces[3].piece);
    rotate(pieces[3].piece);
    printf("%s\n\n", pieces[3].piece);
    rotate(pieces[3].piece);
    printf("%s\n\n", pieces[3].piece);
    rotate(pieces[3].piece);
    printf("%s\n\n", pieces[3].piece);
    rotate(pieces[3].piece);

    return 0;
}