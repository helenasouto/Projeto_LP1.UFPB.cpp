#include "gerenciador.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <memory>
#include <sstream>

using namespace std;

gerenciador::gerenciador() {
    carregarDados();
    salvarDados();
}

gerenciador::~gerenciador() {

}

// Removido duplicata da função mostrarPacientesPorHorario

void gerenciador::salvarDados() {
    // Salvar Pacientes
    ofstream arquivoPacientes("pacientes.txt");
    if (arquivoPacientes.is_open()) {
        for (const auto& pessoa : pacienteList) {
            if (const Paciente* paciente = dynamic_cast<const Paciente*>(pessoa)) {
                arquivoPacientes << paciente->getNome() << "," 
                                 << paciente->getCPF() << "," 
                                 << paciente->getHora() << "," 
                                 << paciente->getMinuto() << "," 
                                 << paciente->getIdade() << "," 
                                 << paciente->getTelefone() << "," 
                                 << paciente->getResponsavel() << "," 
                                 << paciente->getTipoPacote() << "," 
                                 << (paciente->verificarpagamento() ? "1" : "0") << endl;

                cout << "Salvando paciente: " << paciente->getNome() << ", CPF: " << paciente->getCPF() << endl;
            }
        }
        arquivoPacientes.close();
    } else {
        cout << "Não foi possível abrir o arquivo para salvar os dados dos pacientes." << endl;
    }

    // Salvar Fisioterapeutas
    ofstream arquivoFisioterapeutas("fisioterapeutas.txt");
    if (arquivoFisioterapeutas.is_open()) {
        for (const auto& pessoa : fisioList) {
            if (const Fisioterapeuta* fisio = dynamic_cast<const Fisioterapeuta*>(pessoa)) {
                arquivoFisioterapeutas << fisio->getNome() << "," 
                                       << fisio->getCPF() << "," 
                                       << fisio->getDRF() << endl;
            cout << "Salvando fisioterapeuta: " << fisio->getNome() << ", CPF: " << fisio->getCPF() << endl;
            }
        }
        arquivoFisioterapeutas.close();
    } else {
        cout << "Não foi possível abrir o arquivo para salvar os dados dos fisioterapeutas." << endl;
    }
}

void gerenciador::carregarDados() {
    // Carregar Pacientes
    ifstream arquivoPacientes("pacientes.txt");
    if (arquivoPacientes.is_open()) {
        cout << "Arquivo de pacientes aberto com sucesso." << endl;
        string linha;
        while (getline(arquivoPacientes, linha)) {
            stringstream ss(linha);
            string nome, cpf, telefone, responsavel, tipoPacote;
            int hora, minuto, idade;
            bool pagamento;

            getline(ss, nome, ',');
            getline(ss, cpf, ',');
            ss >> hora;
            ss.ignore(); // Ignora a vírgula
            ss >> minuto;
            ss.ignore(); // Ignora a vírgula
            ss >> idade;
            ss.ignore(); // Ignora a vírgula
            getline(ss, telefone, ',');
            getline(ss, responsavel, ',');
            getline(ss, tipoPacote, ',');
            int pago;
            ss >> pago;
            pagamento = (pago == 1);

            cout << "Carregando paciente: Nome: " << nome << ", CPF: " << cpf 
                 << ", Hora: " << hora << ", Minuto: " << minuto 
                 << ", Idade: " << idade << ", Telefone: " << telefone 
                 << ", Responsável: " << responsavel << ", Pacote: " 
                 << tipoPacote << ", Pagamento: " << (pagamento ? "Pago" : "Não Pago") << endl;

            Paciente* novoPaciente = new Paciente(nome, hora, minuto, cpf, idade, telefone, pagamento, responsavel, tipoPacote);
            cadastrarpaciente(novoPaciente);
        }
        arquivoPacientes.close();
    } else {
        cout << "Não foi possível abrir o arquivo para carregar os dados dos pacientes." << endl;
    }

    // Carregar Fisioterapeutas
    ifstream arquivoFisioterapeutas("fisioterapeutas.txt");
    if (arquivoFisioterapeutas.is_open()) {
        string linha;
        while (getline(arquivoFisioterapeutas, linha)) {
            stringstream ss(linha);
            string nome, cpf, drf;

            getline(ss, nome, ',');
            getline(ss, cpf, ',');
            getline(ss, drf, ',');

            cout << "Carregando fisioterapeuta: Nome: " << nome << ", CPF: " << cpf 
                 << ", DRF: " << drf << endl;

            Fisioterapeuta* novoFisio = new Fisioterapeuta(nome, 0, 0, cpf, 0, "", drf);
            cadastrarfisioterapeuta(novoFisio);
        }
        arquivoFisioterapeutas.close();
    } else {
        cout << "Não foi possível abrir o arquivo para carregar os dados dos fisioterapeutas." << endl;
    }
}

