#ifndef CALCUL_H_INCLUDED
#define CALCUL_H_INCLUDED

enum {AUTO, MANUEL};

int **initLot(int nbCombinaison);
void genererLot(int **tableau, int nbCombinaison, int typeSaisie);
void libererLot(int **tableau);
int doublon(int *tab, int debut, int tailleTab, int interval, int recherche);
int doublonCombinaison(int **tab, int tailleY, int tailleX, int *recherche);

#endif // CALCUL_H_INCLUDED
