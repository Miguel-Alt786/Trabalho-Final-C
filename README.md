# Trabalho 1 de Introdução a C/C++ UFRJ 2020-1 - 21 (Blackjack)
Trabalho Final de Introdução a C/C++ do jogo 21 (Blackjack) <br>
Para rodar o programa basta rodar <code>./jogo21</code> <br>
Caso queira compilar o código basta rodar <code>gcc jogo21.c -lncurses -o jogo21</code> <br>

Grupo formado pelos alunos
<ul>
<li>Felipe Monteiro Herculano</li>
<li>Ian de Andrade Camargo</li>
<li>João Felipe Veras Dantas Rocha</li>
 <li>Miguel de Miranda Alt</li>
</ul> 

### Relatório
***

Blackjack ou 21 é um jogo de cartas que pode ser jogado entre múltiplos jogadores com o objetivo de chegar a vinte e um ou o mais próximo possivel, é um passatempo bem popular e apesar de sua origem ser desconhecida, teve sua primeira ocorrência em um livro do autor espanhol Miguel de Cervantes. Como mencionado anteriormente, o objetivo do jogo é chegar a "21" ou o mais próximo possível e para isso usa-se um baralho de cinquenta e duas cartas divido em 4 naipes (sendo eles: Ouros, Paus, Copas e Espadas) com cartas numeradas de 2 a 10,  Vale mencionar também as cartas especiais de cada naipe: a Dama, o Valete, o Rei e por fim o Ás que é a carta mais intrigante, essas cartas possuem suas peculiaridades (afinal, como o próprio nome já sugere, são diferentes) o Rei, Valete e Dama valem 10 independentemente do naipe porém o Ás pode valer 1 ou 11, dependendo da mão do jogador ou do bom senso. Também adaptamos as regras do Dealer(O Computador), caso a soma das cartas dele seja menor que 15 ele obrigatóriamente terá que comprar mais cartas até que essa soma seja maior que 15, incluimos tambem a regra de que o Dealer sempre tem vantagem, por exemplo, caso empate entre algum jogador e o Dealer, o Dealer ganha. Por fim, adaptamos as regras caso esteja jogando sozinho, caso seja somente um jogador e o computador, as apostas serão dobradas pelo computador em caso de vitória do jogador.<br>
            
Sobre o trabalho,foram delimitados o máximo possível das funções para ajudar na fluidez do código tais como laços de repetição e ponteiro, dessa maneira tornou-se realizável um produto final coeso, fluído e orgânico que gera uma boa experiência para o usuário. Esse projeto foi desafiador do inicío ao fim , mas os maiores problemas enfrentados foram em relação ao Jogador e as cartas , a dificuldade se apresentou durante o processo de visualização em que várias perguntas eram conduzidas para determinar a procedência e a aplicação do código. As bibliotecas assistivas que foram utilizadas  são : "locale" , "ncurses" e "time". Aristóteles uma vez disse : "É fazendo que se aprende a fazer aquilo que se deve aprender a fazer" e essa frase mostrou-se verdadeira durante a confecção do código , afinal , foi onde realmente aprendemos o que já deveriamos ter aprendido durante o curso, compreendemos a melhor utilização do recurso "ponteiro", um tópico que antes era bem dificil de ser visualizado e utilizado, além disso aprendemos a explorar a biblioteca "nCurses" que foi muito útil durante a realização do código. Por fim , esse código foi construído em Linux com a utilização da plataforma "Atom" que permitiu com que todos os integrantes do grupo pudessem trabalhar no código ao mesmo tempo.<br>


### Bibliografia Utilizadas
---
[Bibliografia do Ncurses traduzida](https://terminalroot.com.br/ncurses/) <br>
[Conversão de char para int](https://www.tutorialspoint.com/how-do-i-convert-a-char-to-an-int-in-c-and-cplusplus) <br>
[Limpar o Console](https://www.geeksforgeeks.org/clear-console-c-language/) <br>
[Delay](https://www.geeksforgeeks.org/time-delay-c/) <br>
[Conversão de int para ponteiro](https://stackoverflow.com/questions/42221707/assigning-an-int-to-a-pointer-what-happens) <br>
[Inspiração para a incialização das Cartas](https://www.clubedohardware.com.br/topic/1309926-c%C3%B3digo-em-c-sobre-cartas/) <br>
[Apostilas consultadas](https://www.andrebrito.net/disciplinas/intro-cpp) <br>