void gerenciador::exibirRelatorio() const {
    cout << "Relatorio de Pacientes e Fisioterapeutas\n";
    cout << "=========================================\n\n";

    // Seção de Pacientes
    cout << "=== Pacientes ===\n";
    for (const auto& pessoa : pessoaList) {
        if (const Paciente* paciente = dynamic_cast<const Paciente*>(pessoa)) {
            cout << "Paciente: " << paciente->getNome()
                 << ", CPF: " << paciente->getCPF()
                 << ", Horario: " << paciente->getHora() << ":" 
                 << (paciente->getMinuto() < 10 ? "0" : "") << paciente->getMinuto()
                 << ", Idade: " << paciente->getIdade() 
                 << ", Telefone: " << paciente->getTelefone()
                 << ", Fisioterapeuta Responsavel: " << paciente->getResponsavel() 
                 << ", Tipo de Pacote: " << paciente->getTipoPacote()
                 << ", Pagamento: " << (paciente->verificarpagamento() ? "Sim" : "Não") 
                 << "\n";
        }
    }

    cout << "\n=== Fisioterapeutas ===\n"; // Separador para fisioterapeutas
    for (const auto& pessoa : fisioList) {
        if (const Fisioterapeuta* fisio = dynamic_cast<const Fisioterapeuta*>(pessoa)) {
            cout << "Fisioterapeuta:Dr. " << fisio->getNome()
                 << ", CPF: " << fisio->getCPF()
                 << ", DRF: " << fisio->getDRF() 
                 << "\n";
        }
    }

    cout << "=========================================\n";
}
void gerenciador::mostrarPacientesPorHorario() const {
    // Contagem de pacientes por intervalo de hora
    int contagem[15] = {0}; // Intervalos de 6:00 a 20:00 (15 intervalos)

    // Contar pacientes para cada intervalo
    for (const auto& pessoa : pacienteList) {
        if (const Paciente* paciente = dynamic_cast<const Paciente*>(pessoa)) {
            if (paciente->getHora() >= 6 && paciente->getHora() < 20) {
                contagem[paciente->getHora() - 6]++;
            }
        }
    }

    // Exibir intervalos com pacientes
    cout << "Pacientes por intervalo:" << endl;
    bool tevePacientes = false; // Flag para verificar se teve pacientes

    for (int i = 0; i < 15; ++i) {
        if (contagem[i] > 0) {
            cout << "Horario: " << (i + 6) << ":00 - " << (i + 7) << ":00 : " << contagem[i] << " paciente(s)" << endl;
            tevePacientes = true; // Teve pelo menos um paciente
        }
    }

    if (!tevePacientes) {
        cout << "Nenhum paciente agendado durante o expediente." << endl;
        return;
    }

    // Solicitar intervalo ao usuário com horário real
    int horaInicio;
    cout << "Escolha o horario de início (entre 6 e 19): ";
    cin >> horaInicio;

    if (horaInicio < 6 || horaInicio >= 20) {
        cout << "Horario invalido!" << endl;
        return;
    }

    int minutoInicio = 0;
    int minutoFim = 0;
    int horaFim = horaInicio + 1;

    cout << "Pacientes entre " << horaInicio << ":" << (minutoInicio < 10 ? "0" : "") << minutoInicio 
         << " e " << horaFim << ":" << (minutoFim < 10 ? "0" : "") << minutoFim << ":" << endl;

    bool encontrouPaciente = false; // Para verificar se encontramos pacientes no intervalo

    for (const auto& pessoa : pacienteList) {
        if (const Paciente* paciente = dynamic_cast<const Paciente*>(pessoa)) {
            int hora = paciente->getHora();
            int minuto = paciente->getMinuto();

            if ((hora > horaInicio || (hora == horaInicio && minuto >= minutoInicio)) &&
                (hora < horaFim || (hora == horaFim && minuto < minutoFim))) {
                cout << " - " << hora << ":" << (minuto < 10 ? "0" : "") << minuto << " - " << paciente->getNome() << endl;
                encontrouPaciente = true; // Encontrou pelo menos um paciente
            }
        }
    }

    if (!encontrouPaciente) {
        cout << "Nenhum paciente agendado neste horario." << endl;
        return;
    }

    // Perguntar se deseja ver os dados dos pacientes
    char opcao;
    cout << "Deseja ver os dados desses pacientes? (s/n): ";
    cin >> opcao;

    if (opcao == 's' || opcao == 'S') {
        for (const auto& pessoa : pacienteList) {
            if (const Paciente* paciente = dynamic_cast<const Paciente*>(pessoa)) {
                int hora = paciente->getHora();
                int minuto = paciente->getMinuto();

                // Verifique se hora e minuto estão no intervalo esperado
                if (minuto < 0 || minuto >= 60) {
                    cout << "Minuto invalido: " << minuto << " para paciente " << paciente->getNome() << endl;
                    continue; // Pula para o próximo paciente
                }

                if ((hora > horaInicio || (hora == horaInicio && minuto >= minutoInicio)) &&
                    (hora < horaFim || (hora == horaFim && minuto < minutoFim))) {
                    // Exibir os dados do paciente
                    cout << "Dados do Paciente:" << endl;
                    cout << "Nome: " << paciente->getNome() << endl;
                    cout << "CPF: " << paciente->getCPF() << endl;
                    cout << "Telefone: " << paciente->getTelefone() << endl;
                    // Adicione outros detalhes do paciente que deseja exibir
                    cout << endl;
                }
            }
        }
    }
}

