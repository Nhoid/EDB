## Documentação do Projeto EDB

### Introdução

Nesta documentação, serão apresentados dois projetos desenvolvidos na disciplina de Estrutura Básica de Dados (EDB). Ambos os projetos foram implementados em linguagem C, utilizando conceitos fundamentais de estruturas de dados, como listas ligadas, filas e tabelas de dispersão. Abaixo, são descritas as funcionalidades e a estrutura de cada projeto, bem como as instruções para compilação e execução. Cada pasta do projeto contém um README próprio que fornece uma explicação mais detalhada sobre a implementação e as funcionalidades específicas.

### Estrutura do Repositório

Ambos os projetos possuem a mesma estrutura de diretórios:
```bash
ProjetoX/
│
├── include/ # Contém os arquivos .h
│ ├── arquivo1.h
│ └── arquivo2.h
│
├── src/ # Contém os arquivos .c
│ ├── arquivo1.c
│ └── arquivo2.c
│
├── Makefile # Script para compilar o projeto
│
└── bin/ # Contém o executável gerado após a compilação
└── programa_executavel
```


### Projeto 1: Sistema de Gerenciamento de Pedidos para Restaurante

#### Descrição

O primeiro projeto consiste em desenvolver um sistema para gerenciar os pedidos de um restaurante. Os pedidos são armazenados em uma lista ligada e processados pela cozinha em ordem de chegada utilizando uma fila. A implementação foi feita na linguagem C.

#### Funcionalidades

- **Gerenciamento de Pedidos**: Os pedidos são adicionados em uma lista ligada.
- **Processamento de Pedidos**: Os pedidos são processados pela cozinha em ordem de chegada utilizando uma fila.
- **Consulta de Pedidos**: Existe uma função que mostra os pedidos que estão em processamento ou os que estão sendo feitos no momento.

#### Compilação e Execução

Para compilar o projeto, utilize o comando:

```bash
make
```

#### O executável será gerado na pasta bin e pode ser executado com:
```bash
./bin/main
```

### Projeto 2: Gerenciador de Concursos da Mega-Sena

#### Descrição

O segundo projeto envolve a criação de um gerenciador de concursos da Mega-Sena que utiliza uma tabela de dispersão (hash table) para armazenar e acessar os dados dos concursos. Além das operações básicas de inserção, busca e remoção, o sistema é capaz de calcular e apresentar estatísticas sobre os resultados dos concursos.

#### Funcionalidades
- **Armazenamento de Concursos**: Utiliza uma tabela de dispersão para armazenar os concursos.
- **Operações Básicas**: Inserção, busca e remoção de concursos.
- **Estatísticas**: Cálculo e apresentação de estatísticas dos resultados.

#### Compilação e Execução

Para compilar o projeto, utilize o comando:

```bash
make
```

#### O executável será gerado na pasta bin e pode ser executado com:
```bash
./bin/main
```

### Conclusão
Ambos os projetos foram desenvolvidos na linguagem C e seguem uma estrutura similar de diretórios. Cada projeto tem seu próprio README que detalha as implementações e funcionalidades específicas.
