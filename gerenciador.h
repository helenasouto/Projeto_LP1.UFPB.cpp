#ifndef GERENCIADOR_H
#define GERENCIADOR_H

#include "Pessoa.h"
#include "Fisioterapeuta.h"
#include "Paciente.h"
#include <vector>
#include <fstream> // Necessário para manipulação de arquivos
#include <iostream> // Necessário para std::cout
#include <string>

using namespace std;

class gerenciador 
{
public:
    gerenciador();
    ~gerenciador();

    void cadastrarpaciente(Paciente* paciente);
    void cadastrarfisioterapeuta(Fisioterapeuta* fisioterapeuta);
    void pesquisarPacientePorNome(const string& nome) const;
    void pesquisarFisioPorNome(const string& nome) const;
    void mostrarPacientesPorHorario() const;
    void atualizarPessoa(const string& cpf, const string& novoNome, int novaHora, int novaMinuto, int novaIdade, const string& novoTelefone);
    void atualizarPaciente(const string& cpf, const string& novoResponsavel, const string& novoTipoPacote, bool novoPagamento);
    void atualizarFisioterapeuta(const string& cpf, const string& novoDRF);
    void mudarHorarioPaciente(const string& cpf, int novaHora, int novoMinuto);
    void removerPaciente(const string& cpf);
    void removerFisioterapeuta(const string& cpf);
    void listarHorariosLivres(const string& cpf) const;
    void exibirRelatorio() const; 
    void adicionarHorarioOcupado(int hora, int minuto); // Cuidado
    const vector<pair<int, int>>& getHorariosOcupados() const;
    void marcarHorarioOcupado(const std::string& cpfFisio, int hora, int minuto);

    vector<Pessoa*> pessoaList;
    vector<Paciente*> pacienteList;
    vector<Fisioterapeuta*> fisioList;
    vector<pair<int, int>> horariosOcupados;
    void salvarDados(); // Declaração da função para salvar dados em um arquivo
    void carregarDados();
};
#endif