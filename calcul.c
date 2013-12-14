#include <stdio.h>
#include <stdlib.h>

#include "calcul.h"

int **initLot(int nbCombinaison)
{
    int i;

    int **tableau = (int**) malloc(nbCombinaison * sizeof(int)); // Alloc du tableau 2D

    if(tableau == NULL)
    {
        exit(EXIT_FAILURE);
    }

    for(i=0; i<nbCombinaison; i++) // Alloc pour chaque combinaison
    {
        tableau[i] = (int*) malloc(28 * sizeof(int));
        if(tableau[i] == NULL)
        {
            exit(EXIT_FAILURE);
        }
    }

    return tableau;
}

void genererLot(int **tableau, int nbCombinaison, int typeSaisie)
{
    int i, j, k;

    int mini[9] = {1, 10, 20, 30, 40, 50, 60, 70, 80};
    int maxi[9] = {9, 19, 29, 39, 49, 59, 69, 79, 90};


    if(typeSaisie == AUTO) // Si on est en tirage automatique
    {
        for(i=0; i<nbCombinaison; i++)
        {
            tableau[i][0] = i+1;
            for(j=0; j<9; j++)
            {
                int tabTemp[3] = {0, 0, 0};
                for(k=0; k<3; k++)
                {
                    tabTemp[k] = (rand() % (maxi[j] - mini[j] + 1)) + mini[j];
                    if(doublon(tabTemp, 0, 3, 1, tabTemp[k]) >= 2) // Gestion des doublons dans une combinaison
                        k--;
                }
                for(k=0; k<3; k++)
                {
                    tableau[i][k*9+j+1] = tabTemp[k];
                }
            }

            for(j=0; j<3; j++)
            {
                int posCasesVide[4] = {0, 0, 0, 0};
                for(k=0; k<4; k++)
                {
                    posCasesVide[k] = (rand() % (8 - 0 + 1)) +0;
                    if(doublon(posCasesVide, 0, 4, 1, posCasesVide[k]) == 2) // Gestion des doublons de position des cases vides
                        k--;
                }
                for(k=0; k<4; k++)
                {
                    tableau[i][j*9+posCasesVide[k]+1] = 0;
                }
            }

            if(doublonCombinaison(tableau, nbCombinaison, 28, tableau[i]) >= 2) // Gestion des combinaisons en double dans le lot
                i--;
        }
    }
    else if(typeSaisie == MANUEL) // Si on est en tirage manuel
    {
        int erreur = 0;
        printf("Saisie du lot en mode manuel\n");
        printf("Veuillez saisir les nombres de la grille sous la forme : 1 2 0 4 ...\n");
        printf("Le 0 represente une case vide\n");
        for(i=0; i<nbCombinaison; i++)
        {
            printf("\nCombinaison de la grille n.%d\n", i+1);
            tableau[i][0] = i+1;
            for(j=0; j<3; j++)
            {
                printf("Ligne %d : ", j+1);
                scanf("%d %d %d %d %d %d %d %d %d", &tableau[i][j*9+1], &tableau[i][j*9+2], &tableau[i][j*9+3], &tableau[i][j*9+4], &tableau[i][j*9+5],
                      &tableau[i][j*9+6], &tableau[i][j*9+7], &tableau[i][j*9+8], &tableau[i][j*9+9]);

                if(doublon(tableau[i], j*9+1, j*9+10, 1, 0) != 4) // Vérification des 4 cases vides par ligne
                {
                    printf("ERREUR : Il faut 4 cases vides par ligne !\n");
                    j--;
                }

                for(k=0; k<9; k++) // Vérification des valeaurs au niveau des lignes
                {
                    if((tableau[i][j*9+k+1] < mini[k] || tableau[i][j*9+k+1] > maxi[k]) && tableau[i][j*9+k+1] != 0)
                    {
                        printf("ERREUR : La valeur de la case %d doit etre comprise entre %d et %d\n", k+1, mini[k], maxi[k]);
                    }
                }
            }
            for(j=0; j<9; j++)
            {
                for(k=mini[j]; k<=maxi[j]; k++)
                {
                    if(doublon(tableau[i], j+1, j+19, 9, k) >= 2)
                    {
                        printf("ERREUR : Colonne %d : il y a 2 fois le nombre %d\n", j+1, k);
                        erreur = 1;
                    }
                }
            }
            if(doublonCombinaison(tableau, nbCombinaison, 28, tableau[i]) >= 2) // Gestion des combinaisons en double dans le lot
            {
                printf("ERREUR : Il y a 2 grilles identiques\n");
                erreur = 1;
            }

            if(erreur)
            {
                erreur = 0;
                i--;
            }

            system("PAUSE");
        }
    }
}

void libererLot(int **tableau)
{
    free(tableau);
}

int doublon(int *tab, int debut, int tailleTab, int interval, int recherche)
{
    int i, c = 0;
    /*for(i=debut; i<tailleTab; i+=interval)
        printf("%d ", tab[i]);*/

    for(i=debut; i<tailleTab; i+=interval) // Parcourt le tableau
        if(tab[i] == recherche) // Si la case en cours contient le nombre recherché
            c++; // On incrémente le nombre d'cccurence trouvé
    /*if(c>1)
        printf("-> doublon");
    printf("\n");*/
    return c;
}

int doublonCombinaison(int **tab, int tailleY, int tailleX, int *recherche)
{
    int i, j, c = 0, d = 0;

    for(i=0; i<tailleY; i++) // Parcourt le tableau
        for(j=1; j<tailleX; j++)
        {
            if(tab[i][j] == recherche[j]) // Si la case en cours contient le nombre recherché
                c++; // On incrémente le nombre d'iccurence trouvé
            if(c == 27)
                d++;
            c = 0;
        }

    return d;
}
