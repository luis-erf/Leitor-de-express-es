#include <iomanip>
#include <iostream>
#include <cctype>
#include "classe_base.h"

using namespace std;

// Funções relacionadas aos algoritmos
// Lógica do algoritmo: pegar uma expressão vazia e ir adicionando a ele os termos enquanto eles aparacem baseado no token atual

//1: Funções do leitor aritmético
Leitor_aritmetico :: Leitor_aritmetico(int i){
    cnt = 0;
    tam = i;
    arrPtr = new string[tam];

};

Leitor_aritmetico :: Leitor_aritmetico(int i, string termo){
    tam = cnt = i;
    arrPtr = new string[tam];
    for(int i = 0; i < cnt; ++i){
        arrPtr[i] = termo;
    }
};

Leitor_aritmetico :: ~Leitor_aritmetico(){
    delete[] arrPtr;
};

string& Leitor_aritmetico :: operator[] (int i){
    if( i < 0 || i >= cnt){
        cout << "\n List out of range";
    }
    return arrPtr[i];
};

string Leitor_aritmetico :: operator[] (int i) const{
    if( i < 0 || i >= cnt){
        cout << "\n List out of range";
    }
    return arrPtr[i];
};

bool Leitor_aritmetico :: append(string termo){
    if(cnt < tam){
        arrPtr[cnt++] = termo;
        return true;
    }
    else{
        return false;
    }
};

// Função responsável por analisar os tokens

void Leitor_aritmetico :: read_next_token(){
    if(arrPtr[token].length() > 1){
        if(arrPtr[token][0] == '-'){
            if(token < cnt - 1){
                token++;
            }
        }
    }
    while(isdigit(arrPtr[token][0]) || (arrPtr[token] == "true") || (arrPtr[token] == "false")){
        if(token < cnt - 1){
            token++;
        }
        else{
            break;
        }
    }

}

// Funções realacionadas ao funcionamento do algoritmo

string Leitor_aritmetico :: exp(int current_token_pos, int current_exp_pos){
    token = current_token_pos;
    read_next_token();
    exp_term = current_exp_pos;
    return or_exp(current_token_pos, current_exp_pos);
}

string Leitor_aritmetico :: or_exp(int current_token_pos, int current_exp_pos){
    string e1;
    e1 = and_exp(current_token_pos, current_exp_pos);
    while(arrPtr[token] == "||"){
        string op = arrPtr[token];
        token++;
        read_next_token();
        string e2;
        e2 = and_exp(current_token_pos, current_exp_pos);
        string retorno;
        retorno = or_op(e1, op, e2);
        e1 = retorno;
    }
    return e1;
};

string Leitor_aritmetico :: and_exp(int current_token_pos, int current_exp_pos){
    string e1;
    e1 = eq_exp(current_token_pos, current_exp_pos);
    while(arrPtr[token] == "&&"){
        string op = arrPtr[token];
        token++;
        read_next_token();
        string e2;
        e2 = eq_exp(current_token_pos, current_exp_pos);
        string retorno;
        retorno = and_op(e1, op, e2);
        e1 = retorno;
    }
    return e1;
};

string Leitor_aritmetico :: eq_exp(int current_token_pos, int current_exp_pos){
    string e1;
    e1 = rel_exp(current_token_pos, current_exp_pos);
    while(arrPtr[token] == "==" || arrPtr[token] == "!="){
        string op = arrPtr[token];
        token++;
        read_next_token();
        string e2;
        e2 = rel_exp(current_token_pos, current_exp_pos);
        string retorno;
        retorno = eq_op(e1, op, e2);
        e1 = retorno;
    }
    return e1;
};

string Leitor_aritmetico :: rel_exp(int current_token_pos, int current_exp_pos){
    string e1;
    e1 = add_exp(current_token_pos, current_exp_pos);
    while(arrPtr[token] == "<" || arrPtr[token] == ">" || arrPtr[token] == "<=" || arrPtr[token] == ">="){
        string op = arrPtr[token];
        token++;
        read_next_token();
        string e2;
        e2 = add_exp(current_token_pos, current_exp_pos);
        string retorno;
        retorno = rel_op(e1, op, e2);
        e1 = retorno;
    }
    return e1;
};

string Leitor_aritmetico :: add_exp(int current_token_pos, int current_exp_pos){
    string e1;
    e1 = mul_exp(current_token_pos, current_exp_pos);
    while(arrPtr[token] == "+" || arrPtr[token] == "-"){
        string op = arrPtr[token];
        token++;
        read_next_token();
        string e2;
        e2 = mul_exp(current_token_pos, current_exp_pos);
        string retorno;
        retorno = add_op(e1, op, e2);
        e1 = retorno;
    }
    return e1;
};

string Leitor_aritmetico :: mul_exp(int current_token_pos, int current_exp_pos){
    string e1;
    e1 = unary_exp(current_token_pos, current_exp_pos);
    while(arrPtr[token] == "*" || arrPtr[token] == "/"){
        string op = arrPtr[token];
        token++;
        read_next_token();
        string e2;
        e2 = unary_exp(current_token_pos, current_exp_pos);
        string retorno;
        retorno = mul_op(e1, op, e2);
        e1 = retorno;
    }
    return e1;
};

