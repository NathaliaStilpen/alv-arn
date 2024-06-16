#ifndef RUBRONEGRA
#define RUBRONEGRA

typedef struct tno tno;
typedef struct arn arn;

arn *criarRN();

void apagarRN(arn *T);

void rotEsq(arn *T, tno *x);

void rotDir(arn *T, tno *y);

void consertarInclusao(arn *T, tno *z);

void incluirRN(arn *T, int k);

void transplantar(arn *T, tno *u, tno *v);

void consertarRemocao(arn *T, tno *x);

void removerRN(arn *T, tno *z);

tno *buscarRN(arn *T, int k);

int qtde_RotacoesRN(arn *T);

tno *getRaiz2(arn *T);

int qtde_ElementosRN(arn *T);

#endif//



#ifndef TRABALHO_ARVORES_ARN_H
#define TRABALHO_ARVORES_ARN_H

#endif
