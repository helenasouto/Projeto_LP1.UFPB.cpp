#ifndef PACOTE_H
#define PACOTE_H

class Pacote
{

public:

    Pacote(int quantidadeAulas, double valorPorPacote);

    int getQuantidadeAulas() const;
    double getValorPorPacote() const;

private:
    int quantidadeAulas;
    double valorPorPacote;

};

#endif
