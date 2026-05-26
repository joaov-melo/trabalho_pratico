#ifndef PADRAO_CPP
#define PADRAO_CPP
#include <iostream>
#include <string>


using namespace std;

// ------------------------------------------------------------------------------
// FUNÇÕES AUXILIARES
// Como é proibido usar funções prontas do C++ (como to_string ou stoll),
// fiz essa função abaixo para transformar número em texto manipulando
// os caracteres um por um através da tabela ASCII.
// ------------------------------------------------------------------------------

// Pega um número inteiro e vai isolando os dígitos para transformá-los em letras
string numero_para_string(long long n) {
    if (n == 0) return "0";
    string texto = "";
    while (n > 0) {
        char digito = (n % 10) + '0'; // Converte o resto da divisão no caractere correspondente
        texto = digito + texto;       // Vai grudando os caracteres da direita para a esquerda
        n /= 10;
    }
    return texto;
}

// Faz o inverso: lê um texto cheio de algarismos e reconstrói o valor numérico dele
long long string_para_numero(string s) {
    long long numero = 0;
    for (int i = 0; i < (int)s.length(); i++) {
        numero = numero * 10 + (s[i] - '0'); // Anda com a casa decimal para a esquerda e soma o novo dígito
    }
    return numero;
}

// F6: Analisa o texto da entrada, isola o ponto/vírgula e valida se os caracteres batem com a base
bool separar_e_validar(string entrada, string &inteira, string &fracionaria, int base) {
    inteira = "";
    fracionaria = "";
    bool encontrou_separador = false;
    
    if (entrada == "") return false;
    
    for (int i = 0; i < (int)entrada.length(); i++) {
        char c = entrada[i];
        
        // F6: Se achar um ponto ou uma vírgula, ativa a chave para começar a preencher a fração
        if (c == '.' || c == ',') {
            if (encontrou_separador) return false; // F6: Se o cara digitou mais de uma vírgula, bloqueia na hora
            encontrou_separador = true;
            continue;
        }
        
        // F6: Faz o papel do F5, testando se o caractere pertence de fato à base escolhida
        if (base == 2) {
            if (c != '0' && c != '1') return false;
        } else if (base == 8) {
            if (c < '0' || c > '7') return false;
        } else if (base == 10) {
            if (c < '0' || c > '9') return false;
        } else if (base == 16) {
            if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F'))) return false;
        }
        
        // F6: Joga o caractere na gaveta certa de acordo com a posição dele em relação ao separador
        if (!encontrou_separador) {
            inteira += c;
        } else {
            fracionaria += c;
        }
    }
    
    if (inteira == "") inteira = "0"; // F6: Se o usuário digitar algo como ",5", nós assumimos que é "0,5"
    return true;
}

// F6: Junta a parte inteira e fracionária limpando zeros extras e cuidando do teto de 16 casas
string formatar_resultado(string parte_int, string parte_frac, bool truncado) {
    // F6: Remove os zeros inúteis que sobraram no começo da parte inteira
    int idx_valido = 0;
    while (idx_valido < (int)parte_int.length() - 1 && parte_int[idx_valido] == '0') {
        idx_valido++;
    }
    string int_limpa = "";
    for (int i = idx_valido; i < (int)parte_int.length(); i++) {
        int_limpa += parte_int[i];
    }
    
    // F6: Se não existir fração, devolve só a parte inteira limpa e bem formatada
    if (parte_frac == "") {
        return int_limpa;
    }
    
    bool foi_truncado = truncado;
    // F6: Aplica a regra rígida do teto de 16 dígitos decimais após a vírgula
    if ((int)parte_frac.length() > 16) {
        string frac_cortada = "";
        for (int i = 0; i < 16; i++) {
            frac_cortada += parte_frac[i];
        }
        parte_frac = frac_cortada;
        foi_truncado = true; // F6: Como cortamos algarismos válidos, avisamos que foi truncado
    }
    
    // F6: Se a conta foi exata, limpa os zeros bobos do final (ex: de 1,5000 deixa só 1,5)
    if (!foi_truncado) {
        int fim = (int)parte_frac.length() - 1;
        while (fim >= 0 && parte_frac[fim] == '0') {
            fim--;
        }
        string frac_limpa = "";
        for (int i = 0; i <= fim; i++) {
            frac_limpa += parte_frac[i];
        }
        parte_frac = frac_limpa;
    }
    
    if (parte_frac == "") {
        return int_limpa;
    }
    
    // F6: Cola as duas partes usando a vírgula padrão e anexa o texto de aviso se necessário
    if (foi_truncado) {
        return int_limpa + "," + parte_frac + " (truncado)";
    } else {
        return int_limpa + "," + parte_frac;
    }
}

