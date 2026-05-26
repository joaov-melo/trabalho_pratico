#ifndef PASSO_A_PASSO_CPP
#define PASSO_A_PASSO_CPP

#include <iostream>
#include <string>
#include "padrao.cpp"

using namespace std;

// --- FUNÇÕES DE RASTREAMENTO (TRACE) ---

// Exibe a tabela de divisões e restos (Usado para Decimal -> Qualquer Base)
void trace_decimal_para_base(string inteira, int base) {
    long long num = string_para_numero(inteira);
    cout << "--- METODO DAS DIVISOES SUCESSIVAS (Parte Inteira) ---" << endl;
    if (num == 0) {
        cout << "Numero 0, convertido direto para 0." << endl;
        return;
    }
    string resultado = "";
    while (num > 0) {
        long long quociente = num / base;
        int resto = num % base;
        char digito;
        if (resto < 10) digito = resto + '0';
        else digito = (resto - 10) + 'A';
        
        cout << num << " dividido por " << base << " = " << quociente 
             << " | Resto: " << resto << " (" << digito << ")" << endl;
        resultado = digito + resultado;
        num = quociente;
    }
    cout << "-> Lendo os restos de baixo para cima: " << resultado << endl;
}

// Exibe a soma de cada digito pelo peso de sua posição (Usado para Qualquer Base -> Decimal)
void trace_base_para_decimal(string inteira, int base) {
    cout << "--- METODO DO SOMATORIO POSICIONAL (Parte Inteira) ---" << endl;
    long long decimal = 0;
    long long casa = 1;
    cout << "Formula: Somatorio(digito * base^posicao)" << endl;
    
    for (int i = (int)inteira.length() - 1, pos = 0; i >= 0; i--, pos++) {
        int valor;
        if (inteira[i] >= '0' && inteira[i] <= '9') valor = inteira[i] - '0';
        else valor = (inteira[i] - 'A') + 10;
        
        cout << "Posicao " << pos << " (digito " << inteira[i] << "): " 
             << valor << " * " << casa << " = " << (valor * casa) << endl;
        decimal += valor * casa;
        casa *= base;
    }
    cout << "-> Somatorio total: " << decimal << endl;
}

// Exibe o processo de pegar N bits do binario e transformar em um digito (Binario -> Octal/Hexa)
void trace_agrupamento(string inteira, int bits) {
    cout << "--- AGRUPAMENTO DE BITS (Parte Inteira) ---" << endl;
    cout << "Agrupando de " << bits << " em " << bits << " da direita para a esquerda:" << endl;
    string resultado = "";
    int i = (int)inteira.length() - 1;
    while (i >= 0) {
        string grupo = "";
        int valor_grupo = 0;
        int peso = 1;
        for (int j = 0; j < bits; j++) {
            if (i - j >= 0) {
                grupo = inteira[i - j] + grupo; // Auxiliar de montagem do grupo
                grupo = inteira[i - j] + grupo;
                valor_grupo += (inteira[i - j] - '0') * peso;
            } else {
                grupo = "0" + grupo; 
            }
            peso *= 2;
        }
        char digito;
        if (valor_grupo < 10) digito = valor_grupo + '0';
        else digito = (valor_grupo - 10) + 'A';
        
        cout << "Grupo [" << grupo << "] -> Valor base 10: " << valor_grupo << " | Digito convertido: " << digito << endl;
        resultado = digito + resultado;
        i -= bits;
    }
    cout << "-> Resultado do agrupamento: " << resultado << endl;
}

// Exibe o processo de pegar 1 digito e expandir para N bits (Octal/Hexa -> Binario)
void trace_expansao(string inteira, int bits) {
    cout << "--- EXPANSAO PARA BINARIO (Parte Inteira) ---" << endl;
    cout << "Expandindo cada digito em " << bits << " bits:" << endl;
    string resultado = "";
    for (int i = 0; i < (int)inteira.length(); i++) {
        int valor;
        if (inteira[i] >= '0' && inteira[i] <= '9') valor = inteira[i] - '0';
        else valor = (inteira[i] - 'A') + 10;
        
        string bin_grupo = "";
        int temp = valor;
        for (int j = 0; j < bits; j++) {
            char b = (temp % 2) + '0';
            bin_grupo = b + bin_grupo;
            temp /= 2;
        }
        cout << "Digito [" << inteira[i] << "] (valor " << valor << ") expande para -> " << bin_grupo << endl;
        resultado += bin_grupo;
    }
    cout << "-> Resultado da expansao: " << resultado << endl;
}


