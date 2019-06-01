#include <iostream>
#include "src/processo.h"
#include "src/escalonador.h"
#include "src/circular.h"
#include "src/utils/utils.h"

using namespace std;

int main(int argc, char** argv) {
	Circular* c = new Circular();

	Utils::Ler("arquivo/processos.txt", c);
	
	c->execute();

	return 0;
}