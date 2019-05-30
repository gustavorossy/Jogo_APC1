#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>

#define COLUNAS 150
#define LINHAS 38
char mapa[LINHAS][COLUNAS];


void desenha_mapa();
int getch();
int quests();

int main() {
    srand( (unsigned)time(NULL) );
    int i, j, y, x, resultado;
    char andar;

    desenha_mapa(mapa);
    y=(COLUNAS/2);
    x=(LINHAS/2);

    while (1) {
        mapa[x][y]='0';
        printf("\033[H\033[J");
        for(i=0; i<LINHAS; i++){
            for(j=0; j<COLUNAS; j++){
                printf("%c", mapa[i][j]);

            }
            printf("\n");
        }
        printf("Utilize as telas W A S D para se mover: ");
        andar=getch();
        if(andar=='w' || andar=='W'){//cima
            if(mapa[x-1][y]=='?'){
                resultado=quests();
                if(resultado==1){
                    mapa[x-1][y]=='!';
                }
            }
            else if(mapa[x-1][y]!='#'){
                mapa[x][y]=' ';
                x--;
                mapa[x][y]=='0';
            }
        }
        else if(andar=='a' || andar=='A'){//esquerda
            if(mapa[x][y-1]=='?'){
                if(quests()==1){
                    mapa[x][y-1]=='!';
                }
            }
            else if(mapa[x][y-1]!='#'){
                mapa[x][y]=' ';
                y--;
                mapa[x][y]='0';
            }
        }
        else if(andar=='d' || andar=='D'){//direita
            if(mapa[x][y+1]=='?'){
                if(quests()==1){
                    mapa[x][y+1]=='!';
                }
            }
            else if(mapa[x][y+1]!='#'){
                mapa[x][y]=' ';
                y++;
                mapa[x][y]='0';
            }
        }
        else if(andar=='s' || andar=='S'){//baixo
            if(mapa[x+1][y]=='?'){
                if(quests()==1){
                    mapa[x+1][y]=='!';
                }
            }
            else if(mapa[x+1][y]!='#'){
                mapa[x][y]=' ';
                x++;
                mapa[x][y]='0';
            }
        }
        printf("\033[H\033[J");
    } //END WHILE
    return 0;
}

void desenha_mapa(){
    int i, j, x, y;
    for(i=0; i<LINHAS; i++){
        for(j=0; j<COLUNAS; j++){
            if(j==0|| j==(COLUNAS-1)) mapa[i][j]=':';
            else if(i!=0 && i!=(LINHAS-1) && mapa[i][j]!='#') mapa[i][j]=' ';
            if(i==0 || i==(LINHAS-1)) mapa[i][j]='=';
        }
    }
    for(i=0;i<250;i++){ //arvores
        x=1+rand()%(LINHAS-2);
        y=1+rand()%(COLUNAS-2);
        mapa[x][y]='#';
    }
    for(i=0;i<30;i++){
        x=1+rand()%(LINHAS-2);
        y=1+rand()%(COLUNAS-2);
        if(mapa[x][y]!='#'){
            if(mapa[x+1][y]!='#' || mapa[x-1][y]!='#' || mapa[x][y+1]!='#' || mapa[x][y-1]!='#') mapa[x][y]='?';
        }
    }

}
int quests(){
    int a, i, result, x, y;
    a=1+rand%30;
    if(a==1){
        printf("Qual sera a saida do codigo a seguir?\n\n");
        printf("#include <stdio.h>\n\nint main()\n{\n  const int a = %i;\n  a++;\n  printf("%%d", a)\nreturn 0;");
    }
    return 1;
}

/* reads from keypress, doesn't echo */
int getch(void){
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
