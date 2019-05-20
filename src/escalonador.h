#ifndef _ESCALONADOR_H_
#define _ESCALONADOR_H_

#define PROCESS_MAX 20

class Escalonador{
	public:		
		Processo* getProcessos(){
			return _processos;
		}
		
		Processo* getProcesso(int indice){
			return &_processos[indice];
		}
		
		int getContador(){
			return _contador;
		}
		
		void setContador(int c){
			_contador = c;
		}
		
		virtual void execute() = 0;

	private:
		Processo    _processos[PROCESS_MAX];
		int 		_contador; 
};

#endif
