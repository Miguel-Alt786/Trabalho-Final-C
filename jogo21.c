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
}carta; //Estrutura das cartas utilizadas durante o Jogo.

typedef struct{
  int creditos;
  int rodadas_ganhas;
  carta cartas[11];
  int soma_cartas;
  int num_cartas;
  int id;
}jogador; //Estrutura do jogador.

typedef struct{
  int rodadas_ganhas;
  carta cartas[11];
  int soma_cartas;
  int num_cartas;
}dealer; //Estrutura do CPU.

void delay(int segundos)
{
    //Funcao que implementa um delay simples
  int milisegundos = segundos * 1000000;
  clock_t relogioComeco = clock();
  while (clock() < relogioComeco + milisegundos)
  {
    ;
  }
}

void init_Cartas(carta baralho[52])
{
    //Funcao que inicializa as cartas do vetor baralho
  char cartas[13] = {'A', '2', '3', '4', '5', '6','7', '8', '9', 'X', 'J', 'Q', 'K'}; //Nomes das Cartas

  for (int i = 0; i <= 52; i++)
  {
    if (i<=12) {
      baralho[i].nome[0] = cartas[i];
      baralho[i].naipe[0] = 'O'; //Cartas do Naipe de Ouros
    }
    else if (i<=25 && i>12) {
      baralho[i].nome[0] = cartas[i-13];
      baralho[i].naipe[0] = 'E'; //Cartas do Naipe de Espadas
    }
    else if (i<=38 && i>25) {
      baralho[i].nome[0] = cartas[i-26];
      baralho[i].naipe[0] = 'C'; //Cartas do Naipe de Copas
    }
    else if (i<=52 && i>38) {
      baralho[i].nome[0] = cartas[i-39];
      baralho[i].naipe[0] = 'P'; //Cartas do Naipe de Paus
    }
  }
}

int pega_Carta(carta baralho[52], int *sorteada[52])
{
    //Funcao que coleta uma carta aleatoriamente sem repetir
  int n;
  do{
    n=rand()%52; //Pega um valor inteiro de até 52
  }
  while (sorteada[n]!=0); //Repete a chamada de um valor inteiro até este valor não for mais repetido
  sorteada[n] = (int*) 1; //Marca a carta como sorteada

  return n;
}

