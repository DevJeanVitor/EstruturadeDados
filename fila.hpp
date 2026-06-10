#ifndef FILA_HPP
#define FILA_HPP
#include "estruturas.hpp"

// Estrutura de controle da Fila
struct FilaAtendimentoPrioritario {
    NoFilaAtendimento* primeiroDaFila;
    NoFilaAtendimento* ultimoDaFila;
};

//Prototipação das funções
void inicializarFilaAtendimento(FilaAtendimentoPrioritario* filaAtendimento);
NoFilaAtendimento* alocarNovoNoAtendimento(RequerimentoAcademico novoRequerimento); 

void inserirNaFilaPorPrioridade(FilaAtendimentoPrioritario* filaAtendimento, RequerimentoAcademico novoRequerimento);
RequerimentoAcademico removerFrenteFilaAtendimento(FilaAtendimentoPrioritario* filaAtendimento);

bool filaAtendimentoEstaVazia(FilaAtendimentoPrioritario* filaAtendimento);
RequerimentoAcademico consultarFrenteFilaAtendimento(FilaAtendimentoPrioritario* filaAtendimento);

void removerRequerimentoEspecificoPorMatricula(FilaAtendimentoPrioritario* filaAtendimento, int matriculaAlvo);
void desalocarFilaAtendimento(FilaAtendimentoPrioritario* filaAtendimento);

#endif