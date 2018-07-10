/*
* Universidade de Brasilia
* Instituto de Ciencias Exatas
* Departamento de Ciencia da Computacao
*
* Algoritmos e Programação de Computadores – 1/2018
*
* Aluno(a): Cleidson Deusdara Chagas de Oliveira
* Matricula: 18/0052250
* Turma: A
* Versão do compilador: gcc (Ubuntu 7.3.0-16ubuntu3) 7.3.0 
* Descricao: BShoot eh um jogo arcade a onde o jogador avanca contra dificuldades buscando a maior pontuacao possivel
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h> 
#include <fcntl.h>
#include <time.h>
#ifndef _WIN32
	#define CLEAR "clear"
	int kbhit(){
		struct termios oldt, newt;
		int ch, oldf;
		tcgetattr(STDIN_FILENO,&oldt);
		newt = oldt;
		newt.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &newt);
		oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
		fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
		ch = getchar();
		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
		fcntl(STDIN_FILENO, F_SETFL, oldf);
		if(ch != EOF){
		ungetc(ch,stdin);
		return 1;
		}
		return 0;
	}
	int getch(void) {
		int ch;
		struct termios oldt;
		struct termios newt;
		tcgetattr(STDIN_FILENO,&oldt);
		newt = oldt;
		newt.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &newt);
		ch = getchar();
		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
		return ch;
	}
	/* Definicao de teclas */
	#define ESC    27
	/******** Definicao de cores *********/
	#define PRETO       printf("%c[30m", ESC)
	#define VERMELHO    printf("%c[31m", ESC)
	#define VERDE       printf("%c[32m", ESC)
	#define AMARELO     printf("%c[33m", ESC)
	#define AZUL        printf("%c[34m", ESC)
	#define MAGENTA     printf("%c[35m", ESC)
	#define CIANO       printf("%c[36m", ESC)
	#define BRANCO      printf("%c[37m", ESC)
	#define NEGRITO	  printf("\033[1m")
	#define RESETCOLOR  printf("\033[0m")
	/******** Definiciao Fundo de cores **/
	#define FPRET       printf("%c[40m", ESC)
	#define FVERMELH    printf("%c[41m", ESC)
	#define FVERD       printf("%c[42m", ESC)
	#define FAMAREL     printf("%c[43m", ESC)
	#define FAZU        printf("%c[44m", ESC)
	#define FMAGENT     printf("%c[45m", ESC)
	#define FCIAN       printf("%c[46m", ESC)
	#define FBRANC      printf("%c[47m", ESC)
#else
	#include <conio.h>
	#define CLEAR "cls"
	#define VERMELHO		printf("\033[31m")
	#define VERDE			printf("\033[32m")
	#define AMARELO		printf("\033[33m")
	#define AZUL			printf("\033[34m")
	#define ROXO 			printf("\033[35m")
	#define CIANO 			printf("\033[36m")
	#define BRANCO 		printf("\033[37m")
	#define PRETO 			printf("\033[30m")
	#define NEGRITO 		printf("\033[1m")
	#define RESETCOLOR 	printf("\033[0m") 
#endif
/*Codigos Globais*/
typedef struct {
	int combustivel;
	long long int pontos;
	int buff;
	int vivo;
	int armas[3][2];
	char elementos[5];
	int dificuldade;
	int probX;
	int probF;
	int probE;
	int probO;
	int probX2;
	int probF2;
	int probE2;
	int probO2;
	int rank;
	char nome[11];
} BShoot; /*Definindo a estrutura do sistema */

typedef struct{
	char tipo;
	int vida;
} NPCs; /* Definindo a estrutura dos elementos */

typedef struct {
		long long int pontos;
		char nome[11];
	} Jogador; /* Definindo a estrutura do jogador */

int lrg = 135,
	 alt = 10;

/*Programa*/
void Zera(NPCs* elem){
	elem->tipo = ' ';
	elem->vida = -1;
}

