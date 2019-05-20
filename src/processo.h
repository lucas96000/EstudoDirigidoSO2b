#ifndef _PROCESSO_H
#define _PROCESSO_H_

#include <iostream>
using namespace std;

class Processo{
	public:
		// Construtor
		Processo(int tempoCriacao = 0, string id = "", int prioridade = 0, int tempoCPU = 0) : 
		_tempoCriacao(tempoCriacao),
		_id(id),
		_prioridade(prioridade),
		_tempoCPU(tempoCPU)		
		{
			
		}
		
		// Destrutor
		~Processo(){
		}
		
		// getters and setters
		int getTempoC(){
			return _tempoCriacao;
		}	
		
		void setTempoC(int tempoCriacao){
			_tempoCriacao = tempoCriacao;
		}
		
		string getID(){
			return _id;
		}	
		
		void setID(string id){
			_id = id;
		}
		
		int getPrioridade(){
			return _prioridade;
		}	
		
		void setPrioridade(int pri){
			_prioridade = pri;
		}
		
		int getTempoCPU(){
			return _tempoCPU;
		}	
		
		void setTempoCPU(int tempoCPU){
			_tempoCPU = tempoCPU;
		}		
		
		void imprime(){
			cout << "PROCESSO -> " << getID() << endl;
		}
	
	private:
		// Atributos
		int 	_tempoCriacao;
		string 	_id;
		int 	_prioridade;
		int 	_tempoCPU;
};

#endif
