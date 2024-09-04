#include "Fisioterapeuta.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

Fisioterapeuta::Fisioterapeuta(const string& nome, int hora, int minuto, const string& cpf, int idade, const string& telefone, const string& drf)
    : Pessoa(nome, hora, minuto, cpf, idade, telefone), drf(drf) {}

void Fisioterapeuta::atualizarFisioterapeuta(vector<Fisioterapeuta>& fisioList, const string& cpf, const string& novoDRF) {
    for (auto& fisioterapeuta : fisioList) {
        if (fisioterapeuta.getCPF() == cpf) {
            fisioterapeuta.atualizarDRF(novoDRF);
            return;
        }
    }
    
    cout << "Fisioterapeuta não encontrado" << endl;
}

string Fisioterapeuta::getDRF() const {
    return drf;
}

void Fisioterapeuta::adicionarHorarioLivre(int hora, int minuto) {
    horarios_livres.push_back(make_pair(hora, minuto));
}

void Fisioterapeuta::removerHorarioLivre(int hora, int minuto) {
    for (size_t i = 0; i < horarios_livres.size(); i++) {
        if (horarios_livres[i].first == hora && horarios_livres[i].second == minuto) {
            horarios_livres.erase(horarios_livres.begin() + i);
            break;
        }
    }
}

void Fisioterapeuta::adicionarPaciente(const string& nome_paciente) { // Corrigido
    pacientes.push_back(nome_paciente);
}

void Fisioterapeuta::mostrarPacientes() const {
    cout << "Pacientes do(a) fisioterapeuta: " << nome << endl; 
    for (const auto& paciente : pacientes) {
        cout << paciente << endl;
    }
}

vector<pair<int, int>> Fisioterapeuta::getHorariosLivres() const {
    return horarios_livres;
}

void Fisioterapeuta::atualizarDados(const string& nome, int hora, int minuto, int idade, const string& telefone) {
    this->nome = nome;
    this->hora = hora;
    this->minuto = minuto;
    this->idade = idade;
    this->telefone = telefone;
}

void Fisioterapeuta::atualizarDRF(const string& novoDRF) {
    this->drf = novoDRF;
}

void Fisioterapeuta::adicionarHorarioOcupado(int hora, int minuto) {
    
    for (const auto& horario : horarios_ocupados) {
        if (horario.first == hora && horario.second == minuto) {
            cout << "Horário " << hora << ":" << (minuto < 10 ? "0" : "") << minuto 
                 << " já está ocupado." << endl;
            return; // Se já estiver ocupado, não faz nada
        }
    }
  
    horarios_ocupados.push_back(make_pair(hora, minuto));
    cout << "Horário " << hora << ":" << (minuto < 10 ? "0" : "") << minuto 
         << " marcado como ocupado." << endl;
}
