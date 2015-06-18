// Copyright [2015] <Jonatan Zimath>
//! Classe de implementacao da fila encadeada.
/*!
*   Implementacao da fila encadeada usando templates.
*/

#ifndef FILAENC_HPP
#define FILAENC_HPP

#include "Elemento.cpp"
#include "ListaEnc.cpp"

template <typename T>
class FilaEnc: private ListaEnc<T>{  // atributos herdados ficam private
 public:
    // construtor, usa o construtor da classe-base
	FilaEnc<T>(): ListaEnc<T>::ListaEnc() {
	    last = NULL;
	}

    // destrutor
	~FilaEnc() {
	    limparFila();
	}

    // adiciona um elemento no final da fila
	void inclui(const T& dado) {
	    Elemento<T> *novo = new Elemento<T>(dado, NULL);
	    if (novo == NULL)
	        throw(20);
	    if (filaVazia()) {
	        ListaEnc<T>::head = novo;
	    } else {
	        last->setProximo(novo);
	    }
	    last = novo;
	    ListaEnc<T>::size++;
	}

    // retira um elemento do inicio da fila
	T retira() {
	    if (filaVazia()) {
            throw 20;
        }
        if (ListaEnc<T>::size == 1) {
            last = NULL;
        }
        return ListaEnc<T>::retiraDoInicio();
	}

    // retorna o dado do ultimo elemento da fila
	T ultimo() {
	    if (filaVazia())
            throw(20);
	    T dado;
	    dado = last->getInfo();
	    return dado;
	}

    // retorna o dado do primeiro elemento da fila
	T primeiro() {
	    if (filaVazia())
            throw(20);
	    T dado;
	    dado = ListaEnc<T>::head->getInfo();
	    return dado;
	}

    // verifica se a fila está vazia ou não
	bool filaVazia() {
	    return ListaEnc<T>::listaVazia();
	}

    // limpa e elimina a fila
	void limparFila() {
	    ListaEnc<T>::destroiLista();
	}

	Elemento<T>* getHead() {
		return ListaEnc<T>::head;
	}
 private:
    Elemento<T> *last;  // ponteiro para o ultimo elemento da fila
};

#endif
