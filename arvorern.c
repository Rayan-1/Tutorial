#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define MAX_NO 10000
#define MAX_VALOR_NO 100000
#define TRUE 1
#define FALSE 0

typedef struct no *No;

typedef struct no{
	int valor;
	char cor;
	No dir,esq,pai;
}no;

struct rubronegra{
	no *raiz;
};

typedef struct rubronegra *Rubronegra;

No externo = NULL;

Rubronegra criarRubroNegra();
No criarNo(int valor);
No sucessor(No x);

void RotacaoEsquerda(Rubronegra arvore, No x);
void RotacaoDireita(Rubronegra arvore, No x);
void consertarInserir(Rubronegra arvore, No z);
int inserirArvore(Rubronegra arvore, int valor);
void moverPaiRN(Rubronegra arvore, No u, No v);
No buscarNo(No x, int valor);
void consertarRemover(Rubronegra arvore, No x);
void removerRN(Rubronegra arvore, No z);
int remover(Rubronegra arvore, int valor);
void imprimeArvore(No x);
void preOrdem(Rubronegra arvore);
int numAlea();
int quantNo(No no);
void liberarMemoria(Rubronegra pt);
void liberNo(No no);
int verificarRN(No raiz);
int verificarNo(No pt);
void execucaoTeste();

int main (int argc, char const *argv[]){
	srand(time(NULL));
	
	
	Rubronegra a = criarRubroNegra();
	int contadorNo = 0;
	printf("Executando arvore de apresentacao\n");
	
	while(contadorNo < 100){
		inserirArvore(a, contadorNo);
		contadorNo++;
	}
	
	preOrdem(a);
	
	while(contadorNo > 89){
		remover(a,contadorNo);
		contadorNo--;
	}
	preOrdem(a);
	
	return 0;
	
}

void execucaoTeste(){
	
	int countRubroNegras = 0;//MAX 1000
	int countNo = 0;//MAX 10000
	int numGerado = 0;
	Rubronegra arvore = criarRubroNegra();
	
	while(countRubroNegras < 1000){
		printf("ARVORE%d\n", 1+countRubroNegras);
		printf("INSERINDO NOS\n");
		arvore  = criarRubroNegra();
		countNo=0;
		
		while(countNo < MAX_NO){
			numGerado = numAlea();
			if(buscarNo(arvore->raiz,numGerado)->valor == 0){
				inserirArvore(arvore, numGerado);
				countNo++;

     }
}

       preOrdem(arvore);
       
       printf("\tREMOVENDO NOS\n");
       
       while(countNo > (MAX_NO - 1000)){
		   remover(arvore, arvore->raiz->valor);
		   countNo--;
	   }
	   
	   preOrdem(arvore);
	   
	   countRubroNegras++;
	   liberarMemoria(arvore);
	   arvore->raiz = externo;
   }
}

//criar a arvore rubro negra

Rubronegra criarRubroNegra(){
	if(externo == NULL){
		externo = (No) malloc(sizeof(struct no));
		externo->cor = 'N';
		externo->dir = externo;
		externo->esq = externo;
		externo->pai = externo;
		externo->valor = 0;
	}
	Rubronegra novaArvore = (Rubronegra) malloc(sizeof(struct rubronegra));
	novaArvore-> raiz = externo;
	return novaArvore;
}

//criar um nó da rubro negra

No criarNo(int valor){
	No novo = (No) malloc(sizeof(struct no));
	novo->valor = valor;
    novo->cor = 'R';
    novo->dir = externo;
    novo->esq = externo;
    novo->pai = externo;
    return novo;
}
	
//Buscar o sucessor
No sucessor(No x){
	No y = x;
	while (y->esq != externo)
	y = y->esq;
	return y;
}

//Rotação a esquerda

void RotacaoEsquerda(Rubronegra arvore, No x){
	No y;
	y = x->dir;
	x->dir = y->esq;
	if(y->esq != externo){
		y->esq->pai = x;
	}
	y->pai = x->pai;
	if(x->pai == externo){
		arvore->raiz = y;
	}else if(x == x->pai->esq){
		x->pai->esq = y;
	}else{
		x->pai->dir = y;
	}
	y->esq = x;
	x->pai = y;
}

//Rotacao a direita

