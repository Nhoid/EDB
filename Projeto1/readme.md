# Sistema de Gerenciamento de Pedidos para Restaurante


### Descrição Geral do Projeto
O objetivo deste projeto é implementar um sistema de gerenciamento de pedidos de restaurante utilizando a linguagem C. O sistema permite que os pedidos sejam armazenados em uma lista ligada, proporcionando a flexibilidade necessária para adicionar e remover pratos específicos de forma dinâmica. Além disso, para garantir que os pedidos sejam processados de maneira justa e eficiente, uma fila é utilizada para gerenciar a ordem de chegada dos pedidos, permitindo que a cozinha processe os pratos na sequência correta.

### Contexto
Este projeto é relevante dentro da disciplina de Estrutura Básica de Dados porque envolve a aplicação prática de estruturas de dados fundamentais, como listas ligadas e filas. A lista ligada é ideal para o gerenciamento dinâmico de pedidos, permitindo inserções e remoções eficientes, enquanto a fila garante que os pedidos sejam processados na ordem correta, refletindo a operação real de um restaurante. Implementar essas estruturas em C ajuda a consolidar o entendimento sobre alocação dinâmica de memória e manipulação de ponteiros, conceitos cruciais para a programação em baixo nível.

### Estrutura do Projeto

O projeto está organizado em várias pastas e arquivos, cada um com um papel específico na implementação do sistema de gerenciamento de pedidos para restaurante. Abaixo está a descrição da estrutura do projeto:

#### Diretórios Principais

- **`include/`**: Contém os arquivos de cabeçalho `.h`, que definem as estruturas de dados e as funções utilizadas em todo o projeto.
- **`src/`**: Contém as implementações de todas as funções declaradas nos arquivos `.h`, distribuídas em seus respectivos arquivos `.c`. O código está comentado o máximo possível para facilitar o entendimento e a manutenção.
- **`bin/`**: Após a compilação, esta pasta conterá o executável do programa.
- **`Makefile`**: Script que automatiza o processo de compilação do projeto.

#### Descrição dos Arquivos em `include/`

- **`cardapio.h`**: Define uma estrutura que encapsula uma linked list para armazenar o cardápio do restaurante. Este arquivo lida com a estrutura de dados específica que organiza os pratos disponíveis.

- **`funcionalidades.h`**: Contém as funções principais do menu do sistema, além de algumas funções auxiliares que suportam as operações principais. Estas funções facilitam a interação do usuário com o sistema.

- **`linkedlist.h`**: Declara a estrutura de dados da lista ligada e as funções associadas para manipulação da lista. Este arquivo é fundamental para o gerenciamento dinâmico dos pedidos, permitindo a adição e remoção de itens de maneira eficiente.

- **`queue.h`**: Semelhante ao `linkedlist.h`, este arquivo declara a estrutura de dados da fila e as funções para sua manipulação. A fila é utilizada para garantir que os pedidos sejam processados na ordem em que chegam ao sistema.

- **`structstring.h`**: Define uma estrutura básica de string (`text*` e `length`) e algumas funções personalizadas para manipulação de strings. Esta estrutura é utilizada para facilitar o tratamento de textos dentro do sistema, como nomes de pratos e outras informações textuais.

### Funcionalidades

O sistema oferece as seguintes funcionalidades, disponíveis no menu principal:

```c
printf("+----------------------------------+\n");
printf("|          MENU PRINCIPAL           |\n");
printf("+----------------------------------+\n");
printf("| 1. Adicionar Pedido               |\n");
printf("| 2. Remover Pedido                 |\n");
printf("| 3. Processar Pedido               |\n");
printf("| 4. Esperar pedido                 |\n");
printf("| 5. Listar Pedidos Pendentes       |\n");
printf("| 6. Listar Pedidos em Processamento|\n");
printf("| 0. Sair                           |\n");
printf("+----------------------------------+\n");
```
- **`Adicionar Pedido`**: Adiciona um novo pedido à lista ligada.
- **`Remover Pedido`**: Remove um prato específico de um pedido.
- **`Processar Pedido`**: Move o prato mais antigo da linked list para a fila de preparação da cozinha.
- **`Esperar Pedido`**: "Prepara" o prato mais antigo da fila da cozinha e o remove.
- **`Listar pedidos pendentes`**: Lista todos os pedidos que ainda estão na lista ligada.
- **`Listar pedidos em Processamento`**: Lista os pedidos que já estão na fila de preparação.
- **`Sair`**: Encerra o programa.