void Logo(int i){ /* Logo do Game */
	if(i==0){
		VERMELHO;
		printf("00000000   000000000   000  000  0000000000 0000000000  0000000000 \n");
		RESETCOLOR;
		printf("00   0000  0000        000  000  000    000 000    000  0000000000 \n00  0000    0000       00000000  000    000 000    000      00\n0000000      000000    00000000  000    000 000    000      00\n00  0000        0000   000  000  000    000 000    000      00\n00   0000       0000   000  000  000    000 000    000      00\n");
		VERMELHO;
		printf("00000000   00000000    000  000  0000000000 0000000000      00\n");
		RESETCOLOR;
	}
	if(i==1){
		VERMELHO;
		printf("\t\t00000000   000000000   000  000  0000000000 0000000000  0000000000 \n\t\t00   0000  0000        000  000  000    000 000    000  0000000000 \n\t\t00  0000    0000       00000000  000    000 000    000      00\n\t\t0000000      000000    00000000  000    000 000    000      00\n\t\t00  0000        0000   000  000  000    000 000    000      00\n\t\t00   0000       0000   000  000  000    000 000    000      00\n\t\t00000000   00000000    000  000  0000000000 0000000000      00\n\n\t\t\t01010101  0101010  101      010 101010101\n\t\t\t01       010   010 0101    0101 01\n\t\t\t10       101   101 10 01  01 10 10\n\t\t\t01  0101 010101010 01  0101  01 010101010\n\t\t\t10    10 101010101 10   01   10 10\n\t\t\t01    01 010   010 01        01 01\n\t\t\t10101010 101   101 10        10 101010101\n\n\t\t\t0101010101 101      101 101010101  01010101\n\t\t\t101    010 010      010 01         10     01\n\t\t\t010    001 101      101 10         01     10\n\t\t\t101    010 010      010 01010101   10101010\n\t\t\t010    100  010    010  10         01  01  \n\t\t\t101    010   010  101   01         10   10 \n\t\t\t0101010101    010101    101010101  01    01\n");
		RESETCOLOR;
	}
}

void PowerO(NPCs elem[alt][lrg], BShoot* sistema){ /* Esta funcao deleta todos os X do mapa */
	int i,j, soma = 0;
	for(i=0;i<alt;i++) {
		for(j=0;j<lrg;j++) {
			if(elem[i][j].tipo == 'X') {
				soma++;
				Zera(&elem[i][j]);
			}
		}
	}
	soma = soma * 10;
	sistema->pontos += soma;
}

int Impacto(NPCs elem[alt][lrg], BShoot* sistema,int opcoes,int i, int j){ /*Controle de Impacto de Elementos e Projeteis */
	if(opcoes == 0){
		if(elem[i][j].tipo == sistema->elementos[0]){
				sistema->vivo = 0;
				return 1;
		}
		else if(elem[i][j].tipo == sistema->elementos[1]){
				sistema->combustivel += 40; 
				return 1;
		}
				return 0; 
	} else if(opcoes == 1){
		if(elem[i][j].tipo != sistema->elementos[2]){
				if(elem[i][j].tipo == sistema->elementos[0]){
					sistema->pontos +=50;
					elem[i][j].vida = 0;
					return 1;
				} else if(elem[i][j].tipo == sistema->elementos[1]) {
					return 1;					
				} else if(elem[i][j].tipo == sistema->elementos[4]) {
					if(elem[i][j].vida > 1)
						elem[i][j].vida--;
					else{
						PowerO(elem,sistema);
						return 1;
					}
				}
				return 0;
		}  
	}
	return 0;
}

void MovimentoJogador(int* i, int* j, NPCs elem[alt][lrg],BShoot* sistema){/* Controle de Movimentos do Jogador */
	char mov;
	NPCs salvo;
	mov = getch(); /*Armazena a tecla pressionada */
	switch(mov){ /*Cima, baixo, esquerdo, direito respectivamente W,S,A,D -- K atira */
		case 'w':
		case 'W':    
				if(elem[*i-1][*j].tipo != '#'){
					sistema->combustivel -=2;
					if(elem[*i-1][*j].tipo != sistema->elementos[2]){
						Impacto(elem, sistema, 0,*i-1,*j);
						salvo = elem[*i][*j];
						elem[--*i][*j] = salvo;
						Zera(&elem[*i+1][*j]);
					} 
					else{
						salvo = elem[*i][*j];
						elem[--*i][*j] = salvo;
						Zera(&elem[*i+1][*j]);
					}
				}
		break;
		case 's':
		case 'S':
				if(elem[*i+1][*j].tipo != '#'){
					sistema->combustivel -=2;
					if(elem[*i+1][*j].tipo != sistema->elementos[2]){
						Impacto(elem, sistema, 0,*i+1,*j);
						salvo = elem[*i][*j];
						elem[++*i][*j] = salvo;
						Zera(&elem[*i-1][*j]);
					} 
					else {
						salvo = elem[*i][*j];
						elem[++*i][*j] = salvo;
						Zera(&elem[*i-1][*j]);
					}
				}
		break;
		case 'a':
		case 'A':    
				if(*j != 0){
					sistema->combustivel -=2;
					if(elem[*i][*j-1].tipo != sistema->elementos[2]){
						Impacto(elem, sistema, 0,*i,*j-1);
						salvo = elem[*i][*j];
						elem[*i][--*j] = salvo;
						Zera(&elem[*i][*j+1]);
					} 
					else {
						salvo = elem[*i][*j];
						elem[*i][--*j] = salvo;
						Zera(&elem[*i][*j+1]);
					}
				}
		break;
		case 'd':
		case 'D':
				if(*j != lrg-2){
					sistema->combustivel -=2;
					if(elem[*i][*j+1].tipo != sistema->elementos[2]){
						Impacto(elem, sistema, 0,*i,*j+1);
						salvo = elem[*i][*j];
						elem[*i][++*j] = salvo;
						Zera(&elem[*i][*j-1]);
					} 
					else {
						salvo = elem[*i][*j];
						elem[*i][++*j] = salvo;
						Zera(&elem[*i][*j-1]);
					}
				}
		break;
		case 'k':
		case 'K':
				if(*j != lrg-1){
					sistema->combustivel -=3;
					if(Impacto(elem,sistema,1,*i,*j+1)){
						Zera(&elem[*i][*j+1]);
					} else {
						elem[*i][*j+1].tipo = '>';
						elem[*i][*j+1].vida = -1;
					}
				}
		break;
	}
}

