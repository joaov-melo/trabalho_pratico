#ifndef MAXIMOS_CPP
#define MAXIMOS_CPP
#include <iostream>
#include <string>
#include "padrao.cpp"


using namespace std;

// ----------------------------------------------------------------------------
// F10 - CALCULADORA DE MÁXIMOS
// Esta função recebe uma quantidade k de bits e mostra o maior valor
// representável (2^k - 1) em todas as 4 bases simultaneamente.
// ----------------------------------------------------------------------------
void executar_calculadora_maximos(string n) {
    // Nova validação (F5): Impede que o usuário digite letras ou símbolos
    for (int i = 0; i < (int)n.length(); i++) {
        if (n[i] < '0' || n[i] > '9') {
            cout << "Erro: A quantidade de bits deve ser um numero inteiro valido." << endl;
            return;
        }
    }

    int k = string_para_numero(n);
   

    // Validação básica para impedir valores negativos ou zerados
    if (k <= 0) {
        cout << "Erro: A quantidade de bits deve ser maior que zero." << endl;
        return;
    }
    
    // Como as funções internas usam 'long long' para processar o somatório decimal,
    // limitamos em 62 bits para garantir que a conta não estoure o tamanho do C++.
    if (k > 62) {
        cout << "Erro: Escolha um valor de k ate 62 bits para evitar estouro numerico." << endl;
        return;
    }

    // O maior número com k bits (2^k - 1) em binário 
    // é sempre composto por uma sequência de 'k' vezes o caractere '1'.
    // Exemplo: Com 4 bits, o máximo é 15, que em binário é exatamente "1111".
    string binario_max = "";
    for (int i = 0; i < k; i++) {
        binario_max += "1";
    }

    // Agora aproveitamos a estrutura que voce já fez no primeiro arquivo para
    // descobrir como esse monte de '1s' fica nas outras bases sem refazer trabalho!
    string decimal_max = binario_somatorio_decimal(binario_max);
    string octal_max   = binario_agrupamento_octal(binario_max);
    string hexa_max    = binario_agrupamento_hexa(binario_max);

    // Exibe os resultados todos juntos na tela conforme pede o requisito
    cout << "\nMaior valor representavel com " << k << " bits (2^" << k << " - 1):" << endl;
    cout << "-> Decimal:     " << decimal_max << endl;
    cout << "-> Binario:     " << binario_max << endl;
    cout << "-> Octal:       " << octal_max << endl;
    cout << "-> Hexadecimal: " << hexa_max << endl;
}
#endif