### LinkedList

A implementação de `LinkedList` no projeto fornece uma estrutura de dados fundamental para o gerenciamento de pedidos. A lista ligada permite a adição, remoção e busca de elementos de forma eficiente.

#### Estruturas de Dados

- **`NodeList`**: Representa um elemento da lista, contendo um dado do tipo `string` e ponteiros para o próximo e o anterior nó na lista.
- **`LinkedList`**: Contém ponteiros para os nós sentinela de cabeça e cauda (`header` e `tail`), além de um inteiro que armazena o tamanho da lista.

#### Operações Disponíveis

- **Adição**:
  - Adicionar um nó em uma posição específica (`addNodeAfter`).
  - Adicionar um nó no início (`addNodeAtFirst`).
  - Adicionar um nó no final (`addNodeAtLast`).

- **Remoção**:
  - Remover um nó específico (`removeNode`).
  - Remover o primeiro nó da lista (`removeAtFirst`).
  - Remover o último nó da lista (`removeAtLast`).

- **Busca**:
  - Procurar um nó pelo conteúdo (`searchByData`).
  - Procurar um nó pelo índice (`searchByIndex`).

- **Outras Operações**:
  - Obter o primeiro (`getFirst`) e o último (`getLast`) nó da lista.
  - Verificar se a lista está vazia (`isListEmpty`).
  - Limpar toda a lista (`clearLinkedList`).
  - Imprimir a lista (`printList`).

A implementação detalhada dessas funções pode ser encontrada no arquivo `src/linkedlist.c`. Os usuários do projeto são encorajados a revisar esse arquivo para entender a lógica e o funcionamento das operações da lista ligada.

### Queue

A implementação de `Queue` no projeto fornece uma estrutura de dados essencial para o processamento de pedidos em ordem de chegada. A fila permite a adição e remoção de elementos de forma eficiente.

#### Estruturas de Dados

- **`NodeQueue`**: Representa um elemento da fila, contendo um dado do tipo `string` e um ponteiro para o próximo nó na fila.
- **`Queue`**: Contém ponteiros para o primeiro (`first`) e o último (`last`) nós da fila, além de um inteiro que armazena o tamanho da fila.

#### Operações Disponíveis

- **Adição**:
  - Adicionar um elemento no fim da fila (`enqueue`).

- **Remoção**:
  - Remover e retornar o primeiro elemento da fila (`dequeue`).

- **Consulta**:
  - Obter o tamanho da fila (`size`).
  - Verificar se a fila está vazia (`isQueueEmpty`).
  - Obter o primeiro elemento sem removê-lo (`front`).

- **Outras Operações**:
  - Imprimir todos os elementos da fila (`printQueue`).
  - Liberar a memória da fila por completo (`deleteQueue`).

A implementação detalhada dessas funções pode ser encontrada no arquivo `src/queue.c`. Os usuários do projeto são encorajados a revisar esse arquivo para entender a lógica e o funcionamento das operações da fila.

> **Observação**: Tanto a `LinkedList` quanto a `Queue` utilizam estruturas semelhantes para encapsular os dados (`NodeList` e `NodeQueue`, respectivamente). Ambas as estruturas possuem funções para criar um novo nó e adicionar esse nó à estrutura correspondente.
>

### Exemplo de Uso

Para utilizar o sistema de gerenciamento de pedidos do restaurante, siga estas etapas:


### **Compilação do Projeto**:
   - Navegue até o diretório onde está localizado o `Makefile`.
   - Execute o comando `make` no terminal. Isso compilará o projeto e gerará o arquivo executável chamado `main` no diretório `src`.

   ```bash
   cd path/to/project/directory
   make
  ```
