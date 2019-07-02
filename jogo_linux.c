#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

// DEFINIÇÃO DAS CONSTANTES
#define COLUNAS 146
#define LINHAS 38

// VARIÁVEIS E ESTRUTURAS
char mapa[LINHAS][COLUNAS], chave[20], verifica_chave[20], cont_chave=0;
typedef struct{
    char nome[16];
    int vidas;
} dados;
dados personagem;
int *quests_respondidas, num=0, loop=0, dificuldade, cod, vidas_boss;

// DECLARAÇÃO DAS FUNÇÕES QUE SERÃO USADAS
int getch();
void inicio();
void introducao();
void desenha_mapa();
void boss();
void printa_mapa();
int quests();
void resposta_certa();
void resposta_errada();
void treme();
int quest_boss();
void morreu();
void grey();
void portal();


int main() {
    inicio();
    quests_respondidas=(int *)malloc(sizeof(int));
    srand( (unsigned)time(NULL) );
    int i, j, y, x, resultado;
    char andar;
    personagem.vidas=5;

    y=(COLUNAS/2);
    x=(LINHAS/2);
    desenha_mapa();
    mapa[x][y]='0';
    mapa[x-1][y]='*';
    introducao();
    mapa[x-1][y]='*';
    while (1) {
        if(personagem.vidas<1){
            morreu();
            return 0;
        }
        mapa[x][y]='0';

        system("clear");
        printa_mapa();


        printf("\nUtilize as telas W A S D para se mover: ");
        andar=getch();
        if(andar=='w' || andar=='W' || andar==27){//cima
            if(mapa[x-1][y]=='?'){
                resultado=quests();
                if(resultado==1){
                    mapa[x-1][y]='!';
                    printf("Fragmento: %c\n", chave[cont_chave]);
                    cont_chave++;
                    sleep(3);
                }
            }
            else if(mapa[x-1][y]=='*'){
                quest_boss();
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
                    printf("Fragmento: %c\n", chave[cont_chave]);
                    cont_chave++;
                    sleep(3);
                }
            }
            else if(mapa[x][y-1]=='&'){
                if(quest_boss()==1){
                    mapa[x][y-1]=' ';
                }
                else{
                    morreu();
                    return 0;
                }
            }
            else if(mapa[x][y-1]=='@'){
                mapa[x][y+1]='*';
                printa_mapa();
                grey();
                portal();
                return 0;
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
                    printf("Fragmento: %c\n", chave[cont_chave]);
                    cont_chave++;
                    sleep(3);
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
                    printf("Fragmento: %c\n", chave[cont_chave]);
                    cont_chave++;
                    sleep(3);
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

void inicio(){
    char c;
    printf("Pressione F11 para deixar em tela cheia e melhorar sua experiência.\nApós isso, pressione ENTER para continuar...");
    c=getchar();
    system("clear");
    printf("###############   ###############   ###############   ###############   ##                ###############   ###############   ###############\n");
    usleep(200000);
    printf("###############   ###############   ###############   ###############   ##                ###############   ###############   ###############\n");
    usleep(200000);
    printf("##                ##           ##         ##          ##           ##   ##                ##           ##   ##                      ##\n");
    usleep(200000);
    printf("##                ##           ##         ##          ##           ##   ##                ##           ##   ##                      ##\n");
    usleep(200000);
    printf("##                ##           ##         ##          ##           ##   ##                ##           ##   ##                      ##\n");
    usleep(200000);
    printf("##                ##           ##         ##          ##           ##   ##                ##           ##   ###############         ##\n");
    usleep(200000);
    printf("##                ###############         ##          ###############   ##                ##           ##   ###############         ##\n");
    usleep(200000);
    printf("##                ###############         ##          ###############   ##                ##           ##                ##         ##\n");
    usleep(200000);
    printf("##                ##           ##         ##          ##           ##   ##                ##           ##                ##         ##\n");
    usleep(200000);
    printf("###############   ##           ##         ##          ##           ##   ###############   ###############   ###############         ##\n");
    usleep(200000);
    printf("###############   ##           ##         ##          ##           ##   ###############   ###############   ###############         ##\n");
    usleep(300000);
    printf("\n\n\n\nBem vindo ao CATALOST! A seguir, digite a dificuldade desejada: \n1) Facil\n2) Medio\n3) Dificil\nNote que a dificuldade selecionada afetará apenas o número de questões a serem respondidas.\nOpcão: ");
    scanf("%i", &dificuldade);
    if(dificuldade==1){
        dificuldade=6;
        strcpy(chave, "fwwfdx");
        strcpy(verifica_chave, "arrays");
        vidas_boss=4;
        cod=5;
    }
    else if(dificuldade==2) {
        dificuldade=10;
        strcpy(chave, "bnlotszbzn");
        strcpy(verifica_chave, "computacao");
        vidas_boss=6;
        cod=-1;
    }
    else if(dificuldade==3) {
        dificuldade=18;
        strcpy(chave, "ygxfupuyqzeuazmx");
        strcpy(verifica_chave, "multidimensional");
        vidas_boss=8;
        cod=12;
    }
}

void introducao(){
    int i;
    system("clear");
    printf("Hey, você finalmente acordou!\n");
    sleep(5);
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
    printf("O que você está vendo agora é o mapa de Catalost. Estamos ali, bem no centro! Eu( * ) e você ( 0 )...\n");
    sleep(10);
    printa_mapa();
    printf("Agora, vêm a parte difícil. Ao redor do mapa, repare que existem vários pontos de interrogação.\nEsses pontos de interrogação serão sua saída. Chamamos eles de goblins.\n");
    sleep(10);
    printf("Cada um deles possui um fragmento que você precisará para sair daqui.\n");
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
    sleep(7);
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
    i=0;
    while(i<dificuldade){
        x=1+rand()%(LINHAS-2);
        y=1+rand()%(COLUNAS-2);
        if(mapa[x][y]!='#'){
            if(mapa[x+1][y]!='#' || mapa[x-1][y]!='#' || mapa[x][y+1]!='#' || mapa[x][y-1]!='#') mapa[x][y]='?';
            i++;
        }
    }


}

void boss(){

    int x, y, i, j, verifica=0;
    y=15+rand()%100;
    x=5+rand()%20;
    printf("\n\n%i %i\n\n", x, y);

    for(i=x;i<=x+9;i++){
        for(j=y;j<=y+15;j++){
            if(mapa[i][j]=='0') verifica=1;
        }
    }

    if(verifica==1) boss();
    else{
        for(i=x;i<=(x+9);i++){
            for(j=y;j<=(y+15);j++){
                if(i==x){
                    if(j<y+11) mapa[i+1][j+1]='#';
                    else mapa[i+1][j+1]=' ';
                }
                if(i==x+1){
                    if(j<y+11) mapa[i+1][j+1]='#';
                    else mapa[i+1][j+1]=' ';
                }
                if(i==x+2){
                    if(j<y+2) mapa[i+1][j+1]='#';
                    if(j>=y+2 && j<y+8) mapa[i+1][j+1]=' ';
                    if(j>=y+8) mapa[i+1][j+1]='#';
                }
                if(i==x+3){
                    if(j<y+2) mapa[i+1][j+1]='#';
                    if(j>=y+2 && j<y+8) mapa[i+1][j+1]=' ';
                    if(j>=y+8) mapa[i+1][j+1]='#';
                }
                if(i==x+4){
                    if(j==y+0) mapa[i+1][j+1]='#';
                    if(j==y+1) mapa[i+1][j+1]='@';
                    if(j>=y+2 && j<y+8) mapa[i+1][j+1]=' ';
                    if(j==y+8) mapa[i+1][j+1]='&';
                    if(j>y+8) mapa[i+1][j+1]=' ';
                }
                if(i==x+5){
                    if(j<y+2) mapa[i+1][j+1]='#';
                    if(j>=y+2 && j<y+8) mapa[i+1][j+1]=' ';
                    if(j>=y+8) mapa[i+1][j+1]='#';
                }
                if(i==x+6){
                    if(j<y+2) mapa[i+1][j+1]='#';
                    if(j>=y+2 && j<y+8) mapa[i+1][j+1]=' ';
                    if(j>=y+8) mapa[i+1][j+1]='#';
                }
                if(i==x+7){
                    if(j<y+11) mapa[i+1][j+1]='#';
                    else mapa[i+1][j+1]=' ';
                }
                if(i==x+8){
                    if(j<y+11) mapa[i+1][j+1]='#';
                    else mapa[i+1][j+1]=' ';
                }
            }
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
    printf("Vidas: ");
    for(i=0;i<personagem.vidas;i++){
        printf("♥ ");
    }
    if(cont_chave>0){
        printf("\nFragmentos: ");
        for(i=0;i<cont_chave; i++){
            printf("%c", chave[i]);
        }
    }
    printf("\n");
}

int quests(){
    srand( (unsigned)time(NULL) );
    int a, i, j, k, result=0, x, y, verifica=0;
    char c;
    a=rand()%(dificuldade-1);
    //a=5;
    if(num>0) {
        for(i=0;i<num;i++){
            if(quests_respondidas[i]==a) {
                if(loop<10){
                    loop++;
                    return quests();
                }
                else{
                    loop=0;
                    for(j=0, a=0;j<num;j++){
                        verifica=0;
                        for(k=0;k<num;k++){
                            if(a==quests_respondidas[k]) verifica=1;
                        }
                        if(verifica==1) a++;
                        else break;
                    }
                }
            }
        }
    }


    if(a==0){
        printf("\n\nQual sera a saida do codigo a seguir?\n\n");
        printf("#include <stdio.h>\n\nint main()\n{\n  const int a = 5;\n  a++;\n  printf(\"%%d\", a)\n  return 0;\n}\n");
        printf("A) 5\nB) 6\nC) Runtime error\nD) Compile error\n");
        printf("Resposta: ");
        scanf("%c", &c);

        if(c=='D' || c=='d'){
            resposta_certa();
            personagem.vidas++;
            sleep(6);
            result=1;
            if(num==0)quests_respondidas[num]=a;
            else{
                quests_respondidas=(int *) realloc(quests_respondidas, sizeof(int)*num+1);
                quests_respondidas[num]=a;
            }
            num++;

        }
        else {
            resposta_errada();
            personagem.vidas--;
            sleep(6);

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
            personagem.vidas++;
            result=1;
            if(num==0)quests_respondidas[num]=a;
            else{
                quests_respondidas=(int *) realloc(quests_respondidas, sizeof(int)*num+1);
                quests_respondidas[num]=a;
            }
            num++;
        }
        else{
            resposta_errada();
            personagem.vidas--;
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
            personagem.vidas++;
            sleep(6);
            result=1;
            if(num==0)quests_respondidas[num]=a;
            else{
                quests_respondidas=(int *) realloc(quests_respondidas, sizeof(int)*num+1);
                quests_respondidas[num]=a;
            }
            num++;
        }
        else{
            resposta_errada();
            personagem.vidas--;
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
            personagem.vidas++;
            sleep(6);
            result=1;
            if(num==0)quests_respondidas[num]=a;
            else{
                quests_respondidas=(int *) realloc(quests_respondidas, sizeof(int)*num+1);
                quests_respondidas[num]=a;
            }
            num++;
        }
        else{
            resposta_errada();
            personagem.vidas--;
            sleep(6);
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
            personagem.vidas++;
            sleep(6);
            result=1;
            if(num==0)quests_respondidas[num]=a;
            else{
                quests_respondidas=(int *) realloc(quests_respondidas, sizeof(int)*num+1);
                quests_respondidas[num]=a;
            }
            num++;

        }
        else{
            resposta_errada();
            personagem.vidas++;
            sleep(6);
            result=0;
        }
    }
    else if(a==5){
        printf("\n\nQual sera a saida do programa a seguir: \n\n");
        printf("#include <stdio.h>\n\nint main() {\n  char c='A'+255;\n\n  printf(\"%%c\", c);\n  return 0;\n}\n");
        printf("\nA) A\nB) B\nC) Overflow error at runtime\nD) Compile error\n");
        printf("Resposta: ");
        scanf("%c", &c);
        if(c=='c' || c=='C'){
            resposta_certa();
            personagem.vidas++;
            sleep(6);
            result=1;
            if(num==0)quests_respondidas[num]=a;
            else{
                quests_respondidas=(int *) realloc(quests_respondidas, sizeof(int)*num+1);
                quests_respondidas[num]=a;
            }
            num++;
        }
        else{
            resposta_errada();
            personagem.vidas--;
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
            personagem.vidas++;
            sleep(6);
            result=1;
            if(num==0)quests_respondidas[num]=a;
            else{
                quests_respondidas=(int *) realloc(quests_respondidas, sizeof(int)*num+1);
                quests_respondidas[num]=a;
            }
            num++;
        }
        else{
            resposta_errada();
            personagem.vidas--;
            sleep(6);
            result=0;
        }
    }
    else if(a==7){
        printf("\n\nQual será a saída do codigo a seguir:\n\n");
        printf("#include <stdio.h>\n\nint main(){\n    short unsigned int i=0;\n    printf(\"%%u\", i--);\n    return 0;\n}\n");
        printf("A) 0\nB) Compile error\nC) 65535\nD) -1\nResposta: ");
        scanf("%c", &c);
        if(c=='a' || c=='A'){
            resposta_certa();
            personagem.vidas++;
            sleep(6);
            result=1;
            if(num==0)quests_respondidas[num]=a;
            else{
                quests_respondidas=(int *) realloc(quests_respondidas, sizeof(int)*num+1);
                quests_respondidas[num]=a;
            }
            num++;
        }
        else{
            resposta_errada();
            personagem.vidas--;
            sleep(6);
            result=0;
        }
    }
    else if(a==8){
        printf("\n\nQual sua opnião a respeito da seguinte linha: \n");
        printf("\nsigned int *p=(int*)malloc(sizeof(unsigned int));\n");
        printf("\nA) Casting inapropriado\nB) Incorrerá em runtime error\nC) A memoria será alocada mas não terá o mesmo tamanho de um signed int\nD) Não há problemas com a declaração\nResposta: ");
        scanf("%c", &c);
        if(c=='c' || c=='C'){
            resposta_certa();
            personagem.vidas++;
            sleep(6);
            result=1;
            if(num==0)quests_respondidas[num]=a;
            else{
                quests_respondidas=(int *) realloc(quests_respondidas, sizeof(int)*num+1);
                quests_respondidas[num]=a;
            }
            num++;
        }
        else{
            resposta_errada();
            personagem.vidas--;
            sleep(6);
            result=0;
        }
    }
    else if(a==9){
        printf("\n\nint x = ~1;\nQual o valor de 'x'?\n");
        printf("A) 1\nB) 2\nC) -1\nD) -2\nResposta: ");
        scanf("%c", &c);
        if(c=='d' || c=='D'){
            resposta_certa();
            personagem.vidas++;
            sleep(6);
            result=1;
            if(num==0)quests_respondidas[num]=a;
            else{
                quests_respondidas=(int *) realloc(quests_respondidas, sizeof(int)*num+1);
                quests_respondidas[num]=a;
            }
            num++;
        }
        else{
            resposta_errada();
            personagem.vidas--;
            sleep(6);
            result=0;
        }
    }
    else if(a==10){
        printf("\n\nQual será a saida?\n");
        printf("int main(){\n    int *p = 15;\n    printf(\"%%d\", *p);\n    return 0;\n}\n");
        printf("A) 15\nB) Lixo de memória\nC) Runtime error\nD) Compile error\nResposta: ");
        scanf("%c", &c);
        if(c=='b' || c=='B'){
            resposta_certa();
            personagem.vidas++;
            sleep(6);
            result=1;
            if(num==0)quests_respondidas[num]=a;
            else{
                quests_respondidas=(int *) realloc(quests_respondidas, sizeof(int)*num+1);
                quests_respondidas[num]=a;
            }
            num++;
        }
        else{
            resposta_errada();
            personagem.vidas--;
            sleep(6);
            result=0;
        }
    }
    else if(a==11){
        printf("\n\nQual será a saída a seguir: \n");
        printf("#incude <stdio.h>\n\nvoid f(){\n    printf(\"Hello World\");\n}\n");
        printf("\nint main(){\n    return 0;\n}\n");
        printf("A) Não haverá saída\nB) Erro, pois a função não foi chamada\nC) Erro, pois a função main está vazia\nD) Erro, pois a funcão não foi declarada\nResposta: ");
        scanf("%c", &c);
        if(c=='a' || c=='A'){
            resposta_certa();
            personagem.vidas++;
            sleep(6);
            result=1;
            if(num==0)quests_respondidas[num]=a;
            else{
                quests_respondidas=(int *) realloc(quests_respondidas, sizeof(int)*num+1);
                quests_respondidas[num]=a;
            }
            num++;
        }
        else{
            resposta_errada();
            personagem.vidas--;
            sleep(6);
            result=0;
        }
    }
    else if(a==12){
        printf("\n\nQual será a saída a seguir: \n");
        printf("#incude <stdio.h>\n\nint main(){\n    f();\n    return 0;\n}\n");
        printf("\nvoid f(){\n    printf(\"Hello World\");\n}\n");
        printf("A) Não haverá saída\nB) Erro, pois a função não foi chamada\nC) Erro, pois a função main está vazia\nD) Erro, pois a funcão não foi declarada\nResposta: ");
        scanf("%c", &c);
        if(c=='d' || c=='d'){
            resposta_certa();
            personagem.vidas++;
            sleep(6);
            result=1;
            if(num==0)quests_respondidas[num]=a;
            else{
                quests_respondidas=(int *) realloc(quests_respondidas, sizeof(int)*num+1);
                quests_respondidas[num]=a;
            }
            num++;
        }
        else{
            resposta_errada();
            personagem.vidas--;
            sleep(6);
            result=0;
        }
    }
    else if(a==13){
        printf("\n\nQual será a saída do código a seguir: \n");
        printf("\ninclude <stdio.h>\n\nvoid inv(int a, int b){\n    int x = a;\na = b;\n b = x;\n}\n");
        printf("\nint main(){\n    int x = 5, y = 3;\n    inv(x,y);\n    printf(\"%%d %%d\", x, y);\n    return 0;\n}\n");
        printf("A) 3 5\nB) 5 3\n C) 5 5\n D) Compile error\nResposta: ");
        scanf("%c", &c);
        if(c=='d' || c=='d'){
            resposta_certa();
            personagem.vidas++;
            sleep(6);
            result=1;
            if(num==0)quests_respondidas[num]=a;
            else{
                quests_respondidas=(int *) realloc(quests_respondidas, sizeof(int)*num+1);
                quests_respondidas[num]=a;
            }
            num++;
        }
        else{
            resposta_errada();
            personagem.vidas--;
            sleep(6);
            result=0;
        }
    }
    else if(a==14){
        printf("\n\nQual será a saída a seguir: \n");
        printf("\n#include<stdio.h>\n\nint main(){\n    int r, x = 2;\n    float y = 5;\n    r = y%%x;\n     return 0;\n}\n");
        printf("A) 1\nB) 0\nC) 2\nD) Compile error\nReposta: ");
        scanf("%c", &c);
        if(c=='d' || c=='d'){
            resposta_certa();
            personagem.vidas++;
            sleep(6);
            result=1;
            if(num==0)quests_respondidas[num]=a;
            else{
                quests_respondidas=(int *) realloc(quests_respondidas, sizeof(int)*num+1);
                quests_respondidas[num]=a;
            }
            num++;
        }
        else{
            resposta_errada();
            personagem.vidas--;
            sleep(6);
            result=0;
        }
    }
    else if(a==15){
        printf("\n\nQual é o tamanho de 'int'?\n");
        printf("A) 2\nB) 4\nC) 8\nD) Depende do compilador\n Resposta: ");
        scanf("%c", &c);
        if(c=='b' || c=='B'){
            resposta_certa();
            personagem.vidas++;
            sleep(6);
            result=1;
            if(num==0)quests_respondidas[num]=a;
            else{
                quests_respondidas=(int *) realloc(quests_respondidas, sizeof(int)*num+1);
                quests_respondidas[num]=a;
            }
            num++;
        }
        else{
            resposta_errada();
            personagem.vidas--;
            sleep(6);
            result=0;
        }
    }
    else if(a==16){
        printf("\n\nQual será a saída a seguir: \n");
        printf("\n#include <stdio.h>\n\nint main(){\n    int i=1;\n    while(++i <=5){\n        printf(\"%%d \");\n    }\n}\n");
        printf("A) 1 3 5\nB) 2 4\nC) 2 4 6\nD) 2\nResposta: ");
        scanf("%c", &c);
        if(c=='b' || c=='B'){
            resposta_certa();
            personagem.vidas++;
            sleep(6);
            result=1;
            if(num==0)quests_respondidas[num]=a;
            else{
                quests_respondidas=(int *) realloc(quests_respondidas, sizeof(int)*num+1);
                quests_respondidas[num]=a;
            }
            num++;
        }
        else{
            resposta_errada();
            personagem.vidas--;
            sleep(6);
            result=0;
        }
    }
    else if(a==17){
        printf("\n\nQual será a saída a seguir: \n");
        printf("\n#include <stdio.h>\n\nint main(){\n    int i=1;\n    while(++i <=5){\n        printf(\"%%d \");\n    }\n}\n");
        printf("A) 1 3 5\nB) 2 4\nC) 2 4 6\nD) 2\nResposta: ");
        scanf("%c", &c);
        if(c=='c' || c=='C'){
            resposta_certa();
            personagem.vidas++;
            sleep(6);
            result=1;
            if(num==0)quests_respondidas[num]=a;
            else{
                quests_respondidas=(int *) realloc(quests_respondidas, sizeof(int)*num+1);
                quests_respondidas[num]=a;
            }
            num++;
        }
        else{
            resposta_errada();
            personagem.vidas--;
            sleep(6);
            result=0;
        }
    }
    if(num==dificuldade) treme();
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

void treme(){
    int i, j, k;

    //printf("\033[H\033[J");
    for(k=0;k<10;k++){
        system("clear");
        if(k%2==0){
            for(i=0; i<LINHAS; i++){
                for(j=0; j<COLUNAS; j++){
                    if(j==0) printf("    ");
                    printf("%c", mapa[i][j]);

                }
                printf("\n");
            }
        }
        else printa_mapa();

        usleep(170000);
    }

    printa_mapa();
    printf("\nO que...?\n");
    sleep(4);
    printa_mapa();
    printf("\nO que é esse terremoto?\n");
    sleep(6);

    for(k=0;k<10;k++){
        system("clear");
        if(k%2==0){
            for(i=0; i<LINHAS; i++){
                for(j=0; j<COLUNAS; j++){
                    if(j==0) printf("    ");
                    printf("%c", mapa[i][j]);

                }
                printf("\n");
            }
        }
        else printa_mapa();

        usleep(170000);
    }
    boss();

    printa_mapa();
    sleep(6);
    printf("\nVocê... Você não vai conseguir sair! O chefe não vai deixar!!!\n");
    sleep(7);
}

int quest_boss(){
    char opcao;
    printa_mapa();
    printf("\n\nEntão é você que vem pertubando minha floresta e derrotando meus minions...\n");
    sleep(5);
    printf("Como ousa?\n");
    sleep(4);
    printa_mapa();
    printf("Mas, para o seu azar, você só vai conseguir sair daqui se me derrotar, e a cada resposta errada, você perderá %i vidas!! Hahahaha\n", vidas_boss);
    sleep(8);
    printf("Se você conseguir chegar ao final das perguntas ainda com vida, te deixarei sair.\n");
    sleep(7);
    printf("Vamos acabar com isso logo.\n");
    sleep(6);
    printa_mapa();
    if(personagem.vidas<1){
        return 0;
    }
    printf("A linguagem C é a sucessora de qual linguagem de programação?\n\n");
    printf("A) C++\nB) Fortran\nC) B\nD) Assembly\n");
    printf("Opcao: %c\n", opcao);
    if(opcao=='c' || opcao=='C'){
        printf("Essa estava facil... mas na proxima você falhará!\n");
        sleep(6);
    }
    else {
        printf("E aqui começa a sua derrota! Hahahaha\n");
        personagem.vidas-=vidas_boss;
        sleep(6);
    }
    if(personagem.vidas<1){
        return 0;
    }
    printa_mapa();
    printf("Qual será a saída do programa a seguir: \n\n");
    printf("#include <stdio.h>\n\nint* f(){\n    int x=5;\n\n    return &x;\n}\n\nint main(){\nprintf(\"%%d\", *f());\n}\n\n");
    printf("A) 5\nB) Endereço de x\nC) Compile error\nD) Runtime error\nOpcao: ");
    getchar();
    scanf("%c", &opcao);
    if(opcao=='D' || opcao=='d'){
        printf("Mais um acerto, em? Mas não vá se achando.\n");
        sleep(6);
    }
    else {
        printf("Logo você perecerá perante a mim!\n");
        personagem.vidas-=vidas_boss;
        sleep(6);
    }
    if(personagem.vidas<1){
        return 0;
    }
    printa_mapa();
    printf("Quantas vezes o programa a seguir printará \"APC?\" \n\n");
    printf("#include <stdio.h>\n\nint main(){\n    int x;\n    for(x=-1;x<20;x++){\n        if(x<10) continue;\n        else break;\n        printf(\"APC \");\n    }\n}\n");
    printf("A) Infinito\nB) 21 vezes\nC) 0 vezes\nD) 11\nOpcao: ");
    getchar();
    scanf("%c", &opcao);
    if(opcao=='C' || opcao=='c'){
        printf("O que...? Você nao vai conseguir sair!!!\n");
        sleep(6);
    }
    else {
        printf("Hahaha, você ainda vai tentar mesmo depois de errar essa? Eu desistiria.\n");
        personagem.vidas-=vidas_boss;
        sleep(6);
    }
    if(personagem.vidas<1){
        return 0;
    }
    printa_mapa();
    printf("Preveja a saída do código a seguir: \n\n");
    printf("#include <stdio.h>\n\nint main(){\n   int i=0;\ndo {\n        printf(\"APC1 \")\n        i=i++;\n    } while(i<5);\n    return 0;\n}\n");
    printf("A) APC1 APC1 APC1 APC1 APC1 \nB) APC1 infinitas vezes\nC) Compile error\nD) Overflow error\nOpcao: ");
    getchar();
    scanf("%c", &opcao);
    if(opcao=='C' || opcao=='c'){
        printf("... Você pretende mesmo sair... Vamos para a ultima então!\n");
        sleep(6);
    }
    else {
        printf("Recomendo você desistir agora e aprender a viver aqui. A proxima será a ultima.\n");
        personagem.vidas-=vidas_boss;
        sleep(6);
    }
    if(personagem.vidas<1){
        return 0;
    }
    printa_mapa();
    printf("Qual será a saída do programa a seguir: \n\n");
    printf("#include stdio\n\nvoid funcao(int *point){\n    int q = 10;\n    *point = &q;\n}\n");
    printf("\nint main(){    int x = 20;\n    int *p = &x;\n    funcao(p)\n    printf(\"%%d\", *p)\n    return 0;\n}\n");
    printf("A) 10\nB) 20\nC) Compile error\n D) Runtime error\nOpcao: ");
    getchar();
    scanf("%c", &opcao);
    if(opcao=='B' || opcao=='b'){
        printf("...\n");
        sleep(6);
        printf("Você... Você me derrotou e conquistou seu direito de sair. Agora, o último desafio.\n");
        sleep(7);
        printa_mapa();
        printf("\nLembra-se dos fragmentos que você conseguiu? Eles são as chaves para passar pelo portal.\n");
        sleep(7);
        printf("Agora, eu te darei a chave para resolver o quebra-cabeça.\n");
        sleep(5);
        printf("Sua chave de codificacão é: %i. Não se esqueça desse número.\n", cod);
        sleep(10);
        return 1;
    }
    else {
        personagem.vidas-=vidas_boss;
        if(personagem.vidas>0){
            printf("...\n");
            sleep(6);
            printf("Você... Você me derrotou e conquistou seu direito de sair. Agora, o último desafio.\n");
            sleep(7);
            printa_mapa();
            printf("\nLembra-se dos fragmentos que você conseguiu? Eles são as chaves para passar pelo portal.\n");
            sleep(7);
            printf("Agora, eu te darei a chave para resolver o quebra-cabeça.\n");
            sleep(5);
            printf("Sua chave de codificacão é: %i. Não se esqueça desse número.\n", cod);
            sleep(6);
            return 1;
        }
    }
}

void morreu(){
    printf("\n...\n");
    sleep(4);
    printf("%s, sou eu, Greybeard... Parece que você perdeu todas as suas vidas... Infeizmente terá que passar o resto de sua vida aqui.\n", personagem.nome);
    sleep(6);
    printf("Eu realmente acreditei que você seria a pessoa que venceria essa floresta horrível... Mas não percamos as esperanças.\n");
    sleep(5);
    printf("Há de aparecer alguém que conseguirá libertar a todos.\n");
    sleep(5);
    printf("Até a proxima, %s.\n", personagem.nome);
    sleep(8);
}

void grey(){
    printf("\n%s!!\n", personagem.nome);
    sleep(7);
    printf("%s, sou eu, o Greybeard!! Eu sabia que você conseguiria!!!\n", personagem.nome);
    sleep(7);
    printf("Você foi o primeiro a chegar aqui, e como recompensa, eu te darei uma dica de como resolver o desafio do portal!\n");
    sleep(7);
    printa_mapa();
    printf("\nOuvi rumores na floresta de que esse portal é protegido por uma criptografia\n");
    sleep(7);
    printf("Os goblins disseram que é uma criptografia antiga, criada por um imperador romano.\n");
    sleep(7);
    printf("Isso é tudo que eu sei, infelizmente. Agora é com você. Boa sorte, e obrigado por derrotar o chefe dos goblins.\n");
    sleep(8);
}

void portal(){
    char senha[50];
    int tentativa=0;
    printf("\nVocê está tentando atravessar o portal do fim.\nDigite a senha para conseguir o acesso: ");
    while(1){
        scanf("%s", senha);
        if(strcmp(senha, verifica_chave)==0){
            system("clear");
            printf("###############   ###############   ###############   ###############   ##                ###############   ###############   ###############\n");
            usleep(200000);
            printf("###############   ###############   ###############   ###############   ##                ###############   ###############   ###############\n");
            usleep(200000);
            printf("##                ##           ##         ##          ##           ##   ##                ##           ##   ##                      ##\n");
            usleep(200000);
            printf("##                ##           ##         ##          ##           ##   ##                ##           ##   ##                      ##\n");
            usleep(200000);
            printf("##                ##           ##         ##          ##           ##   ##                ##           ##   ##                      ##\n");
            usleep(200000);
            printf("##                ##           ##         ##          ##           ##   ##                ##           ##   ###############         ##\n");
            usleep(200000);
            printf("##                ###############         ##          ###############   ##                ##           ##   ###############         ##\n");
            usleep(200000);
            printf("##                ###############         ##          ###############   ##                ##           ##                ##         ##\n");
            usleep(200000);
            printf("##                ##           ##         ##          ##           ##   ##                ##           ##                ##         ##\n");
            usleep(200000);
            printf("###############   ##           ##         ##          ##           ##   ###############   ###############   ###############         ##\n");
            usleep(200000);
            printf("###############   ##           ##         ##          ##           ##   ###############   ###############   ###############         ##\n");
            usleep(300000);
            printf("\n\n\nParabéns!!! Você conseguiu concluir o desafio de Catalost!!!( E agora está apto a cursar APC2 =D )\n");
            sleep(10);
            return;
        }
        else{
            tentativa++;
            if(tentativa==10) printf("Dica: O imperador romano citado por Greybeard se chama Cesar.\n");
        }

    }
}
