#include "Pessoa.h"
#include <iostream>

using namespace std;

Pessoa::Pessoa(const string& nome, int hora, int minuto,const string& cpf, int idade, const string& telefone) : nome(nome), hora(hora), minuto(minuto), cpf(cpf), idade(idade), telefone(telefone) {}

string Pessoa::getNome() const {
    return nome;
}

int Pessoa::getHora() const {
        return hora;
}

int Pessoa::getMinuto() const {
    return minuto;
}

string Pessoa::getCPF() const {
    return cpf;
}

int Pessoa::getIdade() const {
    return idade;
}

string Pessoa::getTelefone() const {
    return telefone;
}
