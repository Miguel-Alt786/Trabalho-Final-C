#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct{
  char naipe;
  int valor;
}carta;

typedef struct{
  int creditos;
  int rodadas_ganhas;
  carta cartas[11];
  int soma_cartas;
}jogador;

typedef struct{
  int rodadas_ganhas;
  carta cartas[11];
  int soma_cartas;
}dealer;

int func_Jogador(jogador jogador, carta baralho[52], int sorteada[52], int cartas)
{
  jogador.cartas[] = random_dist(&baralho, &sorteada, cartas);
  if (jogador.cartas[0] != 0 && jogador.cartas[1] != 0)
  {
    for (int i = 0; i < sizeof(jogador.cartas); i++)
    {
      jogador.soma_cartas += jogador.cartas[i];
    }
  }
}

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
      strcpy(baralho[i].naipe, naipe1 );
    }
    else if (i<=25 && i>12) {
      baralho[i].valor = i-12;
      strcpy(baralho[i].naipe, naipe2 );
    }
    else if (i<=38 && i>25) {
      baralho[i].valor = i-25;
      strcpy(baralho[i].naipe, naipe3 );
    }
    else if (i<=52 && i>38) {
      baralho[i].valor = i-38;
      strcpy(baralho[i].naipe, naipe4 );
    }
  }
}

int random_dist(carta baralho[52], int sorteada[52], int num_cartas){
  int n;

  for(int j=0;j<num_cartas;j++){
    do{
      n=rand()%52;
    }
    while (sorteada[n]!=0);
    sorteada[n] = 1;
    printf("%d de %s\n",baralho[n].valor, baralho[n].naipe );
  }
  return 0;
}

int jogar (int num_jogadores, int fichas, int rodadas, jogador jogador_1, jogador jogador_2, jogador jogador_3, jogador jogador_4, carta *baralho[52], int *sorteada[52])
{
  for (int i = 1; i <= rodadas; i++)
  {
    if (i==1)
    {
      printf("Primeira Rodada\n");
      for (int j = 0; j <= num_jogadores; j++)
      {
        func_Jogador(&jogador_1, &baralho, &sorteada, 2);
      }
    }
    else if (i==rodadas)
    {
      printf("RODADA FINAL\n");
    }
    else
    {
      printf("Rodada %d \n",i);
    }

  }
}

int main()
{
  carta baralho[52] = {0};
  int sorteada[52] = {0};

  srand( (unsigned)time(NULL) );
  int jogadores=1,fichas=2500,rodadas=5;
  int menu,config,men_cred,men_jogadores,men_rodadas;
  printf("          ******       ****\n         ********     ***** \n        ****  ****   ****** \n             ****      ****\n            ****       ****\n           ****        ****\n         **********    ****\n        ***********    ****\n\n");
  printf("    *        *       **   **      **\n   ***      ***     *********   * ** *\n  *****    ** **     *******    * ** *\n   ***       *         ***        **  \n    *        *          *         **  \n");
  do{
    printf("Opções do Menu\n\n(1)Jogar\n(2)Configurações de Jogo\n(3)Sair\n");
    scanf("%d",&menu);
    if (menu==1)
    {

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
              printf("Valor de 2500 créditos \n" );
            }
            else if(men_cred==2)
            {
              printf("Valor de 3000 créditos \n" );
            }
            else if(men_cred==3)
            {
              printf("Valor de 3500 créditos \n" );
            }
            else if(men_cred==4)
            {
              printf("Valor de 4000 créditos \n" );
            }
            else
            {
              printf("Opção Inválida\n");
            }
          }
          while(men_cred>=4 || men_cred<=1);
        }
        else if (config == 2) {
          do{
            printf("Numero de Jogadores\n\n(1)1 Jogador\n(2)2 Jogadores\n(3)3 Jogadores\n(4)4 Jogadores\n");
            scanf("%d",&men_jogadores);
            if(men_jogadores==1)
            {
              printf("1 Jogador\n" );
            }
            else if(men_jogadores==2)
            {
              printf("2 Jogadores\n" );
            }
            else if(men_jogadores==3)
            {
              printf("3 Jogadores\n" );
            }
            else if(men_jogadores==4)
            {
              printf("4 Jogadores \n" );
            }
            else
            {
              printf("Opção Inválida\n");
            }
          }
          while(men_jogadores>=4 || men_jogadores<=1);

        }
        else if (config == 3) {
          do{
            printf("Numero de Rodadas\n\n(1)3\n(2)5\n(3)7\n(4)10\n");
            scanf("%d",&men_rodadas);

            if(men_rodadas==1)
            {
              printf("3 Rodadas\n" );
            }
            else if(men_rodadas==2)
            {
              printf("5 Rodadas\n" );
            }
            else if(men_rodadas==3)
            {
              printf("7 Rodadas\n" );
            }
            else if(men_rodadas==4)
            {
              printf("10 Rodadas \n" );
            }
            else
            {
              printf("Opção Inválida\n");
            }
          }
          while(men_rodadas>=4 || men_rodadas<=1);
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