NPCs Elementos(BShoot* sistema,int opcao){ /* Controle de Elementos no Mapa */
	if(opcao == 0){
		sistema->elementos[0] = 'X';
		sistema->elementos[1] = 'F';
		sistema->elementos[2] = ' ';
		sistema->elementos[3] = '>';
		sistema->elementos[4] = 'O';
		sistema->probE = ((999-sistema->probX)-sistema->probF)-sistema->probO;
		sistema->probX = sistema->probX+sistema->probE;
		sistema->probF = sistema->probF+sistema->probX;
		sistema->probO = sistema->probO+sistema->probF;
	}
	if (opcao == 1){
		NPCs elem;
		int seedElemento = rand()%1000;
		if(seedElemento < sistema->probE){
				elem.tipo = sistema->elementos[2];
				elem.vida = -1;
				return elem;
		} else if( (seedElemento >= sistema->probE) && (seedElemento < sistema->probX)){
				elem.tipo = sistema->elementos[0];
				elem.vida = 1;
				return elem;
		} else if( (seedElemento >= sistema->probX) && (seedElemento < sistema->probF)) {
				elem.tipo = sistema->elementos[1];
				elem.vida = 1;
				return elem;
		} else if( (seedElemento >= sistema->probF) && (seedElemento <= sistema->probO)) {
				elem.tipo = sistema->elementos[4];
				int seedVida = (rand()%5)+1;
				elem.vida = seedVida;
				return elem;
		}
	} 
}

void GeraElementos(NPCs elem[alt][lrg], BShoot* sistema){ /* Gera Novos Elementos no Mapa */
	int i, j = lrg-1;
	for(i=0;i<alt;i++){ 
		if( (elem[i][j].tipo == ' ') && (elem[i][j].tipo != '#') && (elem[i][j].tipo != '+') ){
					elem[i][j] = Elementos(sistema,1);            
		}
	}
}

void MovimentoElementos(NPCs elem[alt][lrg], int posI, int posJ,BShoot* sistema){ /*Movimenta todos os elementos exceto jogador */
	int i,j;
	NPCs salvo;
	for(i=0;i<alt;i++){ /* Escaneia a Matriz para Movimento de Projetil */
		for(j=lrg-1;j>=0;j--){
				if(elem[i][j].tipo == '>'){ /* Checa se eh um projetil */
					if(elem[i][j+1].tipo != sistema->elementos[2]){
						if(Impacto(elem,sistema,1,i,j+1)){
							Zera(&elem[i][j]);
							Zera(&elem[i][j+1]);
						} else {
							Zera(&elem[i][j]);
						}
					} else if (j != lrg-1){
						elem[i][j+1] = elem[i][j];
						Zera(&elem[i][j]);
					} else
						Zera(&elem[i][j]);
				}
		}
	}
    
	for(i=0;i<alt;i++){ /* Escaneia a Matriz para Movimento de Elementos Gerais */
		for(j=0;j<lrg;j++){
				salvo = elem[i][j]; /* Salva o elemento analisado */
				if( (elem[i][j].tipo != '#') && (elem[i][j].tipo != elem[posI][posJ].tipo) && (elem[i][j].tipo != sistema->elementos[3]) && (elem[i][j].tipo != ' ') ){ /* Checa se nao e o personagem ou a borda ou um projetil */
					if(j != 0){
						if(elem[i][j].tipo == sistema->elementos[2]){
							Zera(&elem[i][j]);
						}
						if( (elem[i][j-1].tipo != elem[posI][posJ].tipo) && (elem[i][j-1].tipo != sistema->elementos[3]) ){ /* Checa se ao se mover ira no personagem ou projetil */
								elem[i][j-1] = salvo;								
								Zera(&elem[i][j]);	
						} else if(elem[i][j-1].tipo == elem[posI][posJ].tipo){ /* Se for colidir com o personagem */
								Impacto(elem, sistema,0,i,j);
								Zera(&elem[i][j]);									
						}
						else if(elem[i][j-1].tipo == sistema->elementos[3]){ /*Se for colidir com o projetil */
								if(Impacto(elem,sistema,1,i,j)){
									Zera(&elem[i][j]);
									Zera(&elem[i][j-1]);
								} else{
									salvo = elem[i][j];
									Zera(&elem[i][j]);
									elem[i][j-1] = salvo;								
								}
						}
					}
					if(j == 0){ /* Se ta no final da matriz, apenas apaga */
						Zera(&elem[i][j]);
					}
				}
		} 
	}
}
    