void RotacaoDireita(Rubronegra arvore, No x){
	No y;
	y = x->esq;
	x->esq = y->dir;
	if(y->dir != externo){
		y->dir->pai = x;
	}
	
	y->pai = x->pai;
	if(x->pai == externo){
		arvore->raiz = y;
	}else if (x == x->pai->dir){
		x->pai->dir = y;
	}
	else{
		x->pai->esq = y;
	}
	y->dir = x;
	x->pai = y;
}
//Conserta a arvore de acordo com os casos de inserção

void consertarInserir(Rubronegra arvore, No z){
	No y;
	while(z->pai->cor == 'R'){
		if(z->pai == z->pai->pai->esq){
			y = z->pai->pai->dir;
			if(y->cor == 'R'){ //Caso 1 - Tio rubro
				z->pai->cor = 'N';
				y->cor = 'N';
				z->pai->pai->cor = 'R';
				z = z->pai->pai;
			}else{ //Caso 2
				if(z == z->pai->dir){
					z = z->pai;
					RotacaoEsquerda(arvore, z);
				}
				z->pai->cor = 'N'; //Caso 3
				z->pai->pai->cor = 'R';
				RotacaoDireita(arvore,z->pai->pai);
			}
		}else{
			y = z->pai->pai->esq;
			if(y->cor == 'R'){
				z->pai->cor = 'N';
				y->cor = 'N';
				z->pai->pai->cor = 'R';
				z = z->pai->pai;
			}else{
				if(z == z->pai->esq){
					z = z->pai;
					RotacaoDireita(arvore,z);
	  }
	
	        z->pai->cor = 'N';
	        z->pai->pai->cor = 'R';
	        RotacaoEsquerda(arvore,z->pai->pai);
		}
	}
}

 arvore->raiz->cor = 'N';
}

//Cria um nó com o valor inserido e insere na arvore
int inserirArvore(Rubronegra arvore, int valor){
	No y,x,z;
	
	z = criarNo(valor);
	y = externo;
	x = arvore->raiz;
	
	while(x != externo){
		y = x;
		if(z->valor == x->valor){
			return 1;
		}
		if(z->valor < x-> valor){
			x = x->esq;
		}
		else{
			x = x->dir;
		}
	}
	
	z->pai = y;
	if(y == externo){
		arvore->raiz = z;
	}
	else if(z->valor < y->valor){
		y->esq = z;
	}
	else if (z->valor < y ->valor){
		y->esq = z;
	}
	else{
		y->dir = z;
	}
	z->esq = externo;
	z->dir = externo;
	z->cor = 'R';
	
	consertarInserir(arvore,z);
	return 0;
}

//Ultilizando na remoção

void moverPaiRN(Rubronegra arvore, No u, No v){
	if(u->pai == externo){
		arvore->raiz = v;
	}else if(u==u->pai->esq){
		u->pai->esq = v;
	}else{
		u->pai->dir = v;
	}
	v->pai = u->pai;
}

//Busca nó na arvore

No buscarNo(No x, int valor){
	if( x == externo || x->valor == valor){
		return x;
	}
	if(valor < x->valor){
		buscarNo(x->esq,valor);
	}
	else{
		buscarNo(x->dir,valor);
	}

}

//Conserta arvore apos a remoção

void consertarRemover(Rubronegra arvore, No x){
	No w;
	while(x!=arvore->raiz && x->cor == 'N'){
		if(x == x->pai->esq){
			w = x->pai->dir;
			if(w->cor == 'R'){//caso 1
				w->cor = 'N';
				x->pai->cor = 'R';
				RotacaoEsquerda(arvore, x->pai);
				w = x->pai->dir;
			}
			if(w->esq->cor == 'N' && w->dir->cor == 'N'){ //caso 2
				w->cor = 'R';
				x = x->pai;
			}else{
                                     if(w->dir->cor == 'N'){ // Caso 3
                                      w->esq->cor = 'N';
                                      w->cor = 'R';
                                      RotacaoDireita(arvore, w);
                                      w = x->pai->dir;
                                    } 
                                     w->cor = x->pai->cor; // Caso 4
                                     x->pai->cor = 'N';
                                     w->dir->cor = 'N';
                                     RotacaoEsquerda(arvore, x->pai);
                                     x = arvore->raiz;
                                    }
                                    }else{

                                      w = x->pai->esq;
                                      if(w->cor == 'R'){
                                         w->cor = 'N';
                                         x->pai->cor = 'R';
                                         RotacaoDireita(arvore, x->pai);
                                         w = x->pai->esq;
                                      }
                                      if(w->dir->cor == 'N' && w->esq->cor == 'N'){
                                         w->cor = 'R';
                                         x = x->pai;
                                     }else{
                                        if(w->esq->cor == 'N'){
                                           w->dir->cor = 'N';
                                           w->cor = 'R';
                                           RotacaoEsquerda(arvore,w);
                                           w = x->pai->esq;
                                     }
                                           w->cor = x->pai->cor;
                                           x->pai->cor = 'N';
                                           w->esq->cor = 'N';
                                           RotacaoDireita(arvore,x->pai);
                                           x = arvore->raiz;
                          }
            }
}
     x->cor = 'N';
}

	

