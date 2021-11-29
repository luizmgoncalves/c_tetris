#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <windows.h>
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

void blit(char matrix[LINES][COLUMNS+1], struct piece_model *piece){
    int i, j;

    for (i=0; i < PL; i++){
        for (j=0; j < PC-1 ; j++){
            if (piece->y+i>=LINES || piece->x+j>=COLUMNS || piece->y+i<0 || piece->x+j<0)
                continue ;
            
            if (piece->piece[i][j] == CL)
                matrix[piece->y+i][piece->x+j] = piece->piece[i][j];
        }
    }
}

void random_piece(struct piece_model *piece){
    int op;
    srand(time(NULL));
    op = rand()%5;
    switch (op)
    {
    case 0:
        fill_square(piece->piece);
        break;
    case 1:
        fill_line(piece->piece);
        break;
    case 2:
        fill_l(piece->piece);
        break;
    case 3:
        fill_p_stair(piece->piece);
        break;
    case 4:
        fill_p_triangle(piece->piece);
        break;
    }
    
    piece->x = 0, piece->y = 0;
}

void move_piece_on_board(char static_matrix[LINES][COLUMNS+1], struct piece_model *piece, int x, int y){
    int i, j;

    for (i=0; i < PL; i++){
        for (j=0; j < PC-1 ; j++){
            if(piece->y+i+y>=LINES &&  piece->piece[i][j] == CL){
                // is touching board bottom border
                blit(static_matrix, piece);
                random_piece(piece);
                return ;
            }
            if(piece->x+j+x>=COLUMNS &&  piece->piece[i][j] == CL){
                // is touching board right border
                x = 0;
            }
            if(piece->x+j+x<0){
                // is touching board left border
                x = 0;
            }
            if(piece->piece[i][j] == CL && static_matrix[piece->y+i+y][piece->x+j+x] == CL){
                if (y==1){
                    blit(static_matrix, piece);
                    random_piece(piece);
                    return ;
                }
                x = 0;
            }
        }
    }

    piece->y += y;
    piece->x += x;
}

void copy_matrix(char copy[LINES][COLUMNS+1], char matrix[LINES][COLUMNS+1]){
    int i, j;

    for (i=0; i < LINES; i++){
        for (j=0; j < COLUMNS+1 ; j++){
            matrix[i][j] = copy[i][j];
        }
    }
}

int main(){
    char matrix[LINES][COLUMNS+1];
    char running=1, changes=0;
    int op, frames;
    char static_matrix[LINES][COLUMNS+1];
    struct piece_model piece;

    fill_board(static_matrix, BG);

    copy_matrix(static_matrix, matrix);

    random_piece(&piece);
    piece.x = 0, piece.y = 0;

    for (;running; frames++, frames %= 300){
        copy_matrix(static_matrix, matrix);
        blit(matrix, &piece);
        if (frames==1 || changes){
            printf("%s\n\n", matrix);
            changes = 0;
        }
        
        if (frames==0){
            move_piece_on_board(static_matrix, &piece, 0, 1);
            changes = 1;
        }

        if(kbhit()){
            op = getch();
            switch (op)
            {
            case 'a':
                move_piece_on_board(static_matrix, &piece, -1, 0);
                changes = 1;
                break;
            case 'd':
                move_piece_on_board(static_matrix, &piece, 1, 0);
                changes = 1;
                break;
            case 'w':
                rotate(piece.piece);
                changes = 1;
                break;
            case 's':
                running = 0;
                break;
            default:
                break;
            }
        }

        Sleep(1);
        if (frames==0 || changes)
            system("cls");
    }


    return 0;
}
