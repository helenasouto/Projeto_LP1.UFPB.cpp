#ifndef PACIENTE_H
#define PACIENTE_H
#include "Pessoa.h"

#include <string>

using namespace std;

class Paciente : public Pessoa {

public:
    Paciente(const string& nome, int hora, int minuto,const string& cpf, int idade, const string& telefone, bool pagamento, const string& responsavel, const string& tpacote);
    string getResponsavel() const;
    string getTipoPacote () const;
    bool verificarpagamento() const;
    void setPagamento(bool pagamento);
    void atualizarDados(const string& nome, int hora, int minuto, int idade, const string& telefone) override;
    void atualizarResponsavel(const string& novoResponsavel);
    void atualizarTipoPacote(const string& novoTipoPacote);
    void atualizarPagamento(bool novoPagamento);
    int getHorap ();
    int getMinutop ();

protected:
    string responsavel;
    string tpacote;
private:
    bool pagamento;
};

#endif