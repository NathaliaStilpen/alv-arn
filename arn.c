#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arn.h"

#define RUBRO 0
#define NEGRO 1

struct tno {
    int chave;
    struct tno *pai, *esq, *dir;
    char cor;
};

struct arn {
    struct tno *sentinela;
    struct tno *nulo;
    int rotacoes;
    int num_elem;
};


arn *criarRN() {
    arn *T;

    T = malloc(sizeof(arn));
    T->nulo = malloc(sizeof(tno));

    T->nulo->cor = NEGRO;

    T->sentinela = malloc(sizeof(tno));
    T->sentinela->dir = T->nulo;
    T->sentinela->esq = NULL; // Sentinela à esquerda é sempre NULL
    T->sentinela->cor = NEGRO;
    T->sentinela->pai = T->nulo;
    T->sentinela->chave = -1000; // Valor da chave da sentinela
    T->rotacoes = 0;
    T->num_elem = 0;

    return T;
}


void apagarRN(arn *T) {
    if (T == NULL) return;

    tno *x = T->sentinela->dir;
    while (x != T->nulo) {
        tno *temp = x->dir;
        free(x);
        x = temp;
    }

    free(T->nulo);
    free(T->sentinela);
    free(T);
}

tno *getRaiz2(arn *T){
    return T->sentinela->dir;
}

void rotEsq(arn *T, tno *x) {
    tno *y;
    y = x->dir;

    x->dir = y->esq;
    if (y->esq != T->nulo)
        y->esq->pai = x;

    y->pai = x->pai;
    if (x->pai == T->nulo)
        T->sentinela->dir = y;
    else if (x == x->pai->esq)
        x->pai->esq = y;
    else
        x->pai->dir = y;

    y->esq = x;
    x->pai = y;
    T->rotacoes++;
}

void rotDir(arn *T, tno *y) {
    tno *x;
    x = y->esq;

    y->esq = x->dir;
    if (x->dir != T->nulo)
        x->dir->pai = y;

    x->pai = y->pai;
    if (y->pai == T->nulo)
        T->sentinela->dir = x;
    else if (y == y->pai->esq)
        y->pai->esq = x;
    else
        y->pai->dir = x;

    x->dir = y;
    y->pai = x;
    T->rotacoes++;
}

void consertarInclusao(arn *T, tno *z) {
    tno *y;

    while (z->pai->cor == RUBRO) {
        if (z->pai == z->pai->pai->esq) { // 3 casos
            y = z->pai->pai->dir;
            if (y->cor == RUBRO) { // Caso 1
                z->pai->cor = NEGRO;
                y->cor = NEGRO;
                z = y->pai;
                z->cor = RUBRO;
            } else {
                if (z == z->pai->dir) { // Caso 2
                    z = z->pai;
                    rotEsq(T, z);
                }
                // Caso 3
                z->pai->cor = NEGRO;
                z->pai->pai->cor = RUBRO;
                rotDir(T, z->pai->pai);
            }
        } else { // 3 casos simétricos
            y = z->pai->pai->esq;
            if (y->cor == RUBRO) { // Caso 1 simétrico
                z->pai->cor = NEGRO;
                y->cor = NEGRO;
                z = y->pai;
                z->cor = RUBRO;
            } else {
                if (z == z->pai->esq) { // Caso 2 simétrico
                    z = z->pai;
                    rotDir(T, z);
                }
                // Caso 3 simétrico
                z->pai->cor = NEGRO;
                z->pai->pai->cor = RUBRO;
                rotEsq(T, z->pai->pai);
            }
        }
    }
    T->sentinela->dir->cor = NEGRO;
}

void incluirRN(arn *T, int k) {
    tno *z, *x, *y;

    z = malloc(sizeof(tno));
    z->chave = k;

    y = T->nulo;
    x = T->sentinela->dir;

    while (x != T->nulo) {
        y = x;
        if (k < x->chave)
            x = x->esq;
        else
            x = x->dir;
    }

    z->pai = y;
    if (y == T->nulo)
        T->sentinela->dir = z;
    else if (k < y->chave)
        y->esq = z;
    else
        y->dir = z;

    z->esq = z->dir = T->nulo;
    z->cor = RUBRO;
    consertarInclusao(T, z);

    // Atualização do pai da raiz
    T->sentinela->dir->pai = T->sentinela;
    T->num_elem++;
}

