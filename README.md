  # Sistema de Gestão de Estacionamento

## 1. Identificação

- **Disciplina:** Lógica de Programação e Algoritmos
- **Semestre:** 2026/2
- **Trabalho:** Sistema de Gestão de Estacionamento
- **Linguagem:** C (padrão C11)
- **Integrante:** Rafael De Souza Porto
- **GitHub:** https://github.com/R0587358-lab
- **Arquivo principal:** `main.c`
- **Repositório GitHub:**https://github.com/R0587358-lab/sistema-gestao-estacionamento-4

## 2. Descrição do projeto

O projeto consiste em um sistema de gerenciamento de estacionamento executado pelo terminal. O estacionamento possui 4 fileiras e 5 colunas, totalizando 20 vagas.

O sistema permite cadastrar e consultar veículos, atualizar suas informações, movimentá-los entre as vagas, removê-los, listar os registros cadastrados, visualizar o mapa de ocupação e consultar um relatório com os dados do estacionamento.

As informações ficam armazenadas durante a execução do programa. Ao encerrar o sistema, a memória utilizada pelo vetor dinâmico de veículos é liberada.

## 3. Funcionalidades implementadas

- Cadastro de veículos com identificador, descrição, categoria, fileira e coluna.
- Validação do identificador, que deve possuir exatamente 7 caracteres alfanuméricos.
- Conversão de letras minúsculas para maiúsculas nos identificadores.
- Verificação de identificadores duplicados.
- Consulta de veículos pelo identificador.
- Atualização da descrição e/ou categoria de um veículo.
- Movimentação de veículos para vagas disponíveis.
- Remoção de veículos, com liberação da vaga correspondente.
- Listagem dos veículos cadastrados.
- Exibição do mapa de ocupação das 20 vagas.
- Relatório com quantidade de vagas ocupadas e livres, percentual de ocupação, carros e motos.
- Ampliação automática da capacidade do vetor dinâmico.
- Liberação da memória dinâmica ao encerrar o programa.

## 4. Organização dos dados e da solução

O programa utiliza duas estruturas principais para controlar o estacionamento.

**Matriz de vagas:** uma matriz de inteiros com 4 fileiras e 5 colunas. O valor `0` representa uma vaga livre e o valor `1` representa uma vaga ocupada.

**Struct `Veiculo`:** armazena os dados de cada veículo:
- Identificador;
- Descrição;
- Categoria;
- Fileira;
- Coluna.

**Struct `Estacionamento`:** reúne a matriz de vagas, o ponteiro para o vetor dinâmico de veículos, a quantidade de registros cadastrados e a capacidade reservada.

O vetor dinâmico começa com capacidade para 2 veículos. Quando essa capacidade é atingida e um novo cadastro é realizado, o espaço é ampliado utilizando `realloc`, dobrando a capacidade anterior. A memória é liberada com `free` no encerramento.

### 4.1 Organização das funções

A solução foi organizada em funções com responsabilidades diferentes:

- `lerLinha`, `converterInteiro` e `lerInteiro`: realizam a leitura e a conversão dos dados informados.
- `normalizarIdentificador`, `identificadorValido`, `descricaoValida`, `categoriaValida` e `posicaoValida`: realizam as validações das informações.
- `inicializarMapa`, `contarOcupadas` e `exibirMapa`: trabalham com a matriz de vagas.
- `inicializarEstacionamento`, `liberarEstacionamento` e `ampliarCapacidade`: cuidam da inicialização e do gerenciamento da memória dinâmica.
- `buscarVeiculo`, `inserirVeiculo`, `removerVeiculoPorIndice` e `moverVeiculoPara`: realizam operações sobre os registros e as vagas.
- `contarCategoria`: contabiliza os veículos de acordo com a categoria.
- `telaCadastrar`, `telaConsultar`, `telaAtualizar`, `telaMover`, `telaRemover`, `telaListar` e `telaRelatorio`: organizam as operações disponíveis ao usuário.
- `exibirMenu`: apresenta as opções do sistema.
- `main`: inicializa o estacionamento, controla o menu e realiza o encerramento do programa.

## 5. Compilação

O projeto utiliza o padrão C11 e pode ser compilado com o GCC.

Com o terminal aberto na pasta onde está o arquivo `main.c`, execute:

```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c -o estacionamento
```

## 6. Execução

Após a compilação, execute o programa com:

```bash
./estacionamento
```

O menu será apresentado no terminal. Basta informar o número correspondente à operação desejada. Para encerrar o sistema, escolha a opção `0`.

## 7. Testes realizados

Os testes abaixo foram realizados para verificar as operações principais e situações previstas no roteiro da atividade.

