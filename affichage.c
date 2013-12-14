#include <stdio.h>
#include <stdlib.h>

#include "affichage.h"
#include "calcul.h"


void menuGeneraXor()
{
    int choix, choixOk = 0, continuer = 1, nbCombinaison = 500;
    int **lot = NULL;
    while(continuer)
    {
        while(!choixOk)
        {
            printf("GeneraXor\n\n"); // Affichage du menu principal
            printf("Menu Principal\n\n");
            printf("1 : Saisie des combinaisons\n");
            printf("2 : Affichage des combinaisons\n");
            printf("3 : Modifier le nombre de combinaison dans un lot (actuellement %d)\n", nbCombinaison);
            printf("0 : Quitter\n\n");
            printf("Votre choix: ");

            if(scanf("%d", &choix) != 1) // Si l'entrée obtenu n'est pas un nombre
                fflush(stdin);

            if(choix >= 0 && choix <= 3) //Si le nombre est compris entre 0 et 3
                choixOk = 1;

            system("CLS");
        }
        choixOk = 0;

        switch(choix)
        {
        case 1:
            while(!choixOk)
            {
                printf("Saisie des combinaisons :\n\n"); // Affichage du menu de saisie des combinaisons
                printf("1 : Saisie aleatoire de la combinaison\n");
                printf("2 : Saisie manuel de la combinaison\n");
                printf("0 : Retour au menu principal\n\n");
                printf("Votre choix: ");

                if(scanf("%d", &choix) != 1) // Si l'entrée obtenu n'est pas un nombre
                    fflush(stdin);

                if(choix >= 0 && choix <= 2) //Si le nombre est compris entre 0 et 2
                    choixOk = 1;

                system("CLS");
            }


            if(lot != NULL)
                libererLot(lot);

            lot = initLot(nbCombinaison); // Initailisation de la mémoire pour contenir le lot

            switch(choix)
            {
            case 1:
                genererLot(lot, nbCombinaison , AUTO); // Génération du lot en mode automatique
                enregistrerLot(lot, nbCombinaison);
                break;

            case 2:
                genererLot(lot, nbCombinaison , MANUEL); // Génération du lot en mode manuel
                enregistrerLot(lot, nbCombinaison);
                break;

            default:
                break;
            }
            choixOk = 0;
            choix = 0;
            break;

        case 2:
            while(!choixOk)
            {
                printf("Affichage des combinaisons :\n\n"); // Menu pour afficher les combinaisons
                printf("1 : Affichage des combinaisons avec vides\n");
                printf("2 : Affichage des combinaisons sans vides\n");
                printf("0 : Retour au menu principal\n\n");
                printf("Votre choix: ");

                if(scanf("%d", &choix) != 1) // Si l'entrée obtenu n'est pas un nombre
                    fflush(stdin);

                if(choix >= 0 && choix <= 2) //Si le nombre est compris entre 0 et 2
                    choixOk = 1;

                system("CLS");
            }


            if(lot == NULL) // Si le lot n'a pas encore été généré
            {
                printf("ERREUR : Le lot n'a pas encore ete genere !\n\n");
            }
            else
            {
                switch(choix)
                {
                case 1:
                    afficherLot(lot, nbCombinaison, AVEC_VIDE); // Affichage du lot avec les cases vides
                    break;
                case 2:
                    afficherLot(lot, nbCombinaison, SANS_VIDE); // Affichage du lot sans les cases vides
                    break;
                default:
                    break;
                }
            }

            system("PAUSE");

            choixOk = 0;
            choix = 0;
            break;

        case 3:
            while(!choixOk)
            {
                printf("Modifier le nombre de combinaisons dans un lot\n\n"); // Modification du nombre de combinaison dans un lot
                printf("Actuellement le nombre de combinaison est de %d\n", nbCombinaison);
                printf("Entrez le nouveau nombre de combinaisons souhait%c dans la limite de 9999 maximum\n", 130);

                if(scanf("%d", &nbCombinaison) != 1) // Si l'entrée obtenu n'est pas un nombre
                    fflush(stdin);

                if(nbCombinaison >= 1 && nbCombinaison <= 9999) //Si le nombre est compris entre 1 et 9999
                    choixOk = 1;

                system("CLS");
            }
            choixOk = 0;
            choix = 0;
            break;

        case 0:
            continuer = 0;
            break;
        }
        system("CLS");
    }

    if(lot != NULL) // Libération de la mémoire contenant le lot
        libererLot(lot);
}

void afficherLot(int **lot, int nbCombinaison, int vide)
{
    int i, j;
    for(i=0; i<nbCombinaison; i++)
    {
        for(j=0; j<28; j++)
        {
            if(lot[i][j] != 0 && vide == SANS_VIDE)
            {
                printf("%d ", lot[i][j]);
            }
            else
            {
                printf("%d ", lot[i][j]);
            }

        }
        printf("\n");
    }
}

void enregistrerLot(int **tab, int nbCombinaison)
{
    int i, j;
    FILE *fichier = fopen("lot.txt", "w+");
    fprintf(fichier, "%s:%d\n", "NOMLOT", nbCombinaison);
    for(i=0; i<nbCombinaison; i++)
    {
        fprintf(fichier, "%04d", tab[i][0]);
        for(j=1; j<28; j++)
        {
            if(tab[i][j] == 0)
                fputc(':', fichier);
            else
                fprintf(fichier, ":%d", tab[i][j]);
        }

        fputc('\n', fichier);
    }
    fclose(fichier);
}
