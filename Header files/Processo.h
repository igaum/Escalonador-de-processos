#ifndef _PROCESSO_H
#define _PROCESSO_H

#include <string>

class Processo {

public:

	//construtor, chamado pela funcao de leitura
	Processo(int tempo_criacao = 0, int prioridade = 0, int tempo_cpu = 0, std::string ID = "") {
		this->tempo_criacao = tempo_criacao;
		this->tempo_cpu = tempo_cpu;
		this->prioridade = prioridade;
		this->ID = ID;
	}

	//getters
	int get_tempo_criacao() { return tempo_criacao; }
	int get_prioridade() { return prioridade; }
	int get_tempo_cpu() { return tempo_cpu; }
	std::string get_ID() { return ID; }

private:
	//info do processo, lidas do arquivo
	int tempo_criacao, prioridade, tempo_cpu;
	std::string ID;
};

#endif
