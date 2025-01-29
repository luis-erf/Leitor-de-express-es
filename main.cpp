#include <iostream>
#include <string>
#include <iomanip>
#include "funcoes.cpp"

using namespace std;

/*Lógica que eu pretendo usar:
1: Receber a string com a expressão
2: Gerar uma árvore infixa de precedência
3: Analisar essa árvore baseado no algoritmo fornecido
*/

/*Problema principal: encontrar onde serão encaixadas as classes
No algoritmo você lê os tokens para saber como seguir na recursão, então essa leitura pode ser feita a partir das seguintes lógicas:
1: Pode-se separar os operadores e operandos em duas pilhas e ir analisando elas em conjunto,
nesse caso cada classe serveria para direcionar cada termo para suas respectivas pilhas
2: Analisar diretamente como se estivesse resolvendo a equação seguindo a ordem da árvore da esquerda para direita,
nesse caso as classes deveriam ter um parâmetro que retornasse o resultado atual, ou as classes poderiam ser chamadas
e os resultados serem fornecidos ao longo da análise da árvore*/

int main(){

// Guardar os casos a serem analisados
int qnt;
cin >> qnt;
cin.ignore();
string exp;
string resultados[qnt];
for(int i = 0; i < qnt; i++){
    getline(cin, exp);  
    string base = "";
    int pos = 0;
    int tamanho = 1;
    while(pos < exp.length()){
        if(exp[pos] == ' '){
            tamanho++;
        }
        pos++;
    }
    Leitor_aritmetico expressao(tamanho);
    for(int j = 0; j <= exp.length() + 1; j++){
        if(exp[j] != ' ' && j < exp.length()){
            base += exp[j];
        }
        else{
            expressao.append(base);
            base = "";
        }
    }
    string resultado;
    try{
        resultados[i] = expressao.exp(0);
        
    }
    catch(Error& output){
        resultados[i] = "error";
    }
}

for(int k = 0; k < qnt; k++){
    cout << resultados[k] << endl;
}

return 0;
}


