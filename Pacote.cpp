#include "Pacote.h"
#include <string>
#include <iostream>

using namespace std;

Pacote::Pacote(int quantidadeAulas, double valorPorPacote) : quantidadeAulas(quantidadeAulas), valorPorPacote(valorPorPacote) {};

int Pacote::getQuantidadeAulas() const {
     return quantidadeAulas; 
     }

double Pacote::getValorPorPacote() const {
     return valorPorPacote; 
     }
