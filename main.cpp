#include <string.h>
#include <iostream>
#include "Pessoa.h"
#include "Paciente.h"
#include "Pacote.h"
#include "Fisioterapeuta.h"
#include "Menu.h"

using namespace std;

gerenciador g;

int main (){
    Menu menu;
    menu.exibirMenuPrincipal();
    g.carregarDados();
    g.salvarDados();
}
