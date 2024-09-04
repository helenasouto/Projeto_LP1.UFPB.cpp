#include "Paciente.h"
    #include "Pessoa.h"
    #include "Fisioterapeuta.h"
    #include <vector>
    #include <string>
    #include <iostream>

    using namespace std;

    Paciente::Paciente(const string& nome, int hora, int minuto, const string& cpf, int idade, const string& telefone, bool pagamento, const string& responsavel, const string& tpacote)
    : Pessoa(nome, hora, minuto, cpf, idade, telefone), pagamento(pagamento), responsavel(responsavel), tpacote(tpacote) {
    }

    string Paciente::getResponsavel() const {
        return responsavel;
    }

    string Paciente::getTipoPacote() const {
        return tpacote;
    }

    bool Paciente::verificarpagamento() const {
        return pagamento;
    }

    void Paciente::setPagamento(bool pagamento) {
        this->pagamento = pagamento;
    }

    void Paciente::atualizarDados(const string& nome, int hora, int minuto, int idade, const string& telefone) {
        this->nome = nome;
        this->hora = hora;
        this->minuto = minuto;
        this->idade = idade;
        this->telefone = telefone;
    }

    void Paciente::atualizarResponsavel(const string& novoResponsavel) {
        this->responsavel = novoResponsavel;
    }

    void Paciente::atualizarTipoPacote(const string& novoTipoPacote) {
        this->tpacote = novoTipoPacote;
    }

    void Paciente::atualizarPagamento(bool novoPagamento) {
        this->pagamento = novoPagamento;
    }

    int Paciente:: getHorap(){
        return hora;
    }
    int Paciente::getMinutop(){
        return minuto;
    }