#include "fila.hpp"
#include <iostream>

// Zera os ponteiros de controle para evitar lixo de memória
void inicializarFilaAtendimento(FilaAtendimentoPrioritario* filaAtendimento) {
    filaAtendimento->primeiroDaFila = nullptr;
    filaAtendimento->ultimoDaFila = nullptr;
}

// Ciração de um novo nó isolado na memória 
NoFilaAtendimento* alocarNovoNoAtendimento(RequerimentoAcademico novoRequerimento) {
    NoFilaAtendimento* novoNo = new NoFilaAtendimento;
    novoNo->requerimentoArmazenado = novoRequerimento;
    novoNo->proximoNo = nullptr;
    novoNo->noAnterior = nullptr;
    return novoNo;
}

bool filaAtendimentoEstaVazia(FilaAtendimentoPrioritario* filaAtendimento) {
    return filaAtendimento->primeiroDaFila == nullptr;
}

// Adiciona o requerimento mantendo a fila ordenada decrescentemente pelo Nível de Prioridade
void inserirNaFilaPorPrioridade(FilaAtendimentoPrioritario* filaAtendimento, RequerimentoAcademico novoRequerimento) {
    NoFilaAtendimento* novoNoParaInserir = alocarNovoNoAtendimento(novoRequerimento);

    // Caso 1: A fila está vazia
    if (filaAtendimentoEstaVazia(filaAtendimento)) {
        filaAtendimento->primeiroDaFila = novoNoParaInserir;
        filaAtendimento->ultimoDaFila = novoNoParaInserir;
        return;
    }

    NoFilaAtendimento* noAtualEmAnalise = filaAtendimento->primeiroDaFila;
    
    // Análisa a fila até encontrar um nó que tenha prioridade MENOR que o novo requerimento
    while (noAtualEmAnalise != nullptr && noAtualEmAnalise->requerimentoArmazenado.nivelPrioridade >= novoRequerimento.nivelPrioridade) {
        noAtualEmAnalise = noAtualEmAnalise->proximoNo;
    }

    // Caso 2: Inserção no início da fila 
    if (noAtualEmAnalise == filaAtendimento->primeiroDaFila) { 
        novoNoParaInserir->proximoNo = filaAtendimento->primeiroDaFila;
        filaAtendimento->primeiroDaFila->noAnterior = novoNoParaInserir;
        filaAtendimento->primeiroDaFila = novoNoParaInserir;
    
    // Caso 3: Inserção no final da fila
    } else if (noAtualEmAnalise == nullptr) { 
        novoNoParaInserir->noAnterior = filaAtendimento->ultimoDaFila;
        filaAtendimento->ultimoDaFila->proximoNo = novoNoParaInserir;
        filaAtendimento->ultimoDaFila = novoNoParaInserir;
    
    // Caso 4: Inserção no meio da fila
    } else { 
        novoNoParaInserir->proximoNo = noAtualEmAnalise;
        novoNoParaInserir->noAnterior = noAtualEmAnalise->noAnterior;
        noAtualEmAnalise->noAnterior->proximoNo = novoNoParaInserir;
        noAtualEmAnalise->noAnterior = novoNoParaInserir;
    }
}

// Elimina o elemento do início, com maior prioridade, e refaz as conexões para o segundo se tornar o primeiro
RequerimentoAcademico removerFrenteFilaAtendimento(FilaAtendimentoPrioritario* filaAtendimento) {
    if (filaAtendimentoEstaVazia(filaAtendimento)) {
        RequerimentoAcademico requerimentoVazio;
        requerimentoVazio.numeroMatricula = -1; 
        return requerimentoVazio; 
    }

    NoFilaAtendimento* noSendoAtendido = filaAtendimento->primeiroDaFila;
    RequerimentoAcademico dadosDoRequerimento = noSendoAtendido->requerimentoArmazenado;

    filaAtendimento->primeiroDaFila = noSendoAtendido->proximoNo;
    
    if (filaAtendimento->primeiroDaFila != nullptr) {
        filaAtendimento->primeiroDaFila->noAnterior = nullptr;
    } else {
        filaAtendimento->ultimoDaFila = nullptr;
    }
    
    delete noSendoAtendido;
    return dadosDoRequerimento;
}

// Refere-se  a operação de "Desfazer", realiza uma busca em um nó específico no meio da fila e o remove
void removerRequerimentoEspecificoPorMatricula(FilaAtendimentoPrioritario* filaAtendimento, int matriculaAlvo) {
    NoFilaAtendimento* noAtualEmAnalise = filaAtendimento->primeiroDaFila;
    
    while(noAtualEmAnalise != nullptr) {
        if(noAtualEmAnalise->requerimentoArmazenado.numeroMatricula == matriculaAlvo) {
            
            // Caso específico : Se o alvo for o primeiro da fila
            if(noAtualEmAnalise == filaAtendimento->primeiroDaFila) {
                filaAtendimento->primeiroDaFila = noAtualEmAnalise->proximoNo;
                if(filaAtendimento->primeiroDaFila) {
                    filaAtendimento->primeiroDaFila->noAnterior = nullptr;
                } else {
                    filaAtendimento->ultimoDaFila = nullptr;
                }
            
            // Caso específico 2: Se o alvo for o último da fila
            } else if(noAtualEmAnalise == filaAtendimento->ultimoDaFila) {
                filaAtendimento->ultimoDaFila = noAtualEmAnalise->noAnterior;
                filaAtendimento->ultimoDaFila->proximoNo = nullptr;
            
            // Remoção no item do meio da fila: "pula" o nó atual, ligando seu anterior diretamente ao seu próximo
            } else {
                noAtualEmAnalise->noAnterior->proximoNo = noAtualEmAnalise->proximoNo;
                noAtualEmAnalise->proximoNo->noAnterior = noAtualEmAnalise->noAnterior;
            }
            
            delete noAtualEmAnalise;
            return;
        }
        noAtualEmAnalise = noAtualEmAnalise->proximoNo;
    }
}

// Limpa a fila, apagando todos os nós alocados dinamicamente no encerramento do sistema
void desalocarFilaAtendimento(FilaAtendimentoPrioritario* filaAtendimento) {
    NoFilaAtendimento* noAtualParaDeletar = filaAtendimento->primeiroDaFila;
    while (noAtualParaDeletar != nullptr) {
        NoFilaAtendimento* proximoNoSalvo = noAtualParaDeletar->proximoNo;
        delete noAtualParaDeletar;
        noAtualParaDeletar = proximoNoSalvo;
    }
    filaAtendimento->primeiroDaFila = nullptr;
    filaAtendimento->ultimoDaFila = nullptr;
}