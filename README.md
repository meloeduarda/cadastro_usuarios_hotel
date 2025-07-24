# Cadastro de Usuários para Hotel

Este projeto foi desenvolvido na disciplina de **Introdução aos Algoritmos** e implementa um sistema simples de cadastro, busca, edição e exclusão de usuários de um hotel.

## Funcionalidades

- Cadastro de novos usuários com informações: Nome, CPF, ID, preço diário, quantidade de dias hospedado e valor total.
- Busca de usuários por ID, nome ou CPF.
- Exclusão lógica de usuários.
- Ordenação dos usuários por ID ou CPF.
- Persistência dos dados em arquivo CSV (`register.csv`).

## Tecnologias Utilizadas

- Linguagem: C++
- Arquivo de dados: CSV (`register.csv`)
- Ambiente: Qualquer compilador C++ com suporte à leitura e escrita de arquivos

## Como compilar e executar

1. Compile o código:
bash
g++ main.cpp -o cadastro_hotel

2. Execute o programa
./cadastro_hotel

3. Utilize o menu interativo para navegar pelas funções do sistema.

## Estrutura dos Dados
Cada usuário possui os seguintes campos:

userId (inteiro): Identificador único gerado automaticamente

userName (string): Nome do usuário

cpf (string): CPF do usuário

dailyPrice (float): Preço diário do quarto escolhido

days (inteiro): Quantidade de dias hospedado

totalPrice (double): Valor total a pagar (dailyPrice * days)

## Autora
Maria Eduarda Melo
Estudante de Engenharia de Controle e Automação - UFLA