| Teste | Entrada ou operação | Resultado esperado | Resultado observado | Situação |
|---|---|---|---|---|
| T02 – Cadastro válido | Cadastrar um veículo com informações válidas. | Veículo cadastrado e vaga ocupada. | O veículo foi cadastrado corretamente na vaga informada. | Aprovado |
| T03 – Duplicidade sem distinção de caixa | Cadastrar `abc1d23` e depois tentar cadastrar `ABC1D23`. | O segundo cadastro deve ser recusado por duplicidade. | O segundo cadastro foi recusado porque o identificador já estava registrado. | Aprovado |
| T04 – Vaga ocupada | Tentar cadastrar outro veículo em uma vaga já ocupada. | O cadastro deve ser recusado sem alterar os dados existentes. | O cadastro foi recusado porque a vaga já estava ocupada. | Aprovado |
| T05 – Crescimento dinâmico | Cadastrar um terceiro veículo após os dois primeiros. | A capacidade do vetor deve passar de 2 para 4. | A capacidade do vetor aumentou de 2 para 4, preservando os registros. | Aprovado |
| T06 – Atualização | Alterar a descrição e/ou categoria de um veículo cadastrado. | Os dados do veículo devem ser atualizados. | As informações do veículo foram atualizadas corretamente. | Aprovado |
| T07 – Movimentação | Mover um veículo para uma vaga livre. | A vaga de origem deve ficar livre e a de destino ocupada. | O veículo foi movimentado e as posições foram atualizadas. | Aprovado |
| T08 – Remoção | Remover um veículo cadastrado. | O registro deve ser removido e sua vaga liberada. | O veículo foi removido e a vaga correspondente foi liberada. | Aprovado |
| T09 – Lotação | Cadastrar 20 veículos e tentar cadastrar o 21º. | O novo cadastro deve ser recusado porque o estacionamento está lotado. | Os 20 veículos foram cadastrados e a tentativa de inclusão do 21º foi recusada. | Aprovado |
| T10 – Encerramento | Encerrar o programa utilizando a opção `0`. | A memória dinâmica deve ser liberada. | O programa exibiu a mensagem de memória liberada ao encerrar. | Aprovado |

Além desses testes, foram realizadas verificações de identificador inválido e de atualização, movimentação e remoção de veículos.

O programa também foi compilado utilizando o comando apresentado neste documento, sem erros ou avisos do compilador na verificação realizada.


## 8. Desenvolvimento e responsabilidades

O trabalho foi desenvolvido individualmente, embora o roteiro da atividade previsse a realização em duplas.

Antes de iniciar o desenvolvimento, procurei alguns colegas da turma para saber se alguém ainda estava sem dupla e tinha disponibilidade para realizar o trabalho comigo. Entretanto, as pessoas com quem conversei já haviam formado suas duplas. Mesmo perguntando a diferentes colegas, não consegui encontrar alguém disponível dentro do tempo que eu tinha para desenvolver a atividade.

Diante dessa situação, para não deixar de realizar e entregar o trabalho, optei por desenvolvê-lo individualmente. Fiquei responsável por todas as etapas do projeto, incluindo a organização e implementação do código, a criação das estruturas de dados, o desenvolvimento das funções, as validações e a realização dos testes.

O desenvolvimento foi concentrado no arquivo `main.c`, que reúne as funções e o programa principal. Por ter sido realizado individualmente, não houve divisão de tarefas entre integrantes nem integração de branches com outro participante.

## 9. Uso de Inteligência Artificial

Utilizei o ChatGPT (OpenAI) como ferramenta de apoio durante o desenvolvimento do trabalho.

A ferramenta foi utilizada para esclarecer dúvidas sobre a linguagem C, compreender o funcionamento de estruturas, ponteiros e alocação dinâmica, analisar mensagens de erro e auxiliar na revisão e verificação do programa.

Entre as solicitações realizadas, estão:

- Explicações sobre o uso de `struct`, matrizes, vetores e ponteiros em C.
- Dúvidas sobre alocação e liberação de memória com `malloc`, `realloc` e `free`.
- Ajuda para compreender erros e verificar a compilação do programa.
- Orientações para conferir o funcionamento do cadastro, da movimentação e da remoção de veículos.

As respostas foram utilizadas como apoio para estudo e revisão. As orientações foram analisadas durante o desenvolvimento e aplicadas de acordo com a necessidade do programa.

## 10. Fontes consultadas

- Roteiro de desenvolvimento, colaboração e entrega do trabalho **Sistema de Gestão de Estacionamento**, da disciplina Lógica de Programação e Algoritmos, semestre 2026/2.
- ChatGPT (OpenAI), utilizado como ferramenta de apoio para esclarecimento de dúvidas e revisão durante o desenvolvimento.

## 11. Considerações finais

O desenvolvimento deste projeto permitiu aplicar conceitos da linguagem C, como estruturas, matrizes, vetores dinâmicos, ponteiros, funções e validação de dados.

Durante a implementação, foi necessário organizar as operações do sistema e manter a consistência entre os registros dos veículos e o mapa de vagas. Os testes realizados permitiram verificar o funcionamento das principais funcionalidades, incluindo o crescimento do vetor dinâmico, a movimentação e remoção de veículos, a identificação de cadastros duplicados e o limite de ocupação do estacionamento.

