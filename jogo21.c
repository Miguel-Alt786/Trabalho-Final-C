#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ncurses.h>
#include <locale.h>

typedef struct{
  char naipe[1];
  char nome[1];
  int valor;
}carta;

typedef struct{
  int creditos;
  int rodadas_ganhas;
  carta cartas[11];
  int soma_cartas;
  int num_cartas;
  int id;
}jogador;

typedef struct{
  int rodadas_ganhas;
  carta cartas[11];
  int soma_cartas;
  int num_cartas;
}dealer;

void delay(int segundos)
{
  int milisegundos = segundos * 1000000;
  clock_t relogioComeco = clock();
  while (clock() < relogioComeco + milisegundos)
  {
    ;
  }
}

void init_Cartas(carta baralho[52])
{

  char cartas[13] = {'A', '2', '3', '4', '5', '6','7', '8', '9', 'X', 'J', 'Q', 'K'};

  for (int i = 0; i <= 52; i++)
  {
    if (i<=12) {
      baralho[i].nome[0] = cartas[i];
      baralho[i].naipe[0] = 'O';
    }
    else if (i<=25 && i>12) {
      baralho[i].nome[0] = cartas[i-13];
      baralho[i].naipe[0] = 'E';
    }
    else if (i<=38 && i>25) {
      baralho[i].nome[0] = cartas[i-26];
      baralho[i].naipe[0] = 'C';
    }
    else if (i<=52 && i>38) {
      baralho[i].nome[0] = cartas[i-39];
      baralho[i].naipe[0] = 'P';
    }
  }
}

int pega_Carta(carta baralho[52], int *sorteada[52])
{
  int n;
  do{
    n=rand()%52;
  }
  while (sorteada[n]!=0);
  sorteada[n] = 1;

  return n;
}

jogador func_Jogador(jogador player, carta baralho[52], int *sorteada[52])
{
  int count = 1;
  char cond[1]={'Y'};
  int n = 0;
  if (player.creditos >= 0)
  {
    printf("\n\n\nVez do Jogador %d\n",player.id);
    n = pega_Carta(baralho, sorteada);
    printf("%c de %c\n",baralho[n].nome[0], baralho[n].naipe[0]);
    player.cartas[0].nome[0] = baralho[n].nome[0];
    player.cartas[0].naipe[0] = baralho[n].naipe[0];
    player.num_cartas = 1;

    do {
      n = pega_Carta(baralho, sorteada);
      printf("%c de %c\n",baralho[n].nome[0], baralho[n].naipe[0]);
      player.cartas[count].nome[0] = baralho[n].nome[0];
      player.cartas[count].naipe[0] = baralho[n].naipe[0];
      player.num_cartas ++;
      player.soma_cartas = 0;
      for (int i = 0; i < player.num_cartas; i++)
      {
        if (player.cartas[i].nome[0]=='X' || player.cartas[i].nome[0]=='J' || player.cartas[i].nome[0]=='Q'|| player.cartas[i].nome[0]=='K' ) {
          player.cartas[i].valor = 10;
        }
        else if (player.cartas[i].nome[0]=='A') {
          if ((player.soma_cartas + 11) <= 21)
          {
            player.cartas[i].valor = 11;
            printf("O Ás terá o valor 11\n");
          }
          else{
            printf("O Ás terá o valor 1\n");
            player.cartas[i].valor = 1;
          }
        }
        else{
          player.cartas[i].valor = atoi(player.cartas[i].nome);
        }
        player.soma_cartas += player.cartas[i].valor ;

      }
      printf("Soma das cartas %d\n", player.soma_cartas);
      if (player.soma_cartas > 21)
      {
        printf("Estorou\n");
        return player;
      }
      else if (player.soma_cartas == 21)
      {
        printf("21\n");
        return player;
      }
      printf("Gostaria de obter mais uma carta? ('Y')Sim ('N')Não \n");
      fflush(stdin);
      getchar();
      scanf("%c", &cond[0]);
      if (cond[0] != 'Y' && cond[0] != 'N')
      {
        printf("Opção Inválida\n");
        do {
          printf("Gostaria de obter mais uma carta?? ('Y')Sim ('N')Não \n");
          fflush(stdin);
          getchar();
          scanf("%c", &cond[0]);
        } while(cond[0] != 'Y' && cond[0] != 'N');
      }
      count++;

    } while(cond[0] != 'N');
  }
  else
  {
    printf("\n JOGADOR %d ESTÁ SEM CRÉDITOS \n", player.id);
    player.soma_cartas = 0;
    player.creditos == 0;
  }

  return player;
}

