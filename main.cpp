#include <iostream>
using namespace std;

class No
{
public:
	No *esq, *dir;
	int chave;
  int contador;

	No(int chave)
	{ 
		this->chave = chave;
		esq = NULL;
		dir = NULL;
    contador = 1;
	}
	int getChave(){
		return chave;
	}
	

	No* getEsq(){
		return esq;
	}

	No* getDir(){
		return dir;
	}

	void setEsq(No *no)
	{
		esq = no;
	}

	void setDir(No *no)
	{
		dir = no;
	}
  int getContador(){
    return contador;
  }
};

class Arvore
{
public:
  No *raiz;
  int Altura = 0;

	Arvore()
	{
		raiz = NULL;
    
	}
	void inserir(int chave)
	{
		if(raiz == NULL) //Verifica se a raiz está vazia
			raiz = new No(chave); //Cria node novo
		else
     //Se nao for vazio insere valor
			inserirAux(raiz, chave);
	}
  
	No inserirAux(No *no, int chave)
	{ int cont = no->contador;
    int Key = no->chave;

    if (chave == no->getChave()){;//Se for repetido aumenta a contagem
      cont=cont + 1;
      no->contador = cont; 
      return cont; //Retorna contagem
    }

		// se for menor, insere a esquerda
		else if(chave < no->getChave())
		{
			// verifica se a esquerda esta nulo
			if(no->getEsq() == NULL)
			{
				No *novo_no = new No(chave);
				no->setEsq(novo_no); //Seta o no para esquerda
			}
			else
			{
				// senao, continua percorrendo recursivamente
				inserirAux(no->getEsq(), chave);
			}
		}
		// se for maior, entao insere na direita
		else if(chave > no->getChave())
		{
			// verifica se a direita esta nulo
			if(no->getDir() == NULL)
			{
				No *novo_no = new No(chave);
				no->setDir(novo_no); // seta o novo_no para direita
			}
			else
			{
				// senao, continua percorrendo recursivamente
				inserirAux(no->getDir(), chave);
			}
		}
    return 0;
	}

	void emOrdem(No* no)
	{
		if(no != NULL)
		{
			emOrdem(no->getEsq());
			cout << no->getChave() << "(";
      cout << no->getContador() << ") ";
			emOrdem(no->getDir());
		}
	}

	void preOrdem(No* no)
	{
		if(no != NULL)
		{
			cout << no->getChave() << " ";
			preOrdem(no->getEsq());
			preOrdem(no->getDir());
		}
	}

	void posOrdem(No* no)
	{
		if(no != NULL)
		{
			posOrdem(no->getEsq());
			posOrdem(no->getDir());
			cout << no->getChave() << " ";
				
		}
	}

  No * MenorValor(No* no){//Retorna o menor no para remover raiz
    No *atual = no;
    while(atual->esq!=NULL){
      atual = atual ->esq;
    }
    return atual;
  }

  No * RemoveNode (No *root, int key) {
    if (root == NULL) return root; //Se raiz for nula retorna raiz

    if (key < root->chave){//Se a chave for menor que o valor da raiz
        root->esq = RemoveNode(root->esq, key);
    }
    else if (key > root->chave){//Se a chave for maior que a raiz
        root->dir = RemoveNode(root->dir, key);
    }
    else
    {//Se a chave é mais que uma
      if (root->contador > 1){
        (root->contador)--;
        return root;
      }
      if (root->esq == NULL){//Se o valor esquerdo da raiz for nulo
        No *temp = root->dir;
        free(root);
        return temp;
      }
      else if(root->dir == NULL){//Se o valor direito da raiz for nulo
        No *temp = root->esq;
        free(root);
        return temp;
      }
      //Se tiver mais de um filho remove e reposiciona
      No  *temp = MenorValor(root->dir);
      root->chave = temp->chave;
      root->contador = temp->contador;

      root->dir = RemoveNode(root->dir, temp->chave);
    }
    return root;
  }

  No *ProcuraElemento(No *root, int chave){{
    Altura +=1;
    if (root == NULL) return root;
    if(root->chave == chave){
      cout << "Valor encontrao na altura:" << Altura << endl;
      return root;
    }
    if (root->chave < chave){
    return ProcuraElemento(root->dir, chave);
    }
    
    return ProcuraElemento(root->esq, chave);
  }
}

  int contaNode(No *root){ //Percorre recursivamente toda a árvore contando
    if(root == NULL){
      return 0;
    }
    return 1 + (contaNode(root->esq) + contaNode(root->dir));
  }

  int encontraMaior(No* root) //Percorre a árvore recursivamente até encontrar um valor que seja maior que todos os outros e não tivermos mais nós
  { 
    if (root == NULL)
        return 0;

    int Maior = root->chave;
    int EsquerdaRes = encontraMaior(root->esq);
    int DireitaRes = encontraMaior(root->dir);

    if (EsquerdaRes > Maior) Maior = EsquerdaRes;

    if (DireitaRes > Maior) Maior = DireitaRes;

    else return root->chave;

    return Maior;
  }

};

int main(int argc, char *argv[])
{
  int ValorProc;
  int ValorInse;
  int ValorRemo;
	Arvore arv;
	// insere as chaves
  while (1){
    int opcoes;
    cout << "\nDigite 1 para inserir um valor" << endl;
    cout << "Digite 2 para remover um valor " << endl;
    cout << "Digite 3 para buscar um valor " << endl;
    cout << "Digite 4 contar a quantidade nós" << endl;
    cout << "Digite 5 para achar o maior valor" << endl;
    cout << "Digite -1 para sair da função" << endl;
    cout << "\nQual opção deseja: ";
    cin >> opcoes;
    if (opcoes == 1){
    cout << "\nDigite o valor que deseja inserir: ";
    cin >> ValorInse;
    arv.inserir(ValorInse);
    arv.emOrdem(arv.raiz);
    }
    if (opcoes == 2){
    cout << "\nDigite o valor que deseja remover: ";
    cin >> ValorRemo;
    cout <<"Árvore com o valor removido:" <<arv.RemoveNode(arv.raiz, ValorRemo) << endl;
    arv.emOrdem(arv.raiz);
    cout << "\n";
    }
    if (opcoes == 3){
    cout << "\nDigite o valor que deseja procurar ou digite -1 para sair:";
    cin >> ValorProc;
    arv.ProcuraElemento(arv.raiz, ValorProc);
    arv.Altura = 0;
    }
    if (opcoes == 4){
      printf("Temos um total de %d nós\n",arv.contaNode(arv.raiz));
    }
    if (opcoes == 5){
      printf("O maior valor encontrado em um nó é %d\n",arv.encontraMaior(arv.raiz));
    }
    if(opcoes == -1) return -1;

    }
	return 0;
}