// --- SUBPROGRAMA PRINCIPAL DO MODO ---

void executar_modo_passo_a_passo(int origem, int destino, string n) {
    // 1. Mapeia a opção 'origem' do menu (1 a 4) para a sua base matemática real
    int base_orig = (origem == 1) ? 10 : (origem == 2) ? 2 : (origem == 3) ? 8 : 16;
    
    // 2. Mapeia a opção 'destino' do menu (1 a 3) baseado estritamente na imagem da interface
    int base_dest = (origem == 1) ? (destino == 1 ? 2 : destino == 2 ? 8 : 16) :
                    (origem == 2) ? (destino == 1 ? 10 : destino == 2 ? 8 : 16) :
                    (origem == 3) ? (destino == 1 ? 10 : destino == 2 ? 2 : 16) :
                                    (destino == 1 ? 10 : destino == 2 ? 2 : 8);
    
    string inteira, fracionaria;
    if (!separar_e_validar(n, inteira, fracionaria, base_orig)) {
        cout << "Erro, caracter(es) invalido(s)." << endl;
        return;
    }
    
    cout << "\n--------------------------------------------------------" << endl;
    cout << "[PASSO A PASSO] Convertendo " << n << " da base " << base_orig << " para a base " << base_dest << endl;
    cout << "--------------------------------------------------------\n" << endl;
    
    // Avaliação robusta baseada nas bases numéricas reais calculadas acima
    if (base_orig == 10) { // Decimal para Qualquer Base
        trace_decimal_para_base(inteira, base_dest);
        cout << "\n[Resultado Final Completo (com fracao, se houver)]: ";
        if (base_dest == 2) cout << decimal_divisao_binario(n) << endl;
        else if (base_dest == 8) cout << decimal_divisao_octal(n) << endl;
        else if (base_dest == 16) cout << decimal_divisao_hexa(n) << endl;
    }
    else if (base_dest == 10) { // Qualquer Base para Decimal
        trace_base_para_decimal(inteira, base_orig);
        cout << "\n[Resultado Final Completo (com fracao, se houver)]: ";
        if (base_orig == 2) cout << binario_somatorio_decimal(n) << endl;
        else if (base_orig == 8) cout << octal_somatorio_decimal(n) << endl;
        else if (base_orig == 16) cout << hexa_somatorio_decimal(n) << endl;
    }
    else if (base_orig == 2) {  // Binário para Octal ou Hexadecimal
        int bits = (base_dest == 8) ? 3 : 4;
        trace_agrupamento(inteira, bits);
        cout << "\n[Resultado Final Completo (com fracao, se houver)]: ";
        if (base_dest == 8) cout << binario_agrupamento_octal(n) << endl;
        else if (base_dest == 16) cout << binario_agrupamento_hexa(n) << endl;
    }
    else if (base_dest == 2) { // Octal ou Hexadecimal para Binário
        int bits = (base_orig == 8) ? 3 : 4;
        trace_expansao(inteira, bits);
        cout << "\n[Resultado Final Completo (com fracao, se houver)]: ";
        if (base_orig == 8) cout << octal_agrupamento_binario(n) << endl;
        else if (base_orig == 16) cout << hexa_agrupamento_binario(n) << endl;
    }
    else { // Ponte Binária (Octal <-> Hexadecimal)
        cout << ">> PASSO 1: Ponte para o Binario (Expansao) <<" << endl;
        int bits_orig = (base_orig == 8) ? 3 : 4;
        trace_expansao(inteira, bits_orig);
        
        string binario_intermediario;
        if (base_orig == 8) binario_intermediario = octal_agrupamento_binario(inteira);
        else binario_intermediario = hexa_agrupamento_binario(inteira);
        
        cout << "\n>> PASSO 2: Binario para a Base " << base_dest << " (Agrupamento) <<" << endl;
        int bits_dest = (base_dest == 8) ? 3 : 4;
        
        // Separa para exibir apenas a parte inteira de forma limpa no rastreamento do agrupamento
        string bin_int, bin_frac;
        separar_e_validar(binario_intermediario, bin_int, bin_frac, 2);
        trace_agrupamento(bin_int, bits_dest);
        
        cout << "\n[Resultado Final Completo (com fracao, se houver)]: ";
        if (base_orig == 8 && base_dest == 16) cout << octal_hexa(n) << endl;
        else if (base_orig == 16 && base_dest == 8) cout << hexa_octal(n) << endl;
    }
    
    cout << "--------------------------------------------------------\n" << endl;
}

#endif
