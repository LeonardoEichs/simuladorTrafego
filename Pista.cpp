#ifndef PISTA_ENC
#define PISTA_ENC

#include <stdlib.h>
#include <time.h>
#include "Veiculo.cpp"
#include "FilaEnc.cpp"
#include "Elemento.cpp"

class Pista: private FilaEnc<Veiculo*> {

 private:
   char *id;  // Nome da pista (usado para imprimir no final)
   int tamanhoPista;  // Tamanho da pista
   int velocidade;  // Velocidade em km/h
   int tempoEntrada;  // Tempo medio de criacao de um novo carro
   int variancia;  // Variancia do tempo medio, tempo medio + ou - variancia
   bool pistaFonte;  // Indica se a pista eh fonte de veiculos
   bool pistaSumidouro;  // Indica se a pista eh sumidouro
   Pista *direcao[10];  // para simular aleatoriedade
   double tempo;  // Tempo que cada veiculo levarah para percorrer a pista toda
   bool semaforo = false;  // Inicializa o semaforo fechado da pista
   int contador =  0;  // Contador para a quantidade de carros que passaram pela pista

 public:
   /*  Parametros :
	nome = nome da pista
	tamPista = tamanho da pista
	vel = velocidade da pista
	tmpEntr = tempo medio de criacao de um novo carro da pista
	var = variancia da pista
	pFonte = 1 se a pista eh fonte de veiculos
	pSumidouro = 1 se a pista eh sumidouro
   */
   Pista(char *nome, int tamPista, int vel, int tmpEntr, int var,
         bool pFonte, bool pSumidouro): FilaEnc<Veiculo*>::FilaEnc() {
     id = nome;
     tamanhoPista = tamPista;
     velocidade = vel;
     variancia = var;
     tempoEntrada = tmpEntr;
     pistaFonte = pFonte;
     pistaSumidouro = pSumidouro;
	   for(int i = 0; i < 10; i++)
		   direcao[i] = NULL;  // Inicializaçao
	   tempo = tamanhoPista/(velocidade/3.6);  // Conversao de km/h para m/s
   }

   // Destruir a pista no final
   ~Pista() {
	    FilaEnc<Veiculo*>::limparFila();
   }

   // Método para conectar pistas
   void conectarPistas(Pista* dir[]) {
     int i;
     for (i = 0; i < 10; i++)
       direcao[i] = dir[i];
   }


   // Métodos GET :


   int getTamanhoPista() {
     return tamanhoPista;
   }

   int getVelocidade() {
     return velocidade;
   }

   int getTempoEntrada() {
     return tempoEntrada;
   }

   int getVariancia() {
     return variancia;
   }

   bool getPistaFonte() {
     return pistaFonte;
   }

   bool getPistaSumidouro() {
     return pistaSumidouro;
   }

   bool getSemaforo() {
     return semaforo;
   }

   int getContador() {
     return contador;
   }

   double getTempo() {
     return tempo;
   }

   char* getNome() {
     return id;
   }


   //
   // Métodos SET :


   // Parametro novoTamanho = o novo tamanho da pista, alterado por exclusao/inclusao de veiculos
   void setTamanhoPista(int novoTamanho) {
     tamanhoPista = novoTamanho;
   }

   // Parametro estado = seta o sinal do semaforo
   void setSemaforo(bool estado) {
     semaforo = estado;
   }


   // Outros metodos :


   // Parametro indice = direcao do carro
   // Retorna a pista para a qual o carro irah ser transferido
   Pista* getNovaPista(int indice) {
     if(indice > -1 && indice < 10)
      return direcao[indice];
   }

   // Incrementa o contador de carros que passaram pela pista
   void somaContador(){
     contador++;
   }

   // Calcula e retorna o tempo de entrada de um novo carro
   double tempoParaEntrada() {
    //return int((rand()/RAND_MAX)*(variancia*2+1) + (tempoEntrada-variancia)); ????
    return tempoEntrada + rand() % 2*variancia - variancia;
   }


   // INCLUIR MÉTODOS DA FILA ENC


  void inclui(Veiculo* dado) {
    FilaEnc<Veiculo*>::inclui(dado);
  }

  void retira() {
    FilaEnc<Veiculo*>::retira();
  }

};

#endif
