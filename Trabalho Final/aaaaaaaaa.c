#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct{
  char naipe;
  int valor;
}carta;

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
}

int random_dist(carta baralho[52], int sorteada[52]){
  for(i=1;i<=jogadores, i++){
    printf("cartas do jogador %d:\n",i );
    for(j=0;j<2;j++){
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

int main()
{
  carta baralho[52] = {0};
  int sorteada[52] = {0};
  srand( (unsigned)time(NULL) );
  int jogadores=1,fichas=2500,rodadas=5;
  int menu,config,men_cred,men_jogadores,men_rodadas;
  printf("***JOGAR 21***\n");
  do{
    printf("Opções do Menu\n\n(1)Jogar\n(2)Configurações de Jogo\n(3)Sair\n");
    scanf("%d",&menu);
    if (menu==1)
    {
      jogar(jogadores,fichas,rodadas);
    }
    else if (menu==2){
      do{
        printf("Configurações\n\n(1)Numero de Créditos\n(2)Numero de Jogadores\n(3)Numero de Rodadas\n(4)Voltar\n");
        scanf("%d",&config);
        if (config == 1) {
          do{
            printf("Numero de Créditos\n\n(1)2500\n(2)3000\n(3)3500\n(4)4000\n");
            scanf("%d",&men_cred);
            if(men_cred==1)
            {
              printf("Valor de 2500 créditos \n", );
            }
          }

          break;
        }
        else if (config == 2) {
          printf("Numero de Jogadores\n\n");
          scanf("%d",&jogadores);
          break;
        }
        else if (config == 3) {
          printf("Numero de Rodadas\n\n");
          scanf("%d",&rodadas);
          break;
        }
        else if (config == 4) {
          printf("Voltando\n");
          break;
        }
        else {
          printf("Opção Inválida\n");
        }
      }
      while(config!=4);
      break;
    }
    else if (menu==3){
      printf("Saindo\n");
      break;
    }
    else {
      printf("Opção Inválida\n");
    }
  }while(menu!=3);

  return 0;
}