//remove o nó
void removerRN(Rubronegra arvore, No z){
	No y = z;
	No x;
	char corY = y->cor;
	if(z->esq == externo){
		x = z->dir;
		moverPaiRN(arvore, z,z->dir);
		}else if(z->dir == externo){
			x = z->esq;
		moverPaiRN(arvore,z,z->esq);
			}else{
				y = sucessor(z->dir);
				corY = y->cor;
				x = y->dir;
				if(y->pai == z){
					x->pai = y;
				}else{
					moverPaiRN(arvore,y,y->dir);
					y->dir = z->dir;
					y->dir->pai = y;
				}
				    moverPaiRN(arvore,z,y);
				    y->esq = z->esq;
				    y->esq->pai = y;
				}
				if(corY == 'N'){
					consertarRemover(arvore,x);
				}
				arvore->raiz->cor = 'N';
		}
	
		
//busca o nó que deseja remover
int remover(Rubronegra arvore, int valor){
	No z = buscarNo(arvore->raiz,valor);
	No aux = z;
	if(z == externo){
		return 1;
	}else{
		removerRN(arvore, z);
	}
	free(aux);
	return 0;
}

//imprime arvore a partir do primeiro nó dado

void imprimeArvore(No x){
	printf("RN ou NAO?: %s\n", verificarRN(x) == TRUE? "SIM": "NAO");
	printf("\tNUMERO DE NOS: %d\n",quantNo(x));
}

//inicializar a impressão a partir da raiz
void preOrdem(Rubronegra arvore){
	imprimeArvore(arvore->raiz);
	printf("\n");
}

//auxilia no sorteio aleatorio dos numeros
int numAlea(){
	return(rand()% MAX_VALOR_NO)+1;
}

//conta a quantidade de nó existe recursivamente
int quantNo(No raiz){
	if(raiz == externo){
		return 0;
	}
	   return 1 + quantNo(raiz->esq) + quantNo(raiz->dir);
   }
   
//libera memória
void liberarMemoria(Rubronegra pt){
	if(pt->raiz != externo){
		liberNo(pt->raiz->dir);
		liberNo(pt->raiz->esq);
		free(pt);
	}
}

//libera nó
void liberNo(No no){
	if(no != externo){
		liberNo(no->esq);
		liberNo(no->dir);
		free(no);
	}
}

int verificarRN(No raiz){
	No aux = raiz;
	if(aux->cor == 'R'){
		return FALSE;
	}
	
	int verificadorEsq = verificarNo(aux->esq);
	int verificadorDir = verificarNo(aux->dir);
	
	if(verificadorDir == FALSE || verificadorEsq == FALSE){
		return FALSE;
	}else{
		return TRUE;
	}
}


//verificar a consistencia nó a nó
int verificarNo(No pt){
	if(pt == externo){// caso base como numero externo
	return TRUE;
}


if(pt->cor == 'R'){
	if(pt->dir->cor == 'N' && pt->esq->cor == 'N'){
		int verificadorEsq = verificarNo(pt->esq);
		int verificadorDir = verificarNo(pt->dir);
		if(verificadorDir == FALSE || verificadorEsq == FALSE){
			return FALSE;
		}else{
			return TRUE;
		}
}else{
		return FALSE;
	}
}else{
	int verificadorEsq = verificarNo(pt->esq);
	int verificadorDir = verificarNo(pt->dir);
	if(verificadorDir == FALSE || verificadorEsq == FALSE){
		return FALSE;
	}else{
		return TRUE;
	}
}
}

	



   
	
			

