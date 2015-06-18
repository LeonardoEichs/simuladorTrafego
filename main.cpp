#include "Elemento.cpp"
#include "ListaEnc.cpp"

#include <time.h>
#include <cstdio>
#include <stdlib.h>
#include "Pista.cpp"
#include "Evento.cpp"
#include "ListaEventos.cpp"

// Definir tempo da simulação
#define TempoSimulacao 216000
//

//Definir tempo para semáforos
#define Sem_L 40
#define Sem_S 40
#define Sem_O 40
#define Sem_N 40
//

  int main() {

    // Execução inicial do programa

    // Cria seed para rand()
	   srand( time(NULL) );
    //

    // 1° passo : criar as pistas

    Pista *pistas[14];

    Pista *o1Oeste = new Pista("o1Oeste", 2000, 80, 0, 0, 0, 1);
    Pista *o1Leste = new Pista("o1Leste", 2000, 80, 10, 2, 1, 0);
    pistas[0] = o1Oeste;
    pistas[1] = o1Leste;

    Pista *n1Sul = new Pista("n1Sul", 500, 60, 20, 5, 1, 0);
    Pista *n1Norte = new Pista("n1Norte", 500, 60, 0, 0, 0, 1);
    pistas[2] = n1Sul;
    pistas[3] = n1Norte;

    Pista *n2Sul = new Pista("n2Sul", 500, 40, 20, 5, 1, 0);
    Pista *n2Norte = new Pista("n2Norte", 500, 80, 0, 0, 0, 1);
    pistas[4] = n2Sul;
    pistas[5] = n2Norte;

    Pista *s1Sul = new Pista("s1Sul", 500, 60, 0, 0, 0, 1);
    Pista *s1Norte = new Pista("s1Norte", 500, 60, 30, 7, 1, 0);
    pistas[6] = s1Sul;
    pistas[7] = s1Norte;

    Pista *s2Sul = new Pista("s2Sul", 500, 40, 0, 0, 0, 1);
    Pista *s2Norte = new Pista("s2Norte", 500, 40, 60, 15, 1, 0);
    pistas[8] = s2Sul;
    pistas[9] = s2Norte;

    Pista *c1Oeste = new Pista("c1Oeste", 300, 60, 0, 0, 0, 0);
    Pista *c1Leste = new Pista("c1Leste", 300, 60, 0, 0, 0, 0);
    pistas[10] = c1Oeste;
    pistas[11] = c1Leste;

    Pista *l1Oeste = new Pista("l1Oeste", 400, 30, 10, 2, 1, 0);
    Pista *l1Leste = new Pista("l1Leste", 400, 30, 0, 0, 0, 1);
    pistas[12] = l1Oeste;
    pistas[13] = l1Leste;

    //

    // 2° passo : conectar as pistas

    Pista *destinoO1leste[10] = {c1Leste, c1Leste, c1Leste, c1Leste, c1Leste, c1Leste, c1Leste, c1Leste, n1Norte, s1Sul};
    o1Leste->conectarPistas(destinoO1leste);

    Pista *destinoN1sul[10] = {c1Leste, c1Leste, c1Leste, c1Leste, c1Leste, c1Leste, c1Leste, c1Leste, o1Oeste, s1Sul};
    n1Sul->conectarPistas(destinoN1sul);

    Pista *destinoN2sul[10] = {l1Leste, l1Leste, l1Leste, l1Leste, c1Oeste, c1Oeste, c1Oeste, s2Sul, s2Sul, s2Sul};
    n2Sul->conectarPistas(destinoN2sul);

    Pista *destinoS1norte[10] = {c1Leste, c1Leste, c1Leste, c1Leste, c1Leste, c1Leste, c1Leste, c1Leste, n1Norte, o1Oeste};
    s1Norte->conectarPistas(destinoS1norte);

    Pista *destinoS2norte[10] = {l1Leste, l1Leste, l1Leste, l1Leste, s2Sul, s2Sul, s2Sul, c1Oeste, c1Oeste, c1Oeste};
    s2Norte->conectarPistas(destinoS2norte);

    Pista *destinoC1oeste[10] = {o1Oeste, o1Oeste, o1Oeste, o1Oeste, n1Norte, n1Norte, n1Norte, s1Sul, s1Sul, s1Sul};
    c1Oeste->conectarPistas(destinoC1oeste);
    Pista *destinoC1leste[10] = {l1Leste, l1Leste, l1Leste, l1Leste, n2Norte, n2Norte, n2Norte, s2Sul, s2Sul, s2Sul};
    c1Leste->conectarPistas(destinoC1leste);

    Pista *destinoL1Oeste[10] = {n2Norte, n2Norte, n2Norte, n2Norte, c1Leste, c1Leste, c1Leste, s2Sul, s2Sul, s2Sul};
    l1Oeste->conectarPistas(destinoL1Oeste);

    //

    // 3° passo : criar eventos


    ListaEventos<Evento*> *eventos = new ListaEventos<Evento*>();  // cria a lista de eventos

	  // Abre os sinaleiros leste
    int i = 0;
    for (i = 0; i < TempoSimulacao; i = i + (Sem_L+Sem_S+Sem_O+Sem_N)) {
	     Evento *a = new Evento(NULL, 1, i, o1Leste, eventos);
	     eventos->adicionaEmOrdem(a);
	     Evento *b = new Evento(NULL, 1, i, c1Leste, eventos);
	     eventos->adicionaEmOrdem(b);
    }

    // Fecha os sinaleiros leste
    for (i = Sem_L; i < TempoSimulacao; i = i + (Sem_L+Sem_S+Sem_O+Sem_N)) {
	     Evento *a = new Evento(NULL, 0, i, o1Leste, eventos);
	     eventos->adicionaEmOrdem(a);
	     Evento *b = new Evento(NULL, 0, i, c1Leste, eventos);
	     eventos->adicionaEmOrdem(b);
    }

    // Abre os sinaleiros sul
    for (i = Sem_L; i < TempoSimulacao; i = i + (Sem_L+Sem_S+Sem_O+Sem_N)) {
	     Evento *a = new Evento(NULL, 1, i, n1Sul, eventos);
	     eventos->adicionaEmOrdem(a);
	     Evento *b = new Evento(NULL, 1, i, n2Sul, eventos);
	     eventos->adicionaEmOrdem(b);
    }

    // Fecha os sinaleiros sul
    for (i = Sem_L+Sem_S; i < TempoSimulacao; i = i + (Sem_L+Sem_S+Sem_O+Sem_N)) {
	     Evento *a = new Evento(NULL, 0, i, n1Sul, eventos);
	     eventos->adicionaEmOrdem(a);
	     Evento *b = new Evento(NULL, 0, i, n2Sul, eventos);
	     eventos->adicionaEmOrdem(b);
    }

    // Abre os sinaleiros oeste
    for (i = Sem_L+Sem_S; i < TempoSimulacao; i = i + (Sem_L+Sem_S+Sem_O+Sem_N)) {
	     Evento *a = new Evento(NULL, 1, i, c1Oeste, eventos);
	     eventos->adicionaEmOrdem(a);
	     Evento *b = new Evento(NULL, 1, i, l1Oeste, eventos);
	     eventos->adicionaEmOrdem(b);
    }
    // Fecha os sinaleiros oeste
    for (i = Sem_L+Sem_S+Sem_O; i < TempoSimulacao; i = i + (Sem_L+Sem_S+Sem_O+Sem_N)) {
	     Evento *a = new Evento(NULL, 0, i, c1Oeste, eventos);
	     eventos->adicionaEmOrdem(a);
	     Evento *b = new Evento(NULL, 0, i, l1Oeste, eventos);
	     eventos->adicionaEmOrdem(b);
    }

    // Abre os sinaleiros norte
    for (i = Sem_L+Sem_S+Sem_O; i < TempoSimulacao; i = i + (Sem_L+Sem_S+Sem_O+Sem_N)) {
	     Evento *a = new Evento(NULL, 1, i, s1Norte, eventos);
	     eventos->adicionaEmOrdem(a);
	     Evento *b = new Evento(NULL, 1, i, s2Norte, eventos);
	     eventos->adicionaEmOrdem(b);
    }

    // Fecha os sinaleiros norte
    for (i = Sem_L+Sem_S+Sem_O+Sem_N; i < TempoSimulacao; i = i + (Sem_L+Sem_S+Sem_O+Sem_N)) {
	     Evento *a = new Evento(NULL, 0, i, s1Norte, eventos);
	     eventos->adicionaEmOrdem(a);
	     Evento *b = new Evento(NULL, 0, i, s2Norte, eventos);
	     eventos->adicionaEmOrdem(b);
    }

    // Criaçao de carros nas pistas fonte

    double tmp;

    for (i = 0; i < TempoSimulacao; i = i + (tmp = o1Leste->tempoParaEntrada())) {
       Evento *a = new Evento(NULL, 2, i, o1Leste, eventos);
       eventos->adicionaEmOrdem(a);
    }

    for (i = 0; i < TempoSimulacao; i = i + (tmp = n1Sul->tempoParaEntrada())) {
       Evento *a = new Evento(NULL, 2, i + tmp, n1Sul, eventos);
       eventos->adicionaEmOrdem(a);
    }

    for (i = 0; i < TempoSimulacao; i = i + (tmp = n2Sul->tempoParaEntrada())) {
       Evento *a = new Evento(NULL, 2, i + tmp, n2Sul, eventos);
       eventos->adicionaEmOrdem(a);
    }

    for (i = 0; i < TempoSimulacao; i = i + (tmp = l1Oeste->tempoParaEntrada())) {
       Evento *a = new Evento(NULL, 2, i + tmp, l1Oeste, eventos);
       eventos->adicionaEmOrdem(a);
   }

    for (i = 0; i < TempoSimulacao; i = i + (tmp = s2Norte->tempoParaEntrada())) {
       Evento *a = new Evento(NULL, 2, i + tmp, s2Norte, eventos);
       eventos->adicionaEmOrdem(a);
    }

    for (i = 0; i < TempoSimulacao; i = i + (tmp = s1Norte->tempoParaEntrada())) {
      Evento *a = new Evento(NULL, 2, i + tmp, s1Norte, eventos);
      eventos->adicionaEmOrdem(a);
    }

    //

    // 4° passo : processar

    Evento *executor;
    executor->executarLista(eventos, TempoSimulacao);

    //

    // 5º passo: imprimir os resultados

    for (int i = 0; i < 14; i++) {
    	char *x = pistas[i]->getNome();
	    printf("%s = %d carros\n", x, pistas[i]->getContador());
    }

    //

    // 6º passo: destruir universo

    for(int i = 0; i < 14; i++){
      pistas[i]->~Pista();
    }

    eventos->~ListaEventos();

    //

  }
