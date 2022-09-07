#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <fstream>
using namespace std;

struct fornecedorProduto{
    string nomeFornecedor;
    string telefoneFornecedor;
    string emailFornecedor[2];
};


struct produto {
    string descricaoProduto;
    string marcaProduto;
    string codProduto;
    string situacaoProduto;
    int qtdProdutoVendido;
    int qtdProdutoDisponivel;
    float precoProduto;

    fornecedorProduto fornecedor;
};


void quickSort(produto produtos[], int primeiro, int ultimo){
    int i = primeiro;
    int j = ultimo;
    string pivo = produtos[(i+j)/2].codProduto;

    while (i <= j){

        while (produtos[i].codProduto < pivo)
            i++;
        
        while (produtos[j].codProduto > pivo)
            j--;

        if (i <= j){
            swap(produtos[i].codProduto, produtos[j].codProduto);
            swap(produtos[i].descricaoProduto, produtos[j].descricaoProduto);
            swap(produtos[i].marcaProduto, produtos[j].marcaProduto);
            swap(produtos[i].precoProduto, produtos[j].precoProduto);
            swap(produtos[i].qtdProdutoDisponivel, produtos[j].qtdProdutoDisponivel);
            swap(produtos[i].situacaoProduto, produtos[j].situacaoProduto);
            swap(produtos[i].qtdProdutoVendido, produtos[j].qtdProdutoVendido);
            swap(produtos[i].fornecedor.nomeFornecedor, produtos[j].fornecedor.nomeFornecedor);
            swap(produtos[i].fornecedor.emailFornecedor[0], produtos[j].fornecedor.emailFornecedor[0]);
            swap(produtos[i].fornecedor.emailFornecedor[1], produtos[j].fornecedor.emailFornecedor[1]);
            swap(produtos[i].fornecedor.telefoneFornecedor, produtos[j].fornecedor.telefoneFornecedor);

            i++;
            j--;
        }
    }

    if (j > primeiro)
        quickSort(produtos, primeiro, j);
    if (i < ultimo)
        quickSort(produtos, i, ultimo);
}


void escreveProdutoCadastrado(produto produtos[], int tamanho){
    quickSort (produtos, 0, tamanho-1);
    
    for (int i = 0; i<tamanho; i++){
        cout<<"Descricao: "<<produtos[i].descricaoProduto<<endl;
        cout<<"Codigo: "<<produtos[i].codProduto<<endl;
        cout<<"Fornecedor: "<<produtos[i].fornecedor.nomeFornecedor<<endl;
        
        for (int j = 0; j<2; j++){
            cout<<"E-mail "<<j+1<<": "<<produtos[i].fornecedor.emailFornecedor[j]<<endl;
        }

        cout<<"Situacao: "<<produtos[i].situacaoProduto<<endl;
        cout<<endl;
    }
}


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


void preencheEstrutura(produto produtos[], int capacidade){
    for (int i = capacidade-3; i<capacidade; i++){
        for (int j = 0; j<2; j++){
            produtos[i].fornecedor.emailFornecedor[j] = '-';
        }

        produtos[i].qtdProdutoVendido = 0;
    }
}


produto* redimensiona(produto *produtos, int &capacidade){
    produto *produtosNovo = new produto[capacidade + 3];
    copy(produtos, produtos+capacidade, produtosNovo);
    capacidade += 3;

    preencheEstrutura(produtosNovo, capacidade);

    return produtosNovo;
}


bool ehCadastrado(produto produtos[], string auxiliar, int &tamanho){
    for(int j=0; j<tamanho; j++){
        if (auxiliar == produtos[j].codProduto) return 1;
    }
    return 0;
}


void escreveProduto(produto produtos[], int indice){
    cout<<"Codigo do produto: "<<produtos[indice].codProduto<<endl;
    cout<<"Quantidade disponivel: "<<produtos[indice].qtdProdutoDisponivel<<endl;
    cout<<"Quantidade vendida: "<<produtos[indice].qtdProdutoVendido<<endl;
    cout<<"Situacao: "<<produtos[indice].situacaoProduto<<endl;
}


int buscaBinaria(produto produtos[], int inicio, int tamanho, string codBusca, bool &achou){
    int meio;
    while(inicio <= tamanho and !achou){
        meio = (inicio + tamanho) / 2;
        if (produtos[meio].codProduto == codBusca){
            achou = true;
            return meio;
        } else if (produtos[meio].codProduto < codBusca){
            inicio = meio + 1;
        } else {
            tamanho = meio - 1;
        }
    }
    return -1;
}


