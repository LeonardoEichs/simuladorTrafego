// Copyright [2015] <Jonatan Zimath>
//! Classe de implementacao da lista.
/*!
*   Implementacao da lista usando templates.
*/

#ifndef ELEMENTO_HPP
#define ELEMENTO_HPP

template<typename T>
class Elemento {
 private:
	T *info;  //!< \var Ponteiro para o dado do tipo T. //!<
	Elemento<T>* _next;  //!< \var Ponteiro p/ o proximo elemento da lista. //!<

 public:
    //! Um construtor.
    /*!
        Construtor do elemento.
        \param info eh o endereço do dado do Tipo T.
        \param next eh o o ponteiro para o proximo elemento da lista.
    */
	Elemento(const T& info, Elemento<T>* next) : info(new T(info)), _next(next) {}

    //! Destrutor.
    /*!
        Destrutor para o elemento.
    */
	~Elemento() {
	    delete info;
	}

    //! Metodo normal.
    /*!
        \return Retorna um ponteiro para o proximo elemento.
    */
	Elemento<T>* getProximo() const {
		return _next;
	}

    //! Metodo normal.
    /*!
        \return Retorna um ponteiro para o dado do elemento.
    */
	T getInfo() const {
		return *info;
	}

    //! Metodo normal.
    /*!
        Seta o ponteiro para o proximo elemento.
        \param next eh um ponteiro para o proximo elemento.
    */
	void setProximo(Elemento<T>* next) {
		_next = next;
	}
};

#endif