void TelaDoJogo(NPCs elem[alt][lrg], BShoot* sistema){
		/*Placar */
		printf("Pontos: %lld\nCombustivel: %d\n", sistema->pontos,sistema->combustivel);
		/*Fim Placar */
		int i,j;
		for(i=0;i<alt;i++){ /* Imprime a tela do sistema */
				for(j=0;j<lrg;j++){
					if(elem[i][j].tipo == sistema->elementos[0])
						VERMELHO;
					if(elem[i][j].tipo == sistema->elementos[1])
						VERDE;
					if(elem[i][j].tipo == sistema->elementos[4])
						AZUL; 
					printf("%c", elem[i][j].tipo);
					RESETCOLOR;
				}
				printf("\n");
		}
}

void Rank(BShoot *sistema,int opc){ /* Funcao Responsavel por ler e escrever o ranking */
	FILE *rank;
	Jogador ranked[10];
	int i,j,t;
	if(opc == 1) {
		rank = fopen("rank.bin","rb");
		fread(&ranked,sizeof(Jogador),10,rank);
		fclose(rank);
		if(ranked[9].pontos < sistema->pontos) {
			ranked[9].pontos = sistema->pontos;
			for(t=0;t<11;t++) {
				ranked[9].nome[t] = sistema->nome[t];
			}
			Jogador aux;
			for(i=9;i>0;i--){
				if(ranked[i].pontos > ranked[i-1].pontos) {
					aux.pontos = ranked[i-1].pontos;
					ranked[i-1].pontos = ranked[i].pontos;
					ranked[i].pontos = aux.pontos;
					for(j=0;j<11;j++) {
						aux.nome[j] = ranked[i-1].nome[j];						
						ranked[i-1].nome[j] = ranked[i].nome[j];						
						ranked[i].nome[j] = aux.nome[j];
					}
				}
			}
			rank = fopen("rank.bin","wb");
			fwrite(&ranked,sizeof(Jogador),10,rank);
			fclose(rank);	
		}
	} else if(opc == 2) {
		rank = fopen("rank.bin","rb");
		fread(&ranked,sizeof(Jogador),10,rank);
		fclose(rank);
		printf("\t\tP:   NOME:\t\t\tPONTOS:\n");
		i = 0;
		while( (i<10) ) {
				if(i == 0)
					VERMELHO;
				if(i == 1)
					VERDE;
				if(i == 2)
					AMARELO;
				printf("\t\t%d. %s \t\t\t%lld\n",i+1,ranked[i].nome,ranked[i].pontos);
				RESETCOLOR;
				i++;
		}
	}
}


void GameOver(BShoot* sistema){ /*Funcao da Tela Game Over*/
	setbuf(stdin, NULL);
	system(CLEAR);
	Logo(1);
	setbuf(stdin, NULL);
	if(sistema->combustivel <= 0){
		printf("\t\t Seu combustivel acabou :/\t\t\tMaldita Greve!\n");
	} else{
		printf("\t\t\t\tVoce foi atingido por um asteroide\n\tBoa Sorte na Proxima!");
	}
	printf("\t\t\t\tSua pontuacao nesta rodada foi: %lld\n\t\t\t\tAperte V para voltar ao menu\n", sistema->pontos);
	int np = 0;
	setbuf(stdin, NULL);
	do{
		char lol = getch();
				if((lol == 'V') || (lol == 'v'))
					np = 1;
		setbuf(stdin, NULL);
	} while(!np);   
}