// F6: Lógica de multiplicações sucessivas para converter frações decimais para outras bases
string converter_fracao_decimal_para_base(string frac_str, int base, bool &truncado) {
    truncado = false;
    if (frac_str == "") return "";
    
    unsigned long long valor = 0;
    unsigned long long divisor = 1;
    
    int tam = (int)frac_str.length();
    if (tam > 18) tam = 18; // F6: Trava em 18 dígitos para não estourar o limite de tamanho do C++
    
    // F6: Monta uma fração real usando apenas números inteiros para fugir da imprecisão do double
    for (int i = 0; i < tam; i++) {
        valor = valor * 10 + (frac_str[i] - '0');
        divisor *= 10;
    }
    
    string frac_res = "";
    // F6: Faz o algoritmo clássico de multiplicar a fração pela base até dar 16 dígitos
    for (int i = 0; i < 16; i++) {
        if (valor == 0) break;
        
        valor *= base;
        int digito = valor / divisor;
        valor %= divisor;
        
        char c = (digito < 10) ? (digito + '0') : (digito - 10 + 'A');
        frac_res += c;
    }
    
    if (valor > 0) truncado = true; // F6: Se saiu do loop e ainda sobrou resto, a dízima foi cortada
    return frac_res;
}

// F6: Lógica de divisão escalada manual para converter frações de qualquer base para decimal
string converter_fracao_base_para_decimal(string frac_str, int base, bool &truncado) {
    truncado = false;
    if (frac_str == "") return "";
    
    unsigned long long N = 0; 
    unsigned long long D = 1; 
    
    int tam = (int)frac_str.length();
    if (tam > 15) tam = 15; // F6: Evita estouro de bits limitando a leitura inicial da string
    
    // F6: Monta a proporção matemática baseada no peso de cada casa da base de origem
    for (int i = 0; i < tam; i++) {
        int digito_val = 0;
        char c = frac_str[i];
        if (c >= '0' && c <= '9') digito_val = c - '0';
        else if (c >= 'A' && c <= 'F') digito_val = c - 'A' + 10;
        
        N = N * base + digito_val;
        D = D * base;
    }
    
    string frac_res = "";
    // F6: Simula uma conta de divisão armada no caderno jogando o número para a base 10 casa por casa
    for (int i = 0; i < 16; i++) {
        if (N == 0) break;
        N *= 10;
        int digito = N / D;
        frac_res += (digito + '0');
        N %= D;
    }
    
    if (N > 0 || (int)frac_str.length() > tam) {
        truncado = true;
    }
    
    return frac_res;
}


// ----------------------------------------------------------------------------
// F1 - CONVERSÕES A PARTIR DE DECIMAL (DIVISÕES SUCESSIVAS)
// ----------------------------------------------------------------------------

