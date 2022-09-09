#include <string>
#include <iostream>
#include <fstream>

using namespace std;

struct fornecedores {
    string nome;
    string email;
    string telefone;
};

struct produtos {
    string descricao;
    string codigo;
    int quantidadeDisp;
    int quantidadeVendida;
    string valor;
    fornecedores fornecedor;
    string situacao;
};

void cadastrarProduto (produtos &produto) {
    //preencher os dados do produto
    cout << "Descrição: ";
    getline (cin, produto.descricao);
    cout << "Código: ";
    getline (cin, produto.codigo);
    cout << "Quantidade: ";
    cin >> produto.quantidadeDisp;
    cout << "Valor: ";
    getline (cin, produto.valor);
    cout << "Fornecedor" << endl << "Nome: ";
    getline (cin, produto.fornecedor.nome);
    cout << "Email: ";
    getline (cin, produto.fornecedor.email);
    cout << "Telefone: ";
    getline (cin, produto.fornecedor.telefone);
    produto.situacao = "ativo";
    cout << "Produto cadastrado com sucesso!" << endl;
}

void aumentaVetor (produtos *&vetor, int &tamanho) {
    produtos *aux = new produtos[tamanho + 3];
    for (int i = 0; i < tamanho; i++) {
        aux[i] = vetor[i];
    }
    delete [] vetor;
    vetor = aux;
    tamanho += 3;
}

void exportarProduto(produtos produto[], int tam) {
    //exportar em binario
    ofstream arquivo;
    arquivo.open("produtos.dat");
    if (arquivo.is_open()) {
        arquivo.write((char *)&produto, tam*sizeof(produtos));
    }
    //ler o arquivo
    ifstream arquivo2;
    arquivo2.open("produtos.dat");
    if (arquivo2.is_open()) {
        arquivo2.read((char *)&produto, tam*sizeof(produtos));
    }
    arquivo.close();
    arquivo2.close();
}

int main () {
    //quero abrir o arquivo binario produtos.bin e ler os dados e mostrar na tela
    ifstream arquivo;
    arquivo.open("produtos.bin");
    produtos checagem;
    if (arquivo.is_open()) {
        while (arquivo.read((char*)&checagem, sizeof(produtos))) {
            for (int i = 0; i < 3; i++) {
                cout << checagem.descricao << endl;
                cout << checagem.codigo << endl;
                cout << checagem.quantidadeDisp << endl;
                cout << checagem.valor << endl;
                cout << checagem.fornecedor.nome << endl;
                cout << checagem.fornecedor.email << endl;
                cout << checagem.fornecedor.telefone << endl;
                cout << checagem.situacao << endl;
            }
        }
    }
    arquivo.close();
    return 0;
}