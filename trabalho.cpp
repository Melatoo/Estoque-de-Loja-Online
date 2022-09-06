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

void checaProduto (produtos produto, bool &existe) {
    //checar se o codigo do produto ja existe
    ifstream arquivo;
    arquivo.open("produtos.bin");
    string linha;
    while (getline(arquivo, linha)) {
        if (linha == produto.codigo) {
            existe = true;
            cout << "Produto já cadastrado!" << endl;
            break;
        }
    }
    arquivo.close();
}

void exportarProduto(produtos produto) {
    //exportar em binario
    ofstream arquivo;
    arquivo.open("produtos.bin", ios::binary | ios::app);
    arquivo.write((char*)&produto, sizeof(produto));
    arquivo.close();
}

void consultarProduto (produtos produto) {
    //consultar um produto pelo codigo
    ifstream arquivo;
    arquivo.open("produtos.bin", ios::binary);
    while (arquivo.read((char*)&produto, sizeof(produto))) {
        if (produto.codigo == produto.codigo) {
            cout << "Código: " << produto.codigo << endl;
            cout << "Quantidade: " << produto.quantidadeDisp << endl;
            cout << "Quantidade vendida: " << produto.quantidadeVendida << endl;
            cout << "Situação: " << produto.situacao << endl;
        }
    }
    arquivo.close();
}

int main () {
    //menu da loja
    int opcao;
    produtos produto;
    bool existe = false;
    cout << "1 - Cadastrar produto" << endl;
    cout << "2 - Consultar produtos" << endl;
    cout << "3 - Listar produtos cadastrados disponíveis ordenados pelo código do produto" << endl;
    cout << "4 - Excluir produto" << endl;
    cout << "5 - Efetuar uma venda" << endl;
    cout << "6 - Listar dados de produtos ativos em estoque" << endl;
    cout << "7 - Exportar dados de produtos ativos" << endl;
    cout << "8 - Sair" << endl;
    cout << "Opção: ";
    cin >> opcao;
    cin.ignore();
    switch (opcao) {
        case 1:
        checaProduto(produto, existe);
            if (existe == false) 
                cadastrarProduto (produto);
            else 
                existe = false;
            break;
        case 2:
            consultarProduto (produto);
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            exportarProduto(produto);
            break;
        case 8:
            cout << "Encerrando sistema..." << endl;
            break;
        default:
            cout << "Opção inválida" << endl;
            break;
    }
    return 0;
}
