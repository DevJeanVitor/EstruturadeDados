#ifndef PILHA_HPP
#define PILHA_HPP
#include "estruturas.hpp"

// Estrutura da Pilha implementada via vetor dinâmico.
struct PilhaHistoricoOperacoes {
    RegistroOperacao* vetorRegistros; 
    int capacidadeMaximaAtual;        
    int indiceElementoTopo;           
};

// Prototipação das funções de manipulação da Pilha
void inicializarPilhaHistorico(PilhaHistoricoOperacoes* pilhaHistorico);
void empilharRegistroOperacao(PilhaHistoricoOperacoes* pilhaHistorico, RegistroOperacao novoRegistro);
RegistroOperacao desempilharRegistroOperacao(PilhaHistoricoOperacoes* pilhaHistorico);

bool pilhaHistoricoEstaVazia(PilhaHistoricoOperacoes* pilhaHistorico);
RegistroOperacao consultarTopoPilhaHistorico(PilhaHistoricoOperacoes* pilhaHistorico);

void desalocarPilhaHistorico(PilhaHistoricoOperacoes* pilhaHistorico);

#endif