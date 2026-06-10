#include <iostream>
#include "sistema.hpp"
#include "fila.hpp"
#include "pilha.hpp"
#include "buscas.hpp"

void inserirRequerimentoOrdenado(RequerimentoAcademico vetorFinalizados[], int& totalFinalizados, RequerimentoAcademico requerimentoAtendido) {
    int indiceAtual = totalFinalizados - 1;
    
    // Move os elementos que são maiores que a nova matrícula uma posição para a frente
    while (indiceAtual >= 0 && vetorFinalizados[indiceAtual].numeroMatricula > requerimentoAtendido.numeroMatricula) {
        vetorFinalizados[indiceAtual + 1] = vetorFinalizados[indiceAtual];
        indiceAtual--;
    }
    
    vetorFinalizados[indiceAtual + 1] = requerimentoAtendido;
    totalFinalizados++;
}

void executarSistemaRequerimentos() {
    FilaAtendimentoPrioritario filaDeAtendimento;
    PilhaHistoricoOperacoes historicoDeOperacoes;
    
    inicializarFilaAtendimento(&filaDeAtendimento);
    inicializarPilhaHistorico(&historicoDeOperacoes);

    // Vetor de armazenamento de processos concluídos
    RequerimentoAcademico vetorRequerimentosFinalizados[100]; 
    int totalRequerimentosFinalizados = 0;

    int opcaoMenuUsuario = -1;

    // Loop principal de eventos da interface com o usuário
    while (opcaoMenuUsuario != 0) {
        std::cout << "\n=== SISTEMA DE GERENCIAMENTO DE REQUERIMENTOS ===\n";
        std::cout << "[1] - Cadastrar Novo Requerimento\n";
        std::cout << "[2] - Atender Proximo da Fila\n";
        std::cout << "[3] - Buscar Processo Finalizado via Matricula\n";
        std::cout << "[4] - Desfazer Ultima Acao\n";
        std::cout << "[0] - Finalizar o Sistema\n";
        std::cout << "Opcao Escolhida: ";
        std::cin >> opcaoMenuUsuario;

        switch (opcaoMenuUsuario) {
            case 1: {
                RequerimentoAcademico novoRequerimento;
                std::cout << "Numero da Matricula: ";
                std::cin >> novoRequerimento.numeroMatricula;
                
                std::cout << "Tipo de Solicitacao [sem espacos]: ";
                char textoTemporario[50];
                std::cin >> textoTemporario;
                copiarTextoSeguro(novoRequerimento.descricaoSolicitacao, textoTemporario);
                
                std::cout << "Nivel de Prioridade [Peso numerico]: ";
                std::cin >> novoRequerimento.nivelPrioridade;

                //Insere na Fila
                inserirNaFilaPorPrioridade(&filaDeAtendimento, novoRequerimento);
                
                // Registra na Pilha para possibilitar a ação de "Desfazer"
                RegistroOperacao registroDeOperacao;
                registroDeOperacao.tipoDaOperacao = OPERACAO_INSERIR;
                registroDeOperacao.requerimentoEnvolvido = novoRequerimento;
                empilharRegistroOperacao(&historicoDeOperacoes, registroDeOperacao);
                
                std::cout << "Requerimento enfileirado com sucesso!\n";
                break;
            }
            case 2: {
                // Remove o primeiro elemento
                RequerimentoAcademico requerimentoAtendido = removerFrenteFilaAtendimento(&filaDeAtendimento);
                
                // Verifica o valor base de "-1", referente a estrutura vazia
                if (requerimentoAtendido.numeroMatricula != -1) {
                    // Armazena no histórico definitivo
                    inserirRequerimentoOrdenado(vetorRequerimentosFinalizados, totalRequerimentosFinalizados, requerimentoAtendido);
                    
                    // Salva a ação na Pilha de histórico
                    RegistroOperacao registroDeOperacao;
                    registroDeOperacao.tipoDaOperacao = OPERACAO_REMOVER;
                    registroDeOperacao.requerimentoEnvolvido = requerimentoAtendido;
                    empilharRegistroOperacao(&historicoDeOperacoes, registroDeOperacao);
                    
                    std::cout << "Requerimento da matricula [" << requerimentoAtendido.numeroMatricula << "] foi finalizado e arquivado.\n";
                } else {
                    std::cout << "Aviso: A fila de atendimento esta vazia!\n";
                }
                break;
            }
            case 3: {
                int matriculaBuscada;
                std::cout << "Digite a Matricula para iniciar as buscas: ";
                std::cin >> matriculaBuscada;
                
                int indiceEncontrado = buscarIndicePorBuscaBinaria(vetorRequerimentosFinalizados, totalRequerimentosFinalizados, matriculaBuscada);
                
                if (indiceEncontrado != -1) {
                    std::cout << "Processo Encontrado no Indice de Memoria: " << indiceEncontrado << ".\n";
                    std::cout << "Tipo da Solicitacao: " << vetorRequerimentosFinalizados[indiceEncontrado].descricaoSolicitacao << "\n";
                } else {
                    std::cout << "Erro: O Processo finalizado com a matricula digitada nao foi encontrada.\n";
                }
                break;
            }
            case 4: {
                // Ação de Reversão consumindo o topo da pilha
                RegistroOperacao ultimaOperacao = desempilharRegistroOperacao(&historicoDeOperacoes);
                
                if (ultimaOperacao.requerimentoEnvolvido.numeroMatricula != -1) {
                    // Logica de Inversão: Se a última ação foi INSERIR, o "desfazer" significa REMOVER a matrícula específica da fila
                    if (ultimaOperacao.tipoDaOperacao == OPERACAO_INSERIR) {
                        removerRequerimentoEspecificoPorMatricula(&filaDeAtendimento, ultimaOperacao.requerimentoEnvolvido.numeroMatricula);
                        std::cout << "Acao Desfeita: A insercao da Matricula [" << ultimaOperacao.requerimentoEnvolvido.numeroMatricula << "] foi cancelada.\n";
                    
                    // Logica de Inversão: Se a última ação foi REMOVER (atender), o "desfazer" significa DEVOLVÊ-LO à fila e tirá-lo dos finalizados
                    } else if (ultimaOperacao.tipoDaOperacao == OPERACAO_REMOVER) {
                        inserirNaFilaPorPrioridade(&filaDeAtendimento, ultimaOperacao.requerimentoEnvolvido);
                        totalRequerimentosFinalizados--; 
                        std::cout << "Acao Desfeita: O atendimento da Matricula [" << ultimaOperacao.requerimentoEnvolvido.numeroMatricula << "] foi revertido.\n";
                    }
                } else {
                    std::cout << "Historico vazio. Nao e possivel realizar acoes para desfazer.\n";
                }
                break;
            }
            case 0:
                std::cout << "Iniciando protocolo de encerramento, aguarde.\n";
                break;
            default:
                std::cout << "Opcao Invalida. Tente novamente.\n";
        }
    }
    desalocarFilaAtendimento(&filaDeAtendimento);
    desalocarPilhaHistorico(&historicoDeOperacoes);
}