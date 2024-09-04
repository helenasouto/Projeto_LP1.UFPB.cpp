#include "gerenciador.h"
#include "Menu.h"
#include <iostream>
#include <conio.h>  // Note que isso e específico para Windows
#include <limits>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

Menu::Menu() : Gerenciador() {
    // O gerenciador e inicializado corretamente aqui
}

void Menu::limparTela() const {
    system("clear"); // Para sistemas Unix/Linux
    system("cls");   // Para sistemas Windows
}

int Menu::lerOpcao() const {
    int opcao;
    cin >> opcao;
    while (cin.fail()) {
        cin.clear(); // Limpa o estado de erro
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora entradas invalidas
        cout << "Entrada invalida. Por favor, insira um número: ";
        cin >> opcao;
    }
    return opcao;
}

void Menu::exibirRelatorio() {
    cout << "=== Exibir Relatorio ===" << endl;
    Gerenciador.exibirRelatorio();
}

void Menu::exibirMenuPrincipal() {
    int opcao;
    do {
        //limparTela();
        cout << "=== Menu Principal ===" << endl;
        cout << "1. Cadastrar Paciente" << endl;
        cout << "2. Cadastrar Fisioterapeuta" << endl;
        cout << "3. Pesquisar Paciente por Nome" << endl;
        cout << "4. Pesquisar Fisioterapeuta por Nome" << endl;
        cout << "5. Mostrar Pacientes por Horario" << endl;
        cout << "6. Atualizar Dados de Pessoa" << endl;
        cout << "7. Atualizar Dados de Paciente" << endl;
        cout << "8. Atualizar Dados de Fisioterapeuta" << endl;
        cout << "9. Mudar Horario de Paciente" << endl;
        cout << "10. Remover Paciente" << endl;
        cout << "11. Remover Fisioterapeuta" << endl;
        cout << "12. Listar Horarios Livres de Fisioterapeuta" << endl;
        cout << "13. Gerar Relatorio" << endl;
        cout << "14. Sair" << endl;
        cout << "Escolha uma opcao: ";
        opcao = lerOpcao();

        switch (opcao) {
            case 1: cadastrarPaciente(); break;
            case 2: cadastrarFisioterapeuta(); break;
            case 3: pesquisarPaciente(); break;
            case 4: pesquisarFisioterapeuta(); break;
            case 5: mostrarPacientesPorHorario(); break;
            case 6: atualizarDadosPessoa(); break;
            case 7: atualizarDadosPaciente(); break;
            case 8: atualizarDadosFisioterapeuta(); break;
            case 9: mudarHorarioPaciente(); break;
            case 10: removerPaciente(); break;
            case 11: removerFisioterapeuta(); break;
            case 12: listarHorariosLivres(); break;
            case 13: exibirRelatorio(); break;
            case 14: cout << "Saindo..."<< endl; break;
            default: cout << "Opcao invalida!" << endl; break;
        }

        if (opcao != 14) {
            cout << "Pressione Enter para continuar...";
            cin.ignore();
            cin.get();
        }
    } while (opcao != 14);
}

