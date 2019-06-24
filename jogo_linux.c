#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define COLUNAS 150
#define LINHAS 38
char mapa[LINHAS][COLUNAS];
typedef struct{
    char nome[16];
    int vidas;
} dados;

dados personagem;

int getch();
void introducao();
void desenha_mapa();
void printa_mapa();
int quests();
void resposta_certa();
void resposta_errada();

int main() {
    srand( (unsigned)time(NULL) );
    int i, j, y, x, resultado;
    char andar;


    y=(COLUNAS/2);
    x=(LINHAS/2);
    mapa[x][y]='0';
    desenha_mapa();
    //introducao();
    while (1) {
        mapa[x][y]='0';

        system("clear");
        printa_mapa();
        printf("Utilize as telas W A S D para se mover: ");
        fflush(stdin);
        andar=getch();
        if(andar=='w' || andar=='W'){//cima
            if(mapa[x-1][y]=='?'){
                resultado=quests();
                if(resultado==1){
                    mapa[x-1][y]='!';
                }
            }
            else if(mapa[x-1][y]==' '){
                mapa[x][y]=' ';
                x--;
                mapa[x][y]='0';
            }
        }
        else if(andar=='a' || andar=='A'){//esquerda
            if(mapa[x][y-1]=='?'){
                resultado=quests();
                if(resultado==1){
                    mapa[x][y-1]='!';
                }
            }
            else if(mapa[x][y-1]==' '){
                mapa[x][y]=' ';
                y--;
                mapa[x][y]='0';
            }
        }
        else if(andar=='d' || andar=='D'){//direita
            if(mapa[x][y+1]=='?'){
                resultado=quests();
                if(resultado==1){
                    mapa[x][y+1]='!';
                }
            }
            else if(mapa[x][y+1]==' '){
                mapa[x][y]=' ';
                y++;
                mapa[x][y]='0';
            }
        }
        else if(andar=='s' || andar=='S'){//baixo
            if(mapa[x+1][y]=='?'){
                resultado=quests();
                if(resultado==1){
                    mapa[x+1][y]='!';
                }
            }
            else if(mapa[x+1][y]==' '){
                mapa[x][y]=' ';
                x++;
                mapa[x][y]='0';
            }
        }
        system("clear");
        system("clear");
    } //END WHILE
    return 0;
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

void introducao(){
    int i;
    printf("Olá... como você veio parar aqui?\n");
    sleep(3);
    printf("Não sabe? É... Os outros não sabiam também.\n");
    sleep(3);
    printf("O importante é: agora você está aqui e, acredite, sair não será uma tarefa tão fácil.\n");
    sleep(3);
    printf("Chamamos aqui de Catalost, é uma floresta onde muitos que entram, não conseguem sair. Mas acredito que você será vitorioso.\n");
    sleep(5);
    printf("Vamos começar então. O quanto antes você partir na sua jornada, mais cedo sairá, ou não.\n");
    sleep(3);
    printf("Tudo dependerá de você.\n");
    sleep(3);
    printa_mapa();
    printf("O que você está vendo agora é o mapa de Catalost. Estamos ali, bem no centro...\n");
    sleep(10);
    printa_mapa();
    printf("Agora, vêm a parte difícil. Ao redor do mapa, repare que existem vários pontos de interrogação.\nEsses pontos de interrogação serão sua saída. Chamamos eles de goblins.\n");
    sleep(10);
    printf("Cada um deles possui um fragmento de chave, que você precisará para sair daqui.\n");
    sleep(3);
    printf("Para conseguir que eles te entreguem os fragmentos, você terá que responder corretamente uma pergunta que cada um lhe fará.\n");
    sleep(5);
    printa_mapa();
    printf("Só tem um problema...\n");
    sleep(3);
    printf("Por algum motivo desconhecido, eles tendem a fazer perguntas relacionadas à programação de computadores...\n");
    sleep(5);
    printf("Loucura, não?\n");
    sleep(3);
    printf("São criaturas traiçoeiras, por isso tome cuidado. Eles tentarão fazer de tudo para te enganar.\n");
    sleep(3);
    printf("Por último, mas não menos importante, você possui uma barra de vida, a cada resposta certa, você receberá uma\n vida extra, e a cada resposta errada, será tirada uma, portanto... Tome cuidado.\n");
    sleep(5);
    printf("Acho que lhe expliquei tudo. Agora, é com você. Boa sorte na sua jornada!\n");
    sleep(2);
    printf("...");
    sleep(3);
    printf("\nAh, quase me esqueci! Não nos apresentamos!! Qual é o seu nome?\nDigite seu nome: ");
    scanf("%s", personagem.nome);
    printf("\nMuito prazer %s, me chamo Greybeard! Agora, vá! Espero que nos encontremos outra vez!\n", personagem.nome);
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

void printa_mapa(){
    int i, j;
    system("clear");
    //printf("\033[H\033[J");
    for(i=0; i<LINHAS; i++){
        for(j=0; j<COLUNAS; j++){
            printf("%c", mapa[i][j]);

        }
        printf("\n");
    }
}

int quests(){
    srand( (unsigned)time(NULL) );
    int a, i, result=0, x, y;
    char c;
    //a=rand()%3;
    a=5;
    if(a==0){
        printf("\n\nQual sera a saida do codigo a seguir?\n\n");
        printf("#include <stdio.h>\n\nint main()\n{\n  const int a = 5;\n  a++;\n  printf(\"%%d\", a)\n  return 0;\n}\n");
        printf("A) 5\nB) 6\nC) Runtime error\nD) Compile error\n");
        printf("Resposta: ");
        scanf("%c", &c);

        if(c=='D' || c=='d'){
            resposta_certa();
            sleep(6);
            //vida(+1);
            result=1;
        }
        else {
            resposta_errada();
            sleep(6);
            //vida(-1);
            result=0;
        }
    }
    else if(a==1){
        printf("\n\nO que a linha a seguir define?\n\n");
        printf("int *ptr[10];\n\n");
        printf("A) ptr é um ponteiro para um vetor inteiro de 10 ponteiros\n");
        printf("B) ptr é um vetor de 10 ponteiros para inteiros\n");
        printf("C) ptr é um ponteiro para um vetor inteiro de 10 posições\n");
        printf("D) nenhuma das anteriores\n");
        printf("Resposta: ");
        scanf("%c", &c);

        if(c=='B' || c=='b'){
            resposta_certa();
            sleep(6);
            //vida(+1);
            result=1;
        }
        else{
            resposta_errada();
            sleep(6);
            //vida(-1);
            result=0;
        }
    }
    else if(a==2){
        printf("\n\nQual será a saída do programa a seguir:\n\n");
        printf("#include <stdio.h>\n\nint main(){\n  char s[]=\"hello\", t[]=\"hello\";\n\n");
        printf("  if(s==t){\n    printf(\"strings iguais\");\n  }\n}\n\n");
        printf("A) strings iguais\n");
        printf("B) Compile error\n");
        printf("C) Não haverá nenhuma saída\n");
        printf("D) nenhuma das anteriores\n");
        printf("Resposta: ");
        scanf("%c", &c);

        if(c=='c' || c=='C'){
            resposta_certa();
            sleep(6);
            //vida(+1);
            result=1;
        }
        else{
            resposta_errada();
            sleep(6);
            //vida(-1);
            result=0;
        }
    }
    else if(a==3){
        printf("\n\nQual sera a saida do codigo a seguir:\n\n");
        printf("#include <stdio.h>\n\nint main(){\n  int a=5, b=3, c=4;\n\n  printf(\"a=%%d, b=%%d\", a, b, c)\n  return 0;\n}\n");
        printf("\nA) a=5, b=3\nB) a=5, b=3, c=4\nC) a=5, b=3 4\nD) Compile error\n");
        printf("Resposta: ");
        scanf("%c", &c);
        if(c=='a' || c=='A'){
            resposta_certa();
            sleep(6);
            //vida(+1);
            result=1;
        }
        else{
            resposta_errada();
            sleep(6);
            //vida(-1);
            result=0;
        }
    }
    else if(a==4){
        printf("\n\nQual sera a saida do codigo a seguir:\n\n");
        printf("#include<stdio.h>\n\nint main() {\n  int a = 1.3;\n  float b = 1.0;\n  double c;\n  c = a + b;\n  printf(\"%%.2lf\", c);\n  return 0;\n}\n\n");
        printf("A) 2.30\nB) 2.3\nC) Compile error\nD) 2.0\n");
        printf("Resposta: ");
        scanf("%c", &c);
        if(c=='d' || c=='D'){
            resposta_certa();
            sleep(6);
            //vida(+1);
            result=1;
        }
        else{
            resposta_errada();
            sleep(6);
            //vida(-1);
            result=0;
        }
    }
    else if(a==5){
        printf("\n\nQual sera a saida do programa a seguir: \n\n");
        printf("#include <stdio.h>\n\nint main() {\n  char c='A'+255;\n\n  printf(\"%%c\", c);\n  return 0;\n}\n");
        printf("\nA) A\nB) B\nC) Overflow error at runtime\nCompile error\n");
        printf("Resposta: ");
        scanf("%c", &c);
        if(c=='c' || c=='C'){
            resposta_certa();
            sleep(6);
            //vida(+1);
            result=1;
        }
        else{
            resposta_errada();
            sleep(6);
            //vida(-1);
            result=0;
        }
    }
    else if(a==6){
        printf("\n\nQual será a saída do programa a seguir?\n\n");
        printf("\n#include<stdio.h>\n\nint main(){\n  short unsigned int i=0;\n  printf(\"%%u\", i--);\n  return 0;\n}");
        printf("A) 0\nB) Compile error\nC) 65535\nD) 32767\n");
        printf("Resposta: ");
        scanf("%c", &c);
        if(c=='a' || c=='A'){
            resposta_certa();
            sleep(6);
            //vida(+1);
            result=1;
        }
        else{
            resposta_errada();
            sleep(6);
            //vida(-1);
            result=0;
        }
    }
    else if(a==7){
        
    }
    return result;
}

void resposta_certa(){
    int i;
    srand( (unsigned)time(NULL) );
    i=rand()%6;
    if(i==0) printf("Hmmm... Pelo visto sua resposta está certa! Pegue mais uma vida, mas não se acostume!\n");
    if(i==1) printf("O quê? Você acertou essa? Impossível!! Hmpf, tome sua vida!\n");
    if(i==2) printf("Não se ache muito!! Essa tava fácil!! Tome uma vida.\n");
    if(i==3) printf("Parabéns... Eu acho. Você ganhou mais uma vida.\n");
    if(i==4) printf("Cá entre nós...Você colou nessa né?! Mas tudo bem, leve essa vida.\n");
    if(i==5) printf("Você acertou. Grande coisa! Pegue essa vida e suma!\n");
}

void resposta_errada(){
    int i;
    srand( (unsigned)time(NULL) );
    i=rand()%6;
    if(i==0) printf("Hahaha não acredito que você errou essa! Me dê essa vida.\n");
    if(i==1) printf("Você perdeu uma vida por causa disso? Lamentável.\n");
    if(i==2) printf("É... Essa até que não estava tão fácil, mas mesmo assim! Menos uma vida!!\n");
    if(i==3) printf("Parabéns! Você acabou de perder uma vida! Hahaha.\n");
    if(i==4) printf("Acho melhor você arrumar umas colas, já que está tão dificil assim. Ah, quase me esqueço da vida!\n");
    if(i==5) printf("Errrrou!\n");
}

