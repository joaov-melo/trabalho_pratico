

# Conversor Universal de Sistemas de Numeração

**Disciplina:** GCC241 - Introdução à Computação (2026/1) **Professor:** Prof. Dr. Rafael Serapilha Durelli **Instituição:** Universidade Federal de Lavras (UFLA) - Departamento de Ciência da Computação 

## 👥 Integrantes da Dupla

* **João Vitor Melo Alves Freitas** - Matrícula: 202610130
* **Vinícius Ferreira de** - Matrícula: 202610122

## 💻 Linguagem Escolhida

* 
**C++** 



## 🎯 Sobre o Projeto

Este projeto é um conversor de bases numéricas (decimal, binário, octal e hexadecimal) implementado a partir do zero. O objetivo central foi compreender e codificar os algoritmos matemáticos por trás das conversões (como divisões sucessivas e somatório posicional), respeitando a restrição de **não utilizar funções nativas de conversão** da linguagem C++ (como `std::stoi`, `strtol`, ou `printf("%x")`).

### Estrutura dos Módulos

O código foi modularizado para separar as responsabilidades:

* `main.cpp`: Ponto de entrada do programa, menu interativo e validação de dados de entrada.
* `padrao.cpp`: Núcleo contendo os algoritmos de conversão padrão (Requisitos F1 a F4 e F6).
* `passo_a_passo.cpp`: Lógica para exibir o "trace" e detalhes matemáticos do cálculo (Requisito F7).
* `batch.cpp`: Manipulação de arquivos `.csv` para conversões em lote (Requisito F8).
* `quiz.cpp`: Jogo interativo de conversões com 5 níveis de dificuldade (Requisito F9).
* `maximos.cpp`: Calculadora do valor máximo representável para *k* bits (Requisito F10).
* `testes.cpp`: Suíte com no mínimo 30 testes automatizados cobrindo as funções.



## 🚀 Instruções de Execução

### Pré-requisitos

* Compilador C++ (ex: GCC/G++) instalado na máquina.

### Compilação e Execução

Abra o terminal, navegue até a pasta do projeto e execute os seguintes comandos:

```bash
# 1. Compilar o código fonte
g++ main.cpp -o conversor

# 2. Executar o programa
./conversor

```

### Como Rodar os Testes Automatizados

Para executar a suíte de testes (que contempla os 30 casos obrigatórios cobrindo as conversões e casos de borda):

```bash
g++ src/testes.cpp -o testes && ./testes

```

## 📖 Exemplos de Uso

Ao rodar o programa, um menu interativo será exibido:

```text
Digite 1 para modo padrão de conversão;
Digite 2 para modo passo a passo de conversão;
Digite 3 para modo batch de conversão;
Digite 4 para modo quiz;
Digite 5 para modo calculadora de máximos;
Digite 6 para sair.

```

* **Exemplo - Conversão Padrão (Opção 1):** O usuário seleciona a base de origem (ex: 1 para Decimal) e a base de destino (ex: 2 para Binário). O programa pedirá o número e fará a validação, retornando o resultado diretamente.
* **Exemplo - Validação (F5):** Se o usuário escolher "Base Binária" e digitar `102`, o programa exibirá: `Erro: Entrada invalida. [cite_start]A base binaria aceita apenas os digitos 0 e 1.` e abortará a conversão.


* **Exemplo - Batch (Opção 3):** Certifique-se de que o arquivo `entrada.csv` está no mesmo diretório do executável. O programa lerá os dados e gerará um arquivo `saida.csv` com os resultados.



## ⚠️ Limitações Conhecidas

* **Tipo da base de origem e de destino:** As variáveis que representam as bases de origem e base destino foram declaradas como do tipo int, então ao colocar um caracter inválido para esse tipo como base o sistema fica em loop infinito.

## 🔗 Links Importantes

* 
**Vídeo de Demonstração (YouTube/Drive):** 