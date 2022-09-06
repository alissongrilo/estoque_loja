#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

using namespace std;


struct fornecedorProduto{
    string nomeFornecedor;
    string telefoneFornecedor;
    string emailFornecedor[2];
    // 
};

struct produto {
    string descricaoProduto;
    string marcaProduto;
    string codProduto;
    int qtdProdutoDisponivel;
    float precoProduto;
    string situacaoProduto;

    fornecedorProduto fornecedor;
};

void escreveMenu(){
    cout<<"| CONTROLE DE ESTOQUE |"<<endl;
    cout<<"Informe a opcao desejada:"<<endl;
    cout<<"1. Cadastrar produto"<<endl;
    cout<<"2. Consultar produto"<<endl;
    cout<<"3. Listar produtos cadastrados disponiveis (ordenados pelo codigo do produto)"<<endl;
    cout<<"4. Excluir um produto"<<endl;
    cout<<"5. Efetuar uma venda"<<endl;
    cout<<"6. Listar dados de produtos ativos em estoque"<<endl;
    cout<<"7. Exportar dados de produtos ativos em estoque"<<endl;
    cout<<"8. Sair"<<endl;
}

produto* redimensiona(produto *produtos, int &capacidade){
    produto *produtosNovo = new produto[capacidade + 3];
    copy(produtos, produtos+capacidade, produtosNovo);
    capacidade += 5;

    return produtosNovo;
}


bool ehCadastrado(produto produto[], string auxiliar, int &tamanho){
    for(int j=0; j<tamanho; j++){
        if (auxiliar == produto[j].codProduto) return 1;
        else return 0;
    }
}


void cadastraProduto(produto produtos[], int &tamanho){
    string auxiliar;
    int qtdEmails;
        
    cout<<"Descricao do produto: ";
    cin>>produtos[tamanho].descricaoProduto;

    cout<<"Codigo de identificacao: ";
    cin>>auxiliar;

    if (ehCadastrado(produtos, auxiliar, tamanho)){
        cout<<"ERRO! Codigo de produto ja cadastrado no sistema"<<endl;
    } else{
        produtos[tamanho].codProduto = auxiliar;

        cout<<"Quantidade disponivel: ";
        cin>>produtos[tamanho].qtdProdutoDisponivel;

        cout<<"Preco unitario: ";
        cin>>produtos[tamanho].precoProduto;
        
        cout<<"| Fornecedor |"<<endl;
        cout<<"Nome: ";
        cin>>produtos[tamanho].fornecedor.nomeFornecedor;

        cout<<"Informe quantos emails deseja cadastrar (MAX: 2): ";
        cin>>qtdEmails;
        
        cout<<"Informe seu(s) email(s): ";
        for (int i = 0; i<qtdEmails; i++){        
            cin>>produtos[tamanho].fornecedor.emailFornecedor[i];
        }

        cout<<"Telefone: ";
        cin>>produtos[tamanho].fornecedor.telefoneFornecedor;
        
        cout<<"Situacao: ";
        cin>>produtos[tamanho].situacaoProduto;

        cout<<"Cadastro efetuado com sucesso!"<<endl;
        tamanho++;
    }
}


int main(){
    int capacidade, tamanho;
    int opcao;

    capacidade = 3;
    tamanho = 0; 

    produto *produtos = new produto[capacidade];

    do{
        escreveMenu();
        cin>>opcao;
        
        if (opcao == 1){
            if (tamanho < capacidade){
                cadastraProduto(produtos, tamanho);
            } else {
                produto *aux = produtos;
                aux = redimensiona(produtos, capacidade);
                delete [] produtos;
                produtos = aux;

                cadastraProduto(produtos, tamanho); 
            }
        }
        
        /*else if (opcao == 2){
            escreveConsulta(produto);
        } else if (opcao == 3){
        }*/

    } while (opcao != 8);







    delete [] produtos;


    return 0;
}