void gerenciador::pesquisarPacientePorNome(const string& nome) const {
    for (const auto& pessoa : pacienteList) {
        if (const Paciente* p = dynamic_cast<const Paciente*>(pessoa)) {
            if (p->getNome() == nome) {
                cout << "Paciente: " << p->getNome() << " - Horario: " << p->getHora() << ":" << (p->getMinuto() < 10 ? "0" : "") << p->getMinuto() << endl;
                return;
            }
        }
    }
    cout << "Paciente nao encontrado" << endl;
}
void gerenciador::pesquisarFisioPorNome(const string& nome) const {
    string nomeFormatado = nome;
    nomeFormatado.erase(remove(nomeFormatado.begin(), nomeFormatado.end(), ' '), nomeFormatado.end()); // Remover espaços

    for (const auto& pessoa : fisioList) {
        if (const Fisioterapeuta* f = dynamic_cast<const Fisioterapeuta*>(pessoa)) {
            string nomeFisioFormatado = f->getNome();
            nomeFisioFormatado.erase(remove(nomeFisioFormatado.begin(), nomeFisioFormatado.end(), ' '), nomeFisioFormatado.end()); // Remover espaços

            if (nomeFisioFormatado == nomeFormatado) {
                cout << "Fisioterapeuta: " << f->getNome() << " - DRF: " << f->getDRF() << endl;
                return;
            }
        }
    }
    cout << "Fisioterapeuta nao encontrado" << endl;
}

void gerenciador::atualizarPessoa(const string& cpf, const string& novoNome, int novaHora, int novoMinuto, int novaIdade, const string& novoTelefone) {
    for (auto& pessoa : pessoaList) {
        if (pessoa->getCPF() == cpf) {
            pessoa->atualizarDados(novoNome, novaHora, novoMinuto, novaIdade, novoTelefone);
            
            return;
        }
    }
    cout << "Pessoa nao encontrada" << endl;
    salvarDados();
}

void gerenciador::atualizarPaciente(const string& cpf, const string& novoResponsavel, const string& novoTipoPacote, bool novoPagamento) {
    for (auto& pessoa : pacienteList) {
        if (Paciente* paciente = dynamic_cast<Paciente*>(pessoa)) {
            if (paciente->getCPF() == cpf) {
                paciente->atualizarResponsavel(novoResponsavel);
                paciente->atualizarTipoPacote(novoTipoPacote);
                paciente->atualizarPagamento(novoPagamento);
            
                return;
            }
        }
    }
    cout << "Paciente nao encontrado" << endl;                
    salvarDados();

}

void gerenciador::atualizarFisioterapeuta(const string& cpf, const string& novoDRF) {
    for (auto& pessoa : fisioList) {
        if (Fisioterapeuta* fisio = dynamic_cast<Fisioterapeuta*>(pessoa)) {
            if (fisio->getCPF() == cpf) {
                fisio->atualizarDRF(novoDRF);

                return;
            }
        }
    }
    cout << "Fisioterapeuta nao encontrado" << endl;
    salvarDados();
}

void gerenciador::mudarHorarioPaciente(const string& cpf, int novaHora, int novoMinuto) {
    for (auto& pessoa : pacienteList) {
        if (Paciente* paciente = dynamic_cast<Paciente*>(pessoa)) {
            if (paciente->getCPF() == cpf) {
                paciente->atualizarDados(paciente->getNome(), novaHora, novoMinuto, paciente->getIdade(), paciente->getTelefone());

               
                return;
            }
        }
    }
    cout << "Paciente nao encontrado" << endl;
    salvarDados();
}

void gerenciador::removerPaciente(const string& cpf) {
    for (auto it = pacienteList.begin(); it != pacienteList.end(); ++it) {
        if (Paciente* paciente = dynamic_cast<Paciente*>(*it)) {
            if (paciente->getCPF() == cpf) {
                delete *it;
                pacienteList.erase(it);
                cout << "Paciente removido com sucesso." << endl;
              
                return;
            }
        }
    }
    cout << "Paciente nao encontrado" << endl;
    salvarDados();
}

