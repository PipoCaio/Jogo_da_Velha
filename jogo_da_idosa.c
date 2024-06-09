#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void limpar(char tab[3][3]){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            tab[i][j] = ' ';
        }
    }   
}

void mostrar(char tab[3][3]){
    printf("\033[H\033[J");//É um 'clear'

    printf("     ( Y )     \n( 0 )( 1 )( 2 )\n");
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            printf("[ %c ]", tab[i][j]);
        }
        printf("( %d )", i);
        if(i ==1){printf("( X )");}
        printf("\n");
    }   
}

void jogada(char tab[3][3]){
    int x, y;
    printf("\nOnde por 'x'? \n->X= ");
    scanf("%d", &x);
    printf("\n->Y= ");
    scanf("%d", &y);

    if (x >= 0 && x < 3 && y >= 0 && y < 3){
        if (tab[x][y] == ' '){
            tab[x][y] = 'X';
        } else {
            printf("Casa ocupada\n");   
            jogada(tab);
        }
    } else {
        printf("Posição inválida\n");
        jogada(tab);
    }
}

void jogadaMaq(char tab[3][3]){
    int x, y;
    do {
        x = rand() % 3; 
        y = rand() % 3;
    } while (tab[x][y] != ' ');
    tab[x][y] = 'O';
}

void soMaisUma(char tab[3][3], int *End){
    int verif;
    printf("\n\nMais uma?\n0)Negativo\n1)Sim\n");
    scanf("%d", &verif);

    switch (verif)
    {
    case 0:
        *End = verif;
        printf("\033[H\033[J");//É um 'clear'
        break;
    
    case 1:
        limpar(tab);
        break;
    
    default:
        break;
    }
}

void xeca(char tab[3][3],int *End, int *placarPlayer, int *placarMaquina){
    int trad[3][3];
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            switch (tab[i][j]){
                case 'X':
                    trad[i][j] = 5;
                    break;
                case 'O':
                    trad[i][j] = 3;
                    break;
                case ' ':
                    trad[i][j] = 0;
                    break;
                default:
                    break;
            }
        }
    }

    if (
        ((trad[0][0] + trad[1][0] + trad[2][0]) == 15) ||
        ((trad[0][1] + trad[1][1] + trad[2][1]) == 15) ||
        ((trad[0][2] + trad[1][2] + trad[2][2]) == 15) ||

        ((trad[0][0] + trad[0][1] + trad[0][2]) == 15) ||
        ((trad[1][0] + trad[1][1] + trad[1][2]) == 15) ||
        ((trad[2][0] + trad[2][1] + trad[2][2]) == 15) ||

        ((trad[0][0] + trad[1][1] + trad[2][2]) == 15) ||
        ((trad[0][2] + trad[1][1] + trad[2][0]) == 15))
    {
        mostrar(tab);
        printf("Jogador Real Ganhou!!!\n");
        
        (*placarPlayer)++;
        printf("___PLACAR___\nPlayer:=%d\nMaquina:=%d", *placarPlayer, *placarMaquina);
        
        soMaisUma(tab, End);
    }
    else if (
        ((trad[0][0] + trad[1][0] + trad[2][0]) == 9) ||
        ((trad[0][1] + trad[1][1] + trad[2][1]) == 9) ||
        ((trad[0][2] + trad[1][2] + trad[2][2]) == 9) ||

        ((trad[0][0] + trad[0][1] + trad[0][2]) == 9) ||
        ((trad[1][0] + trad[1][1] + trad[1][2]) == 9) ||
        ((trad[2][0] + trad[2][1] + trad[2][2]) == 9) ||

        ((trad[0][0] + trad[1][1] + trad[2][2]) == 9) ||
        ((trad[0][2] + trad[1][1] + trad[2][0]) == 9))
    {
        mostrar(tab);
        printf("Acabou o jogo...\nMaquina ganhou....\n");
        
        (*placarMaquina)++;

        printf("___PLACAR___\nPlayer:=%d\nMaquina:=%d", *placarPlayer, *placarMaquina);

        soMaisUma(tab, End);
    }
    else {
        int tie = 1;
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if (tab[i][j] == ' '){
                    tie = 0;
                    break;
                }
            }
        }
        if (tie) {
            mostrar(tab);
            printf("Empatou com uma maquina?!?!?!?!\nNada contra mas.....\nSorte?!?\nTa maluco.....");

            printf("___PLACAR___\nPlayer:=%d\nMaquina:=%d", *placarPlayer, *placarMaquina);

            soMaisUma(tab, End);
        }
    }
}

int main(){
    char tab[3][3];
    int End = 1;
    int placarPlayer=0;
    int placarMaquina=0;
    srand(time(NULL)); 
    limpar(tab);

    while (End != 0){
        mostrar(tab);
        jogada(tab);
        xeca(tab, &End, &placarPlayer, &placarMaquina);
        if (End == 0) break;//so pra ter certza de acabar se o player ganhar hehe
        mostrar(tab);
        jogadaMaq(tab);
        xeca(tab, &End, &placarPlayer, &placarMaquina);
    }
    return 0;
}
