typedef struct no no;
typedef struct avl avl;


avl *criaArvore();


int insereNo(avl *arv, int valor);


int removeNo(avl *arv, int valor);


void imprimeOrdem(no *raiz);


void imprimePreOrdem(no *raiz);


no *getRaiz(avl *arv);


int getNumElementos(avl *arv);


int processaCarga(avl *arv, int num, int tipo);

/***FUNÇÕES DA AVL***/


void atualizaFB_insercao(avl *arv, no *novoNo);


void balanceamento(avl *arv, no *noDesbal);


void rotacaoDir(avl *arv, no *noDesbal);


void rotacaoEsq(avl *arv, no *noDesbal);

//Função que verifica o desbalanceamento na remoção
void atualizaFB_remocao(avl *arv, no *pai, int chaveRemovida);

int qtde_Rotacoes(avl *arv);

no *encontraNo(avl *arv, int valor);