jogador func_Jogador(jogador player, carta baralho[52], int *sorteada[52])
{
    //Funcao responsavel pelas jogadas dos jogadores
  int count = 1;
  char cond[1]={'Y'};//Incializa uma variavel do tipo char e forma de vetor, para não ocorrer erros
  int n = 0;
  if (player.creditos >= 0) //Checa se o jogador possui créditos ou não
  {
    printf("\n\n\nVez do Jogador %d\n",player.id);
    n = pega_Carta(baralho, sorteada); //Pega uma carta
    printf("%c de %c\n",baralho[n].nome[0], baralho[n].naipe[0]);
    player.cartas[0].nome[0] = baralho[n].nome[0]; //Iguala a carta do jogador á carta sorteada
    player.cartas[0].naipe[0] = baralho[n].naipe[0];
    player.num_cartas = 1;

    do {
      n = pega_Carta(baralho, sorteada);
      printf("%c de %c\n",baralho[n].nome[0], baralho[n].naipe[0]);
      player.cartas[count].nome[0] = baralho[n].nome[0];
      player.cartas[count].naipe[0] = baralho[n].naipe[0];
      player.num_cartas ++;
      player.soma_cartas = 0;
      for (int i = 0; i < player.num_cartas; i++) // para todas as cartas que o jogador possui
      {
        if (player.cartas[i].nome[0]=='X' || player.cartas[i].nome[0]=='J' || player.cartas[i].nome[0]=='Q'|| player.cartas[i].nome[0]=='K' ) {
          //Caso a carta seja igual ou maior que 10
            player.cartas[i].valor = 10;
        }
        else if (player.cartas[i].nome[0]=='A')
        {
            //Caso a carta seja um Ás
          if ((player.soma_cartas + 11) <= 21)
          { //Se a soma das cartas mais o Ás não passar de 21, o valor de Ás será 11
            player.cartas[i].valor = 11;
            printf("O Ás terá o valor 11\n");
          }
          else{
              //Se a soma das cartas mais o Ás passar de 21, o valor de Ás será 1
            printf("O Ás terá o valor 1\n");
            player.cartas[i].valor = 1;
          }
        }
        else{
          player.cartas[i].valor = atoi(player.cartas[i].nome); //Converte o nome da carta (char) para o valor (int)
        }
        player.soma_cartas += player.cartas[i].valor ; // soma os valores das cartas do jogador

      }
      printf("Soma das cartas %d\n", player.soma_cartas);
      if (player.soma_cartas > 21)
      {
          //Caso a soma das cartas do jogador seja maior que 21 o jogador não poderá comprar mais cartas
        printf("Estorou\n");
        return player;
      }
      else if (player.soma_cartas == 21)
      {
          //Caso a soma das cartas do jogador seja igual a 21 o jogador não podera comprar mais cartas
        printf("21\n");
        return player;
      }
      printf("Gostaria de obter mais uma carta? ('Y')Sim ('N')Não \n"); //Pergunta se o jogador deseja mais cartas
      fflush(stdin);
      getchar();//Nescessario para não ter "lixo" no scanf
      scanf("%c", &cond[0]);
      if (cond[0] != 'Y' && cond[0] != 'N') //Caso não tenha sido digitada corretamente
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
    printf("\n JOGADOR %d ESTÁ SEM CRÉDITOS \n", player.id); //Caso o jogador não tenha mais creditos nao pode mais jogar
    player.soma_cartas = 0;
  }

  return player;
}

dealer func_Dealer(dealer player, carta baralho[52], int *sorteada[52])
{
    //Funcao responsavel pelas jogadas do CPU
  int count = 1;
  int n = 0;
  printf("Vez do Dealer \n");
  n = pega_Carta(baralho, sorteada);
  printf("%c de %c\n",baralho[n].nome[0], baralho[n].naipe[0]);
  player.cartas[0].nome[0] = baralho[n].nome[0];
  player.cartas[0].naipe[0] = baralho[n].naipe[0];
  n = pega_Carta(baralho, sorteada);
  printf("carta virada \n" );
  player.cartas[1].nome[0] = baralho[n].nome[0]; //Pega uma carta mas não mostra aos jogadores
  player.cartas[1].naipe[0] = baralho[n].naipe[0];
  player.soma_cartas = 0;
  for (int i = 0; i < 2; i++)
  {
    if (player.cartas[i].nome[0]=='X' || player.cartas[i].nome[0]=='J' || player.cartas[i].nome[0]=='Q'|| player.cartas[i].nome[0]=='K' ) {
      //Caso a carta seja igual ou maior que 10
        player.cartas[i].valor = 10;
    }
    else if (player.cartas[i].nome[0]=='A') {
      if ((player.soma_cartas + 11) <= 21)
      {
          //Se a soma das cartas mais o Ás não passar de 21, o valor de Ás será 11
        player.cartas[i].valor = 11;
      }
      else{
          //Se a soma das cartas mais o Ás passar de 21, o valor de Ás será 1
        player.cartas[i].valor = 1;
      }
    }
    else{
      player.cartas[i].valor = atoi(player.cartas[i].nome);//Converte o nome da carta (char) para o valor (int)
    }
    player.soma_cartas += player.cartas[i].valor ; // soma os valores das cartas do jogador
  }
  if (player.soma_cartas > 21)
  {
    printf("Dealer Estorou\n"); //Caso o delaer tenha passado de 21
    return player;
  }

  return player;
}

int aposta (int num_jogadores, jogador jogador[4])
{
    //Funcao que coleta as apostas dos jogadores
  int valor = 0;
  int aux;
  for (int i = 0; i < num_jogadores; i++)
  {
    if (jogador[i].creditos <= 0)
    {
      printf("Jogador %d Não tem mais créditos \n", jogador[i].id); //Caso o jogador não possua mais creditos
      jogador[i].creditos--;
    }

    else
    {
      printf("Jogador %d - Qual valor da aposta? (Min. 200) \n", jogador[i].id);
      scanf("%d", &aux);
      while (aux > jogador[i].creditos || aux < 200) //Checagem por valores invalidos
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
    //Funcao que chama as funcoes nescessarias para cada rodada
  int count = 2;
  int n = 0;
  computador = func_Dealer(computador,baralho,sorteada); //Iguala a variavel computador ao return de func_Dealer
  for (int i = 0; i < num_jogadores; i++)
  {
    jogador[i] = func_Jogador(jogador[i],baralho,sorteada); //Iguala a variavel jogador na posicao i ao return de func_Jogador
    delay(1);
  }
  printf("A outra carta do Dealer \n");
  printf("%c de %c\n", computador.cartas[1].nome[0], computador.cartas[1].naipe[0]); //Mostra a outra carta do Dealer
  printf("Soma do Dealer: %d \n", computador.soma_cartas);

  while (computador.soma_cartas < 15)
  {
    printf("Soma das cartas do Dealer é menor que 15\n"); //Caso a soma do Dealer seja menor que 15 ele compra mais uma carta
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

  int maior = 0; //Variaveis criadas para fazer a comparacao de quem teve os maiores valores
  int pos_Maior = 0;
  int empate [4] = {0}; // e caso alguns dos jogadores tenham empatados
  int empatados = 1;
  int pos_empatados = 0;
  int h = 0;

  for (int j = 0; j < num_jogadores; j++)
  {
    if (jogador[j].soma_cartas == maior)
    {
        //Confere se houve empare entre os jogadores
      empate[j] = 1;
      empate[pos_Maior] = 1;
      empatados ++;
      pos_empatados = j;
    }

    else if (jogador[j].soma_cartas > maior && jogador[j].soma_cartas <= 21)
    {
        //Confere se o jogador possui a maior carta
      maior = jogador[j].soma_cartas;
      pos_Maior = j;
    }
  }

  if (computador.soma_cartas == 21 || jogador[pos_Maior].soma_cartas > 21)
  {
      //Caso o computador tenha tirado 21
    printf("DEALER GANHOU\n");
  }
  else if(computador.soma_cartas > 21 && jogador[pos_Maior].soma_cartas > 21)
  {
    printf("O DEALER ESTOROU, MAS GANHOU\n");
  }
  else if (computador.soma_cartas < 21)
  {
    if (jogador[pos_Maior].soma_cartas > computador.soma_cartas && empatados == 1)
    {
        //Caso o jogador tenha uma soma maior que o computador
      printf("JOGADOR %d VENCEU A RODADA\n", pos_Maior+1);
      printf("JOGADOR %d RECEBEU %d CRÉDITOS \n", pos_Maior+1, cred_Total);
      jogador[pos_Maior].creditos += cred_Total;
    }
    else if (jogador[pos_Maior].soma_cartas < computador.soma_cartas)
    {
        //Caso o computador tenha uma soma maior que os jogadores
      printf("DEALER VENCEU\n");
    }
    else if (jogador[pos_Maior].soma_cartas == computador.soma_cartas)
    {
        //Caso tenha empate entre o computador e o jogador, o computador ganha
      printf("Empate, mas o DEALER VENCEU\n");
    }
    else if(jogador[pos_Maior].soma_cartas > computador.soma_cartas && empatados > 1 && jogador[pos_Maior].soma_cartas == jogador[pos_empatados].soma_cartas)
    {
        //caso tenha jogadores empatados, os creditos sao dividos de forma igualitaria
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
      //Caso o Dealer tenha passado de 21
    if (empatados == 1)
    { //Caso nao tenha empates
      printf("JOGADOR %d VENCEU A RODADA\n", pos_Maior+1);
      printf("JOGADOR %d RECEBEU %d CRÉDITOS \n", pos_Maior+1, cred_Total);
      jogador[pos_Maior].creditos += cred_Total;
    }
    else if(empatados > 1 && jogador[pos_Maior].soma_cartas == jogador[pos_empatados].soma_cartas)
    {
        //Caso tenha empates
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

return 0;
}

int placar(int num_jogadores, jogador jogador[4])
{
    //Funcao que ordena os jogadores e imprime o placar na tela
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
        printf("Último Lugar %d créditos - jogador %d \n", jogador[i].creditos, jogador[i].id );

      }
      else{
        printf("%d° Lugar %d créditos - jogador %d\n", count,jogador[i].creditos, jogador[i].id );
      }
      count++;
    }
    printf("O jogador %d é o vencedor\n", jogador[num_jogadores-1].id);
  return 0;
}

int jogar (int num_jogadores, int rodadas, jogador jogador[4], dealer computador, carta baralho[52], int *sorteada[52])
{
    //Funcao responsavel em chamar as rodadas e suas dependencias
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
      if (num_jogadores == 1)
      {
        cred_Total = cred_Total * 2;
      }
      rodada(num_jogadores, jogador, computador, baralho, sorteada, cred_Total);
      placar(num_jogadores, jogador);
    }
    else
    {
      printf("\n\nRodada %d \n",i);
      cred_Total = aposta(num_jogadores, jogador);
      if (num_jogadores == 1)
      {
        cred_Total = cred_Total * 2;
      }
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
  delay (10); //Espera 10 segundos antes de voltar ao menu
  printf("\e[1;1H\e[2J"); // Limpa a tela
  return 0;
}

void print_menu(WINDOW *menu_win, int highlight, char *escolhas[], int n_escolhas)
{
    //Funcao responsavel por destacar o indice selecionado do menu
  int aux;
  aux = 1;
  box(menu_win, 0, 0); //Desenha uma borda ao redor da janela
  for(int i = 0; i < n_escolhas; ++i)
  {
    if(highlight == i + 1)
    {
        wattron(menu_win, A_REVERSE); //Destaca aonde o usuario estiver
        mvwprintw(menu_win, aux, 1, "%s", escolhas[i]); //Imprime o valor de escolhas na posicao i
        wattroff(menu_win, A_REVERSE);
    }
    else
    {
      mvwprintw(menu_win, aux, 1, "%s", escolhas[i]);
    }
    ++aux;
  }
  wrefresh(menu_win); //Reinicia a janela
}

int menu(WINDOW *menu_win, char *escolhas[], int n_escolhas, int altura, int largura, char titulo[13])
{
    //Funcao reponsavel por criar o menu utilizando ncurses
  int highlight = 1;
  int choice = 0;
  int c;
  int startx = 0;
  int starty = 0;

  initscr(); //Incializa a tela do ncurses
  clear();
  noecho();
  cbreak();
  curs_set(0); //Desabilita o cursor de texto
  getmaxyx(stdscr, starty, startx); //Pega o tamanho maximo para x e y
  startx = (startx/2)-(largura/2); //Divide o tamanho pela mentade e centraliza a caixa
  starty = (starty/2)-(altura/2);

  mvprintw(starty - 1 , startx + ((strlen(titulo)/2)-3), titulo); //Printa o titulo da opcao
  menu_win = newwin(altura, largura, starty, startx); // inicializa a caixa com a altura e a largura ja setadas
  keypad(menu_win, TRUE);//habilita a utilização do teclado na caixa
  refresh(); //atualiza a tela
  print_menu(menu_win, highlight, escolhas, n_escolhas); //chama a funcao para imprimir na tela
  while(1)
  {
    c = wgetch(menu_win); //recebe o input do teclado
    switch(c)
    {
        case KEY_UP: //caso o recebido tenha sido a tecla de seta pra cima
            if(highlight == 1) // caso a opcao selecionada seja a primeira
            {
                highlight = n_escolhas; //a opcao seguinte sera a ultima
            }
            else
            {
                --highlight; // diminui highlight, resultando no aumento da selecao
            }
            break;

        case KEY_DOWN: //caso o recebido tenha sido a tecla de seta pra baixo
            if(highlight == n_escolhas)// caso a opcao selecionada seja a ultima
            {
                highlight = 1; //a opcao seguinte sera a primeira
            }
            else
            {
                ++highlight;
            }
            break;

        case 10: //Caso o recebido seja Enter
            choice = highlight; //Iguala a variavel choice com a variavel highlight
            break;
      default:
          //Caso alguma outra tecla seja apertada
          mvprintw(starty + 6, startx - 5  , "Aperte ENTER para selecionar");
          refresh();
          break;

    }
    print_menu(menu_win, highlight, escolhas, n_escolhas); //imprime o menu com os dados previamente recebidos

    if(choice != 0)
    {
        break;
    }

  }

  clrtoeol();
  refresh(); // Limpa o cursor
  endwin();
  return choice; //Retorna o valor selecionado
}

int main()
{
    //Funcao principal do codigo
  setlocale(LC_ALL, ""); //Utiliza a biblioteca locale para poder utilizar letras e acentos especificos da lingua portuguesa
  carta baralho[52] = {0};
  WINDOW *menu_win; //inicializa a variavel menu_win, responsavel pela janela do ncurses

  srand( (unsigned)time(NULL) ); // pega um valor aleatorio tendo como base o valor do relogio
  int jogadores=1,creditos=2500,rodadas=5; //Valores padroes do jogo
  dealer computador;
  jogador jogador[4];
  jogador[0].id = 1;
  jogador[1].id = 2;
  jogador[2].id = 3;
  jogador[3].id = 4;

  int sel_menu,config,men_cred,men_jogadores,men_rodadas;
  char *escolhas[] = {"Jogar", "Opções", "Sair"}; //Inicializa os vetores responsaveis pelos menus do ncurses
  char *opcoes[] = {"Créditos", "Rodadas", "Jogadores", "Voltar"};
  char *opc_Jogadores[] = {"1 Jogador", "2 Jogadores", "3 Jogadores", "4 Jogadores"};
  char *opc_Creditos[] = {"2500 ©", "3000 ©", "3500 ©", "4000 ©", "Voltar"};
  char *opc_Rodadas[] = {"3 Rodadas", "5 Rodadas", "7 Rodadas", "10 Rodadas"};
  do {
    int altura = 5, largura = 10;
    int n_escolhas = 3; // seta o numero de opcooes este menu possui
    sel_menu = menu(menu_win, escolhas, n_escolhas, altura, largura, "Bem Vindo!");
    if (sel_menu==1)
    {
        //caso a opcao seja igual a 1 incia o jogo
      jogador[0].creditos = creditos;
      jogador[1].creditos = creditos;
      jogador[2].creditos = creditos;
      jogador[3].creditos = creditos;
      int *sorteada[52] = {0}; //
      init_Cartas(baralho);
      jogar(jogadores, rodadas, jogador, computador, baralho, sorteada);
    }
    else if (sel_menu==2){
      do {
          //caso a selececao seja igual a 2 mostra as outras opcoes do menu
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
  //Caso seja igual a 3 o codigo é acabado

  return 0;
}