dealer func_Dealer(dealer player, carta baralho[52], int *sorteada[52])
{
  int count = 1;
  int n = 0;
  printf("Vez do Dealer \n");
  n = pega_Carta(baralho, sorteada);
  printf("%c de %c\n",baralho[n].nome[0], baralho[n].naipe[0]);
  player.cartas[0].nome[0] = baralho[n].nome[0];
  player.cartas[0].naipe[0] = baralho[n].naipe[0];
  n = pega_Carta(baralho, sorteada);
  printf("carta virada \n" );
  player.cartas[1].nome[0] = baralho[n].nome[0];
  player.cartas[1].naipe[0] = baralho[n].naipe[0];
  player.soma_cartas = 0;
  for (int i = 0; i < 2; i++)
  {
    if (player.cartas[i].nome[0]=='X' || player.cartas[i].nome[0]=='J' || player.cartas[i].nome[0]=='Q'|| player.cartas[i].nome[0]=='K' ) {
      player.cartas[i].valor = 10;
    }
    else if (player.cartas[i].nome[0]=='A') {
      if ((player.soma_cartas + 11) <= 21)
      {
        player.cartas[i].valor = 11;
      }
      else{
        player.cartas[i].valor = 1;
      }
    }
    else{
      player.cartas[i].valor = atoi(player.cartas[i].nome);
    }
    player.soma_cartas += player.cartas[i].valor ;
  }
  if (player.soma_cartas > 21)
  {
    printf("Dealer Estorou\n");
    return player;
  }

  return player;
}

int aposta (int num_jogadores, jogador jogador[4])
{
  int valor = 0;
  int aux;
  for (int i = 0; i < num_jogadores; i++)
  {
    if (jogador[i].creditos <= 0)
    {
      printf("Jogador %d Não tem mais créditos \n", jogador[i].id);
      jogador[i].creditos--;
    }

    else
    {
      printf("Jogador %d - Qual valor da aposta? \n", jogador[i].id);
      scanf("%d", &aux);
      while (aux > jogador[i].creditos)
      {
        printf("Valor Inválido \n");
        printf("Jogador %d - Qual valor da aposta? \n", jogador[i].id);
        scanf("%d", &aux);
      }

      jogador[i].creditos -= aux;
      valor += aux;
    }
  }
  printf("\e[1;1H\e[2J");

  return valor;
}

