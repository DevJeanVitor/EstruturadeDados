#include "buscas.hpp"

// Implementação do algoritmo  de Busca Binária
int buscarIndicePorBuscaBinaria(RequerimentoAcademico vetorRequerimentosOrdenados[], int totalRequerimentos, int numeroMatriculaAlvo) {
    int limiteInferiorBusca = 0;
    int limiteSuperiorBusca = totalRequerimentos - 1;

    while (limiteInferiorBusca <= limiteSuperiorBusca) {
        
        // A matemática do ponto médio definido dessa forma, previne o erro  de estouro de inteiro que poderia acontecer com a fórmula básica: (inferior + superior) / 2 
        int indicePontoMedio = limiteInferiorBusca + (limiteSuperiorBusca - limiteInferiorBusca) / 2;

        if (vetorRequerimentosOrdenados[indicePontoMedio].numeroMatricula == numeroMatriculaAlvo) {
            return indicePontoMedio; 
        }
        
        if (vetorRequerimentosOrdenados[indicePontoMedio].numeroMatricula < numeroMatriculaAlvo) {
            limiteInferiorBusca = indicePontoMedio + 1;
        } else {
            limiteSuperiorBusca = indicePontoMedio - 1;
        }
    }
        return -1; 
}