void gerenciador::removerFisioterapeuta(const string& cpf) {
    for (auto it = fisioList.begin(); it != fisioList.end(); ++it) {
        if (Fisioterapeuta* fisio = dynamic_cast<Fisioterapeuta*>(*it)) {
            if (fisio->getCPF() == cpf) {
                delete *it;
                fisioList.erase(it);
                cout << "Fisioterapeuta removido com sucesso." << endl;
            
                return;
            }
        }
    }
    cout << "Fisioterapeuta nao encontrado" << endl;
}

void gerenciador::listarHorariosLivres(const string& nome) const {
    cout << "Procurando Fisioterapeuta com Nome: " << nome << endl; // Mensagem de depuração
    for (auto& pessoa : fisioList) {
        if (Fisioterapeuta* fisio = dynamic_cast<Fisioterapeuta*>(pessoa)) {
            if (fisio->getNome () == nome) {
                cout << "Horarios livres para " << fisio->getNome() << ":" << endl;

                // Supondo que o expediente vai de 6:00 a 20:00
                for (int hora = 6; hora < 20; ++hora) {
                    int vagasDisponiveis = 0; // Supondo um limite de 3 pacientes por intervalo
                    
                    // Verifica quantos horários ocupados estão nesse intervalo
                    for (const auto& horario : fisio->getHorariosOcupados()) {
                        cout << "Verificando horário ocupado: " << horario.first << endl; // Mensagem de depuração
                        if (horario.first == hora) {
                            --vagasDisponiveis; // Reduz a contagem de vagas se estiver ocupado
                        }
                    }
                    // Exibe horário se houver vagas disponíveis
                    if (vagasDisponiveis > 0) {
                        cout << hora << ":00 às " << hora + 1 << ":00 - Vagas disponíveis: " << vagasDisponiveis << endl;
                    }
                }
                return;
            }
        }
    }
    cout << "Fisioterapeuta nao encontrado" << endl;
}


void gerenciador::cadastrarpaciente(Paciente* paciente) {

    /*if(fisioList.empty()) {
        cout << "Não é permitido cadastrar paciente sem Fisioterapeuta";

        return;
    }*/
    // Adiciona paciente à lista
    pacienteList.push_back(paciente); // Presumindo que você tenha uma lista de pacientes
    pessoaList.push_back(paciente);
    
    // Obtém o nome do fisioterapeuta responsável e o horário do paciente
    string nomeFisio = paciente->getResponsavel();
    int hora = paciente->getHorap();
    int minuto = paciente->getMinutop();

    // Verifica se o horário já está ocupado
    int contagemPacientes = 0;
    for (const auto& p : pacienteList) {
        if (Paciente* pPaciente = dynamic_cast<Paciente*>(p)) {
            if (pPaciente->getHorap() == hora && pPaciente->getMinutop() == minuto && pPaciente->getResponsavel() == nomeFisio) {
                contagemPacientes++;
            }
        }
    }

    if (contagemPacientes < 3) {
        // Se há menos de 3 pacientes para o mesmo horário, permite o cadastro
        marcarHorarioOcupado(nomeFisio, hora, minuto);
        cout << "Paciente cadastrado com sucesso das " << hora << "h às " << hora + 1 << "h. É permitido o cadastro de 3 pacientes por intervalo de horário." << endl;
    } else {
        // Caso contrário, não permite o cadastro
        cout << "Horário " << hora << ":" << (minuto < 10 ? "0" : "") << minuto << " já está ocupado. Não é possível cadastrar mais pacientes neste horário." << endl;
    }
    if (pacienteList.empty()) {
    cout << "A lista de pacientes está vazia antes de salvar os dados." << endl;
}

}

void gerenciador::cadastrarfisioterapeuta(Fisioterapeuta* fisioterapeuta) {
    pessoaList.push_back(fisioterapeuta);
    fisioList.push_back(fisioterapeuta);
    salvarDados();
}
 void gerenciador::adicionarHorarioOcupado(int hora, int minuto) {
    horariosOcupados.push_back(make_pair(hora, minuto));
    salvarDados();
}

void gerenciador::marcarHorarioOcupado(const string& nomeFisio, int hora, int minuto) {
    for (auto& pessoa : fisioList) {
        if (Fisioterapeuta* fisio = dynamic_cast<Fisioterapeuta*>(pessoa)) {
            if (fisio->getNome() == nomeFisio) {
                fisio->adicionarHorarioOcupado(hora, minuto); // Marca o horário como ocupado
                //cout << "Horario " << hora << ":" << (minuto < 10 ? "0" : "") << minuto 
                     //<< " marcado como ocupado para " << fisio->getNome() << "." << endl;

                return;

            }
        }
    }
    cout << "Fisioterapeuta nao encontrado" << endl;
}
