### Descrição Geral

Este projeto envolve o desenvolvimento de um gerenciador de concursos da Mega-Sena, que utiliza uma tabela de dispersão (hash table) para armazenar e acessar os dados dos concursos. O sistema deve ser capaz de executar operações básicas como inserção, busca e remoção de dados referentes aos concursos. Além disso, o sistema é projetado para calcular e apresentar estatísticas relevantes sobre os números sorteados, fornecendo uma visão mais aprofundada dos resultados dos concursos.

### Objetivo

O principal objetivo deste projeto é criar um sistema eficiente para o gerenciamento de concursos da Mega-Sena, implementando as seguintes funcionalidades:

- **Armazenamento e Acesso de Dados**: Utilizar uma tabela de dispersão (hash table) para armazenar e acessar os resultados dos concursos de forma rápida e eficiente.
- **Operações Básicas**: Implementar as operações de inserção, busca e remoção de dados na tabela de dispersão.
- **Cálculo de Estatísticas**: Calcular e apresentar estatísticas relevantes sobre os números sorteados nos concursos, como frequências de números, padrões de sorteio, entre outros.
- **Linguagem de Implementação**: Desenvolver todo o sistema utilizando a linguagem C.

### Estrutura do Projeto

O projeto é organizado em três diretórios principais, além de um Makefile para compilar o sistema:

