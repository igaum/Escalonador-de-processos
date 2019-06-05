#ifndef _LEITURA_H_
#define _LEITURA_H_

#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "Processo.h"

using namespace std;

/* Funcao responsavel pela leitura do arquivo de informacoes dos processos.
 *
 * le o arquivo "processos.csv" no diretorio atual por padrao, caso este arquivo 
 * nao exista no diretorio, sera solicitado que informe um longpath para o arquivo
 * 
 * Apos a leitura, salva os dados em um vector de objetos
 */

struct metodo_ordenacao {
	inline bool operator() (Processo &processoA, Processo &processoB) {
		return (processoA.get_tempo_criacao() < processoB.get_tempo_criacao());
	}
};

void Leitura_csv(vector<Processo> &processos, int &num_processos) {

	//abre o arquivo em read only, pede pelo arquivo ate encontra-lo
	fstream dados;
	dados.open("processos.csv", ios::in);

	while (!dados) {

		string dir;
		cout << "Arquivo nao encontrado!" << endl;
		cout << "Informe o diretorio para o aquivo .csv: ";
		cin >> dir;

		dados.open(dir, ios::in);
	}

	while (dados.good()) {

		string st_tempo_criacao, ID, st_prioridade, st_tempo_cpu;

		//le os dados do arquivo
		getline(dados, st_tempo_criacao, ';');
		getline(dados, ID, ';');
		getline(dados, st_prioridade, ';');
		getline(dados, st_tempo_cpu); //delimitador padrao eh \n

		//converte de string para int
		int tempo_criacao = stoi(st_tempo_criacao);
		int prioridade = stoi(st_prioridade);
		int tempo_cpu = stoi(st_tempo_cpu);

		//cria um objeto Processo no vetor processos 
		processos.push_back(Processo(tempo_criacao, prioridade, tempo_cpu, ID));
		num_processos++;
	}

	//ordena este vetor com base no tempo de criacao
	sort(processos.begin(), processos.end(), metodo_ordenacao());
}

#endif