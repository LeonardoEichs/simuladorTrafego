// Copyright [2015] <Jonatan Zimath>
//! Classe de implementacao da lista encadeada.
/*!
*   Implementacao da lista encadeada usando templates.
*/

#ifndef LISTAENC_HPP
#define LISTAENC_HPP

#include "Elemento.cpp"  // Arquivo Elemento.hpp incluido.
#include <cstdio>
#define NULL __null

template<typename T>

class ListaEnc {
 public:
    //! Construtor.
    /*!
        Construtor da lista.
    */
	ListaEnc() {
		size = 0;
		head = NULL;
	}

    //! Destrutor.
    /*!
        Destrutor da lista.
    */
	~ListaEnc() {
		destroiLista();
	}

    //! Metodo normal.
    /*!
        Adiciona um dado no inicio da lista.
        \param dado é o endereço dado do tipo T que sera adicionado na lista.
    */
	void adicionaNoInicio(const T& dado) {
		Elemento<T>* elNovo = new Elemento<T>(dado, head);
		if (elNovo == NULL)
			throw(20);
		head = elNovo;
		size++;
	}

    //! Metodo normal.
    /*!
        \return Retorna o 1º dado da lista e retira o 1º elemento da lista.
    */
	T retiraDoInicio() {
		T dado;
		Elemento<T>* sai;
		if (listaVazia())
			throw(20);
		sai = head;
		dado = sai->getInfo();
		head = sai->getProximo();
		size--;
		sai->~Elemento();
		return dado;
	}

    //! Metodo normal.
    /*!
        \return Retira o primeiro elemento da lista.
    */
	void eliminaDoInicio() {
		Elemento<T>* sai;
		if (listaVazia())
			throw(20);
		sai = head;
		head = sai->getProximo();
		size--;
		//printf("Endereco do evento eliminado = %d\n", sai->getInfo());
		sai->~Elemento();
	}

    //! Metodo normal.
    /*!
        Adiciona um elemento na posicao especifica.
        \param dado é o endereço do dado do tipo T que sera inserido na lista.
        \param pos é o lugar do em que o dado sera inserido na lista. (inicio=0)
    */
	void adicionaNaPosicao(const T& dado, int pos) {
		Elemento<T> *elNovo, *ant;
		if (pos > size)
			throw(20);
		if (pos == 0) {
			adicionaNoInicio(dado);
		    return;
		}
		ant = head;
		for (int controle = 0; controle < pos-1; controle++)
			ant = ant->getProximo();
		elNovo = new Elemento<T>(dado, ant->getProximo());
		if (elNovo == NULL)
			throw(20);
		ant->setProximo(elNovo);
		size++;
	}

	//! Metodo normal.
    /*!
        \return Retorna um int da posicao do dado, caso ele esteja na lista.
        \param dado eh o endereço do dado do tipo T.
    */
	int posicao(const T& dado) const {
		Elemento<T>* aux;
		aux = head;
		for (int controle = 0; controle < size; controle++) {
			if (aux->getInfo() == dado)
				return controle;
			aux = aux->getProximo();
		}
		throw(20);
	}

    //! Metodo normal.
    /*!
        \return Retorna um ponteiro do tipo T para o dado.
        \param dado eh o endereço do dado do tipo T que sera procurado na lista.
    */
	T* posicaoMem(const T& dado) const {
		Elemento<T>* aux;
		aux = head;
		for (int controle = 0; controle < size; controle++) {
			if (igual(aux->getInfo(), dado))
				return aux;  // tem diferenca aqui
			aux = aux->getProximo();
		}
		throw(20);
	}

	//! Metodo normal.
    /*!
        \return Retorna true se o o dado estivar na lista.
        \param dado eh o endereço do dado do tipo T a ser verificado.
    */
	bool contem(const T& dado) {
        Elemento<T> *aux;
        aux = head;
        for (int controle = 0; controle < size; controle++) {
        if (igual(aux->getInfo(), dado))
            return true;
        aux = aux->getProximo();
      }
      return false;
    }

