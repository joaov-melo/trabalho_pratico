#ifndef QUIZ_CPP
#define QUIZ_CPP

#include <iostream>
#include <string>
#include <cstdlib> 
#include <ctime>   
#include "padrao.cpp"

using namespace std;

// --- FUNÇÕES AUXILIARES ---

string nome_base(int b) {
    if (b == 2) return "Binaria (2)";
    if (b == 8) return "Octal (8)";
    if (b == 10) return "Decimal (10)";
    return "Hexadecimal (16)";
}

string para_maiusculo(string s) {
    string resultado = "";
    for (int i = 0; i < (int)s.length(); i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            resultado += (s[i] - 32); 
        } else {
            resultado += s[i];
        }
    }
    return resultado;
}

string converter_decimal_para(string num_dec_str, int base_dest) {
    if (base_dest == 2) return decimal_divisao_binario(num_dec_str);
    if (base_dest == 8) return decimal_divisao_octal(num_dec_str);
    if (base_dest == 16) return decimal_divisao_hexa(num_dec_str);
    return num_dec_str; 
}

// --- SUBPROGRAMA PRINCIPAL DO MODO QUIZ (F9) ---
// AGORA RECEBE UMA STRING PARA EVITAR BUGS DE INPUT (EX: LETRAS DIGITADAS SEM QUERER)
void executar_modo_quiz(string dificuldade_str) {
    
    // Nova validação: Bloqueia caracteres inválidos no menu do quiz
    if (dificuldade_str.length() != 1 || dificuldade_str[0] < '1' || dificuldade_str[0] > '5') {
        cout << "Erro: Nivel de dificuldade invalido. Escolha de 1 a 5." << endl;
        return;
    }

    // Converte a string segura para o número inteiro que a lógica precisa
    int dificuldade = string_para_numero(dificuldade_str);

    srand(time(0)); 
    
    int bases_orig[4], num_bases = 0;
    int max_val = 15;
    bool usar_fracao = false;

    if (dificuldade == 1) {
        bases_orig[0] = 2; bases_orig[1] = 10; 
        num_bases = 2; max_val = 15; 
    } else if (dificuldade == 2) {
        bases_orig[0] = 2; bases_orig[1] = 8; bases_orig[2] = 10; 
        num_bases = 3; max_val = 63;
    } else if (dificuldade == 3) {
        bases_orig[0] = 2; bases_orig[1] = 8; bases_orig[2] = 10; bases_orig[3] = 16; 
        num_bases = 4; max_val = 255;
    } else if (dificuldade == 4) {
        bases_orig[0] = 2; bases_orig[1] = 8; bases_orig[2] = 10; bases_orig[3] = 16; 
        num_bases = 4; max_val = 63; usar_fracao = true; 
    } else { // Nível 5
        bases_orig[0] = 8; bases_orig[1] = 16; 
        num_bases = 2; max_val = 255; usar_fracao = true;
    }

    int idx_orig = rand() % num_bases;
    int idx_dest = rand() % num_bases;
    
    while (idx_orig == idx_dest) {
        idx_dest = rand() % num_bases;
    }

    int base_origem = bases_orig[idx_orig];
    int base_destino = bases_orig[idx_dest];

    int int_part = 1 + (rand() % max_val);
    string fracao_str = "";
    
    if (usar_fracao) {
        string fracoes[5] = {"5", "25", "75", "125", "625"};
        fracao_str = "," + fracoes[rand() % 5];
    }

    string num_dec_str = numero_para_string(int_part) + fracao_str;

    string str_pergunta = converter_decimal_para(num_dec_str, base_origem);
    string str_correta = converter_decimal_para(num_dec_str, base_destino);


    cout << "\n--------------------------------------------------------" << endl;
    cout << "           MODO QUIZ (NIVEL " << dificuldade << ") - QUESTAO ABERTA      " << endl;
    cout << "--------------------------------------------------------\n" << endl;
    
    cout << "PERGUNTA:" << endl;
    cout << "Converta o numero [" << str_pergunta << "] da base " << nome_base(base_origem) 
         << " para a base " << nome_base(base_destino) << "." << endl;
    cout << "---------------------------------------------------------------------" << endl;

    string entrada_usuario;
    cout << "\nDigite o resultado final: ";
    cin >> entrada_usuario;

    // Nova validação: Avisa se o formato da resposta for impossível para a base
    string int_dummy, frac_dummy;
    if (!separar_e_validar(entrada_usuario, int_dummy, frac_dummy, base_destino)) {
        cout << "Aviso: Formato incorreto! Voce digitou caracteres invalidos para a base " << nome_base(base_destino) << "." << endl;
    }

    if (para_maiusculo(entrada_usuario) == str_correta) {
        cout << "\n-> EXCELENTE! Resposta corretíssima!" << endl;
    } else {
        cout << "\n-> INCORRETO!" << endl;
        cout << "O resultado correto era: " << str_correta << endl;
    }
    cout << "--------------------------------------------------------\n" << endl;
}

#endif