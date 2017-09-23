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
  int cb, dado;

  if (argc!=2) { 					//se não insere o tamanho do mapa criado na hora de executar no terminal. fecha o programa
    printf("uso: <%s> <tamanhoMapa>\n", argv[0]);
    exit(1);
  }
  tamanho = strtol (argv[1], NULL, 10); 		//se o tamanho for 0, tamanho inválido e fecha o programa
  if (tamanho == 0) {
    printf("tamanho invÃ¡lido!\n");
    exit(1);
  }


  Mapa *ummapa = cria(); 				//aponta *ummapa para NULL
  Mapa *outromapa = cria();				//aponta *outromapa para NULL 

  for (i=0;i<tamanho;i++) muitos[i]=i;			//cria vetor com o número de 0 a tamanho-1. (tamanho inserido no terminal

  printf("constroi um mapa -------------- \n");		//constroi o ummapa com os vetores de 0 a tamanho-1
  for (i=0;i<tamanho;i++) {
    ummapa = insere(ummapa, i, muitos[i]);		
  }
  debug_mostra_mapa (ummapa);				//mostra o ummapa

  printf("constroi outro mapa -------------- \n");
  outromapa = preenche (outromapa, muitos, 0, tamanho-1);

  debug_mostra_mapa (outromapa);

  while (1) {
    printf ("chave a buscar: ");
    scanf ("%d", &cb);
    if (cb==-1) break;

    dado = busca (ummapa, cb);
    printf ("achou? %s\n", (dado!=-1)?"sim":"nÃ£o");
  }


  destroi(ummapa); destroi(outromapa);

  return 0;}


