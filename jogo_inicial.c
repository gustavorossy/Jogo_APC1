#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define LARGURA 60
#define ALTURA 27


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
    int i, j, x=5, y=5;
    char mapa [LARGURA][ALTURA], andar;

    while (1) {
        for(i=0; i<ALTURA; i++){
            for(j=0; j<LARGURA; j++){
                if(j<1 || j==(ALTURA-1)) mapa[i][j]=':';
                if(i<1 || i==(LARGURA-1)) mapa[i][j]='=';
                if(mapa[i][j]!='=' && mapa[i][j]!=':' && mapa[i][j]!='#') mapa[i][j]=' ';
            }
        }
        system("clear");
        mapa[x][y]='0';
        printf("\n");
        for(i=0; i<ALTURA; i++){
            for(j=0; j<LARGURA; j++){
                printf("%c", mapa[i][j]);
            }
            printf("\n");
        }
        printf("Utilize as setas para se mover: ");
        andar=getch();
        if(andar=='w' || andar=='W'){//cima
            printf("CIMA");
            mapa[x][y]=' ';
            x--;
            mapa[x][y]=='0';
        }
        else if(andar=='a' || andar=='A'){//esquerda
            printf("ESQUERDA");
            mapa[x][y]=' ';
            y--;
            mapa[x][y]='0';
        }
        else if(andar=='d' || andar=='D'){//direita
            printf("DIREITA");
            mapa[x][y]=' ';
            y++;
            mapa[x][y]='0';
        }
        else if(andar=='s' || andar=='S'){//baixo
            printf("BAIXO");
            mapa[x][y]=' ';
            x++;
            mapa[x][y]='0';
        }

    }
    return 0;
}

/*for(i=0; i<ALTURA; i++){
    for(j=0; j<LARGURA; j++){
        if(j<1 || j==(ALTURA-1)) mapa[i][j]=':';
        if(i<1 || i==(LARGURA-1)) mapa[i][j]='=';
        if(mapa[i][j]!='=' && mapa[i][j]!=':' && mapa[i][j]!='#') mapa[i][j]=' ';
    }
}*/
