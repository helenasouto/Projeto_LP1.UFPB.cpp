#ifndef PESSOA_H
#define PESSOA_H

#include <string>
#include <vector>

using namespace std;

class Pessoa {
public:
    Pessoa(const string& nome, int hora, int minuto,const string& cpf, int idade, const string& telefone);
    virtual ~Pessoa() {} 
    string getNome() const;
    int getHora() const;
    int getMinuto() const;
    string getCPF() const;
    int getIdade() const;
    string getTelefone() const;

    virtual void atualizarDados (const string& nome, int hora, int minuto, int idade, const string& telefone)= 0;

protected:
    string nome;
    int hora;
    int minuto;
    string cpf;
    int idade;
    string telefone;
    vector<Pessoa*> pessoas;
    vector<Pessoa*> pessoaList;
};

#endif