int rodada(int num_jogadores,jogador jogador[4], dealer computador, carta baralho[52], int *sorteada[52], int cred_Total)
{
  int count = 2;
  int n = 0;
  computador = func_Dealer(computador,baralho,sorteada);
  for (int i = 0; i < num_jogadores; i++)
  {
    jogador[i] = func_Jogador(jogador[i],baralho,sorteada);
  }
  printf("A outra carta do Dealer \n");
  printf("%c de %c\n", computador.cartas[1].nome[0], computador.cartas[1].naipe[0]);
  printf("Soma do Dealer: %d \n", computador.soma_cartas);

  while (computador.soma_cartas < 15)
  {
    printf("Soma das cartas do Dealer é menor que 15\n");
    n = pega_Carta(baralho, sorteada);
    printf("%c de %c\n",baralho[n].nome[0], baralho[n].naipe[0]);
    computador.cartas[count].nome[0] = baralho[n].nome[0];
    computador.cartas[count].naipe[0] = baralho[n].naipe[0];
    if (computador.cartas[count].nome[0]=='X' || computador.cartas[count].nome[0]=='J' || computador.cartas[count].nome[0]=='Q'|| computador.cartas[count].nome[0]=='K' ) {
      computador.cartas[count].valor = 10;
    }
    else if (computador.cartas[count].nome[0]=='A') {
      if ((computador.soma_cartas + 11) <= 21)
      {
        computador.cartas[count].valor = 11;
      }
      else{
        computador.cartas[count].valor = 1;
      }
    }
    else{
      computador.cartas[count].valor = atoi(computador.cartas[count].nome);
    }
    computador.soma_cartas += computador.cartas[count].valor;
    printf("Soma do Dealer: %d \n", computador.soma_cartas);
    count ++;
  }

  int maior = 0;
  int pos_Maior = 0;
  int empate [4] = {0};
  int empatados = 1;
  int pos_empatados = 0;
  int h = 0;

  for (int j = 0; j < num_jogadores; j++)
  {
    if (jogador[j].soma_cartas == maior)
    {
      empate[j] = 1;
      empate[pos_Maior] = 1;
      empatados ++;
      pos_empatados = j;
    }

    else if (jogador[j].soma_cartas > maior && jogador[j].soma_cartas <= 21)
    {
      maior = jogador[j].soma_cartas;
      pos_Maior = j;
    }
  }

  if (computador.soma_cartas == 21)
  {
    printf("DEALER GANHOU\n");
  }
  else if (computador.soma_cartas < 21)
  {
    if (jogador[pos_Maior].soma_cartas > computador.soma_cartas && empatados == 1)
    {
      printf("JOGADOR %d VENCEU A RODADA\n", pos_Maior+1);
      printf("JOGADOR %d RECEBEU %d CRÉDITOS \n", pos_Maior+1, cred_Total);
      jogador[pos_Maior].creditos += cred_Total;
    }
    else if (jogador[pos_Maior].soma_cartas < computador.soma_cartas)
    {
      printf("DEALER VENCEU\n");
    }
    else if (jogador[pos_Maior].soma_cartas == computador.soma_cartas)
    {
      printf("Empate, mas o DEALER VENCEU\n");
    }
    else if(jogador[pos_Maior].soma_cartas > computador.soma_cartas && empatados > 1 && jogador[pos_Maior].soma_cartas == jogador[pos_empatados].soma_cartas)
    {
      printf("TIVEMOS %d EMPATADOS\n", empatados);
      printf("OS %d CRÉDITOS SERÃO DIVIDIDOS ENTRE ELES\n", cred_Total);
      while (h < 4)
      {
        if (empate[h] == 1)
        {
          jogador[h].creditos += (cred_Total/empatados);
        }
        h++;
      }
    }
  }
  else
  {
    if (empatados == 1)
    {
      printf("JOGADOR %d VENCEU A RODADA\n", pos_Maior+1);
      printf("JOGADOR %d RECEBEU %d CRÉDITOS \n", pos_Maior+1, cred_Total);
      jogador[pos_Maior].creditos += cred_Total;
    }
    else if(empatados > 1 && jogador[pos_Maior].soma_cartas == jogador[pos_empatados].soma_cartas)
    {
      printf("TIVEMOS %d EMPATADOS\n", empatados);
      printf("OS %d CRÉDITOS SERÃO DIVIDIDOS ENTRE ELES\n", cred_Total);
      while (h < 4)
      {
        if (empate[h] == 1)
        {
          jogador[h].creditos = (cred_Total/empatados);
        }
        h++;
      }
    }

  }

  for (int i = 0; i < num_jogadores; i++) {

  }


}

