#ifndef _CIRCULAR_H_
#define _CIRCULAR_H_
#include <map>
#include <deque>
#include <algorithm>

class Circular: public Escalonador{
	public:
		Circular(){
		}
		
		virtual ~Circular(){
		}
		
		void execute(){
			int timeline = 0, q = 0;
			
			// Map parametros
			// 1- string ID
			// 2- int tempo de processo 
			map<string, int> processos;
			
			deque<string> fila;
			
			for(int i = 0; i < Escalonador::getContador(); ++i){
				processos[Escalonador::getProcesso(i)->getID()] = Escalonador::getProcesso(i)->getTempoCPU();				
			}
			
			while(processos.size() > 0){
				for(int i = 0; i < Escalonador::getContador(); ++i){
					if(Escalonador::getProcesso(i)->getTempoC() == timeline){
											
						if(q != 0){
							fila.push_back(Escalonador::getProcesso(i)->getID());
						}
						else{
							if(fila.size() == 0){
								fila.push_back(Escalonador::getProcesso(i)->getID());
							}
							else{
								string _aux = fila.back();
								fila.pop_back();							
								
								fila.push_back(Escalonador::getProcesso(i)->getID());
								fila.push_back(_aux);
							} 							
						}							
					}							
				}					
							
				//Executa o processo	
				cout << timeline << " -> " << fila.front() << endl;				

				if(processos.find(fila.front())->second > 1){				
					processos[fila.front()] = processos.find(fila.front())->second - 1;			
					q++;					
				}
				//processo finalizado
				else{
					processos.erase(fila.front());
					fila.pop_front();
					q = 0;
				}			
				
				if(q == 2){
					string aux = fila.front();						
					fila.pop_front();
					
					fila.push_back(aux);
					q = 0;
				}
								
				timeline++;
			}
		}
};

#endif
