//  Savin Ana-Bianca - 314CB
#include "headers.h"

//  Calculul valorii medii mean
unsigned long long CalcMean(TImg img, int istart, int jstart, int iend, int jend) {
    unsigned long long red = 0, green = 0, blue = 0, mean = 0;
    unsigned long long size = iend - istart;

    for (int i = istart; i < iend; i++)
        for (int j = jstart; j < jend; j++) {
            red += img[i][j].red;
            green += img[i][j].green;
            blue += img[i][j].blue;
        }

    red /= (size * size);
    green /= (size * size);
    blue /= (size * size);

    for (int i = istart; i < iend; i++)
        for (int j = jstart; j < jend; j++) {
            mean += (red - img[i][j].red)*(red - img[i][j].red) +
                    (green - img[i][j].green)*(green - img[i][j].green) +
                    (blue - img[i][j].blue)*(blue - img[i][j].blue);
        }
    mean /= (3 * size * size);

    return mean;
}

//  Calcul valorii medii individuale
TPixel ValMed(TImg img, int istart, int jstart, int iend, int jend) {
    TPixel aux;
    unsigned long long red = 0, green = 0, blue = 0;
    unsigned long long size = iend - istart;

    for (int i = istart; i < iend; i++)
        for (int j = jstart; j < jend; j++) {
            red += img[i][j].red;
            green += img[i][j].green;
            blue += img[i][j].blue;
        }

    red /= (size * size);
    green /= (size * size);
    blue /= (size * size);
    aux.red = red;
    aux.green = green;
    aux.blue = blue;

    return aux;
}

//  Verifica daca toata imaginea are aceeasi culoare
int VerifOCul(TArb a, TImg img, int height, int width, int prag) {
    unsigned long long mean = CalcMean(img, 0, 0, height, width);

    if (mean <= prag) {
        a->culoare = ValMed(img, 0, 0, height, width);
        return 1;
    } else {
        return 0;
    }
}

//  Construirea arborelui
void ConstrArbore(TArb a, TImg img, int istart, int jstart, int iend, int jend, int prag) {
    AlocareFii(a);
    int iUpdate = istart + (iend - istart) / 2;
    int jUpdate = jstart + (jend - jstart) / 2;
    unsigned long long mean1 = CalcMean(img, istart, jstart, iUpdate, jUpdate);
    unsigned long long mean2 = CalcMean(img, istart, jUpdate, iUpdate, jend);
    unsigned long long mean3 = CalcMean(img, iUpdate, jUpdate, iend, jend);
    unsigned long long mean4 = CalcMean(img, iUpdate, jstart, iend, jUpdate);

    if (mean1 <= prag) {
        a->fiu1->culoare = ValMed(img, istart, jstart, iUpdate, jUpdate);
    } else {
        ConstrArbore(a->fiu1, img, istart, jstart, iUpdate, jUpdate, prag);
    }

    if (mean2 <= prag) {
        a->fiu2->culoare = ValMed(img, istart, jUpdate, iUpdate, jend);
    } else {
        ConstrArbore(a->fiu2, img, istart, jUpdate, iUpdate, jend, prag);
    }

    if (mean3 <= prag) {
        a->fiu3->culoare = ValMed(img, iUpdate, jUpdate, iend, jend);
    } else {
        ConstrArbore(a->fiu3, img, iUpdate, jUpdate, iend, jend, prag);
    }

    if (mean4 <= prag) {
        a->fiu4->culoare = ValMed(img, iUpdate, jstart, iend, jUpdate);
    } else {
        ConstrArbore(a->fiu4, img, iUpdate, jstart, iend, jUpdate, prag);
    }
}

//  Aflarea nivelului maxim
int NrNiv(TArb a, int crtLevel) {
    if (a == NULL)
        return 0;

    int arb1 = NrNiv(a->fiu1, crtLevel + 1);
    int arb2 = NrNiv(a->fiu2, crtLevel + 1);
    int arb3 = NrNiv(a->fiu3, crtLevel + 1);
    int arb4 = NrNiv(a->fiu4, crtLevel + 1);

    int max = arb1;
    if (max < arb2)
        max = arb2;
    if (max < arb3)
        max = arb3;
    if (max < arb4)
        max = arb4;
    return max + 1;
}

//  Numarul blocurilor ce respecta conditia
int NrBlocuri(TArb a, TImg img, int istart, int jstart, int iend, int jend, int prag) {
    int iUpdate = istart + (iend - istart) / 2;
    int jUpdate = jstart + (jend - jstart) / 2;
    unsigned long long mean1 = CalcMean(img, istart, jstart, iUpdate, jUpdate);
    unsigned long long mean2 = CalcMean(img, istart, jUpdate, iUpdate, jend);
    unsigned long long mean3 = CalcMean(img, iUpdate, jUpdate, iend, jend);
    unsigned long long mean4 = CalcMean(img, iUpdate, jstart, iend, jUpdate);
    int arb1 = 0, arb2 = 0, arb3 = 0, arb4 = 0;

    if (mean1 <= prag)
        arb1 = 1;
    else
        arb1 = NrBlocuri(a->fiu1, img, istart, jstart, iUpdate, jUpdate, prag);

    if (mean2 <= prag)
        arb2 = 1;
    else
        arb2 = NrBlocuri(a->fiu2, img, istart, jUpdate, iUpdate, jend, prag);

    if (mean3 <= prag)
        arb3 = 1;
    else
        arb3 = NrBlocuri(a->fiu3, img, iUpdate, jUpdate, iend, jend, prag);

    if (mean4 <= prag)
        arb4 = 1;
    else
        arb4 = NrBlocuri(a->fiu4, img, iUpdate, jstart, iend, jUpdate, prag);

    return arb1 + arb2 + arb3 + arb4;
}