void Jogo(BShoot* sistema, NPCs elem[alt][lrg]){ /* Funcao principal para rodar o jogo */
	/* Tamanho da tela, seed e posicial inicial do personagem */ 
	srand( time(NULL) );
	setbuf(stdin,NULL);
	int	posI = alt/2,
			posJ = 0,
			i,j; 
	/* Preenche o mapa */
	for(i=0;i<alt;i++){ 
		for(j=0;j<lrg;j++){
				if( (i == 0) || (i==alt-1) ) /* Preenche bordas superior e inferior com '#' */
					elem[i][j].tipo = '#';
				else if( (i == posI ) && (j == posJ) ) /* Posicao do Personagem */
					elem[i][j].tipo = '+';
				else {
					elem[i][j].tipo = ' '; /* Resto do Mapa */
					elem[i][j].vida = -1;
				}
		}
	}
	/* --- Fim Preparamento --- *
	* -Chamadas Pro Jogo Rodar */
	while((sistema->vivo) && (sistema->combustivel > 0)){
		TelaDoJogo(elem,sistema);
		/* Detecta se foi pressionado alguma tecla para controle */
		if(kbhit()) 
				MovimentoJogador(&posI, &posJ,elem,sistema);
		else
				sistema->combustivel--;
		MovimentoElementos(elem,posI,posJ,sistema); /*Movimenta a Tela */
		GeraElementos(elem,sistema); /* Gera novos Elemtnos no Mapa */
		sistema->pontos++;
		/* Aumenta a Dificuldade do Jogo com o tempo */
		if(sistema->pontos < 1000) {
			usleep(sistema->dificuldade);
		} else if(sistema->pontos < 2000) {
			usleep(sistema->dificuldade-1000);
			sistema->probX = sistema->probX2+20;
			sistema->probO = sistema->probO2;
			sistema->probF = sistema->probF2;
			Elementos(sistema,0);
		} else if(sistema->pontos < 2500) {
			usleep(sistema->dificuldade-1200);
			sistema->probX = sistema->probX2+30;
			sistema->probO = sistema->probO2-5;
			sistema->probF = sistema->probF2;
			Elementos(sistema,0);
		} else if(sistema->pontos < 3000) {
			usleep(sistema->dificuldade-1300);
			sistema->probX = sistema->probX2+30;
			sistema->probO = sistema->probO2-5;
			sistema->probF = sistema->probF2+10;
			Elementos(sistema,0);
		} else if(sistema->pontos < 3500) {
			usleep(sistema->dificuldade-1400);
			sistema->probX = sistema->probX2+35;
			sistema->probO = sistema->probO2-5;
			sistema->probF = sistema->probF2+10;
			Elementos(sistema,0);
		} else if(sistema->pontos < 4000) {
			sistema->probX = sistema->probX2+35;
			sistema->probO = sistema->probO2-6;
			sistema->probF = sistema->probF2+15;
			Elementos(sistema,0);
			usleep(sistema->dificuldade-1500);
		} else if(sistema->pontos < 4500) {
			sistema->probX = sistema->probX2+35;
			sistema->probO = sistema->probO2-7;
			sistema->probF = sistema->probF2+18;
			Elementos(sistema,0);
			usleep(sistema->dificuldade-1600);
		} else if(sistema->pontos < 5000) {
			usleep(sistema->dificuldade-1700);
			sistema->probX = sistema->probX2+45;
			sistema->probO = sistema->probO2-7;
			sistema->probF = sistema->probF2+19;
			Elementos(sistema,0);
		} else if(sistema->pontos < 6000) {
			sistema->probX = sistema->probX2+45;
			sistema->probO = sistema->probO2-7;
			sistema->probF = sistema->probF2+20;
			Elementos(sistema,0);
			usleep(sistema->dificuldade-1800);
		} else if(sistema->pontos < 7000) {
			usleep(sistema->dificuldade-1900);
		} else if(sistema->pontos < 8000) {
			usleep(sistema->dificuldade-10000);
			sistema->probX = sistema->probX2+60;
			sistema->probO = sistema->probO2-8;
			sistema->probF = sistema->probF2+20;
			Elementos(sistema,0);
		} else if(sistema->pontos < 10000) {
			sistema->probX = sistema->probX2+70;
			sistema->probO = sistema->probO2-9;
			sistema->probF = sistema->probF2+25;
			Elementos(sistema,0);
			usleep(sistema->dificuldade-15000);
		} else if(sistema->pontos < 15000) {
			usleep(sistema->dificuldade-17000);
			sistema->probX = sistema->probX2+75;
			sistema->probO = sistema->probO2-9;
			sistema->probF = sistema->probF2+25;
			Elementos(sistema,0);
		} else if(sistema->pontos < 20000) {
			usleep(sistema->dificuldade-18000);
			sistema->probX = sistema->probX2+130;
			sistema->probO = sistema->probO2-9;
			sistema->probF = sistema->probF2+30;
			Elementos(sistema,0);
		}
		system(CLEAR);
	}
	/* Quando sai do Loop o jogo foi encerrado */
	if(sistema->rank == 1){
		Rank(sistema,1);
	GameOver(sistema);
	}
}

