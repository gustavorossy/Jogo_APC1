#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define COLUNAS 60
#define LINHAS 27


/* reads from keypress, doesn't echo */
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

int main() {
    int i, j, y=(COLUNAS/2), x=(LINHAS/2);
    char mapa[LINHAS][COLUNAS], andar;

    while (1) {
        printf("\033[H\033[J");
        for(i=0; i<LINHAS; i++){
            for(j=0; j<COLUNAS; j++){
                if(j==0|| j==(COLUNAS-1)) mapa[i][j]=':';
                else if(i!=0 || i!=(LINHAS-1)) mapa[i][j]=' ';
                if(i==0 || i==(LINHAS-1)) mapa[i][j]='=';

            }
        }
        mapa[x][y]='0';
        //printf("\nMAPA[%i][%i]= %c\n\n", x, y, mapa[x][y]);
        for(i=0; i<LINHAS; i++){
            for(j=0; j<COLUNAS; j++){
                printf("%c", mapa[i][j]);

            }
            printf("\n");
        }
        printf("Utilize as telas W A S D para se mover: ");
        andar=getch();
        if(andar=='w' || andar=='W'){//cima
            //printf("CIMA");
            mapa[x][y]=' ';
            x--;
            mapa[x][y]=='0';
        }
        else if(andar=='a' || andar=='A'){//esquerda
            //printf("ESQUERDA");
            mapa[x][y]=' ';
            y--;
            mapa[x][y]='0';
        }
        else if(andar=='d' || andar=='D'){//direita
            //printf("DIREITA");
            mapa[x][y]=' ';
            y++;
            mapa[x][y]='0';
        }
        else if(andar=='s' || andar=='S'){//baixo
            //printf("BAIXO");
            mapa[x][y]=' ';
            x++;
            mapa[x][y]='0';
        }
    } //END WHILE
    return 0;
}
