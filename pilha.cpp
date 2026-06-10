#include "pilha.hpp"

// Definição inicial do índice, -1 indica que não há possui nenhum elemento válido no array
void inicializarPilhaHistorico(PilhaHistoricoOperacoes* pilhaHistorico) {
    pilhaHistorico->capacidadeMaximaAtual = 10;
    pilhaHistorico->vetorRegistros = new RegistroOperacao[pilhaHistorico->capacidadeMaximaAtual];
    pilhaHistorico->indiceElementoTopo = -1; 
}

// Insere um novo registro de ação no topo da pilha
void empilharRegistroOperacao(PilhaHistoricoOperacoes* pilhaHistorico, RegistroOperacao novoRegistro) {
    // Verifica se o array atingiu seu limite físico. Caso sim, inicia-se a aplicação da técnica de dobrar o tamanho do array
    // Gerando um impactio de amortização no tempo de Big o, chegando em até O(1)
    if (pilhaHistorico->indiceElementoTopo == pilhaHistorico->capacidadeMaximaAtual - 1) {
        int novaCapacidadeMaxima = pilhaHistorico->capacidadeMaximaAtual * 2;
        RegistroOperacao* novoVetorRegistros = new RegistroOperacao[novaCapacidadeMaxima];
        
        // Cópia dos dados antigos para o array
        for (int i = 0; i <= pilhaHistorico->indiceElementoTopo; i++) {
            novoVetorRegistros[i] = pilhaHistorico->vetorRegistros[i];
        }
        
        // Deleta o antigo array
        delete[] pilhaHistorico->vetorRegistros;
        
        // Atualização dos ponteiros:
        pilhaHistorico->vetorRegistros = novoVetorRegistros;
        pilhaHistorico->capacidadeMaximaAtual = novaCapacidadeMaxima;
    }
    
    // Avança o índice e armazena o novo dado na nova posição de topo
    pilhaHistorico->indiceElementoTopo++;
    pilhaHistorico->vetorRegistros[pilhaHistorico->indiceElementoTopo] = novoRegistro;
}

// Remove e retorna o elemento que está no topo da pilha
RegistroOperacao desempilharRegistroOperacao(PilhaHistoricoOperacoes* pilhaHistorico) {
    if (pilhaHistoricoEstaVazia(pilhaHistorico)) {
        RegistroOperacao registroVazio;
        registroVazio.requerimentoEnvolvido.numeroMatricula = -1; 
        return registroVazio;
    }
    
    RegistroOperacao registroRemovido = pilhaHistorico->vetorRegistros[pilhaHistorico->indiceElementoTopo];
    pilhaHistorico->indiceElementoTopo--;
    return registroRemovido;
}

// Verificação booleana do estado da pilha com base no índice do topo
bool pilhaHistoricoEstaVazia(PilhaHistoricoOperacoes* pilhaHistorico) {
    return pilhaHistorico->indiceElementoTopo == -1;
}

// Limpeza de memória
void desalocarPilhaHistorico(PilhaHistoricoOperacoes* pilhaHistorico) {
    delete[] pilhaHistorico->vetorRegistros;
    pilhaHistorico->vetorRegistros = nullptr;
}