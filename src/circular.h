#ifndef _CIRCULAR_H_
#define _CIRCULAR_H_
#include <map>
#include <deque>
#include <algorithm>

#define QUANTUM 2

class Circular: public Escalonador{
	public:
		Circular(){
		}
		
		virtual ~Circular(){
		}
	
		/*void calculaTempoMedioProcesso(){
			int tempoMedio;
		
			//(tempo final - tempo chegada - tempo de processo)
		}*/
		
		void execute(){
			int timeline = 0, q = 0;
			
			// Map parametros
			// 1- string processoID
			// 2- int tempo de processo 
			map<string, int> processos;
			
			// Map parametros
			// 1- string processoID
			// 2- int tempo final do processo
			map<string, int> processosTF;
			
			// DequeAkaPilha
			// 1 - string processoID
			deque<string> pilha;
			
			// Inseri os processos no map
			for(int i = 0; i < Escalonador::getContador(); ++i){
				processos[Escalonador::getProcesso(i)->getID()] = Escalonador::getProcesso(i)->getTempoCPU();				
			}
			
			// Enquanto houver processos pendentes
			while(processos.size() > 0){
				for(int i = 0; i < Escalonador::getContador(); ++i){
					// se o tempo de chegada for igual ao da timeline
					if(Escalonador::getProcesso(i)->getTempoC() == timeline){	
						/* * * * EVENTO ESPECIAL
						*
						* Descricao do evento: se na mesma hora que o quantum acabar e um processo chega,
						* eh necessario que o processo que chegou fique na frente em relacao ao processo
						* que estava em execucao pilha.
						*
						*/
						if(q >= 0 && q < QUANTUM){
							pilha.push_back(Escalonador::getProcesso(i)->getID());
						}
						else{
							if(pilha.size() == 0){
								pilha.push_back(Escalonador::getProcesso(i)->getID());
							}
							else{
								string _aux = pilha.back();
								pilha.pop_back();							
								
								pilha.push_back(Escalonador::getProcesso(i)->getID());
								pilha.push_back(_aux);
							} 							
						}							
					}							
				}					
					
					
				if(pilha.size() == 0){
					cout << timeline << " -> --" << endl;
				}			
				else{
					//Executa o processo	
					cout << timeline << " -> " << pilha.front() << endl;				
	
					if(processos.find(pilha.front())->second > 1){				
						processos[pilha.front()] = processos.find(pilha.front())->second - 1;			
						q++;					
					}
					//processo finalizado
					else{
						processos.erase(pilha.front());
						pilha.pop_front();
						q = 0;
					}			
					
					// QUANTUM
					if(q == QUANTUM){
						string aux = pilha.front();						
						pilha.pop_front();
						
						pilha.push_back(aux);
						q = 0;
					}
				}				
				
				timeline++;
			}
		}
};

#endif
