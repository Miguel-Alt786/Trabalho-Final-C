#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<time.h>


typedef struct
{
    char naipe[12];
    int valor;
} carta;

int init_Cartas(carta baralho[52])
{
   char naipe1[13] = "ouros";
   char naipe2[13] = "espadas";
   char naipe3[13] = "copas";
   char naipe4[13] = "paus";

   for (int i = 0; i <= 52; i++)
  {
    if (i<=12) {
      baralho[i].valor = i+1;
      strcpy( baralho[i].naipe, naipe1 );
    }
    else if (i<=25 && i>12) {
      baralho[i].valor = i-12;
      strcpy( baralho[i].naipe, naipe2 );
    }
    else if (i<=38 && i>25) {
      baralho[i].valor = i-25;
      strcpy( baralho[i].naipe, naipe3 );
    }
    else if (i<=52 && i>38) {
      baralho[i].valor = i-38;
      strcpy( baralho[i].naipe, naipe4 );
    }
  }
  return 0;
}

int random_dist(carta baralho[52], int sorteada[52]){
  int n;
  int jogadores = 26;
  for(int i=1;i<=jogadores; i++){
    printf("cartas do jogador %d:\n",i );
    for(int j=0;j<2;j++){
      do{
        n=rand()%52;
      }
      while (sorteada[n]!=0);
      sorteada[n] = 1;
      printf("%d de %s\n",baralho[n].valor, baralho[n].naipe );
    }
  }
  return 0;
}

int main( void )
{
    carta baralho[52] = {0};
    int sorteada[52] = {0};
    int i,n,n2;
    srand((unsigned)time(NULL));
    init_Cartas(&baralho);
    random_dist(&baralho,&sorteada);
    return 0;
}
