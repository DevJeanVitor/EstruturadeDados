# Sistema de Gerenciamento de Requerimentos do meio Acadêmicos

## Contexto e Descrição do Projeto

O código apresenta um sistema de gerenciamento em C++ focado no processamento de requerimentos do meio acadêmico. O programa simula o fluxo de atendimento genérico de atendimento, onde solicitações são cadastradas com uma breve descrição sobre o motivo da solicitação, como devolução de livros, emissão da segunda via do diploma, solicitação de matricula dentre outros, após o cadastros, são enfileiradas de acordo com seu nível de prioridade, processadas e arquivadas. Além do fluxo padrão, o sistema oferece um recurso de histórico de operações que permite desfazer as últimas ações realizadas.
A aplicação funciona via interface de linha de comando (CLI) e é fortemente baseada em estruturas de dados clássicas implementadas do zero (sem uso da Standard Template Library - STL para as estruturas base).

## Estruturas de Dados Utilizadas e Suas Aplicações

O sistema faz uso de múltiplas estruturas de dados, cada uma escolhida para resolver um problema específico do domínio:

* **Lista Duplamente Encadeada (Fila de Prioridade):**
* **Onde é utilizada:** Nos arquivos `fila.hpp` e `fila.cpp`.
* **Propósito:** Gerenciar os requerimentos pendentes. A estrutura de nós interligados bidirecionalmente (`NoFilaAtendimento`) permite a inserção ordenada baseada no nível de prioridade do requerimento. Como a fila prioriza valores maiores, a varredura e a inserção no meio da lista ocorrem de forma eficiente, enquanto o atendimento (remoção) acontece sempre no início da fila.

* **Pilha Baseada em Vetor Dinâmico (Histórico):**
* **Onde é utilizada:** Nos arquivos `pilha.hpp` e `pilha.cpp`.
* **Propósito:** Viabilizar a funcionalidade de "Desfazer Última Ação" (Undo). Cada inserção ou remoção na fila principal gera um `RegistroOperacao` que é empilhado. Ao solicitar o desfazimento, o sistema consome o topo da pilha e aplica a lógica inversa.

* **Vetor Ordenado (Arquivamento):**
* **Onde é utilizado:** Declarado no loop principal em `sistema.cpp`.
* **Propósito:** Armazenar os requerimentos já atendidos. A inserção neste vetor ocorre de forma ordenada (via *Insertion Sort* adaptado) utilizando o número de matrícula como chave. Isso prepara os dados para consultas futuras otimizadas.

## Destaques Técnicos

### Técnica de Dobra de Array (Amortização)

No arquivo `pilha.cpp`, o controle do histórico foi implementado utilizando um vetor dinâmico que não possui um limite fixo. Quando a capacidade máxima atual é atingida, o sistema emprega a técnica de dobra de array:

> 1. Um novo array com o dobro da capacidade do atual é alocado na memória.
> 2. Os elementos existentes são copiados linearmente para a nova estrutura.
> 3. O espaço de memória do array antigo é liberado para evitar vazamentos (*memory leaks*). 

Esta abordagem é fundamental porque, embora a realocação tenha um custo de tempo linear, ela ocorre com uma frequência cada vez menor. Isso resulta em um custo de inserção amortizado de $O(1)$, unindo a velocidade de acesso de um array contíguo com a flexibilidade de tamanho de uma estrutura puramente dinâmica.

### Cálculo Seguro do Ponto Médio na Busca Binária

Para localizar processos finalizados de forma ágil, o sistema utiliza o algoritmo de Busca Binária (`buscas.cpp`). A implementação destaca-se pela fórmula escolhida para encontrar o meio do vetor:

`int indicePontoMedio = limiteInferiorBusca + (limiteSuperiorBusca - limiteInferiorBusca) / 2;`

**Pontos Fortes desta Abordagem:**

* **Prevenção de *Integer Overflow*:** Em vetores extremamente grandes, a fórmula matemática tradicional (utilizada comumente em literaturas acadêmicas iniciais), representada por $\frac{inferior + superior}{2}$, pode resultar em um valor que ultrapassa o limite de armazenamento do tipo `int` no momento da soma, causando comportamentos indefinidos no programa.
* **Estabilidade:** A subtração prévia garante que a distância entre os limites seja dividida primeiro, e apenas depois somada à base, garantindo segurança estrita nos limites da memória.

## Estruturação do Projeto (Arquitetura Modular)

O projeto adota uma separação de responsabilidades dividida entre arquivos de cabeçalho (`.hpp`) e arquivos de implementação (`.cpp`), o que previne redefinições e acelera a compilação:

* **Arquivos `.hpp` (Headers):** Atuam como contratos e definições do sistema. Eles contêm a prototipação das funções, as definições de `structs`, os `enums` (como o `TipoOperacaoSistema`) e as diretivas de pré-processador (`#ifndef`, `#define`) que protegem contra inclusões múltiplas.
* **Arquivos `.cpp` (Sources):** Carregam a lógica real do comportamento das estruturas e do fluxo de telas. Onde a complexidade algorítmica e a alocação de memória de fato ocorrem.

## Diagrama da Estrutura do Projeto

Abaixo, apresenta-se a topologia dos arquivos e suas interdependências no código:

```text
+=================================================+
|            DIRETÓRIO DO PROJETO                 |
+=================================================+
      |
      +---> [estruturas.hpp] 
      |      (Structs Base e Inline de segurança)
      |
      +---> [fila.hpp] <--------> [fila.cpp]
      |      |-- FilaAtendimentoPrioritario
      |      +-- Requer dependência de estruturas
      |
      +---> [pilha.hpp] <-------> [pilha.cpp]
      |      |-- PilhaHistoricoOperacoes
      |      +-- Requer dependência de estruturas
      |
      +---> [buscas.hpp] <------> [buscas.cpp]
      |      |-- Algoritmo de Busca Binária
      |      +-- Requer dependência de estruturas
      |
      +---> [sistema.hpp] <-----> [sistema.cpp]
      |      |-- Loop Principal e Lógica de Negócio
      |      +-- Integra fila, pilha e buscas
      |
      +---> [main.cpp]
             |-- Ponto de Entrada da Aplicação
             +-- Executa o sistema central

```

## Comandos para Execução

Para compilar e executar o sistema, é necessário ter o compilador GCC (g++) instalado no ambiente. Utilize os seguintes comandos no terminal, no diretório raiz do projeto:

**1. Processo de Compilação Conjunta:**

```bash
g++ buscas.cpp fila.cpp pilha.cpp sistema.cpp main.cpp -o sistema_requerimentos

```

**2. Inicialização do Programa (Sistemas Unix/Linux):**

```bash
./sistema_requerimentos

```

**2. Inicialização do Programa (Sistemas Windows):**

```cmd
sistema_requerimentos.exe

```

---

**Desenvolvido por:** Jean Vítor
