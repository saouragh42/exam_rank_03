#include <stdio.h>
#include <stdlib.h>

void afficher_sous_ensemble(int *ensemble, int *chemin, int taille)
{
    int i = -1;
    int premier = 1;

    while (++i < taille)
    {
        if (chemin[i])
        {
            if (!premier)
                printf(" ");
            printf("%d", ensemble[i]);
            premier = 0;
        }
    }
    printf("\n");
}

void explorer(int *ensemble, int *chemin, int taille, int indice, int somme, int cible)
{
    if (indice == taille)
    {
        if (somme == cible)
            afficher_sous_ensemble(ensemble, chemin, taille);
        return ;
    }
    // on choisit d'inclure l'élément courant
    chemin[indice] = 1;
    explorer(ensemble, chemin, taille, indice + 1, somme + ensemble[indice], cible);

    // on choisit de ne pas inclure l'élément courant
    chemin[indice] = 0;
    explorer(ensemble, chemin, taille, indice + 1, somme, cible);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
        return (1);

    int cible = atoi(argv[1]);
    int taille = argc - 2;

    int *ensemble = malloc(sizeof(int) * taille);
    int *chemin = calloc(taille, sizeof(int));
    if (!ensemble || !chemin)
        return (1);

    int i = 0;
    while (i < taille)
    {
        ensemble[i] = atoi(argv[i + 2]);
        i++;
    }

    explorer(ensemble, chemin, taille, 0, 0, cible);

    free(ensemble);
    free(chemin);
    return (0);
}