void Menu::cadastrarPaciente() {
    string nome, cpf, telefone, responsavel, tipoPacote;
    int hora, minuto, idade;
    bool pagamento;
    
    /*if(Gerenciador.fisioList.empty()) {
        cout << "Nao e permitido cadastrar paciente sem Fisioterapeuta" << endl;
        cout << "Aperte enter para tentar novamente"<< endl;
        cin.ignore();
       getch();
       */
   // } else {
        cout << "=== Cadastrar Paciente ===" << endl;

        cout << "Nome: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  
        getline(cin, nome); // Lê nome completo, incluindo sobrenome

        cout << "CPF: "; 
        getline(cin, cpf);

        cout << "Telefone: ";
        getline(cin, telefone);

        cout << "Idade: "; 
        cin >> idade;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

        cout << "Fisioterapeuta Responsavel: "; 
        getline(cin, responsavel); 

        // Exibir opções de pacotes
        cout << "\n=== PACOTES / MENSALIDADE ===" << endl;
        cout << "1x - sessoes semanais: (sexta) ----- > R$175" << endl;
        cout << "2x - sessoes semanais: (segunda e quarta) ----- > R$260" << endl;
        cout << "3x - sessoes: (terça, quinta e sabado) ----- > R$360" << endl;

        cout << "\nTipo de Pacote escolhido pelo paciente: "; 
        getline(cin, tipoPacote); 

        cout << "Pagamento (1 para pago, 0 para nao): "; 
        while (!(cin >> pagamento) || (pagamento != 0 && pagamento != 1)) {
            cout << "Entrada invalida. Insira 1 ou 0: ";
            cin.clear(); // Limpa o estado de erro
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Hora: "; 
        cin >> hora;
        cout << "Minuto: "; 
        cin >> minuto;

        Paciente* paciente = new Paciente(nome, hora, minuto, cpf, idade, telefone, pagamento, responsavel, tipoPacote);
        Gerenciador.cadastrarpaciente(paciente);

        // Marcar horario como ocupado para o fisioterapeuta responsavel
        Gerenciador.marcarHorarioOcupado(responsavel, hora, minuto);

        cout << "Paciente cadastrado com sucesso!" << endl;
    //}
    Gerenciador.salvarDados();
}

void Menu::cadastrarFisioterapeuta() {
    string nome, cpf, telefone, drf;
    int idade;

    cout << " === Cadastrar Fisioterapeuta ===" << endl;
    cout << "Nome: "; 
    cin.ignore(); 
    getline(cin, nome); // Lê nome completo

    cout << "CPF: "; 
    getline(cin, cpf);

    cout << "Telefone: "; 
    getline(cin, telefone);

    cout << "Idade: "; 
    cin >> idade;

    cout << "DRF: "; 
    cin.ignore(); // Ignora nova linha
    getline(cin, drf); // Permite DRF composto

    Fisioterapeuta* fisioterapeuta = new Fisioterapeuta(nome, 0, 0, cpf, idade, telefone, drf); // Ajustado para nao exigir hora e minuto
    Gerenciador.cadastrarfisioterapeuta(fisioterapeuta);

    cout << "Fisioterapeuta cadastrado com sucesso!" << endl;
    Gerenciador.salvarDados();
}

void Menu::pesquisarPaciente() {
    string nome;
    cout << "=== Pesquisar Paciente ===" << endl;
    cout << "Nome: ";
    cin.ignore(); 
    getline(cin, nome); 
    Gerenciador.pesquisarPacientePorNome(nome);
    Gerenciador.salvarDados();
}

void Menu::pesquisarFisioterapeuta() {
    string nome;
    cout << "=== Pesquisar Fisioterapeuta ===" << endl;
    cout << "Nome: "; 
    cin.ignore(); 
    getline(cin, nome);
    Gerenciador.pesquisarFisioPorNome(nome);
    Gerenciador.salvarDados();
}

void Menu::mostrarPacientesPorHorario() {
    cout << "=== Mostrar Pacientes por Horario ===" << endl;
    Gerenciador.mostrarPacientesPorHorario();
    Gerenciador.salvarDados();
}

void Menu::atualizarDadosPessoa() {
    string cpf, novoNome, novoTelefone;
    int novaHora, novoMinuto, novaIdade;

    cout << "=== Atualizar Dados de Pessoa ===\n" << endl;
    cout << "CPF: "; cin >> cpf;
    cout << "Novo Nome: "; cin.ignore(); getline(cin, novoNome); // Permite nome composto
    cout << "Nova Hora: "; cin >> novaHora;
    cout << "Novo Minuto: "; cin >> novoMinuto;
    cout << "Nova Idade: "; cin >> novaIdade;
    cout << "Novo Telefone: "; cin.ignore(); getline(cin, novoTelefone); // Permite telefone composto, se necessario

    Gerenciador.atualizarPessoa(cpf, novoNome, novaHora, novoMinuto, novaIdade, novoTelefone);
    Gerenciador.salvarDados();
}

void Menu::atualizarDadosPaciente() {
    string cpf, novoResponsavel, novoTipoPacote;
    bool novoPagamento;

    cout << "=== Atualizar Dados de Paciente ===" << endl;
    cout << "CPF: "; cin >> cpf;
    cout << "Novo Responsavel: "; cin.ignore(); getline(cin, novoResponsavel); // Permite nome composto
    cout << "Novo Tipo de Pacote: "; getline(cin, novoTipoPacote); // Permite tipo de pacote composto
    cout << "Novo Pagamento (1 para pago, 0 para nao): "; 
    while (!(cin >> novoPagamento) || (novoPagamento != 0 && novoPagamento != 1)) {
        cout << "Entrada invalida. Insira 1 ou 0: ";
        cin.clear(); // Limpa o estado de erro
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    Gerenciador.atualizarPaciente(cpf, novoResponsavel, novoTipoPacote, novoPagamento);
    Gerenciador.salvarDados();
}

void Menu::atualizarDadosFisioterapeuta() {
    string cpf, novoDrf;

    cout << "=== Atualizar Dados de Fisioterapeuta ===" << endl;
    cout << "CPF: "; cin >> cpf;
    cout << "Novo DRF: "; cin.ignore(); getline(cin, novoDrf); // Permite DRF composto

    Gerenciador.atualizarFisioterapeuta(cpf, novoDrf);
    Gerenciador.salvarDados();
}

void Menu::mudarHorarioPaciente() {
    string cpf, novoResponsavel;
    int novaHora, novoMinuto;

    cout << "=== Mudar Horario de Paciente ===" << endl;
    cout << "CPF: "; cin >> cpf;
    cout << "Novo Responsavel: "; cin.ignore(); getline(cin, novoResponsavel); // Permite nome composto
    cout << "Nova Hora: "; cin >> novaHora;
    cout << "Novo Minuto: "; cin >> novoMinuto;

    Gerenciador.mudarHorarioPaciente(cpf, novaHora, novoMinuto);
    Gerenciador.salvarDados();
}

void Menu::removerPaciente() {
    string cpf;

    cout << "=== Remover Paciente ===" << endl;
    cout << "CPF: "; cin >> cpf;

    Gerenciador.removerPaciente(cpf);
    Gerenciador.salvarDados();
}

void Menu::removerFisioterapeuta() {
    string cpf;

    cout << "=== Remover Fisioterapeuta ===" << endl;
    cout << "CPF: "; cin >> cpf;

    Gerenciador.removerFisioterapeuta(cpf);
    Gerenciador.salvarDados();
}

void Menu::listarHorariosLivres() {
    string nome;

    cout << "=== Listar Horarios Livres ===" << endl;
    cout << "Nome do Fisioterapeuta: "; 
    cin.ignore(); getline(cin, nome); // Permite nome composto

    Gerenciador.listarHorariosLivres(nome);
    Gerenciador.salvarDados();
}
