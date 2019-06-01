#ifndef _CIRCULAR_H_
#define _CIRCULAR_H_
#include <map>
#include <deque>

#define QUANTUM 2

class Circular: public Escalonador{
	public:
		// Construtor
		Circular(){
		}
		
		virtual ~Circular(){
		}
	
		/*
		* Parametro: TF -> tempo final
		*
		* O tempo final de cada processo eh inserido no processosTF, 
		* assim tornando possivel o calculo de tempo medio.
		*/
		void calculaTempoMedioProcesso(map<string, int> TF){
			float tempoMedio = 0;
		
			for(int i = 0; i < Escalonador::getContador(); i++){
				cout << "\nProcessoID       -> " << Escalonador::getProcesso(i)->getID() << endl;

				cout << "Tempo Final      -> " << TF[Escalonador::getProcesso(i)->getID()] << endl;
				cout << "Tempo de Chegada -> " << Escalonador::getProcesso(i)->getTempoC() << endl;
				cout << "Tempo de CPU     -> " << Escalonador::getProcesso(i)->getTempoCPU() << endl;

				tempoMedio += TF[Escalonador::getProcesso(i)->getID()] - Escalonador::getProcesso(i)->getTempoC() - Escalonador::getProcesso(i)->getTempoCPU();
			}
			
			tempoMedio = tempoMedio / Escalonador::getContador();
			
			cout << "\n\nTempo de espera medio de processo -> " << tempoMedio << endl;
		}
		
		void execute(){
			int timeline = 0, q = 0;
			bool delay_event = false;
			
			// Map parametros
			// 1- string processoID
			// 2- int tempo de processo 
			map<string, int> processos;
			
			// Map parametros
			// 1- string processoID
			// 2- int tempo final do processo
			map<string, int> processosTF;
			
			// PilhaAkaDeque
			// 1 - string processoID
			deque<string> pilha;
			
			/* 
			* Inseri os processos no map, o mesmo eh utilizado para saber 
			* quantos processos estão em pendencia. Assim que um processo é finalizado,
			* ele eh retirado do map.
			*/
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
						if(!delay_event){
							pilha.push_back(Escalonador::getProcesso(i)->getID());
						}
						else{
							string _aux = pilha.back();
							pilha.pop_back();							
							
							pilha.push_back(Escalonador::getProcesso(i)->getID());
							pilha.push_back(_aux);
							// reinicializa para falso o evento
							delay_event = false;
						}						
					}							
				}					

				/*
				* Se nao houver processo na pilha, porem ha processos pendente(s)
				* imprime um --
				*/	
				if(pilha.size() == 0){
					cout << timeline << " -> --" << endl;
				}			
				else{
					//Executa uma parte do processo	
					cout << timeline << " -> " << pilha.front() << endl;				
	
					/*
					* encontra o processo que esta na frente da pilha no map de processos
					*/
					if(processos.find(pilha.front())->second > 1){	
						// decrementa o tempo de processo no map			
						processos[pilha.front()] = processos.find(pilha.front())->second - 1;	
						// incrementa o quantum		
						q++;					
					}
					//processo finalizado
					else{
						// Guarda o tempo final
						processosTF[pilha.front()] = timeline + 1;
						// remove do map de processos						
						processos.erase(pilha.front());	
						// remove da pilha de pocessos								
						pilha.pop_front();
						// reinicializa o quantum
						q = 0;
					}			
					
					// se o quantum for atingido, o processo vai para o final da pilha
					if(q == QUANTUM){
						// guarda a ID do processo
						string aux = pilha.front();		
						// remove da frente da pilha				
						pilha.pop_front();						
						// joga no final da pilha
						pilha.push_back(aux);
						// reinicializa o quantum
						q = 0;

						// Verifica se não ocorre o evento especial***
						for(int i = 0; i < Escalonador::getContador(); ++i){
							if(Escalonador::getProcesso(i)->getTempoC() == timeline+1){
								delay_event = true;
							}
						}
					}
				}				

				// incrementa a timeline
				timeline++;
			}

			cout<<"\n";			
			calculaTempoMedioProcesso(processosTF);
		}
};

#endif
