#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "mapa.h"

struct smapa {
  int chave;
  int dados;
  Mapa* esq;
  Mapa* dir;
};

Mapa* cria (void) {
  return NULL;
}

static Mapa *cria_no (int c, int d) {
  Mapa *nn = (Mapa *)malloc(sizeof(Mapa));
  if (nn!=NULL) {
    nn->esq = nn->dir = NULL;
    nn->chave =c;
    nn->dados = d;
  }
  return nn;
}

Mapa *insere (Mapa *m, int chave, int d) {
  if (m==NULL) 
    return cria_no(chave, d);
  else if (chave < m->chave) 
    m->esq = insere(m->esq,chave,d);
  else  /* if (chave > m->chave) */ {
    m->dir = insere(m->dir,chave,d);
  }
  return m;
}

int busca (Mapa *m, int chave) {
  while (m!=NULL) {
    if (chave < m->chave)
      m = m->esq;
    else if (chave > m->chave)
      m = m->dir;
    else
      return m->dados; /* achou */
  }
  return -1;
}  


void debug_mostra_mapa_int (Mapa* m) {

  printf("[");
  if (m != NULL) {
    printf("%d ", m->chave);
    debug_mostra_mapa_int(m->esq);
    debug_mostra_mapa_int(m->dir);
  }
  printf("]");
}

void debug_mostra_mapa (Mapa* m) {
  debug_mostra_mapa_int (m); printf ("\n");
}

void destroi (Mapa *m) {
  if (m==NULL) return;
  destroi (m->esq);
  destroi (m->dir);
  free(m);
}

int iguais (Mapa *m1, Mapa *m2){
  if (m1 == NULL && m2 == NULL) //precisa desse if??
    return 1;
  
  if (m1->chave == m2->chave)
    return (m1->dados == m2->dados && iguais (m1->esq, m2->esq) && iguais (m1->dir, m2->dir));

  return 0;
}

	
int e_abb_aux (Mapa *m, int *maiorvisto) {
  /*if (m == NULL)
    return 1;

  if (m->esq != NULL){
    if (m->chave > m->esq->chave){
      return e_abb(m->esq);
    }
    return 0;
  }

  if (m->dir != NULL){
    if (m->chave < m->dir->chave){
      return e_abb(m->dir);
    }
    return 0;
  }
  return 1;*/

  if (m == NULL) return 1;
  if (!e_abb_aux (m->esq, maiorvisto)) return 0;
  if (*maiorvisto < m->chave){
    *maiorvisto = m->chave;
    return e_abb_aux(m->dir, maiorvisto);
  }  
  else return 0;
}

int e_abb (Mapa *m){
	int maiorvisto = -1;
	return e_abb_aux(m, &maiorvisto);
}


Mapa* debug_troca_chave (Mapa *m, int original, int novachave){
  if(m->chave == original) 
	m->chave = novachave;
  else if(m->chave > original) 
	debug_troca_chave(m->esq, original, novachave);
  else if(m->chave < original) 
	debug_troca_chave(m->dir, original, novachave);

  return m;
}

int max (int a, int b){
   return a>b?a:b;
}

int obtem_altura (Mapa *m){
  if (m==NULL) return 0;

  return max(obtem_altura(m->esq), obtem_altura(m->dir)) +1;
}

int e_avl_aux (Mapa *m) {
  int difh;
  if (!e_abb(m)) return 0;
  if (m == NULL) return 1;
  difh = obtem_altura(m->esq) - obtem_altura(m->dir);
  if (abs(difh)>1) return 0;

  return 1;
} 


int chavek_aux(Mapa *m, int k, int *qtd){
  int num; 
  if (m==NULL) return 0;
  num = chavek_aux(m->esq, k, qtd);

  if (*qtd>=k) return num;
  (*qtd)++;

  if (*qtd == k) return m->chave;
  return chavek_aux (m->dir, k, qtd);

}

int chavek (Mapa* m, int k) {
  int chave,qtd=0;
	chave= chavek_aux(m,k,&qtd);
	if(qtd<k) return -1;
	else return chave;
}

