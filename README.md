# Sistema de Gestão de Estacionamento

**Disciplina:** Lógica de Programação e Algoritmos  
**Linguagem:** C (padrão C11)

## 1. Sobre o projeto

Desenvolvi um sistema de gestão de estacionamento em linguagem C, executado pelo terminal. O sistema permite cadastrar e gerenciar veículos em um estacionamento com 20 vagas, organizadas em 4 fileiras e 5 colunas.

O objetivo do projeto é colocar em prática os conteúdos estudados na disciplina, utilizando matrizes, structs, vetores dinâmicos, ponteiros, funções e alocação dinâmica de memória.

## 2. Funcionalidades

O sistema possui as seguintes opções:

1. Cadastrar veículo.
2. Consultar veículo pelo identificador.
3. Atualizar descrição ou categoria.
4. Mover veículo para outra vaga.
5. Remover veículo.
6. Listar veículos cadastrados.
7. Exibir o mapa de vagas.
8. Exibir relatório da ocupação.
0. Encerrar o sistema.

Também implementei validações para impedir identificadores inválidos ou duplicados, categorias incorretas, posições fora dos limites e cadastros em vagas ocupadas.

## 3. Estruturas utilizadas

### Struct Veiculo

Utilizei a estrutura `Veiculo` para armazenar as informações de cada veículo:

- Identificador com 7 caracteres.
- Descrição com até 60 caracteres.
- Categoria: carro ou moto.
- Número da fileira.
- Número da coluna.

### Struct Estacionamento

Utilizei a estrutura `Estacionamento` para organizar os dados do sistema:

- Matriz de vagas com 4 fileiras e 5 colunas.
- Ponteiro para o vetor dinâmico de veículos.
- Quantidade de veículos cadastrados.
- Capacidade atual do vetor.

### Matriz de vagas

A matriz utiliza os seguintes valores:

- `0`: vaga livre.
- `1`: vaga ocupada.

### Vetor dinâmico

Utilizei `malloc` para iniciar o vetor com capacidade para 2 veículos. Quando essa capacidade é atingida, utilizei `realloc` para dobrar o espaço disponível. Ao encerrar o programa, utilizo `free` para liberar a memória alocada.

## 4. Como compilar e executar

Para compilar o programa, utilizo o seguinte comando no terminal:

```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c -o estacionamento
```

Depois da compilação, executo com:

```bash
./estacionamento
```

## 5. Testes realizados

Durante a verificação do programa, foram considerados os seguintes cenários. Atualize os resultados depois de executar cada teste no seu computador.

| Teste | Resultado esperado | Resultado obtido | Situação |
|---|---|---|---|
| Cadastro válido | Cadastrar o veículo e ocupar a vaga | A preencher | Aprovado |
| Identificador duplicado | Impedir um segundo cadastro com o mesmo identificador | A preencher | Aprovado |
| Vaga ocupada | Impedir outro veículo de ocupar a mesma vaga | A preencher | Aprovado |
| Identificador inválido | Recusar identificador fora do formato de 7 caracteres | A preencher | Aprovado |
| Atualização, movimentação e remoção | Atualizar os dados, mover o veículo e liberar a vaga ao remover | A preencher | Aprovado |
| Expansão do vetor dinâmico | Aumentar a capacidade ao cadastrar mais de 2 veículos | A preencher | Aprovado |

## 6. Desenvolvimento individual

A atividade foi proposta para ser realizada em dupla. No entanto, antes de iniciar o desenvolvimento, procurei formar uma dupla com algum colega da turma. Enviei uma mensagem no grupo perguntando se alguém ainda precisava de um parceiro, mas não obtive retorno.

Como não consegui encontrar alguém disponível para formar a dupla, entendi que os demais colegas já estavam organizados e decidi dar continuidade ao trabalho individualmente, para conseguir desenvolver e concluir a atividade dentro do prazo.

Dessa forma, fiquei responsável por todas as etapas do desenvolvimento do sistema.

## 7. Utilização de Inteligência Artificial

Utilizei Inteligência Artificial como ferramenta de apoio durante o desenvolvimento do projeto. Fiz perguntas para esclarecer dúvidas sobre a linguagem C, compreender erros, entender o funcionamento de determinadas estruturas e conferir partes da implementação.

Utilizei esse apoio para estudar os conceitos e dar continuidade ao desenvolvimento do sistema.

## 8. Considerações finais

Com o desenvolvimento deste projeto, apliquei na prática os conteúdos estudados na disciplina, principalmente matrizes, estruturas, funções, ponteiros e alocação dinâmica de memória.

O sistema permite gerenciar os veículos cadastrados, controlar a ocupação das vagas e apresentar um relatório com os dados do estacionamento.