void Inst(){ /* Instrucoes do jogo */
	system(CLEAR);
	Logo(0);
	printf("Bem vindo ao BShoot\nNeste jogo voce controla uma pequena nave (representada pelo simbolo '+' no mapa) que vaga por este grande universo\nEla se depara com asteroides (representados por 'X' no mapa) que tentam colidir contra ela\nPorem devido a sempre estar em movimento ela gasta combustivel a todo momento e para evitar que ele acabe\nPrecisa coletar os Fhant, asteroides especiais que servem para criar combustivel (representados por 'F' no mapa)\n\nInstrucoes:\nW -> Move para cima\nS -> Move para baixo\nA -> Move para esquerda\nD -> Move para direita\nK -> Atira contra asteroides\n\nElementos do Mapa\n+ -> Sua Nave\n");
	VERMELHO;
	printf("X ");
	RESETCOLOR;
	printf("-> Sao asteroides que vem em sua direcao, se eles te tocarem sua nave eh destruida.\n");
	VERDE;
	printf("F ");
	RESETCOLOR;
	printf("-> Sao asteroides que possuem materia para criar combustivel, ao toca-lo voce ganha 40 litros\n> -> Sao seus tiros que avancam a sua frente destruindo qualquer elemento\nPressione V para voltar ao menu\n");
	int np = 0;
	setbuf(stdin, NULL);
	do{
		char lol = getch();
				if((lol == 'V') || (lol == 'v'))
					np = 1;
		setbuf(stdin, NULL);
	} while(!np); 
}

