#ifndef _ESCALONAMENTO_H_
#define _ESCALONAMENTO_H_

#include <map>
#include <vector>
#include <algorithm>
#include <iterator>

#include "Processo.h"
#include "Leitura.h"

using namespace std;

void executa() {

	//vector armazenando os processos
	vector<Processo> processos;
	int num_processos = 0;

	//faz a leitura do arquivo
	Leitura_csv(processos, num_processos);

	//associa um processo com o tempo restante para o mesmo finalizar
	//no momento em que o int neste map chegar a zero, sera deletado o objeto deste processo
	map<string, int> tempo_cpu;

	//armazena o valor acima, porem sem decrementa-lo
	map<string, int> tempo_cpu_fixo;

	//associa um processo com sua prioridade 
	map<string, int> prioridade;

	//atribui um numero para cada processo, ordenado por tempo de criacao
	//este mapa sera ordenado pelo tempo de criacao e os processos irao para a fila de espera com base nesta ordem
	map<int, string> criacao;

	//associa os valores do mapa acima com seus tempos de criacao
	vector<int> tempo_criacao;

	//armazena os valores de TEA de cada processo
	map<string, int> TEA;

	//preenche os mapas
	for (int i = 0; i < num_processos; i++) {
		tempo_cpu      [processos[i].get_ID()] = processos[i].get_tempo_cpu();
		tempo_cpu_fixo [processos[i].get_ID()] = processos[i].get_tempo_cpu();
		prioridade     [processos[i].get_ID()] = processos[i].get_prioridade();
		criacao        [i+1] = processos[i].get_ID();
		tempo_criacao.push_back(processos[i].get_tempo_criacao());
	}

	int tempo = 0;
	auto fila = criacao.begin();

	//cada iteracao do While eh equivalente a uma unidade de tempo
	while (!processos.empty()) {

		//verifica se outro processo tem mais prioridade 

		// percorre o mapa de prioridades
		for (auto it = prioridade.begin(); it != prioridade.end(); it++) {

			// verifica se o processo atual do For tem mais prioridade
			if ((*it).second < prioridade[(*fila).second]) {

				//procura pelo processo adquirido acima na fila de processos
				for (auto aux = criacao.begin(); aux != criacao.end(); aux++) {

					//substitui o atual da fila pelo processo localizado (com mais prioridade)
					//e verifica se o tempo de criação eh menor que o tempo atual
					if ((*aux).second == (*it).first && tempo_criacao[(*aux).first-1] <= tempo) {
						fila = aux;
						break;
					}
				}
			}
		}
	
		//se ainda houver tempo de cpu restante no processo, executa
		if (tempo_cpu[(*fila).second] > 0) {
			tempo_cpu[(*fila).second]--;
			tempo++;

			cout << "Tempo " << tempo << ": ";
			cout << "Executando processo ID[" << (*fila).second << "]" << endl << endl;

		}
		//se o tempo de cpu acabou...
		else {

			cout << "> Processo ID " << (*fila).second << " Encerrado" << endl << endl;

			//calcula armazena o tempo de espera do processo que acabou de fechar
			//TEA = tempo atual - tempo de criacao - tempo de CPU 
			TEA[(*fila).second] = tempo - tempo_criacao[(*fila).first - 1] - tempo_cpu_fixo[(*fila).second];

			//procura pelo processo para deleta-lo
			for (auto it = processos.begin(); it != processos.end(); it++) {
				if ((*it).get_ID() == (*fila).second) {
					processos.erase(it);
					break;
				}
			}

			criacao.erase((*fila).first);

			//retorna a fila
			fila = criacao.begin();
		}

	}

	//calcula o TME e imprime uma tabela com os TEA's dos processos
	float tempo_medio = 0;

	cout << endl << "Tabela de TEA:" << endl;

	for (auto it = TEA.begin(); it != TEA.end(); it++) {
		cout << "Processo [" << (*it).first << "] = " << (*it).second << " U.T." << endl;
		tempo_medio += (*it).second;
	}
	tempo_medio /= num_processos;

	cout << endl << "Tempo medio de espera (TME): " << tempo_medio << endl;
}

#endif