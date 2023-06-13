//  Savin Ana-Bianca - 314CB
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//  Structura pentru pixeli si imagine
typedef struct pixel {
    unsigned char red, green, blue;
} TPixel, *TVect, **TImg;

//  Structura pentru arborele cuaternar
typedef struct nod {
    TPixel culoare;
    struct nod *fiu1, *fiu2, *fiu3, *fiu4;
} TNod, *TArb;

//  Structuri pentru coada
typedef struct celula {
    TArb info;
    struct celula* urm;
} TCelula, *TLista;

typedef struct coada {
    TLista inc, sf;
} TCoada;

//  Functii pentru coada
TCoada* InitQ();
int ExtrQ(TCoada*c, TArb *a);
int IntrQ(TCoada *c, TArb a);
void DistrQ(TCoada **c);
TLista AlocCelula(TArb a);

//  Functii elementare
TImg InitImg(unsigned int width, unsigned int height);
void DistrImg(TImg img, unsigned int height);
void AlocareFii(TArb a);
TArb AlocaNod();
void DistrArb(TArb *a);

//  Functii care ajuta la rezolvarea cerintelor
void ConstrArbore(TArb a, TImg img, int istart, int jstart, int iend, int jend, int prag);
int VerifOCul(TArb a, TImg img, int width, int height, int prag);
int NrNiv(TArb a, int crtLevel);
int NrBlocuri(TArb a, TImg img, int istart, int jstart, int iend, int jend, int prag);
int MaxLatura(TArb a, TImg img, int istart, int jstart, int iend, int jend, int prag);
void AfisareImg(TArb a, FILE *write);
void ConstrArboreCompr(TArb a, FILE *read);
void ConstrImg(TArb a, TImg img, int istart, int jstart, int iend, int jend);