string decimal_divisao_binario(string decimal_str){
    // F6: Criamos variáveis vazias para receber as duas metades do número fracionário
    string inteira, fracionaria;
    // F6: Chama o validador e separador adaptado para aceitar pontos e vírgulas
    if (!separar_e_validar(decimal_str, inteira, fracionaria, 10)) return "Erro, caracter(es) inválido(s).";

    long long decimal = string_para_numero(inteira); // F6: Convertemos apenas a parte inteira com a lógica antiga
    string binario = "";
    if(decimal == 0) binario = "0"; // F6: Evita que o loop pule o zero caso a entrada comece zerada

    while (decimal > 0){
        char bit = (decimal % 2) + '0'; // Restos guardados de baixo para cima
        binario = bit + binario;
        decimal /= 2;
    }
    
    // F6: Processa a parte fracionária usando multiplicações sucessivas e formata o resultado final
    bool truncado = false;
    string frac_res = converter_fracao_decimal_para_base(fracionaria, 2, truncado);
    return formatar_resultado(binario, frac_res, truncado);
}

string decimal_divisao_octal(string decimal_str){
    // F6: Criamos variáveis vazias para receber as duas metades do número fracionário
    string inteira, fracionaria;
    // F6: Chama o validador e separador adaptado para aceitar pontos e vírgulas
    if (!separar_e_validar(decimal_str, inteira, fracionaria, 10)) return "Erro, caracter(es) inválido(s).";

    long long decimal = string_para_numero(inteira); // F6: Convertemos apenas a parte inteira com a lógica antiga
    string octal = "";
    if (decimal == 0) octal = "0";

    while (decimal > 0){
        char digito = (decimal % 8) + '0';
        octal = digito + octal;
        decimal /= 8;
    }
    
    // F6: Processa a fração decimal em octal e envelopa tudo na formatação limpa
    bool truncado = false;
    string frac_res = converter_fracao_decimal_para_base(fracionaria, 8, truncado);
    return formatar_resultado(octal, frac_res, truncado);
}

string decimal_divisao_hexa(string decimal_str){
    // F6: Criamos variáveis vazias para receber as duas metades do número fracionário
    string inteira, fracionaria;
    // F6: Chama o validador e separador adaptado para aceitar pontos e vírgulas
    if (!separar_e_validar(decimal_str, inteira, fracionaria, 10)) return "Erro, caracter(es) inválido(s).";

    long long decimal = string_para_numero(inteira); // F6: Convertemos apenas a parte inteira com a lógica antiga
    string hexa = "";
    if (decimal == 0) hexa = "0";

    while (decimal > 0){
        int resto = decimal % 16;
        char digito_hexa;
        if (resto < 10){
            digito_hexa = resto + '0';
        }
        else{
            digito_hexa = (resto - 10) + 'A';
        }
        hexa = digito_hexa + hexa;
        decimal /= 16;
    }
    
    // F6: Processa a fração decimal em hexadecimal e gera a formatação de saída
    bool truncado = false;
    string frac_res = converter_fracao_decimal_para_base(fracionaria, 16, truncado);
    return formatar_resultado(hexa, frac_res, truncado);
}


// ----------------------------------------------------------------------------
// F2 - CONVERSÕES PARA DECIMAL (SOMATÓRIO POSICIONAL)
// ----------------------------------------------------------------------------

string binario_somatorio_decimal(string binario){
    // F6: Criamos variáveis vazias para receber as duas metades do número fracionário
    string inteira, fracionaria;
    // F6: Chama o validador e separador adaptado para aceitar pontos e vírgulas
    if (!separar_e_validar(binario, inteira, fracionaria, 2)) return "Erro, caracter(es) inválido(s).";
    long long decimal = 0;
    long long casa = 1;

    // Lendo de trás para frente para aplicar o somatório posicional (agora focado na parte inteira)
    for (int i = (int)inteira.length() - 1; i >= 0; i--) {
        decimal += (inteira[i] - '0') * casa;
        casa *= 2;
    }
    
    // F6: Processa a fração da base para decimal usando frações inteiras e junta tudo com segurança
    bool truncado = false;
    string frac_res = converter_fracao_base_para_decimal(fracionaria, 2, truncado);
    return formatar_resultado(numero_para_string(decimal), frac_res, truncado);
}

