#ifndef VEICULO_HPP
#define VEICULO_HPP

#include <stdlib.h>
#include <time.h>
#include <cstdio>

class Veiculo {

 private:
  int tamanho;  // Tamanho do carro (2m a 10m) + 2m atrás + 1m frente
  int direcao;  // Indica a direcao do carro conforme o array da pista

 public:
  Veiculo() {
    tamanho = (rand() % 8 + 2) + 3;
    direcao = rand() % 10;
  }

  // Retorna o tamanho
  int getTamanho() {
    return tamanho;
  }

  // Retorna a direcao
  int getDirecao() {
    return direcao;
  }

};

#endif
