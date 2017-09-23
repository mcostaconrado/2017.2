#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>
#include "mapa.h"

#define REPETE 1000
#define MAX 100000

Mapa* preenche (Mapa* m, int dados[], int inicio, int fim) {
  int meio;
  if (inicio>fim) return m;
  meio = (fim+inicio)/2;
  m = insere (m, dados[meio], dados[meio]);
  m = preenche (m, dados, inicio, meio-1);
  m = preenche (m, dados, meio+1, fim);
  return m;
}

int main (int argc, char** argv) {

  int muitos[MAX];
  int i;
  long int tamanho;
  int chavedada;

  if (argc!=2) {
    printf("uso: <%s> <tamanhoMapa>\n", argv[0]);
    exit(1);
  }
  tamanho = strtol (argv[1], NULL, 10);
  if (tamanho == 0) {
    printf("tamanho invÃ¡lido!\n");
    exit(1);
  }

  Mapa *mapa1 = cria();
  Mapa *mapa2 = cria();
  Mapa *mapa3 = cria();

  for (i=0;i<tamanho;i++) muitos[i]=i;

  printf("constroi mapa1  -------------- \n");
  for (i=0;i<tamanho;i++) {
    mapa1 = insere(mapa1, i, muitos[i]);
  }
 debug_mostra_mapa (mapa1);
//
//  printf("mapa1 Ã© avl? %s\n", e_avl(mapa1)?"sim":"nÃ£o");
  printf("mapa1 Ã© abb? %s\n", e_abb(mapa1)?"sim":"nÃ£o");
//
  printf("constroi mapa2 -------------- \n");
  mapa2 = preenche (mapa2, muitos, 0, tamanho-1);

  debug_mostra_mapa (mapa2);

  printf("\n\nmapa 1 e mapa 2 Sao iguais??? -> %d\n\n", iguais(mapa1, mapa2)) ;
//
//  printf("mapa2 Ã© avl? %s\n", e_avl(mapa2)?"sim":"nÃ£o");
//  printf("mapa2 Ã© abb? %s\n", e_abb(mapa2)?"sim":"nÃ£o");
//
  printf("constroi mapa3 -------------- \n");
  while (1) {
    printf ("inserir em mapa3 (digite -1 para terminar): ");
    scanf ("%d", &chavedada);
   if (chavedada==-1) break;
   mapa3 = insere(mapa3, chavedada, chavedada);
  }
  debug_mostra_mapa (mapa3);

  
//  printf("mapa3 Ã© avl? %s\n", e_avl(mapa3)?"sim":"nÃ£o");
  printf("mapa3 Ã© abb? %s\n", e_abb(mapa3)?"sim":"nÃ£o");

//  while (1) {
//    printf ("posiÃ§Ã£o (digite -1 para terminar): ");
//    scanf ("%d", &chavedada);
//    if (chavedada==-1) break;
//
//    //printf("em mapa2 chave %d Ã© %d\n", chavedada, chavek(mapa2, chavedada));
//  }

  printf("\n\nmapa 1 e mapa 3 Sao iguais??? -> %d\n\n", iguais(mapa1, mapa3)) ;
  printf("\n\nmapa 2 e mapa 3 Sao iguais??? -> %d\n\n", iguais(mapa2, mapa3)) ;

  destroi(mapa1); 
  destroi(mapa2);
  destroi(mapa3);

  return 0;}