string octal_somatorio_decimal(string octal){
    // F6: Criamos variáveis vazias para receber as duas metades do número fracionário
    string inteira, fracionaria;
    // F6: Chama o validador e separador adaptado para aceitar pontos e vírgulas
    if (!separar_e_validar(octal, inteira, fracionaria, 8)) return "Erro, caracter(es) inválido(s).";
    long long decimal = 0;
    long long casa = 1;

    // F6: Varre a parte inteira aplicando os pesos posicionais base 8 originais
    for (int i = (int)inteira.length() - 1; i >= 0; i--) {
        decimal += (inteira[i] - '0') * casa;
        casa *= 8;
    }
    
    // F6: Calcula a conversão da fração octal e entrega o resultado na formatação correta
    bool truncado = false;
    string frac_res = converter_fracao_base_para_decimal(fracionaria, 8, truncado);
    return formatar_resultado(numero_para_string(decimal), frac_res, truncado);
}

string hexa_somatorio_decimal(string hexa){
    // F6: Criamos variáveis vazias para receber as duas metades do número fracionário
    string inteira, fracionaria;
    // F6: Chama o validador e separador adaptado para aceitar pontos e vírgulas
    if (!separar_e_validar(hexa, inteira, fracionaria, 16)) return "Erro, caracter(es) inválido(s).";
    long long decimal = 0;
    long long casa = 1;

    // F6: Varre a parte inteira aplicando os pesos posicionais base 16 originais
    for(int i = (int)inteira.length() - 1; i >= 0; i--){
        int valor;
        if (inteira[i] >= '0' && inteira[i] <= '9'){
            valor = inteira[i] - '0';
        }
        else if (inteira[i] >= 'A' && inteira[i] <= 'F'){
            valor = (inteira[i] - 'A') + 10;
        }
        decimal += valor * casa;
        casa *= 16;
    }
    
    // F6: Calcula a conversão da fração hexadecimal e entrega na formatação especificada
    bool truncado = false;
    string frac_res = converter_fracao_base_para_decimal(fracionaria, 16, truncado);
    return formatar_resultado(numero_para_string(decimal), frac_res, truncado);
}


// ----------------------------------------------------------------------------
// F3 - CONVERSÕES POR AGRUPAMENTO DIRETAS (SEM PASSAR POR DECIMAL)
// ----------------------------------------------------------------------------

string binario_agrupamento_octal(string binario){
    // F6: Criamos variáveis vazias para receber as duas metades do número fracionário
    string inteira, fracionaria;
    // F6: Chama o validador e separador adaptado para aceitar pontos e vírgulas
    if (!separar_e_validar(binario, inteira, fracionaria, 2)) return "Erro, caracter(es) inválido(s).";

    string octal = "";
    int i = (int)inteira.length() - 1;
    
    // Agrupando de 3 em 3 bits de trás para frente (focado na parte inteira)
    while (i >= 0) {
        int v0 = inteira[i] - '0';
        int v1 = (i - 1 >= 0) ? (inteira[i - 1] - '0') : 0;
        int v2 = (i - 2 >= 0) ? (inteira[i - 2] - '0') : 0;
        
        int valor_trio = v0 * 1 + v1 * 2 + v2 * 4;
        char digito = valor_trio + '0';
        octal = digito + octal;
        i -= 3;
    }
    if (octal == "") octal = "0";

    // F6: Agrupa os bits da fração de 3 em 3, mas andando da esquerda para a direita (frente para trás)
    string frac_res = "";
    int idx = 0;
    while (idx < (int)fracionaria.length()) {
        int v2 = fracionaria[idx] - '0';
        int v1 = (idx + 1 < (int)fracionaria.length()) ? (fracionaria[idx + 1] - '0') : 0;
        int v0 = (idx + 2 < (int)fracionaria.length()) ? (fracionaria[idx + 2] - '0') : 0;
        
        int valor_trio = v2 * 4 + v1 * 2 + v0 * 1;
        frac_res += (char)(valor_trio + '0');
        idx += 3;
    }

    return formatar_resultado(octal, frac_res, false);
}

