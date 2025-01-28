#include <string>

using namespace std;

/*Lógica das classes:
1: Primeiro fazer uma classe responsável por ordenar os elementos da expressão em uma array para poder facilitar o manuseio da expressão => Array dinâmico
*Correção => O array não será uma classe e sim uma função das duas classes de leitura de expressões
2: Classe abstrata da leitura das expressões, contendo o algoritmo de recursão
2.1: Uma classe derivada será responsável por ler expressões aritméticas, ou seja, as funções que possuem tokens booleanos serão onde os erros serão reconhecidos
e serão acrescentadas funções contendo as operações aritméticas
2.2: Outra classe derivada será responsável por ler as expressões booleanas, com as mesmas especificações da aritmética só que voltada para expressões boolenas*/

//Classe abstrata
//class Classe_base{
//    
//    private:
//        string* arrPtr;
//        int tamanho;
//        int cnt;
//    public:
//        Classe_base(int n = 256);
//        Classe_base(int i, string termo);
//        virtual ~Classe_base();
//        virtual string& operator[] (int i);
//        virtual string operator[] (int i) const;
//        virtual bool append(string termo);
//        
//        //Funções do algoritmo recursivo
//        virtual string exp() = 0;
//        virtual string or_exp() = 0;
//        virtual string and_exp();
//        virtual string eq_exp();
//        virtual string rel_exp();
//        virtual string add_exp();
//        virtual string mul_exp();
//        virtual string unary_exp();
//        virtual string primary_exp();
//        virtual string literal();
//};

class Leitor_aritmetico{
    
    private:
        string* arrPtr;
        int token;
        int exp_term;
        int tam;
        int cnt;

    public:
        Leitor_aritmetico(int n = 256);
        Leitor_aritmetico(int i, string termo);
        ~Leitor_aritmetico();
        string& operator[] (int i);
        string operator[] (int i) const;
        bool append(string termo);

        //Funções do algoritmo recursivo
        string exp(int current_token_pos, int current_exp_pos);
        string or_exp(int current_token_pos, int current_exp_pos);
        string and_exp(int current_token_pos, int current_exp_pos);
        string eq_exp(int current_token_pos, int current_exp_pos);
        string rel_exp(int current_token_pos, int current_exp_pos);
        string add_exp(int current_token_pos, int current_exp_pos);
        string mul_exp(int current_token_pos, int current_exp_pos);
        string unary_exp(int current_token_pos, int current_exp_pos);
        string primary_exp(int current_token_pos, int current_exp_pos);
        string literal(int current_token_pos, int current_exp_pos);

        // Função para analisar o próximo token
        void read_next_token();

        // Funções responsáveis por realizar as operações baseadas nos tokens analisados
        string or_op(const string& e1, const string& op, const string& e2);
        string and_op(const string& e1, const string& op, const string& e2);
        string eq_op(const string& e1, const string& op, const string& e2);
        string rel_op(const string& e1, const string& op, const string& e2);
        string add_op(const string& e1, const string& op, const string& e2);
        string mul_op(const string& e1, const string& op, const string& e2);
        string unary_op(const string& e1, const string& op);
        string priamary_op();
};

class Error{
    private:
        string exp;
    
    public:
        Error(const string& base) : exp(base) {}
        const string& output() const {return exp;}
};