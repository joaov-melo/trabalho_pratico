#include <iostream>
#include <string>
#include "padrao.cpp"
#include "maximos.cpp"
#include "passo_a_passo.cpp"
#include "batch.cpp"
#include "quiz.cpp"



using namespace std;
// Função para validar as entradas de acordo com o requisito F5 e F6
bool valida_entrada(string n, int origem) {
    for (char c : n) {
        // Permite separadores de frações (Requisito F6)
        if (c == '.' || c == ',') continue; 
        
        if (origem == 1) { // Decimal
            if (c < '0' || c > '9') return false;
        } else if (origem == 2) { // Binário
            if (c != '0' && c != '1') return false;
        } else if (origem == 3) { // Octal
            if (c < '0' || c > '7') return false;
        } else if (origem == 4) { // Hexadecimal
            if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))) return false;
        }
    }
    return true;
}

int main(){
	bool ativo = true;
	while (ativo){
	cout<<"Digite 1 para modo padrão de conversão;"<<endl;
	cout<<"Digite 2 para modo passo a passo de conversão;"<<endl;
	cout<<"Digite 3 para modo batch de conversão;"<<endl;
	cout<<"Digite 4 para modo quiz;"<<endl;
	cout<<"Digite 5 para modo calculadora de máximos;"<<endl;
	cout<<"Digite 6 para sair."<<endl;
	int entrada;
	int origem,destino;
	string n;
	cin>>entrada;
	switch (entrada){
		case 1:
			cout<<"Escolha sua base de origem:"<<endl;
			cout<<"Digite 1 para decimal;"<<endl;
			cout<<"Digite 2 para binário;"<<endl;
			cout<<"Digite 3 para octal;"<<endl;
			cout<<"Digite 4 para hexadecimal."<<endl;
			cin>>origem;
			cout<<"Escolha sua base destino:"<<endl;
			if(origem==1){
				cout<<"Digite 1 para binário;"<<endl;
				cout<<"Digite 2 para octal;"<<endl;
				cout<<"Digite 3 para hexadecimal;"<<endl;
			}
			else if (origem==2){
				cout<<"Digite 1 para decimal;"<<endl;
				cout<<"Digite 2 para octal;"<<endl;
				cout<<"Digite 3 para hexadecimal;"<<endl;
			}
			else if (origem==3){
				cout<<"Digite 1 para decimal;"<<endl;
				cout<<"Digite 2 para binário;"<<endl;
				cout<<"Digite 3 para hexadecimal;"<<endl;
			}
			else if (origem==4){
				cout<<"Digite 1 para decimal;"<<endl;
				cout<<"Digite 2 para binário;"<<endl;
				cout<<"Digite 3 para octal;"<<endl;
			}
			else {
				cout<<"Erro, digite caracteres válidos.";
				break;
			}
			cin>>destino;
			cout<<"Qual número você quer converter?"<<endl;
			cin>>n;
			
			// Início da Validação (F5)
			if (!valida_entrada(n, origem)) {
				if (origem == 1) cout << "Erro: Entrada invalida. A base decimal aceita apenas digitos de 0 a 9." << endl;
				else if (origem == 2) cout << "Erro: Entrada invalida. A base binaria aceita apenas os digitos 0 e 1." << endl;
				else if (origem == 3) cout << "Erro: Entrada invalida. A base octal nao aceita digitos como 8 ou 9." << endl;
				else if (origem == 4) cout << "Erro: Entrada invalida. A base hexadecimal aceita apenas digitos de 0-9 e letras A-F." << endl;
				break;
			}
			// Fim da Validação
			
			cout<<"O número convertido é: ";
			if(origem==1 and destino==1) cout<<decimal_divisao_binario(n)<<endl;
			else if(origem==1 and destino==2) cout<<decimal_divisao_octal(n)<<endl;
			else if(origem==1 and destino==3) cout<<decimal_divisao_hexa(n)<<endl;
			else if(origem==2 and destino==1) cout<<binario_somatorio_decimal(n)<<endl;
			else if(origem==2 and destino==2) cout<<binario_agrupamento_octal(n)<<endl;
			else if(origem==2 and destino==3) cout<<binario_agrupamento_hexa(n)<<endl;
			else if(origem==3 and destino==1) cout<<octal_somatorio_decimal(n)<<endl;
			else if(origem==3 and destino==2) cout<<octal_agrupamento_binario(n)<<endl;
			else if(origem==3 and destino==3) cout<<octal_hexa(n)<<endl;
			else if(origem==4 and destino==1) cout<<hexa_somatorio_decimal(n)<<endl;
			else if(origem==4 and destino==2) cout<<hexa_agrupamento_binario(n)<<endl;
			else if(origem==4 and destino==3) cout<<hexa_octal(n)<<endl;
			else cout<<"Erro, caracteres inválidos."<<endl;
			break;
	
		case 2:
			cout<<"Escolha sua base de origem:"<<endl;
			cout<<"Digite 1 para decimal;"<<endl;
			cout<<"Digite 2 para binário;"<<endl;
			cout<<"Digite 3 para octal;"<<endl;
			cout<<"Digite 4 para hexadecimal."<<endl;
			cin>>origem;
			cout<<"Escolha sua base destino:"<<endl;
			if(origem==1){
				cout<<"Digite 1 para binário;"<<endl;
				cout<<"Digite 2 para octal;"<<endl;
				cout<<"Digite 3 para hexadecimal;"<<endl;
			}
			else if (origem==2){
				cout<<"Digite 1 para decimal;"<<endl;
				cout<<"Digite 2 para octal;"<<endl;
				cout<<"Digite 3 para hexadecimal;"<<endl;
			}
			else if (origem==3){
				cout<<"Digite 1 para decimal;"<<endl;
				cout<<"Digite 2 para binário;"<<endl;
				cout<<"Digite 3 para hexadecimal;"<<endl;
			}
			else if (origem==4){
				cout<<"Digite 1 para decimal;"<<endl;
				cout<<"Digite 2 para binário;"<<endl;
				cout<<"Digite 3 para octal;"<<endl;
			}
			else {
				cout<<"Erro, digite caracteres válidos.";
				break;
			}
			cin>>destino;
			cout<<"Qual número você quer converter?"<<endl;
			cin>>n;
			
			// Início da Validação (F5)
			if (!valida_entrada(n, origem)) {
				if (origem == 1) cout << "Erro: Entrada invalida. A base decimal aceita apenas digitos de 0 a 9." << endl;
				else if (origem == 2) cout << "Erro: Entrada invalida. A base binaria aceita apenas os digitos 0 e 1." << endl;
				else if (origem == 3) cout << "Erro: Entrada invalida. A base octal nao aceita digitos como 8 ou 9." << endl;
				else if (origem == 4) cout << "Erro: Entrada invalida. A base hexadecimal aceita apenas digitos de 0-9 e letras A-F." << endl;
				break;
			}
			// Fim da Validação
			
			executar_modo_passo_a_passo(origem, destino, n);
			break;
		case 3:
			executar_modo_batch(); 
			break;
		case 4:
			cout << "-------------------------------------------------------------------------" << endl;
			cout << "          Bem-vindo ao Quiz! Escolha o nivel de dificuldade:             " << endl;
			cout << "-------------------------------------------------------------------------" << endl;
			cout << "1 - Muito Facil   (Apenas numeros inteiros pequenos entre Decimal e Binario)" << endl;
			cout << "2 - Facil         (Numeros inteiros maiores, expandindo os testes para a base Octal)" << endl;
			cout << "3 - Normal        (Mistura completa de numeros inteiros cobrindo Decimal, Binario, Octal e Hexa)" << endl;
			cout << "4 - Dificil       (Introducao de numeros fracionarios em bases aleatorias, exigindo calculo com virgula)" << endl;
			cout << "5 - Muito Dificil (O desafio maximo: conversoes diretas e fracionarias apenas entre Octal e Hexa)" << endl;
			cout << "-------------------------------------------------------------------------" << endl;
			{
				cin >> n;
				
				// Avalia o valor real da string digitada
				int valor_dif = string_para_numero(n);
				
				if(valor_dif >= 1 && valor_dif <= 5) {
					// Passa a string para o quiz
					executar_modo_quiz(n);
				} else {
					cout << "Dificuldade invalida! Regressando ao menu." << endl;
				}
			}
			break;
		case 5:
			cout<<"Digite o número de bits desejado: "<<endl;
			cin>>n;
			executar_calculadora_maximos(n);
			break;
		case 6: 
			ativo = false;
			cout<<"Saindo do sistema"<<endl;
			break;
	}	
		}	
return 0;
}