void excluiProduto(produto produtos[], int tamanho, string codBusca){
    int indice;
    bool achou = false;
    int confirmacao;

    quickSort (produtos, 0, tamanho-1);

    indice = buscaBinaria(produtos, 0, tamanho, codBusca, achou);

    if (!achou or produtos[indice].situacaoProduto == "Inativo"){
        cout<<"Produto nao cadastrado ou inativo"<<endl;
    } else{
        cout<<"Codigo do produto: "<<produtos[indice].codProduto<<endl;
        cout<<"Descricao: "<<produtos[indice].descricaoProduto<<endl;
        cout<<"Confirma exclusao? 1-sim 2-nao"<<endl;
        cin>>confirmacao;
        if (confirmacao == 1){
            produtos[indice].situacaoProduto = "Inativo";
            cout<<"Situacao: "<<produtos[indice].situacaoProduto<<endl;
            cout<<"Produto excluido com sucesso!"<<endl;
        } else if (confirmacao == 2){
            cout<<"Situacao: "<<produtos[indice].situacaoProduto<<endl;
        }
    }
}


void consultaProduto(produto produtos[], int tamanho, string codBusca){
    int indice;
    bool achou = false;

    quickSort (produtos, 0, tamanho-1);

    indice = buscaBinaria(produtos, 0, tamanho, codBusca, achou);

    if (!achou)
        cout<<"Codigo do produto: "<<codBusca<<endl<<"Situacao: Produto nao cadastrado"<<endl;
    else
        escreveProduto(produtos, indice);
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


void efetuaVenda(produto produtos[], int tamanho, string codBusca){
    int qtdVendida;
    int indice;
    bool achou = false;

    quickSort (produtos, 0, tamanho-1);
    
    indice = buscaBinaria(produtos, 0, tamanho, codBusca, achou);

    if (!achou){
        cout<<"Produto nao cadastrado"<<endl;
    } else {
        cout<<"Informe a quantidade a ser vendida: ";
        cin>>qtdVendida;
        if (qtdVendida <= produtos[indice].qtdProdutoDisponivel and produtos[indice].situacaoProduto == "Ativo"){
            produtos[indice].qtdProdutoVendido += qtdVendida;
            produtos[indice].qtdProdutoDisponivel -= qtdVendida;
            
            cout<<"Codigo: "<<produtos[indice].codProduto<<endl;
            cout<<"Descricao: "<<produtos[indice].descricaoProduto<<endl;
            cout<<"Quantidade vendida: "<<produtos[indice].qtdProdutoVendido<<endl;
            cout<<"Quantidade em estoque: "<<produtos[indice].qtdProdutoDisponivel<<endl;
            cout<<"Venda realizada com sucesso!"<<endl;
        } else {
            cout<<"Codigo: "<<produtos[indice].codProduto<<endl;
            cout<<"Descricao: "<<produtos[indice].descricaoProduto<<endl;
            cout<<"Quantidade em estoque: "<<produtos[indice].qtdProdutoDisponivel<<endl;
            cout<<"Situacao: "<<produtos[indice].situacaoProduto<<endl;
            cout<<"Quantidade nao disponivel em estoque ou produto inativo"<<endl;
        }
    }
}


void escreveProdutoAtivo(produto produtos[], int tamanho){
    quickSort (produtos, 0, tamanho-1);
    
    for (int i = 0; i<tamanho; i++){
        if (produtos[i].situacaoProduto == "Ativo"){
            cout<<"Descricao: "<<produtos[i].descricaoProduto<<endl;
            cout<<"Codigo: "<<produtos[i].codProduto<<endl;
            cout<<"Fornecedor: "<<produtos[i].fornecedor.nomeFornecedor<<endl;
            for (int j = 0; j<2; j++){
                cout<<"E-mail "<<j+1<<": "<<produtos[i].fornecedor.emailFornecedor[j]<<endl;
            }
            cout<<"Situacao: "<<produtos[i].situacaoProduto<<endl;
            cout<<endl;
        }
    }
}


int main(){
    int capacidade, tamanho;
    int opcao;
    string codBusca;

    capacidade = 3;
    tamanho = 0; 

    produto *produtos = new produto[capacidade];
    ofstream arquivo("arquivo.dat");
    preencheEstrutura(produtos, capacidade);

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
        } else if (opcao == 2){
            cout<<"Informe o codigo do produto desejado: ";
            cin>>codBusca;
            consultaProduto(produtos, tamanho, codBusca);
        } else if (opcao == 3){
            escreveProdutoCadastrado(produtos, tamanho);
        } else if (opcao == 4){
            cout<<"Informe o codigo do produto a ser excluido: ";
            cin>>codBusca;
            excluiProduto(produtos, tamanho, codBusca);
        } else if (opcao == 5){
            cout<<"Informe o codigo do produto a ser vendido: ";
            cin>>codBusca;
            efetuaVenda(produtos, tamanho, codBusca);
        } else if (opcao == 6){
            escreveProdutoAtivo(produtos, tamanho);
        } else if (opcao == 7){
            if (arquivo){            
                arquivo.write((const char *) (produtos), tamanho*sizeof(produto));
                arquivo.close();
                cout<<"Dados exportados com sucesso!"<<endl;
            }
        }
    } while (opcao != 8);
    delete [] produtos;
    return 0;
}