# Descriere
Programul primeste ca parametrii prin linie de comanda -c1 factor sau -c2 factor sau -d, in functie de cerinta dorita. Factorul este pragul cu care va fi comparata valoarea media a culorilor din imagine. Apoi, primeste fisierul de intrare, o imagine in format ppm de tip P6, patratica cu latura putere a lui 2. Si un fisier de iesire in care va fie scris output-ul programului. 

Pentru implementarea arborelui de compresie si a imaginii, am declarat urmatoarele structuri:
Structura TPixel are trei elemente, toate de tipul unsigned char, red, green, blue, reprezentand valorile culorii respective de la 0 la 255.
Structura arborelui are informatia de tipul TPixel si 4 pointeri la sine care reprezinta cei 4 fii.
Imaginea este o matrice cu elementele de tipul TPixel.

# Cerinta 1:
Mai intai, fac convertirea pragului primit ca string in int. Apoi citesc pe rand tipul imaginii (P6), lungimea, latimea imaginii si numarul maxim pentru valorile culorii RGB 255.
Apoi, se aloca spatiul pentru imagine si se citesti din fisierul binar fiecare element de tipul TPixel ce formeaza matricea imaginii, element de tipul TImg.

Pentru construirea arborelui de compresie am definit mai multe functii:
Functia CalcMean primeste ca parametru o imagine, pozitia de inceput, reprezentata de punctul cu indicii istart si jstart si o pozitie de sfarsit, reprezentata de indicii iend si jend. Functia calculeaza si returneaza factorul mean a subimaginii aflata intre indicii primiti.
Functia ValMean calculeaza si returneaza valoriile medii red, green, blue, aflate intr-o subimagine, asemenea functiei de mai sus.
Functia VerifOCul verifica daca dupa compresia cu un anumit prag, imaginea devine un patrat de cu toti pixelii de aceeasi culoare. Daca da se atribuie culoarea radacinii arborelui.
Functia ConstrArbore este cea care construieste propriu-zis arborele. Aceasta calculeaza valoriile mean pentru toti cei 4 fii ai nodului, iar daca aceasta este mai mica sau egala cu pragul, fiului i se atribuie culoarea medie. Daca nu, se face un apel recursiv pentru portiunea din imagine ocupata de acel fiu, in functie de indicii punctului din stanga sus si din dreapta jos ai fiului.

Functii pentru statistici:
Functia NrNiv numara recursiv cate nivele sunt in arbore. La un moment dat este returnat numarul maxim de nivele dintr-un subarbore.
Functia recursiva NrBlocuri returneaza numarul de blocuri formate din pixeli de aceeasi culoare. Asemenea functiei de construire a arborelui, se va apela functia pentru fiecare fiu al arborelui de la un moment dat, returnandu-se 1 daca blocul are valoarea media mai mica decat pragul. Se returneaza suma variabilelor ce retin numarul de blocuri din subarbore.
Functia MaxLatura returneaza latura maxima pe care o are un patrat cu valoare mean mai mica decat pragul. Subprogramul functioneaza similar cu functia descrisa mai sus. Atunci cand mean este mai mic sau egal cu pragul de returneaza lungimea laturii, iar la final se returneaza maximul dintre cei patru subarbori.

In main, mai intai sa verifica daca toti pixelii din imagine ar avea aceeasi culorare dupa compresie. Daca da, atunci numarul de nivele si numarul de blocuri vor fi 1, iar latura maxima va fi lungimea sau latimea imaginii. Se afiseaza aceste data in fisier. Daca nu, se construieste arborele, iar apoi, se apeleaza functiile descrise mai sus si se afiseaza valorile pe care le returneaza.
La final, se fac dezalocarile necesare.

# Cerinta 2:
Construirea arborelui si a matricei imagine se face exact ca la cerinta anterioara. Apoi, scriem in fisier lungimea imaginii.
Pentru parcurgerea si afisarea pe nivele a informatiilor despre arbore, am folosit o coada. Inseram radacina in coada. Cat timp coada nu este vida, extrag din coada un nod. Daca este frunza, afisez in fisier valoarea 1 si culorile red, green, blue ale frunzei. Daca este nod intern, afisez in fisier valoarea 0 si ii adaug toti fii in coada. Am implementata acest algoritm in functia AfisareImg, care este apelata in main.
La final, se fac dezalocarile necesare.

# Cerinta 3:
Mai intai, citim lungimea imaginii din fisier.
Am definit doua functii ajutatoare ConstrArboreCompr si ConstrImg.
Prima functie citeste imaginea dintr-un fisier binar ca cel rezultat de la cerinta doi si construieste arborele de compresie. Pentru acest lucru, am folosit o coada. Primul lucru pe care il facem este sa citim valoarea corespunzatoare radacinii din fisier. Daca este 0, inseram radacina in coada, iar daca este 1, citim culoarile corespunzatoare valorilor red, green, blue si i le atribuim radacinii. Cat timp coada nu e goala (si fisierul nu e gol), extragem un nod, ii alocam patru fii Apoi citim valorile pentru cei patru fii. Daca un fiu are valoarea 1, se citesc si se atribuie culorile. Daca are valoarea 0, nodul este inserat in coada.
A doua functie construieste imaginea din arborele de compresie. Aceasta primeste ca parametri arborele, imaginea creati in main si indicii punctului de inceput si final ai imaginii (La apelul in main ei sunt 0,0 si lingime,lungime). Daca nodul curent este frunza, se atribuie culoarea portiunii din imagine corespunzatoare (Fiecare pixel din subimagine primeste valorile red, green, blue ale nodului). Daca nu, se fac apelurile recursive pentru cei patru fii.
In main, afisam in fisier tipul imaginii P6, lungimea imaginii de doua ori (imaginile fiind patratice) si valoarea maxima 255 pe care pot sa o aiba red, green, blue. Apoi este parcursa matricea imaginii si afisate valorile red, green, blue pentru fiecare element in ordine.
La final se fac dezalocarile necesare.
