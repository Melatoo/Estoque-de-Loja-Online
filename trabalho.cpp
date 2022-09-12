#include <cstring>
#include <iostream>
#include <fstream>
#include <string>

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

int menu () {
    //menu do programa
    int opcao;
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
    return opcao;
}

produtos *aumentaVetor (produtos *produto, int &tamanho) {
    //função que aumenta o vetor produto em 3
    produtos *aux = new produtos[tamanho+3];
    for (int i = 0; i < tamanho; i++) 
        aux[i] = produto[i];
    delete [] produto;
    produto = aux;
    tamanho += 3;
    return produto;
}

bool checaProduto (string codigo, produtos produto[], int tam) {
    //função que checa se o codigo do produto já existe no vetor produto
    for (int i = 0; i < tam; i++) {
        if (codigo == produto[i].codigo) 
            return true;
    }
    return false;
}

void cadastrarProduto (produtos produto[], int p, int tam) {
    //função que preenche os dados do produto
    string codigo;
    cout << "Descrição: ";
    getline (cin, produto[p].descricao);
    cout << "Código: ";
    getline (cin, codigo);
    //checa se o codigo já existe
    if (checaProduto (codigo, produto, tam) == false) {
        produto[p].codigo = codigo;
        produto[p].quantidadeVendida = 0;
        cout << "Quantidade disponível: ";
        cin >> produto[p].quantidadeDisp;
        cin.ignore();
        cout << "Valor: ";
        getline (cin, produto[p].valor);
        cout << "Fornecedor" << endl << "Nome: ";
        getline (cin, produto[p].fornecedor.nome);
        cout << "Email: ";
        getline (cin, produto[p].fornecedor.email);
        cout << "Telefone: ";
        getline (cin, produto[p].fornecedor.telefone);
        produto[p].situacao = "ativo";
        produto[p].quantidadeVendida = 0;
        cout << "Produto cadastrado com sucesso!" << endl;
        
    }
    //caso o codigo do produto já exista, o produto não é cadastrado
    else
        cout << "Produto já cadastrado!" << endl; 
}

void quickSort (produtos produto[], int inicio, int fim) {
    //função que ordena o vetor produto pelo código do produto, usando o método quick sort
    int i = inicio;
    int j = fim;
    //define o pivô
    string pivo = produto[(inicio + fim) / 2].codigo;
    while (i <= j) {
        //encontra o primeiro elemento menor que o pivô
        while (produto[i].codigo < pivo && i < fim) 
            i++;
        //encontra o primeiro elemento maior que o pivô
        while (produto[j].codigo > pivo && j > inicio) 
            j--;
        //troca os elementos
        if (i <= j) {
            produtos aux = produto[i];
            produto[i] = produto[j];
            produto[j] = aux;
            i++;
            j--;
        }
    //chama a função novamente para ordenar as duas metades
    }
    if (j > inicio) 
        quickSort (produto, inicio, j);
    if (i < fim) 
        quickSort (produto, i, fim);
}

void consultarProduto (produtos produto[], int tam) {
    //função que consulta um produto pelo código
    string c;
    cout << "Código: ";
    getline (cin, c);
    int p=-1, pi=0, pf=tam-1;
    int meio;
    //busca binária
    while (pi <= pf){
		meio = (pi + pf)/2;
		if (c == produto[meio].codigo){
			p = meio;
			pi = pf + 1;
		}
		else{
			if (c > produto[meio].codigo)
				pi = meio + 1;
			else
				pf = meio - 1;
		}
	}
	if (p == -1){
		cout << "Produto não encontrado!" <<endl;
	}
	else {
		cout << "Quantidade disponível: " << produto[p].quantidadeDisp << endl;
        cout << "Quantidade vendida: " << produto[p].quantidadeVendida << endl;
		cout << "Situação: " << produto[p].situacao << endl;
	}
		
}

void listarProdutosDisponiveis (produtos produto[], int tam) {
    //função que lista os produtos disponíveis ordenados pelo código do produto
    //chama a função quickSort para ordenar o vetor produto
    quickSort (produto, 0, tam-1);
    for (int i = 0; i < tam; i++) {
        //se o produto estiver disponível(ter pelo menos 1 produto para vender), ele é listado
        if (produto[i].quantidadeDisp > 0) {
            cout << "Descrição: " << produto[i].descricao << endl;
            cout << "Código: " << produto[i].codigo << endl;
            cout << "Fornecedor" << endl << "Nome: " << produto[i].fornecedor.nome << endl;
            cout << "Email: " << produto[i].fornecedor.email << endl;
            cout << "Situação: " << produto[i].situacao << endl;
        }
    }
}

void excluirProduto (produtos produto[], int tam) {
    //função que exclui um produto pela exclusão lógica
    string codigo;
    cout << "Código do produto: ";
    getline (cin, codigo);
    for (int i = 0; i < tam; i++) {
        if (codigo == produto[i].codigo) {
            cout << produto[i].descricao << endl << "Deseja realmente excluir o produto? 1-sim 2-nao" << endl;
            int opcao;
            cin >> opcao;
            cin.ignore();
            if (opcao == 1) {
                produto[i].situacao = "inativo";
                cout << "Produto excluído com sucesso!" << endl;
            }
            else
                cout << "Produto não excluído!" << endl;
        }
    }
    //os produtos excluídos não são removidos do vetor, apenas a situação que é alterada para inativo
}