int placar(int num_jogadores, jogador jogador[4])
{
  int i,j,ajuste,aux;
    int pos[num_jogadores];
    for (i=0;i<num_jogadores-1;i++){
        for (j=0;j<num_jogadores-1-i;j++){
            if(jogador[j].creditos>jogador[j+1].creditos){
                ajuste=jogador[j].creditos;
                aux = jogador[j].id;
                jogador[j].creditos=jogador[j+1].creditos;
                jogador[j].id=jogador[j+1].id;
                jogador[j+1].creditos=ajuste;
                jogador[j+1].id = aux;
            }
        }
    }
    int count = 1;
    for (int i = num_jogadores-1; i >=0; i--)
    {
      if (jogador[i].creditos < 0) {
        printf("O Jogador %d Ficou %d Rodadas fora da mesa \n",jogador[i].id, jogador[i].creditos*-1);
      }
      else if (count == num_jogadores)
      {
        printf("Último Lugar %d - %d \n", jogador[i].creditos, jogador[i].id );

      }
      else{
        printf("%d° Lugar %d - %d \n", count,jogador[i].creditos, jogador[i].id );
      }
      count++;
    }
    printf("O jogador %d é o vencedor\n", jogador[num_jogadores-1].id);
  return 0;
}

int jogar (int num_jogadores, int rodadas, jogador jogador[4], dealer computador, carta baralho[52], int *sorteada[52])
{

  for (int i = 1; i <= rodadas; i++)
  {
    int cred_Total = 0 ;
    if (i==1)
    {
      printf("Primeira Rodada\n");
      cred_Total = aposta(num_jogadores, jogador);
      if (num_jogadores == 1)
      {
        cred_Total = cred_Total * 2;
      }
      rodada(num_jogadores, jogador, computador, baralho, sorteada, cred_Total);
      for (int i = 0; i < num_jogadores; i++)
      {
        printf("Fichas do Jogador %d - %d \n",jogador[i].id ,jogador[i].creditos);
      }
    }
    else if (i==rodadas)
    {
      printf("\n\nRODADA FINAL\n");
      cred_Total = aposta(num_jogadores, jogador);
      rodada(num_jogadores, jogador, computador, baralho, sorteada, cred_Total);
      placar(num_jogadores, jogador);
    }
    else
    {
      printf("\n\nRodada %d \n",i);
      cred_Total = aposta(num_jogadores, jogador);
      rodada(num_jogadores, jogador, computador, baralho, sorteada, cred_Total);
      for (int i = 0; i < num_jogadores; i++)
      {
        if(jogador[i].creditos<=-1){
          printf("\nO jogador %d não tem mais créditos \n", jogador[i].id );
        }
        else
        {
          printf("Fichas do Jogador %d - %d \n",jogador[i].id ,jogador[i].creditos);
        }

      }

    }

  }
  printf("Voltando ao menu em 10 segundos\n");
  delay (10);
  printf("\e[1;1H\e[2J");

}

void print_menu(WINDOW *menu_win, int highlight, char *escolhas[], int n_escolhas)
{
  int aux;

  aux = 1;
  box(menu_win, 0, 0);
  for(int i = 0; i < n_escolhas; ++i)
  {	if(highlight == i + 1)
    {	wattron(menu_win, A_REVERSE);
      mvwprintw(menu_win, aux, 1, "%s", escolhas[i]);
      wattroff(menu_win, A_REVERSE);
    }
    else
    {
      mvwprintw(menu_win, aux, 1, "%s", escolhas[i]);
    }
    ++aux;
  }
  wrefresh(menu_win);
}

