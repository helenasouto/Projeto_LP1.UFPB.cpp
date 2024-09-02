# Projeto_LP1.UFPB.cpp
Sistema de Gerenciamento de Clínica de Fisioterapia
Este projeto é um sistema de gerenciamento desenvolvido em C++ para uma clínica de fisioterapia. O sistema implementa as operações básicas de um CRUD (Create, Read, Update, Delete) para gerenciar dados de pacientes, fisioterapeutas e horários.

O sistema oferece as seguintes funcionalidades:

Inserir: Permite cadastrar novos fisioterapeutas, pacientes e horários;

Listar Todos: Exibe todos os registros cadastrados no sistema;

Exibir Um: Pesquisa e exibe um registro específico pelo nome;

Alterar: Pesquisa e permite a alteração de um registro específico;

Remover: Pesquisa e remove um registro específico;

Exibir Relatório: Gera um relatório com resumo das informações cadastradas, como número de pacientes, fisioterapeutas, horários disponíveis, etc.

Sair: Encerra a aplicação, salvando todos os dados em arquivos para garantir a persistência.


Modelagem do Sistema

O sistema foi modelado utilizando um diagrama UML de classes, seguindo os seguintes requisitos:

Classes e Composição: O sistema possui classes principais com pelo menos quatro atributos;.

Herança: Foi utilizada herança com uma superclasse (Pessoa) e duas subclasses (Fisioterapeuta e Paciente). As classes Paciente e Fisioterapeuta herdam da classe base Pessoa. Isso é visível nos métodos que usam dynamic_cast para verificar se uma Pessoa é um Paciente ou um Fisioterapeuta.

Polimorfismo: O método atualizarDados nas classe Fisioterapeuta e Paciente sobrescreve um método da classe base Pessoa. E dynamic_cast é utilizado para verificar e tratar objetos de classes derivadas (Paciente, Fisioterapeuta) a partir de um ponteiro para a classe base (Pessoa), o que é um tipo de polimorfismo.

Métodos: O sistema foi projetado com foco em reutilização de métodos, incluindo um método de pesquisa que é utilizado em diversas operações.

Persistência de Dados

Todos os dados manipulados no sistema são armazenados em arquivos para garantir que as informações sejam persistentes entre as execuções. Ao iniciar o programa, os dados são carregados automaticamente, e ao finalizar, todos os registros são salvos em um arquivo.

Instruções de Uso

Clone o repositório: git clone https://github.com/helenasoutod/Projeto_LP1.UFPB.cpp.git

Compile o projeto: Use um compilador de C++ para compilar os arquivos do projeto.

Execute o programa: Após a compilação, execute o binário gerado para iniciar o sistema.

Navegue pelo menu: Utilize as opções do menu para inserir, listar, exibir, alterar, remover ou gerar relatórios.

Diagrama UML
O diagrama UML de classes utilizado no projeto está disponível no repositório. Ele fornece uma visão geral da estrutura do sistema e das relações entre as classes.

Apresentação
A apresentação do projeto será realizada durante a aula, com uma breve demonstração das funcionalidades do sistema.
