#ifndef ESTRUTURAS_HPP
#define ESTRUTURAS_HPP

/*Função utilitária para copiar textos com segurança de limite de buffer, evitando o  overflow
Inline: Representa um comando para o compilador chamar o conjunto de código diretamente no local que a função "copiarTextoSeguro" é chamada, evitando assim a sobrecarga das chamadas da função
*/

inline void copiarTextoSeguro(char* textoDestino, const char* textoOrigem) {
    int indiceCaracter = 0;
    while(textoOrigem[indiceCaracter] != '\0' && indiceCaracter < 49) {
        textoDestino[indiceCaracter] = textoOrigem[indiceCaracter];
        indiceCaracter++;
    }
    textoDestino[indiceCaracter] = '\0';
}

// A base que carrega os dados de Requerimento do sistema
struct RequerimentoAcademico {
    int numeroMatricula;
    char descricaoSolicitacao[50];
    int nivelPrioridade; // Nível de Prioridade
};

// Representa um nó de uma lista duplamente encadeada, com os ponteiros anterior e próximo permitem uma navegação bidirecional
struct NoFilaAtendimento {
    RequerimentoAcademico requerimentoArmazenado;
    NoFilaAtendimento* proximoNo;
    NoFilaAtendimento* noAnterior;
};

// Enumeração para definir o tipo de evento que ocorreu
enum TipoOperacaoSistema {
    OPERACAO_INSERIR,
    OPERACAO_REMOVER
};

// Representa o histórico da Pilha
struct RegistroOperacao {
    TipoOperacaoSistema tipoDaOperacao;
    RequerimentoAcademico requerimentoEnvolvido;
};
#endif