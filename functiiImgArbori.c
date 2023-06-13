//  Savin Ana-Bianca - 314CB
#include "headers.h"

//  Functii pentru imagine

//  Alocarea memoriei pentru o imagine
TImg InitImg(unsigned int width, unsigned int height) {
    TImg img = (TImg)malloc(height * sizeof(TVect));
    if (!img) {
        printf("Malloc failed");
        return NULL;
    }

    for (int i = 0; i < height; i++) {
        img[i] = (TVect)malloc(width * sizeof(TPixel));

        //  Daca alocarea esueaza
        if (!img[i]) {
            for (int j = 0; j < i; j++)
                free(img[j]);
            free(img);
            return NULL;
        }
    }
    return img;
}

//  Dezalocarea memoriei folosita pt imagine
void DistrImg(TImg img, unsigned int height) {
    for (int i = 0; i < height; i++)
        free(img[i]);
    free(img);
    img = NULL;
}

//  Functii pentru arbore

//  Alocarea unui nod
TArb AlocaNod() {
    TArb nod = malloc(sizeof(TNod));
    if (!nod) {
        printf("Malloc failed");
        return NULL;
    }
    nod->fiu1 = NULL;
    nod->fiu2 = NULL;
    nod->fiu3 = NULL;
    nod->fiu4 = NULL;
    return nod;
}

//  Alocarea celor 4 fii ai unui nod
void AlocareFii(TArb a) {
    a->fiu1 = AlocaNod();
    a->fiu2 = AlocaNod();
    a->fiu3 = AlocaNod();
    a->fiu4 = AlocaNod();
}

//  Distrugere auxiliar
void Distruge(TArb a) {
    if (!a)
        return;
    Distruge(a->fiu1);
    Distruge(a->fiu2);
    Distruge(a->fiu3);
    Distruge(a->fiu4);
    free(a);
}

//  Distrugere arbore
void DistrArb(TArb *a) {
    if (!(*a))
        return;
    Distruge(*a);
    *a = NULL;
}

//  Functii pentru coada

//  Initializeaza coada
TCoada* InitQ() {
    TCoada* c = (TCoada*)malloc(sizeof(TCoada));
    if (!c) {
        printf("Malloc error");
        return NULL;
    }
    c->inc = c->sf = NULL;
    return c;
}

//  Adauga element la sfarsitul cozii
int IntrQ(TCoada *c, TArb a) {
    TLista aux = AlocCelula(a);

    if (c->sf != NULL)
        c->sf->urm = aux;
    else
        c->inc = aux;
    c->sf = aux;
    return 1;
}

//  Extrage primul element din coada la adresa a
int ExtrQ(TCoada *c, TArb *a) {
    (*a) = c->inc->info;
    TLista aux = c->inc;
    c->inc = c->inc->urm;
    if (!c->inc)
        c->sf = NULL;
    free(aux);
    return 1;
}

// Distruge coada
void DistrQ(TCoada **c) {
    TLista p = NULL, aux = NULL;
    p = (*c)->inc;
    while (p) {
        aux = p;
        p = p->urm;
        free(aux);
    }
    free(*c);
    *c = NULL;
}

//  Aloca o celula din coada
TLista AlocCelula(TArb a) {
    TLista aux = (TLista) malloc(sizeof(TCelula));
    if (!aux) {
        printf("Malloc failed");
        return NULL;
    }
    aux->info = a;
    aux->urm = NULL;
    return aux;
}
