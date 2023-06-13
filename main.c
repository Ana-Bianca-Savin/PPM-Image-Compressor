//  Savin Ana-Bianca - 314CB
#include "headers.h"

int main(int argc, char const *argv[]) {
    //  Initializara variabile folosite pentru citire
    unsigned int width = 0, height = 0, maxNr = 0;
    FILE *read = NULL;
    FILE *write = NULL;

    //  Initializare arbore
    TArb arbore = AlocaNod();
    if (!arbore) {
        printf("Malloc failed");
        return 0;
    }

    //  Alocare variabila ce citeste tipul imaginii P6
    char *tipPPM = malloc(3 * sizeof(char));
    if (!tipPPM) {
        printf("Malloc failed");
        DistrArb(&arbore);
        return 0;
    }

    if (strcmp(argv[1], "-c1") == 0) {
        //  Extragerea factorului
        unsigned int prag = 0;
        for (int i = 0; i < strlen(argv[2]); i++)
            prag = prag * 10 + (argv[2][i] - '0');

        //  Deschiderea fisierelor
        read = fopen(argv[3], "rb");
        write = fopen(argv[4], "w");

        //  Citirea informatiilor de dinaintea imaginii
        fscanf(read, "%s", tipPPM);
        fscanf(read, "%u", &width);
        fscanf(read, "%u", &height);
        fscanf(read, "%u", &maxNr);
        fseek(read, 1, SEEK_CUR);

        //  Initializarea si citirea imaginii
        TImg img = InitImg((signed)width, (signed)height);
        if (!img) {
            printf("Malloc failed");
            DistrArb(&arbore);
            free(tipPPM);
            fclose(read);
            fclose(write);
            return 0;
        }
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                fread(&img[i][j], sizeof(TPixel), 1, read);

        //  Construirea arborelui de compresie si afisarea statisticilor
        if (!VerifOCul(arbore, img, height, width, prag)) {
            //  Construirea arborelui
            ConstrArbore(arbore, img, 0, 0, (signed)height, (signed)width, prag);
            //  Afisari
            fprintf(write, "%d\n", NrNiv(arbore, 0));
            fprintf(write, "%d\n", NrBlocuri(arbore, img, 0, 0, height, width, prag));
            fprintf(write, "%d\n", MaxLatura(arbore, img, 0, 0, height, width, prag));
        } else {
            //  Pentru cazul in care toata imaginea este un patrat de aceeasi culoare
            fprintf(write, "1\n");
            fprintf(write, "1\n");
            fprintf(write, "%d\n", height);
        }

        DistrImg(img, (signed)height);
    } else if (strcmp(argv[1], "-c2") == 0) {
        //  Extragerea factorului
        unsigned int prag = 0;
        for (int i = 0; i < strlen(argv[2]); i++)
            prag = prag * 10 + (argv[2][i] - '0');

        //  Deschiderea fisierelor
        read = fopen(argv[3], "rb");
        write = fopen(argv[4], "w");

        //  Citirea informatiilor de dinaintea imaginii
        fscanf(read, "%s", tipPPM);
        fscanf(read, "%u", &width);
        fscanf(read, "%u", &height);
        fscanf(read, "%u", &maxNr);
        fseek(read, 1, SEEK_CUR);

        //  Initializarea si citirea imaginii
        TImg img = InitImg((signed)width, (signed)height);
        if (!img) {
            printf("Malloc failed");
            DistrArb(&arbore);
            free(tipPPM);
            fclose(read);
            fclose(write);
            return 0;
        }
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                fread(&img[i][j], sizeof(TPixel), 1, read);

        //  Construirea arborelui de compresie
        if (!VerifOCul(arbore, img, (signed)height, (signed)width, prag))
            ConstrArbore(arbore, img, 0, 0, (signed)height, (signed)width, prag);

        //  Rezolvarea cerintei
        //  Scriem dimensiunea
        fwrite(&height, sizeof(unsigned int), 1, write);

        //  Scriem imaginea in format binar
        AfisareImg(arbore, write);

        DistrImg(img, (signed)height);
    } else if (strcmp(argv[1], "-d") == 0) {
        //  Deschiderea fisierelor
        read = fopen(argv[2], "rb");
        write = fopen(argv[3], "w");

        //  Citirea dimensiunii imaginii
        fread(&height, sizeof(unsigned int), 1, read);

        //  Construirea arborelui din fisierul comprimat
        ConstrArboreCompr(arbore, read);

        //  Initializarea imaginii si construirea ei
        TImg img = InitImg((signed)height, (signed)height);
        if (!img) {
            printf("Malloc failed");
            DistrArb(&arbore);
            free(tipPPM);
            fclose(read);
            fclose(write);
            return 0;
        }
        ConstrImg(arbore, img, 0, 0, (signed)height, (signed)height);

        //  Afisarea informatiilor de dinaintea imaginii
        fprintf(write, "P6\n");
        fprintf(write, "%u %u\n", height, height);
        fprintf(write, "255\n");

        // Afisarea imaginii
        for (int i = 0; i < height; i++)
            for (int j = 0; j < height; j++)
                fwrite(&img[i][j], sizeof(TPixel), 1, write);

        DistrImg(img, (signed)height);
    }

    //  Dezalocari
    DistrArb(&arbore);
    free(tipPPM);

    //  Inchidem fisierele de citire si scriere
    fclose(read);
    fclose(write);
    return 0;
}