    //! Metodo normal.
    /*!
        \return Retorna o dado do tipo T da posição especificada.
        \param pos eh a posicao do elemento cujo dado sera retirado da lista.
                (elemento é apagado)
    */
	T retiraDaPosicao(int pos) {
		T dado;
		Elemento<T> *ant, *sai;
		if (pos >= size)
			throw(20);
		if (pos == 0)
			return retiraDoInicio();
		ant = head;
		for (int controle = 0; controle < pos-1; controle++)
			ant = ant->getProximo();
        sai = ant->getProximo();
		dado = sai->getInfo();
		ant->setProximo(sai->getProximo());
		size--;
		return dado;
		sai->~Elemento();
	}

    //! Metodo normal.
    /*
        Adiciona um dado ao fim da lista.
    */
	void adiciona(const T& dado) {
		adicionaNaPosicao(dado, size);
	}

    //! Metodo normal.
    /*
        Retira um dado do fim da lista e elimina elemento.
    */
	T retira() {
	    if (listaVazia())
	        throw(20);
		return retiraDaPosicao(size-1);
	}

    //! Metodo normal.
    /*!
        \return Retorna e retira um dado específico do tipo T (apaga elemento).
        \param dado eh o endereço do dado que será retirado do tipo T.
    */
	T retiraEspecifico(const T& dado) {
		int pos;
		if (!((pos = posicao(dado))+1))
			throw(20);
		return retiraDaPosicao(pos);
	}

    //! Metodo normal.
    /*!
        Adiciona um dado em ordem na lista.
        \param endereço do dado do tipo T que sera inserido em ordem na lista.
    */
	void adicionaEmOrdem(const T& data) {
		printf("Adiciona em ordem errado!\n");
		if (listaVazia())
			adicionaNoInicio(data);
      return;
		Elemento<T>* aux;
		int pos;
		aux = head;
		pos = 0;
		while (aux->getProximo() != NULL && maior(data, aux->getInfo())) {
			aux = aux->getProximo();
			pos++;
		}
		if (maior(data, aux->getInfo())){
			adiciona(data);
      return;
    }
		adicionaNaPosicao(data, pos);
	}

	//! Metodo normal.
    /*!
        \return Retorna um boolean indicando true se a lista esta vazia.
    */
	bool listaVazia() const {
	    if (head == NULL)
	        return true;
	    return false;
	}

	//! Metodo normal.
    /*!
        \return Retorna um boolean indicando true se dado1 = dado2.
        \param dado1 eh o dado que será avaliado do tipo T.
        \param dado2 eh o dado de refencia do tipo T.
    */
	bool igual(T dado1, T dado2) {
	    if (dado1 == dado2)
	        return true;
	    return false;
	}

	//! Metodo normal.
    /*!
        \return Retorna um boolean indicando true se dado1 > dado2.
        \param dado1 eh o dado que será avaliado do tipo T.
        \param dado2 eh o dado de refencia do tipo T.
    */
	bool maior(T dado1, T dado2) {
	    if (dado1 > dado2)
	        return true;
	    return false;
	}

	//! Metodo normal.
    /*!
        \return Retorna um boolean indicando true se dado1 < dado2.
        \param dado1 eh o dado que será avaliado do tipo T.
        \param dado2 eh o dado de refencia do tipo T.
    */
	bool menor(T dado1, T dado2) {
	    if (dado1 < dado2)
	        return true;
	    return false;
	}

	//! Metódo para destruir.
    /*!
        Metódo para destruir a lista e apagar toda a lista.
    */
	void destroiLista() {
    	Elemento<T> *atual;
        if (listaVazia()) {
            delete head;
        }
        atual = head;
        while (atual != NULL) {
            atual = atual->getProximo();
            eliminaDoInicio();
        }
	size = 0;
	}

  T lerDaPosicao(int pos) {
        if (pos >= size)
            throw "POSIÇÃO INVÁLIDA";
        if (pos == 0)
          return head->getInfo();
        Elemento<T> *anterior;
        anterior = head;
        for (int k = 0; k < pos - 1; k++) {  // segue a lista até posição
            anterior = anterior->getProximo();
        }
        return anterior->getProximo()->getInfo();  //Retorna elemento da posição pos sem retirar
    }

 protected:
	Elemento<T>* head;  //!< \var Ponteiro para o 1º elemento da lista. //!<
	int size;  //!< \var Qtd de elementos na lista. //!<
};

#endif
