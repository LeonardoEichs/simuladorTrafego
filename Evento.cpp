#ifndef EVENTO_HPP
#define EVENTO_HPP

#include <stdlib.h>
#include <cstdio>
#include "ListaEventos.cpp"
#include "Veiculo.cpp"
#include "Pista.cpp"
#include "Elemento.cpp"

class Evento {

 private:
	Veiculo *veiculo;  // Recebe veículo
	int tipoDeEvento; // Recebe o tipo do evento
	double tempoDoDisparo; // Recebe o tempo em que ocorre o evento
	Pista *pista; // Recebe uma pista associada ao evento
  ListaEventos<Evento*> *listaEvento; // Recebe a lista de eventos

 public:
	Evento(Veiculo *carro, int tipo, double tempo, Pista *estrada, ListaEventos<Evento*> *lista) {
		veiculo = carro;
		tipoDeEvento = tipo;
		tempoDoDisparo = tempo;
		pista = estrada;
    listaEvento = lista;
	}

  // Retorna tipo de evento
  int getTipoEvento() {
    return tipoDeEvento;
  }

  // Retorna tempo em que ocorre o evento
  double getTempoDoDisparo() {
  	return tempoDoDisparo;
  }

  // Verifica qual o tipo do evento e chama o método associado
	void executar() {
		switch(tipoDeEvento) {
			case 0:
				fecharSemaforo();
				break;
			case 1:
				abrirSemaforo();
				break;
			case 2:
				criarVeiculo();
				break;
			case 3:
				chegouSemaforo();
				break;
			default:
				destruirVeiculo();
		}
	}

  // Método que executa a lista
  /*
  // Executor percorre a lista veridicando o fim dela e o tempo de simulação
  // Chama método executar(), que verifica tipo do evento
  // Retira do inicio da lista o evento que foi executado
  */
  void executarLista(ListaEventos<Evento*> *lista, int tempo) {
		Elemento<Evento*> *executor;
	  executor = lista->getHead();
    while (executor != NULL && (executor->getInfo())->getTempoDoDisparo() < tempo) {
       (executor->getInfo())->executar();
	     executor = executor->getProximo();
       lista->eliminaDoInicio();
    }
   }

  // Método responsável por abrir o semáforo
	void abrirSemaforo() {
    pista->setSemaforo(true);
  }

  // Método responsável por fechar o semáforo
	void fecharSemaforo() {
    pista->setSemaforo(false);
  }

  // Método que cria veículos
  /*
  // Cria um novo carro que recebe um tamanho aleatório
  // Verifica se a pista tem espaço suficiente para receber o carro
  // Responsável por contar quantos carros passaram na pista criadora
  // Inclui carro no fim da pista (Lista Encadeada)
  // Reduz o tamanho da pista pelo tamanho do carro adicionado nela
  // Cria e agenda um novo evento de quando o carro criado irá chegar no semáforo da pista
  */
  void criarVeiculo() {
		Veiculo *carro = new Veiculo();
		if (verificaTamanho(carro, pista)) {
      pista->somaContador();
			pista->inclui(carro);
			pista->setTamanhoPista(pista->getTamanhoPista() - carro->getTamanho());
			Evento *chegouSemaforo = new Evento(carro, 3, (tempoDoDisparo + pista->getTempo()), pista, listaEvento);
			listaEvento->adicionaEmOrdem(chegouSemaforo);
		}
	}

  // Método para chegada de carro no semáforo
  /*
  // Verifica se o semáforo está aberto
  // Se estiver manda para método troca pista
  // Se não estiver, cria um evento para quando o sinaleiro abrir
  // Adiciona esse evento na lista de eventos
  */
	void chegouSemaforo() {
    if (verificarSemaforo())
      trocaPista();
    else {
      Evento* trocaPistaFuturo = new Evento(veiculo, 3, listaEvento->posicaoAbrirSinal(tempoDoDisparo), pista, listaEvento);
      listaEvento->adicionaEmOrdem(trocaPistaFuturo);
    }
  }

  // Método para troca de pista
  /*
  // Recebe a direção do veículo
  // Recebe a pista que está na posição de direção do veículo no array de possíveis destinos
  // Verifica se a pista destino tem espaço suficiente para o veículo
  // Se tiver,
  // Soma contador da nova pista
  // Inclui veículo na nova pista
  // Reduz o tamanho da nova pista pelo tamanho do veículo
  // Aumenta o tamanho da pista antiga pelo tamanho do veículo
  // Retira veículo da pista antiga
  //  Verifica se a nova pista é sumidoura
  // Se for, marca evento para destruir veículo quando este chegar no fim dela
  // Se não for, marca evento para chegada no semáforo das pistas de transição
  // Se não couber na pista, marca novo evento para tentar novamente (e verificando novamente o sinal do semáforo)
  */
	void trocaPista() {
      int direcaoVeiculo = veiculo->getDirecao();
      Pista* novaPista = pista->getNovaPista(direcaoVeiculo);
      if(verificaTamanho(veiculo, novaPista)) {
        novaPista->somaContador();
        novaPista->inclui(veiculo);
        novaPista->setTamanhoPista(novaPista->getTamanhoPista() - veiculo->getTamanho());
        pista->setTamanhoPista(pista->getTamanhoPista() + veiculo->getTamanho());
        pista->retira();
        if (novaPista->getPistaSumidouro() == 1) {
	         Evento *destruir = new Evento(veiculo, 4, (tempoDoDisparo + novaPista->getTempo()), novaPista, listaEvento);
	         listaEvento->adicionaEmOrdem(destruir);
        }
        else {
           Evento *troca = new Evento(veiculo, 3, tempoDoDisparo + novaPista->getTempo(), novaPista, listaEvento);
           listaEvento->adicionaEmOrdem(troca);
        }
      }
      else {
        Evento *trocaPistaNovamente = new Evento(veiculo, 3, getTempoDoDisparo() + 1, pista, listaEvento);
        listaEvento->adicionaEmOrdem(trocaPistaNovamente);
      }
  }

  // Método que destrói veículo
  /*
  // Aumenta o tamnho da pista pelo tamanho do veículo deletado
  // Deleta o veículo
  */
	void destruirVeiculo() {
    pista->setTamanhoPista(pista->getTamanhoPista() + veiculo->getTamanho());
    delete veiculo;
  }

  // Método que verifica se o tamanho do carro é menor do que o tamanho disponível da pista
  bool verificaTamanho(Veiculo *carro, Pista *aPista) {
		if (carro->getTamanho() <= aPista->getTamanhoPista())
			return true;
		return false;
	}

  // Método que verifica estado do semáforo da pista associada ao evento
  bool verificarSemaforo() {
    return pista->getSemaforo();
  }

};

#endif
