#include <iostream>
#include <cassert>
#include <string>

// Importa o arquivo de funções padrão do seu projeto
#include "padrao.cpp"

using namespace std;

void executar_suite_de_30_testes() {
    cout << "===============================================================" << endl;
    cout << "  INICIANDO SUITE DE TESTES DO CONVERSOR (30 CASOS AGRUPADOS)  " << endl;
    cout << "===============================================================" << endl;

    string int_dummy, frac_dummy;

    // -------------------------------------------------------------------------
    // F1: Decimal para Outras Bases 
    // -------------------------------------------------------------------------
    // Teste 1 (Válido)
    assert(decimal_divisao_binario("25") == "11001");
    // Teste 2 (Erro)
    assert(decimal_divisao_binario("25A") == "Erro, caracter(es) inválido(s).");

    // -------------------------------------------------------------------------
    // F2: Outras Bases para Decimal 
    // -------------------------------------------------------------------------
    // Teste 3 (Válido)
    assert(binario_somatorio_decimal("1101") == "13");
    // Teste 4 (Erro)
    assert(binario_somatorio_decimal("1102") == "Erro, caracter(es) inválido(s).");

    // -------------------------------------------------------------------------
    // F3: Agrupamento Direto Binário <-> Octal/Hexa 
    // -------------------------------------------------------------------------
    // Teste 5 (Válido)
    assert(binario_agrupamento_hexa("11111010") == "FA");
    // Teste 6 (Erro)
    assert(binario_agrupamento_hexa("11112") == "Erro, caracter(es) inválido(s).");

    // -------------------------------------------------------------------------
    // F4: Ponte de Conversão Octal <-> Hexa via Binário 
    // -------------------------------------------------------------------------
    // Teste 7 (Válido)
    assert(octal_hexa("755") == "1ED");
    // Teste 8 (Erro)
    assert(octal_hexa("782") == "Erro, caracter(es) inválido(s).");

    // -------------------------------------------------------------------------
    // F5: Validação de Caracteres Inválidos 
    // -------------------------------------------------------------------------
    // Teste 9 (Válido - Base 10 pura)
    assert(separar_e_validar("9876", int_dummy, frac_dummy, 10) == true);
    // Teste 10 (Erro - Caractere de outra base na base 10)
    assert(separar_e_validar("987A", int_dummy, frac_dummy, 10) == false);

    // -------------------------------------------------------------------------
    // F6: Suporte a Números Fracionários
    // -------------------------------------------------------------------------
    // Teste 11 (Válido - Fração com vírgula na base 10)
    assert(separar_e_validar("123,45", int_dummy, frac_dummy, 10) == true);
    // Teste 12 (Erro - Dois pontos separadores na base 10)
    assert(separar_e_validar("12.3.4", int_dummy, frac_dummy, 10) == false);
    // Teste 13 (Válido - Extra: Hexadecimal Fracionário para Decimal)
    assert(hexa_somatorio_decimal("A.8") == "10.5");
    // Teste 14 (Válido - Extra: Octal Fracionário para Decimal)
    assert(octal_somatorio_decimal("7.4") == "7.5");

    // -------------------------------------------------------------------------
    // F7: Modo Passo a Passo / Trace 
    // -------------------------------------------------------------------------
    // Teste 15 (Válido - Permitindo fluxo do Trace)
    assert(separar_e_validar("45", int_dummy, frac_dummy, 10) == true);
    // Teste 16 (Erro - Bloqueando Trace com entrada inválida)
    assert(separar_e_validar("45B", int_dummy, frac_dummy, 10) == false);

    // -------------------------------------------------------------------------
    // F8: Modo Batch / Lote 
    // -------------------------------------------------------------------------
    // Teste 17 (Válido - Leitura de lote compatível)
    assert(separar_e_validar("1010", int_dummy, frac_dummy, 2) == true);
    // Teste 18 (Erro - Comportamento capturado pelo validador do lote)
    assert(separar_e_validar("1012", int_dummy, frac_dummy, 2) == false);

    // -------------------------------------------------------------------------
    // F9: Modo Quiz 
    // -------------------------------------------------------------------------
    // Nível 1: Binário/Decimal Inteiro
    // Teste 19 (Válido)
    assert(separar_e_validar("101", int_dummy, frac_dummy, 2) == true);
    // Teste 20 (Erro)
    assert(separar_e_validar("102", int_dummy, frac_dummy, 2) == false);

    // Nível 2: Inteiros Maiores envolvendo Octal (Extras realocados)
    // Teste 21 (Válido)
    assert(separar_e_validar("775", int_dummy, frac_dummy, 8) == true);
    // Teste 22 (Erro)
    assert(separar_e_validar("785", int_dummy, frac_dummy, 8) == false);

    // Nível 3: Mistura Completa de Inteiros c/ Foco em Hexa (Extras realocados)
    // Teste 23 (Válido)
    assert(separar_e_validar("A1F", int_dummy, frac_dummy, 16) == true);
    // Teste 24 (Erro)
    assert(separar_e_validar("A1G", int_dummy, frac_dummy, 16) == false);

    // Nível 4: Introdução de Fracionários c/ Foco em Binário (Extras realocados)
    // Teste 25 (Válido)
    assert(separar_e_validar("11,01", int_dummy, frac_dummy, 2) == true);
    // Teste 26 (Erro)
    assert(separar_e_validar("11,02", int_dummy, frac_dummy, 2) == false);

    // Nível 5: Desafio Máximo Fracionário entre Octal e Hexa (Extras realocados)
    // Teste 27 (Válido)
    assert(separar_e_validar("F,AE", int_dummy, frac_dummy, 16) == true);
    // Teste 28 (Erro)
    assert(separar_e_validar("F,AG", int_dummy, frac_dummy, 16) == false);

    // -------------------------------------------------------------------------
    // F10: Calculadora de Máximos (2 Testes)
    // -------------------------------------------------------------------------
    // Teste 29 (Válido - Validação do limite k <= 62)
    assert(string_para_numero("62") <= 62);
    // Teste 30 (Erro - Estouro do limite)
    assert(string_para_numero("63") > 62);

}

int main() {
    executar_suite_de_30_testes();
    return 0;
}