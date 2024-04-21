#include <stdio.h>
#include "cdataframe.h"

int main() {
    printf("Bienvenue dans le excel en CDataframe.\n\n");

    // Création d'un CDataframe vide
    printf("1. Creer un CDataframe vide\n");
    CDataframe *df = create_dataframe();
    if (df == NULL) {
        printf("Erreur lors de la creation du CDataframe.\n");
        return 1;
    }
    printf("CDataframe cree avec succes.\n\n");

    int choix;
    do {
        printf("1. Remplir le CDataframe a partir de saisies utilisateur\n");
        printf("2. Remplir le CDataframe en dur\n");
        printf("3. Afficher tout le CDataframe\n");
        printf("4. Afficher une partie des lignes du CDataframe\n");
        printf("5. Afficher une partie des colonnes du CDataframe\n");
        printf("6. Quitter\n\n");
        printf("Choisissez une option : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                fill_dataframe_from_user_input(df);
                break;
            case 2:
                fill_dataframe_hardcoded(df);
                break;
            case 3:
                print_dataframe(df);
                break;
            case 4:
                printf("Entrez la limite de lignes : ");
                int limite_lignes;
                scanf("%d", &limite_lignes);
                print_partial_dataframe(df, limite_lignes);
                break;
            case 5:
                printf("Entrez la limite de colonnes : ");
                int limite_colonnes;
                scanf("%d", &limite_colonnes);
                print_partial_columns(df, limite_colonnes);
                break;
            case 6:
                printf("Programme termine.\n");
                break;
            default:
                printf("Option invalide. Veuillez entrer un nombre entre 1 et 6.\n");
        }
    } while (choix != 6);

    // Libération de la mémoire allouée pour le CDataframe
    delete_dataframe(&df);

    return 0;
}