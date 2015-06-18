#ifndef LISTAEVENTOS_HPP
#define LISTAEVENTOS_HPP

#include <cstdio>
#include <stdlib.h>
#include "ListaEnc.cpp"
#include "Elemento.cpp"

template<typename T>

class ListaEventos: private ListaEnc<T> {

 private:

 public:
	ListaEventos(): ListaEnc<T>::ListaEnc() {
  }

  // Novo método "adiciona em ordem" que leva em consideração o tempo de disparo
	void adicionaEmOrdem(T data) {
		if (ListaEnc<T>::listaVazia()) {
			ListaEnc<T>::adicionaNoInicio(data);
			return;
		}
		Elemento<T> *aux = ListaEnc<T>::head;
		int pos = 0;
		while (aux->getProximo() != NULL && maior(data->getTempoDoDisparo(), (aux->getInfo())->getTempoDoDisparo())) {
			aux = aux->getProximo();
			pos++;
		}
		if (maior(data->getTempoDoDisparo(), (aux->getInfo())->getTempoDoDisparo())) {
			ListaEnc<T>::adiciona(data);
			return;
		}
		ListaEnc<T>::adicionaNaPosicao(data, pos);
	}

  // Método maior que recebe "double" como paramêtro
	bool maior(double dado1, double dado2) {
		if (dado1 > dado2)
			return true;
		return false;
	}

  // Método gethead herdado de ListaEnc
	Elemento<T>* getHead() {
		return ListaEnc<T>::head;
	}

  // Método eliminaDoInicio herdado de ListaEnc
	void eliminaDoInicio() {
		ListaEnc<T>::eliminaDoInicio();
	}

  // Método posição herdado de ListaEnc
  int posicao(const T& dado) const {
    ListaEnc<T>::posicao(dado);
	}

  // Método lerDaPosicao, recebe posição como parâmetro e retorna o elemento contido
  T lerDaPosicao(int pos) {
    ListaEnc<T>::lerDaPosicao(pos);
  }

  // Método retorna o próximo evento de abertura do sinal
  /*
  // Percorre a Lista Encadeada recebendo os elementos contidos
  // Verifica se o tipo do evento é abertura de sinal
  // E verifica se o tempo desse evento é maior que o tempo atual
  // Retorna o tempo em que abre o sinal
  */
  double posicaoAbrirSinal(double tempoAtual){
    int i;
    for(i = 0; i < ListaEnc<T>::size; i ++) {
      T aux = ListaEnc<T>::lerDaPosicao(i);
      if(aux->getTipoEvento() == 1 && aux->getTempoDoDisparo() > tempoAtual) {
        return aux->getTempoDoDisparo();
      }
    }
  }

};

#endif
