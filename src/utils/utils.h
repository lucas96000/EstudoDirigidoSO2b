#ifndef _UTILS_H_
#define _UTILS_H_

#define STR_MAX 200

#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

using namespace std;

class Utils{
	public:
		static void Ler(char* filePath, Escalonador* E){
			// Quantidade de linhas no arquivo
			int linhasQtd = LinhasQtdArq(filePath);
			
			// Vetor de strings para as linhas separadas
			char Linhas[linhasQtd][STR_MAX];
			
			E->setContador(linhasQtd);
			
			// Separa as linhas no vetor
			CsvSeparaLinhas(filePath, Linhas, linhasQtd);
			
			// Realiza a separacao dos elementos e transforma em processos
			LinhasParaListaProcessos(Linhas, E, linhasQtd);
		}
		
		// Retorna a quantidade de linhas no arquivo csv
		static int LinhasQtdArq(char* filePath){
			int linhas  = 0;
			
			FILE * file = fopen(filePath,"r");
		
			if(file == NULL){ //Se nao encontrar o arquivo
				printf("Arquivo nao encontrado.\n");
				exit(EXIT_FAILURE);
			}
			else{
				while(!feof(file)){ //enquanto nao terminar o arquivo
					char c = fgetc(file);
		
					if(c == EOF){
						if(ferror(file)){
						  perror("Nao foi possivel ler o arquivo");
						  fclose(file);
						}
		
						continue;
					}
					if(c == '\n'){
						++linhas;
					}
				}
			}
			
			fclose(file);
		
			return linhas;
		}
		
		// Separa as linhas do arquivo csv em um array de strings
		// Parametros 
		//[filePath]  -> caminho do arquivo 
		//[Linhas]    -> Vetor de strings para aramazenar cada linha inteira
		//[QtdLinhas] -> Quantidade de linhas no arquivo
		static void CsvSeparaLinhas(char* filePath, char Linhas[][STR_MAX], int LinhasQtd){
			// Lê o arquivo
			FILE * file = fopen(filePath,"r");
			
			if(file == NULL){ //Se nao encontrar o arquivo
				printf("Arquivo nao encontrado.\n");
				exit(EXIT_FAILURE);
			}
			else{
				int i = 0, j = 0;
		
				// Enquanto nao terminar o arquivo
				while(!feof(file)){ 
					// pega o char
					char c = fgetc(file);
		
					// Verifica se não é o final do arquivo
					if(c == EOF){
						if(ferror(file)){
						  perror("Nao foi possivel ler o arquivo");
						  fclose(file);
						}
		
						continue;
					}
					
					// Verifica se não é um '\n', se for vai para a próxima linha
					if(c == '\n'){
						// Inseri o caractere nulo para finalizar a string
						Linhas[i][j] = '\0';
						i++;				
						j = 0;
					}
					else{
						// Insere o char
						Linhas[i][j] = c;				
						j++;
					}
					
					// Insere o caractere nulo na ultima linha, pois não um '\n' na ultima linha
					Linhas[i][j+1] = '\0';
				}
		
				fclose(file);
			}
		}
	
		//Pega o array de strings e transforma e uma Mtriz esparsa
		//Parametros
		//[Linhas] 		-> Vetor contendo cada linha do arquivo
		//[E]      		-> Escalonador
		//[LinhasQtd]   	-> Quantidade de linhas no arquivo
		static void LinhasParaListaProcessos(char Linhas[][STR_MAX], Escalonador* E, int LinhasQtd){
			int i, j, m, elementos, n_elementos;
			
			// Verifica se cada linha tem o mesmo numero de elemento
			for(i = 0; i < LinhasQtd; ++i){
				elementos = 1;
				for(j = 0; j < strlen(Linhas[i]); ++j){	
					// É utilizado o ponto e virgula pra saber quantos elementos contem na linha		
					if(Linhas[i][j] == ';'){ 
						elementos++;
					}
				}
				
				
				if(i == 0){
					n_elementos = elementos;
				} else{
					if(elementos != n_elementos || n_elementos != 4){			
						printf("Erro ao ler arquivo, o numero de elementos deve ser o mesmo em todas as linhas e igual a 4.\n");
		    			exit(EXIT_FAILURE);
					}
				}		
			}					
			
			// Pega a linha do arquivo e faz um explode separando os elementos pelo delimitador ';'
			for(i = 0, j = 0, m = 0; i < LinhasQtd; i++){
				char *tok = strtok(Linhas[i], ";");		
										
				while (tok != NULL) {		    
				    switch(j){
				    	case 0:
				    		E->getProcesso(m)->setTempoC(atoi(tok));								    		
				    		break;
				    	case 1:
				    		E->getProcesso(m)->setID(tok);   		
				    		break;
				    	case 2:
				    		E->getProcesso(m)->setPrioridade(atoi(tok));
				    		break;
				    	case 3:
				    		E->getProcesso(m)->setTempoCPU(atoi(tok));			    		
				    		break;				    	
					}
					
					tok = strtok(NULL, ";");
				    j++;			    
				    
				    if(j == 4){
						j = 0;
				    	m++;
					}
				}
			}
		}
};

#endif
