# Gerenciador de Memória Personalizado

- [Eduardo Colla De Bastiani | 23106295](https://github.com/eduardo-de-bastiani)
- [Andrei Rech | 23102140](https://github.com/AndreiRech)  
- [Mariah Backes Freire | 23102560](https://github.com/mariahbf)

Este projeto implementa um gerenciador de memória personalizado em C, permitindo a alocação, liberação e gerenciamento de blocos de memória dentro de um pool pré-alocado.No momento, o gerenciador suporta apenas uma estratégia de alocação, sendo o Primeiro Ajuste (First Fit).

## Funcionalidades

- **Inicialização do Pool de Memória**: Cria um pool de memória de tamanho especificado.
- **Alocação de Memória**: Tenta alocar um bloco de memória de tamanho especificado dentro do pool.
- **Liberação de Memória**: Libera um bloco de memória previamente alocado.
- **Exibição de Alocações**: Exibe todas as alocações atuais no pool de memória.
- **Estatísticas de Memória**: Fornece estatísticas gerais sobre a memória, incluindo o número total de alocações, memória total alocada, memória total livre, maior bloco contíguo livre e número de fragmentos de memória livre.
- **Limpeza de Memória**: Libera todos os recursos alocados, incluindo o pool de memória.

## Estruturas de Dados

- `allocation_t`: Representa um bloco de memória alocado.
  - `start`: Ponteiro para o início do bloco alocado.
  - `size`: Tamanho da alocação.
  - `next`: Ponteiro para a próxima alocação (para formar uma lista encadeada).

- `mymemory_t`: Representa o pool total de memória e todas as alocações atuais.
  - `pool`: Ponteiro para o início do bloco de memória total.
  - `total_size`: Tamanho total do bloco de memória.
  - `head`: Ponteiro para a primeira alocação (cabeça da lista encadeada).

## Compilação e Execução

### Pré-requisitos

- GCC (GNU Compiler Collection)

### Compilação

Para compilar o projeto, execute o seguinte comando no terminal:

```sh
gcc -o exec mymemory.c main.c