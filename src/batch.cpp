#ifndef BATCH_CPP
#define BATCH_CPP

#include <iostream>
#include <fstream>
#include <string>
#include "padrao.cpp"

using namespace std;

// --- FUNÇÃO AUXILIAR DE REDIRECIONAMENTO ---
string realizar_conversao_lote(string n, int base_orig, int base_dest) {
    if (base_orig == 10) {
        if (base_dest == 2) return decimal_divisao_binario(n);
        else if (base_dest == 8) return decimal_divisao_octal(n);
        else if (base_dest == 16) return decimal_divisao_hexa(n);
    }
    else if (base_dest == 10) {
        if (base_orig == 2) return binario_somatorio_decimal(n);
        else if (base_orig == 8) return octal_somatorio_decimal(n);
        else if (base_orig == 16) return hexa_somatorio_decimal(n);
    }
    else if (base_orig == 2) {
        if (base_dest == 8) return binario_agrupamento_octal(n);
        else if (base_dest == 16) return binario_agrupamento_hexa(n);
    }
    else if (base_dest == 2) {
        if (base_orig == 8) return octal_agrupamento_binario(n);
        else if (base_orig == 16) return hexa_agrupamento_binario(n);
    }
    else {
        if (base_orig == 8 && base_dest == 16) return octal_hexa(n);
        else if (base_orig == 16 && base_dest == 8) return hexa_octal(n);
    }
    return "Erro";
}

// --- SUBPROGRAMA PRINCIPAL DO MODO BATCH (F8) ---
void executar_modo_batch() {
    
    string nome_arquivo_entrada = "entrada.csv";
    string nome_arquivo_saida = "saida.csv";

    ifstream arquivo_in(nome_arquivo_entrada.c_str());
    if (!arquivo_in.is_open()) {
        cout << "Erro: Nao foi possivel abrir o arquivo '" << nome_arquivo_entrada << "'." << endl;
        cout << "Certifique-se de que ele existe na mesma pasta do seu programa." << endl;
        return;
    }

    ofstream arquivo_out(nome_arquivo_saida.c_str());
    if (!arquivo_out.is_open()) {
        cout << "Erro: Nao foi possivel criar o arquivo '" << nome_arquivo_saida << "'." << endl;
        arquivo_in.close();
        return;
    }

    cout << "\n--------------------------------------------------------" << endl;
    cout << "                MODO BATCH DE CONVERSAO (F8)            " << endl;
    cout << " Lendo arquivo: " << nome_arquivo_entrada << endl;
    cout << " Gerando arquivo de saida: " << nome_arquivo_saida << endl;
    cout << " Formato gravado: valor;base_origem;resultado;base_destino" << endl;
    cout << "--------------------------------------------------------\n" << endl;

    string token = "";
    string valor = "";
    int base_orig = 0;
    int base_dest = 0;
    int conta_ponto_virgula = 0;
    
    char c;
    while (arquivo_in.get(c)) {
        if (c == ';' || c == '\n' || c == '\r') {
            
            if (conta_ponto_virgula == 0) {
                valor = token;
            } else if (conta_ponto_virgula == 1) {
                base_orig = (int)string_para_numero(token);
            } else if (conta_ponto_virgula == 2 && token != "") {
                base_dest = (int)string_para_numero(token);
            }
            
            token = ""; 
            
            if (c == ';') {
                conta_ponto_virgula++;
            }
            
            if (c == '\n' || c == '\r') {
                if (valor != "" && base_orig != 0 && base_dest != 0) {
            string resultado;
            string int_dummy, frac_dummy;
            
            // Início da validação de erro para o Batch (F5 + F8)
            if (!separar_e_validar(valor, int_dummy, frac_dummy, base_orig)) {
                resultado = "Erro: Entrada invalida para a base de origem";
            } else {
                resultado = realizar_conversao_lote(valor, base_orig, base_dest);
            }
            
            arquivo_out << valor << ";" << base_orig << ";" << resultado << ";" << base_dest << "\n";
            
            cout << " Processado: " << valor << " -> " << resultado << endl;
        }
                valor = ""; base_orig = 0; base_dest = 0; conta_ponto_virgula = 0;
            }
        } 
        else {
            if (c != ' ' && c != '"') { 
                token += c;
            }
        }
    }

    // Tratamento para a última linha caso termine sem quebra de linha
    if (valor != "" || token != "") {
        if (conta_ponto_virgula == 2 && token != "") {
            base_dest = (int)string_para_numero(token);
        }
        if (valor != "" && base_orig != 0 && base_dest != 0) {
            string resultado;
            string int_dummy, frac_dummy;
            
            // Início da validação de erro para o Batch (F5 + F8)
            if (!separar_e_validar(valor, int_dummy, frac_dummy, base_orig)) {
                resultado = "Erro: Entrada invalida para a base de origem";
            } else {
                resultado = realizar_conversao_lote(valor, base_orig, base_dest);
            }
            
            arquivo_out << valor << ";" << base_orig << ";" << resultado << ";" << base_dest << "\n";
            
            cout << " Processado: " << valor << " -> " << resultado << endl;
        }
    }

    arquivo_in.close();
    arquivo_out.close();
    
    cout << "\n -> Tudo certo! Arquivo '" << nome_arquivo_saida << "' gerado com a formatacao completa." << endl;
    cout << "--------------------------------------------------------\n" << endl;
}

#endif