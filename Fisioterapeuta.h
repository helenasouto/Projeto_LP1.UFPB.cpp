#ifndef FISIOTERAPEUTA_H
#define FISIOTERAPEUTA_H
#include "Pessoa.h"
#include <vector>
#include <string>

    using namespace std;

    class Fisioterapeuta : public Pessoa 
    {
    public:
        Fisioterapeuta(const string& nome, int hora, int minuto, const string& cpf, int idade, const string& telefone, const string& drf);
        string getDRF() const;
        void atualizarFisioterapeuta(vector<Fisioterapeuta>& fisioList, const string& cpf, const string& novoDRF);
        void adicionarHorarioLivre(int hora, int minuto);
        void removerHorarioLivre(int hora, int minuto);
        void adicionarHorarioOcupado(int hora, int minuto); // Nova função
        void adicionarPaciente(const string& nome_paciente);
        void mostrarPacientes() const;
        vector<pair<int, int>> getHorariosLivres() const;
        void atualizarDados(const string& nome, int hora, int minuto, int idade, const string& telefone) override;
        void atualizarDRF(const string& novoDRF);
        bool pesquisarPaciente(const string& nome_paciente) const;
        vector<string> mostrarPacientesPorHorario(int horaInicio, int minutoInicio, int horaFim, int minutoFim) const;
        const vector<pair<int, int>>& getHorariosOcupados() const {
            return horarios_ocupados;
        }

    protected:
        vector<pair<int, int>> horarios_livres;
        vector<pair<int, int>> horarios_ocupados; 

    private:
        string drf;
        vector<string> pacientes;
    };

    #endif

