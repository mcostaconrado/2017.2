#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include "mapa.h"

struct smapa {
  int chave;
  int conteudo;
  short int bf; //fator de balanceamento
  struct smapa* esq;
  struct smapa* dir;
};

static Mapa* cria_no(int c, int novodado);
static Mapa* insere2(Mapa *m, int chave, int novodado, int *cresceu);
static Mapa* corrige_dir(Mapa *m);
static Mapa* corrige_esq(Mapa *m);
static Mapa* rotaciona_dir(Mapa *m);
static Mapa* rotaciona_esq(Mapa *m);

static Mapa* cria_no(int c, int novodado) {
  Mapa *m = (Mapa*)malloc(sizeof(Mapa));
  if (m != NULL) {
    m->esq = m->dir = NULL;
    m->chave = c;
    m->conteudo = novodado;
    m->bf = 0;
  }
  return m;
}

int max(int a, int b){
	return (a > b)? a : b;
}


Mapa* cria() {
  return NULL;									//faz o mapa apontar para NULL no começo. na função insere, se o mapa for null, um nó é alocado dinamicamente.
}

Mapa* insere (Mapa* m, int chave, int novodado) { 				//essa função não insere, de fato, um nó no mapa. Ela só passa o endereço da variável 
  int cresceu = 0;								                      //cresceu para outra função, que realmente insere.
  return insere2(m, chave, novodado, &cresceu);					//retorna o resultado da função abaixo - insere2() -
}








static Mapa* insere2(Mapa *m, int chave, int novodado, int *cresceu) {		//essa função, de fato, insere o nó no mapa.
  if (m == NULL) {								          //se chega aqui, é porque a árvore está vazia, ou seja, é hora de criar um novo nó.
    m = cria_no(chave, novodado);						//portanto, a árvore cresceu, alterando o valor da variável cresceu.
    *cresceu = 1;									
  }

  else if (chave < m->chave) {
    m->esq = insere2(m->esq, chave, novodado, cresceu);
    if (*cresceu){
      switch(m->bf){

      case -1: /* já era -1, não pode crescer à esquerda */
        m = corrige_esq(m);
        *cresceu = 0;
        break;

      case 0: /* estava equilibrada, pode aumentar de um lado avisando para cima que cresceu*/
        m->bf = -1;
        break;

      case 1: /* ficou equilibrada, então não cresceu em altura */
        m->bf = 0;
        *cresceu = 0;
        break;
      }
    }
  }

  else if (chave > m->chave) {							//se a chave a ser inserida for maior que a chave corrente, devemos ir para o ramo à direita do mapa.
    m->dir = insere2(m->dir, chave, novodado, cresceu);
    if(*cresceu) {
      switch (m->bf) {

        case 1: /* já era 1, não pode crescer a direita */
          m = corrige_dir(m);
          *cresceu = 0;
          break;

        case 0: /* estava equilibrada, pode aumentar de um lado  avisando para cima que cresceu*/
          m->bf = 1;
          break;

        case -1: /* ficou equilibrada, então não cresceu em altura */
          m->bf = 0;
          *cresceu = 0;
          break;
      }
    }
  }
  return m;
}

static Mapa* corrige_esq(Mapa *m) {
  if (m->esq->bf == -1){
    m->bf = m->esq->bf = 0;
    return rotaciona_dir(m);
  }
  else{
    //m->bf = m->esq->bf = m->esq->dir->bf = 0;
    Mapa *n = m->esq->dir;
    switch(n->bf){
      case -1: 
        m->bf = 1;
        m->esq->bf = 0;
        break;

      case 0:
        m->bf = 0;
        m->esq->bf = 0;
        break;

      case 1:
        m->bf = 1;
        m->esq->bf = 0;
        break;
    }
    n->bf = 0;
    m->esq = rotaciona_esq(m->esq);
    return rotaciona_dir(m);
  }
}


static Mapa* corrige_dir(Mapa *m) {
  if (m->dir->bf == 1) {
    m->bf = m->dir->bf = 0;
    return rotaciona_esq(m);
  }
  else/* if (m->dir->bf == -1) */ {
    Mapa *n = m->dir->esq;
    switch(n->bf){
      case 1:
        m->bf = -1;
        m->dir->bf = 0;
        break;
      case 0:
        m->bf = 0;
        m->dir->bf = 0;
        break;

      case -1:
        m->bf = -1;
        m->dir->bf = 0;
        break;
    }
    n->bf = 0;
    m->dir = rotaciona_dir(m->dir);
    return rotaciona_esq(m); 
  }
}

static Mapa* rotaciona_dir(Mapa *m) {
  Mapa* esq = m->esq;
  m->esq = esq->dir;
  esq->dir = m;
  return esq;
}

static Mapa* rotaciona_esq(Mapa *m) {
  Mapa* dir = m->dir;
  m->dir = dir->esq;
  dir->esq = m;
  return dir;
}

int busca (Mapa *m, int chave) {
  if (m == NULL) {
    return -1;
  }
  else if (m->chave == chave) {
    return m->conteudo;
  }
  else if (chave < m->chave) {
  return busca(m->esq, chave);
  }
  else if (chave > m->chave) {
    return busca(m->dir, chave);
  }
  else {
    return -1;
  }
}


void destroi (Mapa *m) {
  if (m != NULL) {
    destroi(m->esq);
    destroi(m->dir);
    free(m);
  }
}


void debug_mostra_mapa_int (Mapa* m) {

  printf("(");
  if (m != NULL) {
    printf("%d-%d", m->chave,m->bf);
    debug_mostra_mapa_int(m->esq);
    debug_mostra_mapa_int(m->dir);
  }
  printf(")");
}

void debug_mostra_mapa (Mapa* m) {
  debug_mostra_mapa_int (m); printf ("\n");
}