string octal_agrupamento_binario(string octal){
    // F6: Criamos variáveis vazias para receber as duas metades do número fracionário
    string inteira, fracionaria;
    // F6: Chama o validador e separador adaptado para aceitar pontos e vírgulas
    if (!separar_e_validar(octal, inteira, fracionaria, 8)) return "Erro, caracter(es) inválido(s).";
    string binario = "";

    // Cada dígito octal expande diretamente para 3 bits (restruturado para a parte inteira)
    for (int i = 0; i < (int)inteira.length(); i++) {
        int val = inteira[i] - '0';
        char b2 = (val / 4) + '0';
        char b1 = ((val % 4) / 2) + '0';
        char b0 = (val % 2) + '0';
        
        binario += b2;
        binario += b1;
        binario += b0;
    }

    // F6: Faz o espalhamento idêntico de 3 bits para cada caractere da parte fracionária
    string frac_res = "";
    for (int i = 0; i < (int)fracionaria.length(); i++) {
        int val = fracionaria[i] - '0';
        frac_res += (val / 4) + '0';
        frac_res += ((val % 4) / 2) + '0';
        frac_res += (val % 2) + '0';
    }

    return formatar_resultado(binario, frac_res, false);
}

string binario_agrupamento_hexa(string binario){ 
    // F6: Criamos variáveis vazias para receber as duas metades do número fracionário
    string inteira, fracionaria;
    // F6: Chama o validador e separador adaptado para aceitar pontos e vírgulas
    if (!separar_e_validar(binario, inteira, fracionaria, 2)) return "Erro, caracter(es) inválido(s).";

    string hexa = "";
    int i = (int)inteira.length() - 1;
    
    // Agrupando de 4 em 4 bits de trás para frente (focado na parte inteira)
    while (i >= 0) {
        int v0 = inteira[i] - '0';
        int v1 = (i - 1 >= 0) ? (inteira[i - 1] - '0') : 0;
        int v2 = (i - 2 >= 0) ? (inteira[i - 2] - '0') : 0;
        int v3 = (i - 3 >= 0) ? (inteira[i - 3] - '0') : 0;
        
        int valor_quadra = v0 * 1 + v1 * 2 + v2 * 4 + v3 * 8;
        char digito;
        if (valor_quadra < 10) digito = valor_quadra + '0';
        else digito = (valor_quadra - 10) + 'A';
        
        hexa = digito + hexa;
        i -= 4;
    }
    if (hexa == "") hexa = "0";

    // F6: Agrupa os bits da fração de 4 em 4, andando de frente para trás (esquerda para direita)
    string frac_res = "";
    int idx = 0;
    while (idx < (int)fracionaria.length()) {
        int v3 = fracionaria[idx] - '0';
        int v2 = (idx + 1 < (int)fracionaria.length()) ? (fracionaria[idx + 1] - '0') : 0;
        int v1 = (idx + 2 < (int)fracionaria.length()) ? (fracionaria[idx + 2] - '0') : 0;
        int v0 = (idx + 3 < (int)fracionaria.length()) ? (fracionaria[idx + 3] - '0') : 0;
        
        int valor_quadra = v3 * 8 + v2 * 4 + v1 * 2 + v0 * 1;
        char digito;
        if (valor_quadra < 10) digito = valor_quadra + '0';
        else digito = (valor_quadra - 10) + 'A';
        
        frac_res += digito;
        idx += 4;
    }

    return formatar_resultado(hexa, frac_res, false);
}