void transplantar(arn *T, tno *u, tno *v) {
    if (u->pai == T->nulo)
        T->sentinela->dir = v;
    else if (u == u->pai->esq)
        u->pai->esq = v;
    else
        u->pai->dir = v;
    v->pai = u->pai;
}

void consertarRemocao(arn *T, tno *x) {
    tno *w;

    while (x != T->sentinela->dir && x->cor == NEGRO) {
        if (x == x->pai->esq) { // 4 casos
            w = x->pai->dir;
            if (w->cor == RUBRO) { // Caso 1
                w->cor = NEGRO;
                x->pai->cor = RUBRO;
                rotEsq(T, x->pai);
                w = x->pai->dir;
            }
            if (w->esq->cor == NEGRO && w->dir->cor == NEGRO) { // Caso 2
                w->cor = RUBRO;
                x = x->pai;
            } else {
                if (w->dir->cor == NEGRO) { // Caso 3
                    w->esq->cor = NEGRO;
                    w->cor = RUBRO;
                    rotDir(T, x->pai);
                    w = x->pai->dir;
                }
                // Caso 4
                w->cor = x->pai->cor;
                x->pai->cor = NEGRO;
                w->dir->cor = NEGRO;
                rotEsq(T, x->pai);
                x = T->sentinela->dir;
            }
        } else { // 4 casos simétricos
            w = x->pai->esq;
            if (w->cor == RUBRO) { // Caso 1 simétrico
                w->cor = NEGRO;
                x->pai->cor = RUBRO;
                rotDir(T, x->pai);
                w = x->pai->esq;
            }
            if (w->esq->cor == NEGRO && w->dir->cor == NEGRO) { // Caso 2 simétrico
                w->cor = RUBRO;
                x = x->pai;
            } else {
                if (w->esq->cor == NEGRO) { // Caso 3 simétrico
                    w->dir->cor = NEGRO;
                    w->cor = RUBRO;
                    rotEsq(T, x->pai);
                    w = x->pai->esq;
                }
                // Caso 4 simétrico
                w->cor = x->pai->cor;
                x->pai->cor = NEGRO;
                w->esq->cor = NEGRO;
                rotDir(T, x->pai);
                x = T->sentinela->dir;
            }
        }
    }
    x->cor = NEGRO;
}

void removerRN(arn *T, tno *z) {
    tno *x, *y;
    char corOrigy;

    y = z;
    corOrigy = y->cor;

    if (z->esq == T->nulo) {
        x = z->dir;
        transplantar(T, z, x);
    } else if (z->dir == T->nulo) {
        x = z->esq;
        transplantar(T, z, x);
    } else {
        y = z->esq;
        while (y->dir != T->nulo) // Encontrar o predecessor
            y = y->dir;
        x = y->esq;
        corOrigy = y->cor;
        transplantar(T, y, x);

        y->dir = z->dir;
        z->dir->pai = y;
        y->esq = z->esq;
        z->esq->pai = y;
        transplantar(T, z, y);
        y->cor = z->cor;
    }
    if (corOrigy == NEGRO)
        consertarRemocao(T, x);
    T->num_elem--;
}


tno *buscarRN(arn *T, int k) {
    tno *x;

    x = T->sentinela->dir;
    T->nulo->chave = k;

    while (x->chave != k) {
        if (k < x->chave)
            x = x->esq;
        else
            x = x->dir;
    }

    if (x == T->nulo) {
        printf("Elemento %d nao encontrado.\n", k);
    }

    return x;
}

int qtde_RotacoesRN(arn *T) { return T->rotacoes; }

int qtde_ElementosRN(arn *T){ return T->num_elem;}