void Menu(){
	int sair = 0,
		i, j;
	BShoot sistema;
	int mensagem = 0;
	FILE *config;
	/* Configurando arquivo de configuracoes e Ranking do jogo */
		config = fopen("config.txt", "r");
		if(config == NULL){
				config = fopen("config.txt", "w");
				fprintf(config,"50000 135 10 25 10 10 1");
				fscanf(config,"%i %i %i %i %i %i %i",&sistema.dificuldade, &lrg, &alt, &sistema.probX, &sistema.probF, &sistema.probO, &sistema.rank);
				fclose(config);
		} else{
				fscanf(config,"%i %i %i %i %i %i %i",&sistema.dificuldade, &lrg, &alt, &sistema.probX, &sistema.probF, &sistema.probO, &sistema.rank);
				fclose(config);
		}
		config = fopen("rank.bin", "rb");
		if(config == NULL){
				config = fopen("rank.bin", "wb");
				Jogador ranks[10];
				int kt;
				for(kt=0;kt<10;kt++) {
					ranks[kt].nome[0] = '\0';
					ranks[kt].pontos = 0;
				}
				fwrite(&ranks,sizeof(Jogador),10,config);
				fclose(config);
		} else{
				fclose(config);
		}
	while(!sair){ /* Menu de Opcoes */
		/* Definicoes Basicas para Novo Jogo */
		sistema.combustivel    = 400;
		sistema.vivo           = 1;
		sistema.buff           = 0;
		sistema.pontos         = 0;
		for(i=0;i<3;i++){
				for(j=0;j<2;j++){
					if((i == 0) && (j == 0))
						sistema.armas[i][j] = 1;
					else
						sistema.armas[i][j] = 0;
				}
		}
		
		if(!sistema.rank) {
				config = fopen("config.txt", "r");
				fscanf(config,"%i %i %i %i %i %i %i",&sistema.dificuldade, &lrg, &alt, &sistema.probX, &sistema.probF, &sistema.probO, &sistema.rank);
				fclose(config);
		} else {
				sistema.dificuldade = 65000;
				alt = 10;
				lrg = 132;
				sistema.probX = 25;
				sistema.probF = 10;
				sistema.probO = 10;
		}
		NPCs elem[alt][lrg];					
		/* Menu */
		system(CLEAR);
		Logo(0);
		VERMELHO;
		int sair1 = 0;
		int sair2 = 0;
		if(mensagem == 1) {
				printf("\t\t\tTabuleiro atualizado\n");
		} else if (mensagem == 2){
			if(sistema.rank)
				printf("\t\t\tModo Rankeado ATIVADO\n");
			else 
				printf("\t\t\tModo Rankeado DESATIVADO\n");
		}
		RESETCOLOR;
		mensagem = 0;
		int mensagem2 = 0;
		printf("1 - Jogar\n2 - Configuracoes\n3 - Ranking\n4 - Instrucoes\n5 - Sair\n");
		int opc;
		scanf("%d",&opc);
		switch(opc){
				case 1:
					system(CLEAR);
					int passaporte = 3;
					if(sistema.rank) {
						do {
							Logo(0);
							int passe = -1,
								 lpt = -1;
							printf("\t\t\t\tComo o modo rankeado esta ativo, digite seu nick. \n\t\t\t\t[MAX 10 MIN 3 CARACTERES] ");
							VERMELHO;
							if(passaporte == 1)
								printf("\n\t\t\t\tERRO: Nome fora do intervalo permitido ");
							RESETCOLOR;
							setbuf(stdin,NULL);
							do{
								if(lpt < 11)
									lpt++;
								sistema.nome[lpt] = getchar();
								passe++;								
							} while(sistema.nome[lpt] != '\n');
							if((passe > 2) && (passe < 11)) {
								sistema.nome[lpt] = '\0';
								passaporte = 0;
							} else {
								passaporte = 1;
							}
							system(CLEAR);
							setbuf(stdin,NULL);
						} while(passaporte == 1);
					}
					sistema.probX2 = sistema.probX;
					sistema.probO2 = sistema.probO;
					sistema.probF2 = sistema.probF;
					Elementos(&sistema,0);
					setbuf(stdin,NULL);
					Jogo(&sistema,elem);                
				break;
				case 2:
					do{
						system(CLEAR);
						Logo(0);
						printf("1 - Tabuleiro\n2 - NPCs\n");
						if(!sistema.rank){
								printf("3 - Ativar Modo Rankeado\n");
						} else 
								printf("3 - Desativar Modo Rankeado\n");
						printf("4 - Voltar\n");
						int opc1;
						scanf("%d", &opc1);
						switch(opc1){
							case 1:
								system(CLEAR);
								Logo(0);
								config = fopen("config.txt", "r");
								fscanf(config,"%i %i %i %i %i %i %i",&sistema.dificuldade, &lrg, &alt, &sistema.probX, &sistema.probF,&sistema.probO, &sistema.rank);
								fclose(config);
								printf("Atualmente o tabuleiro personalizado esta nas dimensoes %dx%d\nDigite primeiro a largura e depois a altura para altera-lo.\nLargura Maxima: 135 - Altura Maxima: 20\nLargura Minima: 30 - Altura Minima: 5\n", lrg,alt);
								scanf("%d %d", &lrg,&alt);
								int ok = 1;
								do {
									if((lrg < 30) || (lrg > 135) || (alt < 5) || (alt > 20)){
										ok = 0;
										printf("Valor de Largura ou Altura Invalido! Digite Novamente, primeiro a largura e depois a altura:\n");
										scanf("%d %d", &lrg,&alt);
									} else 
										ok = 1;
								} while(!ok);
								config = fopen("config.txt", "w");
								fprintf(config,"%d %d %d %d %d %d %d",sistema.dificuldade, lrg, alt, sistema.probX, sistema.probF, sistema.probO, sistema.rank);
								fclose(config);
								mensagem = 1;
							break;
							case 2:
									do{
										system(CLEAR);
										Logo(0);
										config = fopen("config.txt", "r");
										fscanf(config,"%i %i %i %i %i %i %i",&sistema.dificuldade, &lrg, &alt, &sistema.probX, &sistema.probF,&sistema.probO,&sistema.rank);
										fclose(config);
										VERMELHO;
										if(mensagem2 == 1)
											printf("\t\t\tProbabilidade do X atualizada\n");
										if(mensagem2 == 2)
											printf("\t\t\tProbabilidade do F atualizada\n");
										if(mensagem2 == 3)
											printf("\t\t\tProbabilidade do O atualizada\n");
										RESETCOLOR;
										printf("Probabilidade do NPC aparecer:\n");
										VERMELHO;
										printf("1 - X: %d%% - MAX: 30%% - MIN:5%% \n", sistema.probX);
										VERDE;
										printf("2 - F: %d%% - MAX: 30%% - MIN:1%% \n", sistema.probF);	
										RESETCOLOR;
										AZUL;
										printf("3 - O: %d%% - MAX: 30%% - MIN:1%% \n", sistema.probO);	
										RESETCOLOR;
										printf("4 - Voltar \n");
										printf("Digite qual opcao deseja alterar.\n");
										int opc2;
										scanf("%d",&opc2);
										switch(opc2) {
											case 1:
													printf("Digite a nova probabilidade de X sem o símbolo de porcentagem\n");
													scanf("%d", &sistema.probX);
													int ok3 = 1;
													do{
														if( (sistema.probX < 5) || (sistema.probX > 30) ){
															printf("Valor digitado invalido, digite novamente: \n");
															scanf("%d", &sistema.probX);
															ok3 = 0;
														} else 
															ok3=1;
													}while(!ok3);
													config = fopen("config.txt", "w");
													fprintf(config,"%d %d %d %d %d %d %d",sistema.dificuldade, lrg, alt, sistema.probX, sistema.probF,sistema.probO, sistema.rank);
													fclose(config);
													mensagem2 = 1;
											break;
											case 2:
													printf("Digite a nova probabilidade de F sem o símbolo de porcentagem\n");
													scanf("%d", &sistema.probF);
													int ok4 = 1;
													do{
														if( (sistema.probF < 1) || (sistema.probF > 30)){
															printf("Valor digitado invalido, digite novamente: \n");
															scanf("%d", &sistema.probF);
															ok4 = 0;
														} else 
															ok4=1;
													}while(!ok4);
													config = fopen("config.txt", "w");
													fprintf(config,"%d %d %d %d %d %d %d",sistema.dificuldade, lrg, alt, sistema.probX, sistema.probF, sistema.probO,sistema.rank);
													fclose(config);
													mensagem2 = 2;
											break;
											case 3:
													printf("Digite a nova probabilidade de O sem o símbolo de porcentagem\n");
													scanf("%d", &sistema.probO);
													int ok5 = 1;
													do{
														if( (sistema.probO < 1) || (sistema.probO > 30) ){
															printf("Valor digitado invalido, digite novamente: \n");
															scanf("%d", &sistema.probO);
															ok5 = 0;
														} else 
															ok5=1;
													}while(!ok5);
													config = fopen("config.txt", "w");
													fprintf(config,"%d %d %d %d %d %d %d",sistema.dificuldade, lrg, alt, sistema.probX, sistema.probF,sistema.probO, sistema.rank);
													fclose(config);
													mensagem2 = 3;
											break;
											case 4:
													sair1 = 1;
											break;
										}
									} while(!sair1);
							break;
							case 3:
								mensagem = 2;
								config = fopen("config.txt", "r");
								fscanf(config,"%i %i %i %i %i %i",&sistema.dificuldade, &lrg, &alt, &sistema.probX, &sistema.probF, &sistema.probO);
								fclose(config);
								config = fopen("config.txt", "w");
								if(sistema.rank) 
									fprintf(config,"%d %d %d %d %d %d 0",sistema.dificuldade, lrg, alt, sistema.probX, sistema.probF, sistema.probO);
								else 
									fprintf(config,"%d %d %d %d %d %d 1",sistema.dificuldade, lrg, alt, sistema.probX, sistema.probF, sistema.probO);
								fclose(config);
								config = fopen("config.txt", "r");
								fscanf(config,"%i %i %i %i %i %i %i", &sistema.dificuldade, &lrg, &alt, &sistema.probX, &sistema.probF,&sistema.probO, &sistema.rank);
								fclose(config);
							break;
							case 4:
								sair2 = 1;
							break;
						}
					} while(!sair2);
				break;
				case 3:
					system(CLEAR);
					Logo(0);
					Rank(&sistema,2);
					printf("Aperte V  para voltar ao menu. \n");
					int np = 0;
					setbuf(stdin, NULL);
					do{
						char lol = getch();
						if((lol == 'V') || (lol == 'v'))
							np = 1;
							setbuf(stdin, NULL);
						} while(!np); 
				break;
				case 4:
					Inst();
				break;
				case 5:
					sair = 1;
				break;
		}
	}
	setbuf(stdin,NULL);
}

int main(void){
	system(CLEAR);
	Logo(0);
	setbuf(stdin,NULL);
	char ok;
	do{
		printf("Bem vindo ao BShoot!\nAperte ENTER para continuar!\n");
		ok = getchar();
	}while(ok != '\n');
	Menu();
	return 0;
}	