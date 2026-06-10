#ifndef SISTEMA_HPP
#define SISTEMA_HPP

#include "estruturas.hpp"

// Adiciona um requerimento mantendo a ordenação através da matrícula
void inserirRequerimentoOrdenado(RequerimentoAcademico vetorFinalizados[], int& totalFinalizados, RequerimentoAcademico requerimentoAtendido);

//Prototipação da função "executarSistemaRequerimentos"
void executarSistemaRequerimentos();

#endif