string Leitor_aritmetico :: unary_exp(int current_token_pos, int current_exp_pos){
    string e1;
    if(arrPtr[token] == "-" && !isdigit(arrPtr[token - 1][0])){
        while(arrPtr[token] == "-" && !isdigit(arrPtr[token - 1][0])){
            string op = arrPtr[token];
            token++;
            read_next_token();
            e1 = primary_exp(current_token_pos, current_exp_pos);
            string retorno;
            retorno = unary_op(e1, op);
            e1 = retorno;
        }
    }
    else{
        e1 = primary_exp(current_token_pos, current_exp_pos);
    }
    return e1;
    
};

string Leitor_aritmetico :: primary_exp(int current_token_pos, int current_exp_pos){
    string e1;
    if(arrPtr[token] == "("){
        while(arrPtr[token][0] != ')'){
            token++;
            e1 = exp(token, exp_term);
        }
        if(token + 1 < cnt){
            token++;
            read_next_token();
        }
    }
    else{
        e1 = literal(current_token_pos, current_exp_pos);
    }
    return e1;
};

string Leitor_aritmetico :: literal(int current_token_pos, int current_exp_pos){
    string literal;
    while(!isdigit(arrPtr[exp_term][0])){
        if(arrPtr[exp_term].length() > 1 && arrPtr[exp_term][0] == '-'){
            literal = arrPtr[exp_term];
            exp_term++;
            return literal;
        }
        else if((arrPtr[exp_term][0] == 't') || (arrPtr[exp_term][0] == 'f')){
            literal = arrPtr[exp_term];
            exp_term++;
            return literal;
        }
        else{
            exp_term++;
        }
    }
    literal = arrPtr[exp_term];
    exp_term++;
    return literal;
};

// Funções das operações
string Leitor_aritmetico :: or_op(const string& e1, const string& op, const string& e2){
    if(isdigit(e1[0]) || isdigit(e2[0])){
        throw Error("error");
    }
    else{
        if(e1[0] == 't' || e2[0] == 't'){
            return "true";
        }
        else{
            return "false";
        }
    }
};

string Leitor_aritmetico :: and_op(const string& e1, const string& op, const string& e2){
    if(isdigit(e1[0]) || isdigit(e2[0])){
        throw Error("error");
    }
    else{
        if(e1[0] == 't' && e2[0] == 't'){
            return "true";
        }
        else{
            return "false";
        }
    }
};

string Leitor_aritmetico :: eq_op(const string& e1, const string& op, const string& e2){
    if((isdigit(e1[0]) && !isdigit(e2[0])) || (!isdigit(e1[0]) && isdigit(e2[0]))){
        throw Error("error");
    }
    else{
        if(op == "=="){
            if(e1 == e2){
                return "true";
            }
            else{
                return "false";
            }
        }
        else{
            if(e1 != e2){
                return "true";
            }
            else{
                return "false";
            }
        }
    }
};

string Leitor_aritmetico :: rel_op(const string& e1, const string& op, const string& e2){
    if(!isdigit(e1[0]) || !isdigit(e2[0])){
        throw Error("error");
    }
    else{
        if(op == "<"){
            if(e1 < e2){
                return "true";
            }
            else{
                return "false";
            }
        }
        else if(op == ">"){
            if(e1 > e2){
                return "true";
            }
            else{
                return "false";
            }
        }
        else if(op == "<="){
            if(e1 <= e2){
                return "true";
            }
            else{
                return "false";
            }
        }
        else{
            if(e1 >= e2){
                return "true";
            }
            else{
                return "false";
            }
        }
    }
};

string Leitor_aritmetico :: add_op(const string& e1, const string& op, const string& e2){
    if(!isdigit(e1[0]) || !isdigit(e2[0])){
        throw Error("error");
    }
    else{
        int a = stoi(e1);
        int b = stoi(e2);
        if(op == "+"){
            int soma = a + b;
            string resultado = to_string(soma);
            return resultado;
        }
        else{
            int sub = a - b;
            string resultado = to_string(sub);
            return resultado;
        }
    }
}

string Leitor_aritmetico :: mul_op(const string& e1, const string& op, const string& e2){
    if(!isdigit(e1[0]) || !isdigit(e2[0])){
        throw Error("error");
    }
    else{
        int a = stoi(e1);
        int b = stoi(e2);
        if(op == "*"){
            int mul = a * b;
            string resultado = to_string(mul);
            return resultado;
        }
        else{
            int div = a / b;
            string resultado = to_string(div);
            return resultado;
        }
    }
}

string Leitor_aritmetico :: unary_op(const string& e1, const string& op){
    if(!isdigit(e1[1])){
        throw Error("error");
    }
    else{
        int a = -stoi(e1);
        string resultado = to_string(a);
        return resultado;
    }    
}