int menu(WINDOW *menu_win, char *escolhas[], int n_escolhas, int altura, int largura, char titulo[13])
{
  int highlight = 1;
  int choice = 0;
  int c;
  int startx = 0;
  int starty = 0;

  initscr();
  clear();
  noecho();
  cbreak();
  curs_set(0);
  getmaxyx(stdscr, starty, startx);
  startx = startx/2;
  starty = starty/2;

  mvprintw(starty - 1 , startx + ((strlen(titulo)/2)-3), titulo);
  menu_win = newwin(altura, largura, starty, startx);
  keypad(menu_win, TRUE);
  refresh();
  print_menu(menu_win, highlight, escolhas, n_escolhas);
  while(1)
  {	c = wgetch(menu_win);
    switch(c)
    {	case KEY_UP:
      if(highlight == 1)
      highlight = n_escolhas;
      else
      --highlight;
      break;
      case KEY_DOWN:
      if(highlight == n_escolhas)
      highlight = 1;
      else
      ++highlight;
      break;
      case 10:
      choice = highlight;
      break;
      default:
      mvprintw(starty + 6, startx - 5  , "Aperte ENTER para selecionar");
      refresh();
      break;
    }
    print_menu(menu_win, highlight, escolhas, n_escolhas);
    if(choice != 0)
    break;
  }

  clrtoeol();
  refresh();
  endwin();
  return choice;
}

int main()
{
  setlocale(LC_ALL, "");
  carta baralho[52] = {0};
  WINDOW *menu_win;

  srand( (unsigned)time(NULL) );
  int jogadores=1,creditos=2500,rodadas=5;
  dealer computador;
  jogador jogador[4];
  jogador[0].id = 1;
  jogador[1].id = 2;
  jogador[2].id = 3;
  jogador[3].id = 4;

  int sel_menu,config,men_cred,men_jogadores,men_rodadas;
  char *escolhas[] = {"Jogar", "Opções", "Sair"};
  char *opcoes[] = {"Créditos", "Rodadas", "Jogadores", "Voltar"};
  char *opc_Jogadores[] = {"1 Jogador", "2 Jogadores", "3 Jogadores", "4 Jogadores"};
  char *opc_Creditos[] = {"2500 ©", "3000 ©", "3500 ©", "4000 ©", "Voltar"};
  char *opc_Rodadas[] = {"3 Rodadas", "5 Rodadas", "7 Rodadas", "10 Rodadas"};
  do {
    int altura = 5, largura = 10;
    int n_escolhas = 3;
    sel_menu = menu(menu_win, escolhas, n_escolhas, altura, largura, "Bem Vindo!");
    if (sel_menu==1)
    {
      jogador[0].creditos = creditos;
      jogador[1].creditos = creditos;
      jogador[2].creditos = creditos;
      jogador[3].creditos = creditos;
      int *sorteada[52] = {0};
      init_Cartas(baralho);
      jogar(jogadores, rodadas, jogador, computador, baralho, sorteada);
    }
    else if (sel_menu==2){
      do {
        altura = 6;
        largura = 12;
        n_escolhas = 4;
        config = menu(menu_win, opcoes, n_escolhas, altura, largura,"Opções");

        if (config == 1)
        {
          largura = 10;
          men_cred = menu(menu_win, opc_Creditos, n_escolhas, altura, largura,"Créditos");
          if (men_cred == 1) {
            creditos = 2500;
          }
          else if (men_cred == 2) {
            creditos = 3000;
          }
          else if (men_cred == 3) {
            creditos = 3500;
          }
          else if (men_cred == 4) {
            creditos = 4000;
          }
        }
        else if (config == 2)
        {
          largura = 12;
          men_rodadas = menu(menu_win, opc_Rodadas, n_escolhas, altura, largura,"Rodadas");
          if (men_rodadas == 1) {
            rodadas = 3;
          }
          else if (men_rodadas == 2) {
            rodadas = 5;
          }
          else if (men_rodadas == 3) {
            rodadas = 7;
          }
          else if (men_rodadas == 4) {
            rodadas = 10;
          }
        }
        else if (config == 3)
        {
          largura = 14;
          men_jogadores = menu(menu_win, opc_Jogadores, n_escolhas, altura, largura,"Jogadores");
          if (men_jogadores == 1)
          {
            jogadores = 1;
          }
          else if (men_jogadores == 2)
          {
            jogadores = 2;
          }
          else if (men_jogadores == 3)
          {
            jogadores = 3;
          }
          else if (men_jogadores == 4)
          {
            jogadores = 4;
          }

        }
      } while(config != 4);
    }
  } while(sel_menu !=3);

  return 0;
}