//  Cea mai mare latura
int MaxLatura(TArb a, TImg img, int istart, int jstart, int iend, int jend, int prag) {
    int iUpdate = istart + (iend - istart) / 2;
    int jUpdate = jstart + (jend - jstart) / 2;
    unsigned long long mean1 = CalcMean(img, istart, jstart, iUpdate, jUpdate);
    unsigned long long mean2 = CalcMean(img, istart, jUpdate, iUpdate, jend);
    unsigned long long mean3 = CalcMean(img, iUpdate, jUpdate, iend, jend);
    unsigned long long mean4 = CalcMean(img, iUpdate, jstart, iend, jUpdate);
    int arb1 = 0, arb2 = 0, arb3 = 0, arb4 = 0;

    if (mean1 <= prag)
        return (iend - istart) / 2;
    if (mean2 <= prag)
        return (iend - istart) / 2;
    if (mean3 <= prag)
        return (iend - istart) / 2;
    if (mean4 <= prag)
        return (iend - istart) / 2;

    arb1 = MaxLatura(a->fiu1, img, istart, jstart, iUpdate, jUpdate, prag);
    arb2 = MaxLatura(a->fiu2, img, istart, jUpdate, iUpdate, jend, prag);
    arb3 = MaxLatura(a->fiu3, img, iUpdate, jUpdate, iend, jend, prag);
    arb4 = MaxLatura(a->fiu4, img, iUpdate, jstart, iend, jUpdate, prag);

    int max = arb1;
    if (max < arb2)
        max = arb2;
    if (max < arb3)
        max = arb3;
    if (max < arb4)
        max = arb4;
    return max;
}

//  Afiseaza imaginea in binar in fisier
void AfisareImg(TArb a, FILE *write) {
    TCoada *coada = InitQ();
    TArb aux = NULL;
    unsigned char nodIntern = 0;
    unsigned char frunza = 1;
    IntrQ(coada, a);
    while (coada->inc != NULL) {
        ExtrQ(coada, &aux);
        if (aux->fiu1 == NULL) {
            fwrite(&frunza, sizeof(unsigned char), 1, write);
            fwrite(&aux->culoare.red, sizeof(unsigned char), 1, write);
            fwrite(&aux->culoare.green, sizeof(unsigned char), 1, write);
            fwrite(&aux->culoare.blue, sizeof(unsigned char), 1, write);
        } else {
            fwrite(&nodIntern, sizeof(unsigned char), 1, write);
            IntrQ(coada, aux->fiu1);
            IntrQ(coada, aux->fiu2);
            IntrQ(coada, aux->fiu3);
            IntrQ(coada, aux->fiu4);
        }
    }

    DistrQ(&coada);
}

//  Construirea arborelui din fisierul comprimat
void ConstrArboreCompr(TArb a, FILE *read) {
    TCoada *coada = InitQ();
    TArb aux = NULL;
    unsigned int c = 0;
    unsigned char c1 = 0, c2 = 0, c3 = 0, c4 = 0;

    //  Punem radacina in coada daca img nu are doar 1 culoare
    fread(&c, sizeof(unsigned char), 1, read);
    if (c == 0)
        IntrQ(coada, a);
    else
        fread(&(a->culoare), sizeof(TPixel), 1, read);

    while (coada->inc != NULL && !feof(read)) {
        //  Extragem nodul din coada
        ExtrQ(coada, &aux);
        AlocareFii(aux);

        //  Citim si atribuim culorile nodului daca este cazut,
        //  daca nu, inseram nodul in coada
        fread(&c1, sizeof(unsigned char), 1, read);
        if (c1 == 1)
            fread(&(aux->fiu1->culoare), sizeof(TPixel), 1, read);
        else
            IntrQ(coada, aux->fiu1);

        fread(&c2, sizeof(unsigned char), 1, read);
        if (c2 == 1)
            fread(&(aux->fiu2->culoare), sizeof(TPixel), 1, read);
        else
            IntrQ(coada, aux->fiu2);

        fread(&c3, sizeof(unsigned char), 1, read);
        if (c3 == 1)
            fread(&(aux->fiu3->culoare), sizeof(TPixel), 1, read);
        else
            IntrQ(coada, aux->fiu3);

        fread(&c4, sizeof(unsigned char), 1, read);
        if (c4 == 1)
            fread(&(aux->fiu4->culoare), sizeof(TPixel), 1, read);
        else
            IntrQ(coada, aux->fiu4);
    }

    DistrQ(&coada);
}

//  Coloreaza toti pixelii dintr-o imagine in culoarea data
void ColorImg(TImg img, TPixel culoare, int istart, int jstart, int iend, int jend) {
    for (int i = istart; i < iend; i++)
        for (int j = jstart; j < jend; j++)
            img[i][j] = culoare;
}

//  Construirea imaginii din arborele de compresie
void ConstrImg(TArb a, TImg img, int istart, int jstart, int iend, int jend) {
    if (a->fiu1 == NULL) {
        ColorImg(img, a->culoare, istart, jstart, iend, jend);
    } else {
        int iUpdate = istart + (iend - istart) / 2;
        int jUpdate = jstart + (jend - jstart) / 2;
        ConstrImg(a->fiu1, img, istart, jstart, iUpdate, jUpdate);
        ConstrImg(a->fiu2, img, istart, jUpdate, iUpdate, jend);
        ConstrImg(a->fiu3, img, iUpdate, jUpdate, iend, jend);
        ConstrImg(a->fiu4, img, iUpdate, jstart, iend, jUpdate);
    }
}