- **dataset/**: Este diretório contém arquivos de dados que podem ser carregados pelo usuário para popular o sistema com informações de concursos da Mega-Sena. Esses arquivos servem como entrada para o sistema.

- **include/**: Contém os arquivos de cabeçalho (`.h`) que definem as estruturas de dados e as funções utilizadas no projeto. Os principais arquivos `.h` são:
  - `concurso.h`: Define a estrutura de um concurso da Mega-Sena.
  - `data.h`: Contém uma estrutura básica para representar datas.
  - `funcionalidades.h`: Inclui as funções principais do menu e algumas funções auxiliares para manipulação do sistema.
  - `hashtable.h`: Define a estrutura e as funções para a tabela de dispersão (hash table) usada para armazenar os dados dos concursos.
  - `linkedlist.h`: Contém a definição da estrutura de lista ligada (linked list) e suas funções de manipulação.

- **src/**: Este diretório contém as implementações das funções e estruturas definidas nos arquivos de cabeçalho presentes na pasta `include/`. Cada arquivo `.c` corresponde a um dos arquivos `.h`, onde as funções são implementadas e comentadas para facilitar o entendimento e a manutenção.

Além disso, o projeto possui um **Makefile** que automatiza o processo de compilação. Para compilar o projeto, basta executar o comando `make`, que irá gerar o executável principal na pasta `bin/` com o nome `main`.

### Funcionalidades do Sistema

O sistema possui um conjunto de funcionalidades acessíveis por meio de menus interativos. As principais funcionalidades disponíveis são:

```c
printf("============================================\n");
printf("              MENU DE CONCURSOS            \n");
printf("============================================\n");
printf("1. Inserir Concurso\n");
printf("2. Buscar Concurso\n");
printf("3. Remover Concurso\n");
printf("4. Visualizar Todos os Concursos\n");
printf("5. Carregar arquivo\n");
printf("6. Mostrar Estatísticas\n");
printf("0. Sair\n");
printf("============================================\n");
printf("Digite a opção desejada: ");
```

*   **Inserir Concurso**: Permite adicionar um novo concurso ao sistema.
    
*   **Buscar Concurso**: Busca um concurso específico com base no número do concurso.
    
*   **Remover Concurso**: Remove um concurso do sistema utilizando seu número.
    
*   **Visualizar Todos os Concursos**: Exibe todos os concursos registrados no sistema.
    
*   **Carregar Arquivo**: Carrega os dados de concursos a partir de um arquivo `.csv` ou `.tsv`, gerando uma nova tabela hash.

    **Observação**: Ao carregar um novo arquivo, as estatísticas serão resetadas e uma nova tabela hash será criada. A tabela hash anterior será apagada da memória. A nova tabela hash terá o tamanho ajustado de acordo com o número de entradas no arquivo, visando minimizar colisões e otimizar a velocidade de busca.
    
*   **Mostrar Estatísticas**: Acessa um submenu para visualização de estatísticas sobre os concursos cadastrados. As opções disponíveis são:

    ```c
    printf("============================================\n");
    printf("            MENU DE ESTATÍSTICAS            \n");
    printf("============================================\n");
    printf("1. 10 números mais sorteados\n");
    printf("2. 10 números menos sorteados\n");
    printf("3. Quantidade de repetição de um número\n");
    printf("4. Sorteios realizados em determinado ano\n");
    printf("0. Sair\n");
    printf("============================================\n");
    printf("Digite a opção desejada: ");
    ```

    *   **10 números mais sorteados**: Mostra os 10 números que mais apareceram nos concursos.
    *   **10 números menos sorteados**: Exibe os 10 números que menos apareceram nos concursos.
    *   **Quantidade de repetição de um número**: Mostra quantas vezes um número específico foi sorteado.
    *   **Sorteios realizados em determinado ano**: Lista todos os sorteios que ocorreram em um ano específico.

### Estrutura de Dados: LinkedList

A estrutura de dados `LinkedList` é composta por elementos chamados `NodeList`, que encapsulam um `Concurso` e são organizados em uma lista encadeada. As operações principais oferecidas por essa estrutura incluem:

- **Adição de Elementos**: Há funções para adicionar nós tanto no início (`addNodeAtFirst`) quanto no final (`addNodeAtLast`) da lista, assim como em posições específicas da lista (`addNodeAfter`).

- **Remoção de Elementos**: A lista permite remover nós específicos, seja o primeiro (`removeAtFirst`), o último (`removeAtLast`), ou qualquer outro nó identificado (`removeNode`).

- **Acesso e Busca de Elementos**: Os nós podem ser acessados diretamente, e há uma função específica para buscar um nó com base no número do concurso (`searchById`).

- **Construção e Destruição**: Funções como `builderList` e `nodeListBuilder` permitem a criação de uma nova lista e de novos nós, respectivamente. Além disso, há funções para liberar a memória ocupada por um nó (`eraseNodeList`) e para apagar toda a lista (`clearLinkedList`).

As implementações dessas funções estão no arquivo `src/linkedlist.c`, que pode ser revisado por quem for utilizar.

### Estrutura de Dados: HashTable

A estrutura de dados `HashTable` foi desenvolvida para armazenar e acessar concursos da Mega-Sena de forma eficiente. Esta implementação utiliza uma lista encadeada (`LinkedList`) para lidar com colisões de índice, garantindo que múltiplos elementos possam ser armazenados na mesma posição da tabela.

- **Criação e Inicialização**: A função `hashBuilder` é responsável por criar uma nova tabela hash, enquanto a função `hash` gera o índice apropriado para armazenar um concurso com base em sua chave (`key`).

- **Adição de Elementos**: A função `addElement` permite inserir um novo concurso na tabela. Em caso de colisão de índices, o concurso é adicionado à lista encadeada (`LinkedList`) correspondente.

- **Busca de Elementos**: A função `search` permite localizar um concurso específico utilizando sua chave, navegando pela lista encadeada em caso de colisão.

- **Remoção de Elementos**: É possível remover um concurso da tabela hash utilizando a função `removeFromHash`, que localiza e remove o concurso associado à chave fornecida.

- **Destruição e Impressão**: Funções como `clearHashTable` e `printHashTable` permitem, respectivamente, liberar a memória ocupada pela tabela hash e exibir todos os concursos armazenados.

As implementações dessas funções estão no arquivo `src/hashtable.c`, que pode ser revisado por quem for utilizar.

### Exemplo de Uso

O projeto é compilado utilizando o `Makefile`, que gera o executável `main` na pasta `bin`. O programa pode ser inicializado com opções de linha de comando para personalizar o comportamento da tabela hash.

#### Compilação

Para compilar o projeto, execute o seguinte comando na raiz do projeto:

```bash
make
```

Isso irá gerar o executável `main` na pasta `bin`.

#### Inicialização do Programa

O programa pode ser iniciado com as seguintes opções de linha de comando:

- **Tamanho da HashTable**: Se desejar definir um tamanho específico para a tabela hash, use a flag `-s` seguida do tamanho desejado. O tamanho padrão da tabela é 50.

  ```bash
  ./bin/main -s <tamanho da hashTable>
  ```
- **Carregar Arquivo**: Para iniciar o programa com um arquivo já carregado em memória, utilize a flag -f seguida do caminho para o arquivo. O tamanho da tabela hash será ajustado automaticamente para o tamanho do arquivo, visando minimizar colisões e otimizar a busca.
- ```bash
  ./bin/main -f <diretorio/arquivo>
  ```

  #### Exemplos

- **Inicializar com tamanho de hash table personalizado**:

  ```bash
  ./bin/main -s 100
  ```

- **Inicializar e carregar um arquivo**:
  ```bash
  ./bin/main -f /data/concursos.csv
  ```

>Certifique-se de que o arquivo especificado esteja no formato correto (.csv ou .tsv) para que possa ser processado adequadamente.