void vendaProduto (produtos produto[], int tam) {
    //função que realiza uma venda
    string codigo;
    int quantidade;
    cout << "Código do produto: ";
    getline (cin, codigo);
    for (int i = 0; i < tam; i++) {
        if (codigo == produto[i].codigo) {
            cout << "Quantidade: ";
            cin >> quantidade;
            cin.ignore();
            //se a quantidade que o usuário quer vender for maior que a quantidade disponível, a venda não é realizada
            if (quantidade <= produto[i].quantidadeDisp) {
                produto[i].quantidadeDisp -= quantidade;
                produto[i].quantidadeVendida += quantidade;
                cout << "Quantidade vendida: " << produto[i].quantidadeVendida << endl;
                cout << "Quantidade disponível: " << produto[i].quantidadeDisp << endl;
                cout << "Venda realizada com sucesso!" << endl;
            }
            else
                cout << "Quantidade indisponível!" << endl;
        }
    }
}

void listarProdutosAtivos (produtos produto[], int tam) {
    //função que lista os produtos cadastrados ordenados em quick sort se eles estiverem ativos
    //chama a função quickSort para ordenar o vetor produto
    quickSort (produto, 0, tam - 1);
    // imprime os produtos ativos
    for (int i = 0; i < tam; i++) {
        if (produto[i].situacao == "ativo") {
            cout << "Código: " << produto[i].codigo << endl;
            cout << "Descrição: " << produto[i].descricao << endl;
            cout << "Fornecedor" << endl << "Nome: " << produto[i].fornecedor.nome << endl;
            cout << "Email: " << produto[i].fornecedor.email << endl;
            cout << "Situação: " << produto[i].situacao << endl;
        }
    }
}

void exportarProduto(produtos produto[], int tam) {
    //transformar o vetor produto em um vetor char
    char *vetorChar = new char[tam * sizeof(produtos)];
    memcpy(vetorChar, produto, tam * sizeof(produtos));
    ofstream arquivo("produtos.dat", ios::binary);
    //escrever o vetor char no arquivo
    arquivo.write(vetorChar, tam * sizeof(produtos));
    arquivo.close();
    //ler o arquivo
    ifstream arquivoLeitura("produtos.dat", ios::binary);
    //verificar se o arquivo foi aberto
    if (arquivoLeitura.is_open()) {
        //criar um vetor char para receber os dados do arquivo
        char *vetorCharLeitura = new char[tam * sizeof(produtos)];
        //ler o arquivo e armazenar no vetor char
        arquivoLeitura.read(vetorCharLeitura, tam * sizeof(produtos));
        //criar um vetor produtos para armazenar os dados do vetor char
        produtos *produtoLeitura = new produtos[tam];
        memcpy(produtoLeitura, vetorCharLeitura, tam * sizeof(produtos));
        //imprimir os dados do arquivo
        for (int i = 0; i < tam; i++) {
            cout << "Dados exportados: " << endl;
            if (produtoLeitura[i].situacao == "ativo") {
                cout << "Código: " << produtoLeitura[i].codigo << endl;
                cout << "Descrição: " << produtoLeitura[i].descricao << endl;
                cout << "Fornecedor" << endl << "Nome: " << produtoLeitura[i].fornecedor.nome << endl;
                cout << "Email: " << produtoLeitura[i].fornecedor.email << endl;
                cout << "Situação: " << produtoLeitura[i].situacao << endl;
            }
        }
        arquivoLeitura.close();
    }
}

int main () {
    //menu da loja
    int i = 0, t = 3, opcao;
    produtos *produto = new produtos[t];
    string c;
    opcao = menu();
    while (opcao != 8) {
        switch (opcao) {
            case 1:
                //se o vetor produtos estiver lotado, o programa deve aumentar o tamanho do vetor em 3
                cout << "Cadastrar produto" << endl;
                cadastrarProduto (produto, i, t);
                i++;
                if (i == t)
                produto = aumentaVetor (produto, t);
                break;
            case 2:
                //consultar um produto pelo codigo
                consultarProduto (produto, t);
                break;
            case 3:
                //listar produtos cadastrados disponíveis ordenados pelo código do produto
                listarProdutosAtivos (produto, t);
                break;
            case 4:
                //excluir produto
                excluirProduto (produto, t);
                break;
            case 5:
                //efetuar uma venda
                vendaProduto (produto, t);
                break;
            case 6:
                //listar dados de produtos ativos em estoque
                listarProdutosAtivos (produto, t);
                break;
            case 7:
                exportarProduto (produto, t);
                break;
            default:
                cout << "Opção inválida" << endl;
                break;
            }
            if (opcao != 8)
                opcao = menu();
    }
    cout << "Encerrando sistema..." << endl;
    return 0;
}