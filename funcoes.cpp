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
    if(token + 1 <= cnt){
        token++;
    }
}

// Funções realacionadas ao funcionamento do algoritmo

string Leitor_aritmetico :: exp(int current_token_pos){
    token = current_token_pos;
    return or_exp();
}

string Leitor_aritmetico :: or_exp(){
    string e1;
    e1 = and_exp();
    while(arrPtr[token] == "||"){
        string op = arrPtr[token];
        read_next_token();
        string e2;
        e2 = and_exp();
        string retorno;
        retorno = or_op(e1, e2);
        e1 = retorno;
    }
    return e1;
};

string Leitor_aritmetico :: and_exp(){
    string e1;
    e1 = eq_exp();
    while(arrPtr[token] == "&&"){
        string op = arrPtr[token];
        read_next_token();
        string e2;
        e2 = eq_exp();
        string retorno;
        retorno = and_op(e1, e2);
        e1 = retorno;
    }
    return e1;
};

string Leitor_aritmetico :: eq_exp(){
    string e1;
    e1 = rel_exp();
    while(arrPtr[token] == "==" || arrPtr[token] == "!="){
        string op = arrPtr[token];
        read_next_token();
        string e2;
        e2 = rel_exp();
        string retorno;
        retorno = eq_op(e1, op, e2);
        e1 = retorno;
    }
    return e1;
};

string Leitor_aritmetico :: rel_exp(){
    string e1;
    e1 = add_exp();
    while(arrPtr[token] == "<" || arrPtr[token] == ">" || arrPtr[token] == "<=" || arrPtr[token] == ">="){
        string op = arrPtr[token];
        read_next_token();
        string e2;
        e2 = add_exp();
        string retorno;
        retorno = rel_op(e1, op, e2);
        e1 = retorno;
    }
    return e1;
};

string Leitor_aritmetico :: add_exp(){
    string e1;
    e1 = mul_exp();
    while(arrPtr[token] == "+" || arrPtr[token] == "-"){
        string op = arrPtr[token];
        read_next_token();
        string e2;
        e2 = mul_exp();
        string retorno;
        retorno = add_op(e1, op, e2);
        e1 = retorno;
    }
    return e1;
};

string Leitor_aritmetico :: mul_exp(){
    string e1;
    e1 = unary_exp();
    while(arrPtr[token] == "*" || arrPtr[token] == "/"){
        string op = arrPtr[token];
        read_next_token();
        string e2;
        e2 = unary_exp();
        string retorno;
        retorno = mul_op(e1, op, e2);
        e1 = retorno;
    }
    return e1;
};

string Leitor_aritmetico :: unary_exp(){
    string e1;
    if(arrPtr[token] == "-"){
        while(arrPtr[token] == "-"){
            string op = arrPtr[token];
            read_next_token();
            e1 = primary_exp();
            string retorno;
            retorno = unary_op(e1);
            e1 = retorno;
        }
    }
    else{
        e1 = primary_exp();
    }
    return e1;
    
};

string Leitor_aritmetico :: primary_exp(){
    string e1;
    if(arrPtr[token] == "("){
        while(arrPtr[token][0] != ')'){
            token++;
            e1 = exp(token);
        }
        read_next_token();
    }
    else{
        e1 = literal();
    }
    return e1;
};

string Leitor_aritmetico :: literal(){
    string literal;
    literal = arrPtr[token];
    read_next_token();
    return literal;
};

// Funções das operações
string Leitor_aritmetico :: or_op(const string& e1, const string& e2){
    bool e1_neg = false;
    bool e2_neg = false;
    if(e1[0] == '-' || e2[0] == '-'){
        if(e1[0] == '-'){
            e1_neg = true;
        }
        if(e2[0] == '-'){
            e2_neg = true;
        }
    }
    if(e1_neg || e2_neg || isdigit(e1[0]) || isdigit(e2[0])){
        throw Error("error");
    }
    else{
        if(e1 == "true" || e2 == "true"){
            return "true";
        }
        else{
            return "false";
        }
    }
};

string Leitor_aritmetico :: and_op(const string& e1, const string& e2){
    bool e1_neg = false;
    bool e2_neg = false;
    if(e1[0] == '-' || e2[0] == '-'){
        if(e1[0] == '-'){
            e1_neg = true;
        }
        if(e2[0] == '-'){
            e2_neg = true;
        }
    }
    if(e1_neg || e2_neg || isdigit(e1[0]) || isdigit(e2[0])){
        throw Error("error");
    }
    else{
        if(e1 == "true" && e2 == "true"){
            return "true";
        }
        else{
            return "false";
        }
    }
};

string Leitor_aritmetico :: eq_op(string& e1, const string& op, string& e2){
    bool e1_aritmetico = false;
    bool e1_bool = false;
    bool e2_aritmetico = false;
    bool e2_bool = false;
    if(e1 == "false" || e1 == "true"){
        e1_bool = true;
    }
    else{
        e1_aritmetico = true;
    }
    if(e2 == "true" || e2 == "false"){
        e2_bool = true;
    }
    else{
        e2_aritmetico = true;
    }
    if((e1_aritmetico && e2_bool) || (e1_bool && e2_aritmetico)){
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
    if((e1 == "true" || e1  == "false") || (e2 == "true" || e2 == "false")){
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
    if((e1 == "true" || e1  == "false") || (e2 == "true" || e2 == "false")){
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
    if((e1 == "true" || e1  == "false") || (e2 == "true" || e2 == "false")){
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
            if(b != 0){
                int div = a / b;
                string resultado = to_string(div);
                return resultado;
            }
            else{
                throw Error("error");
            }
        }
    }
}

string Leitor_aritmetico :: unary_op(const string& e1){
    if(e1 == "true" || e1 == "false"){
        throw Error("error");
    }
    else{
        int a = -stoi(e1);
        string resultado = to_string(a);
        return resultado;
    }    
}