string hexa_agrupamento_binario(string hexa){
    // F6: Criamos variáveis vazias para receber as duas metades do número fracionário
    string inteira, fracionaria;
    // F6: Chama o validador e separador adaptado para aceitar pontos e vírgulas
    if (!separar_e_validar(hexa, inteira, fracionaria, 16)) return "Erro, caracter(es) inválido(s).";
    string binario = "";
    
    // Cada dígito hexadecimal vira uma quadra de 4 bits (reestruturado para a parte inteira)
    for (int i = 0; i < (int)inteira.length(); i++) {
        int val;
        if (inteira[i] >= '0' && inteira[i] <= '9') val = inteira[i] - '0';
        else val = (inteira[i] - 'A') + 10;

        char b3 = (val / 8) + '0';
        char b2 = ((val % 8) / 4) + '0';
        char b1 = ((val % 4) / 2) + '0';
        char b0 = (val % 2) + '0';
        
        binario += b3;
        binario += b2;
        binario += b1;
        binario += b0;
    }

    // F6: Faz o espalhamento idêntico de 4 bits para cada caractere da fração hexadecimal
    string frac_res = "";
    for (int i = 0; i < (int)fracionaria.length(); i++) {
        int val;
        if (fracionaria[i] >= '0' && fracionaria[i] <= '9') val = fracionaria[i] - '0';
        else val = (fracionaria[i] - 'A') + 10;

        char b3 = (val / 8) + '0';
        char b2 = ((val % 8) / 4) + '0';
        char b1 = ((val % 4) / 2) + '0';
        char b0 = (val % 2) + '0';
        
        frac_res += b3;
        frac_res += b2;
        frac_res += b1;
        frac_res += b0;
    }

    return formatar_resultado(binario, frac_res, false);
}


// ----------------------------------------------------------------------------
// F4 - CONVERSÕES DIRETAS ENTRE OCTAL E HEXADECIMAL (PONTE BINÁRIA)
// ----------------------------------------------------------------------------

string octal_hexa(string octal){
    // Primeiro passo: transformo o octal em binário de forma agrupada
    string resultado_binario = octal_agrupamento_binario(octal);
    if (resultado_binario == "Erro, caracter(es) inválido(s).") return resultado_binario;
    
    // Segundo passo: pego esse binário e agrupo direto para Hexa
    return binario_agrupamento_hexa(resultado_binario);
}

string hexa_octal(string hexa){
    // Primeiro passo: transformo o hexa em binário de forma espalhada
    string resultado_binario = hexa_agrupamento_binario(hexa);
    if (resultado_binario == "Erro, caracter(es) inválido(s).") return resultado_binario;
    
    // Segundo passo: pego esse binário e agrupo de 3 em 3 para virar octal
    return binario_agrupamento_octal(resultado_binario);
}


// ----------------------------------------------------------------------------
// ÁREA DE TESTES DA VALIDAÇÃO (MAIN)
// ----------------------------------------------------------------------------
//int main(){
//    cout << "--- Testando Validacoes de Erro (F5 + F6) ---" << endl;
//    cout << "Decimal Invalido ('12A3'):    " << decimal_divisao_binario("12A3") << endl;
//    cout << "Hexadecimal Invalido ('1G'):  " << hexa_octal("1G") << endl;
//    cout << "Entrada com duas virgulas:    " << decimal_divisao_binario("12,3,4") << endl;

//    cout << "\n--- Testando Sucessos Fracionarios Reais (F6) ---" << endl;
//    cout << "Decimal '10,625' para Bin:    " << decimal_divisao_binario("10,625") << endl;
//    cout << "Binario '1010,101' para Dec:  " << binario_somatorio_decimal("1010,101") << endl;
//    cout << "Decimal dízima '0,1' para Bin:" << decimal_divisao_binario("0,1") << endl;
//    cout << "Octal '12,5' para Hexa:       " << octal_hexa("12,5") << endl;

  //  return 0;
//}

#endif
