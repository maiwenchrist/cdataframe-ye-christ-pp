#include <stdio.h>
#include <stdlib.h>
#include "cdataframe.h"

int main() {
    printf("Bienvenue dans le excel en CDataframe.\n\n");

    CDataframe *df = create_dataframe();
    if (df == NULL) {
        printf("Erreur lors de la creation du CDataframe.\n");
        return 1;
    }

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Créer un CDataframe vide\n");
        printf("2. Remplir le CDataframe à partir de saisies utilisateurs\n");
        printf("3. Remplir le CDataframe en dur\n");
        printf("4. Afficher tout le CDataframe\n");
        printf("5. Ajouter une ligne\n");
        printf("6. Supprimer une ligne\n");
        printf("7. Ajouter une colonne\n");
        printf("8. Supprimer une colonne\n");
        printf("9. Renommer une colonne\n");
        printf("10. Vérifier l'existence d'une valeur\n");
        printf("11. Accéder/remplacer une valeur\n");
        printf("12. Afficher les noms des colonnes\n");
        printf("13. Afficher le nombre de lignes\n");
        printf("14. Afficher le nombre de colonnes\n");
        printf("15. Nombre de cellules contenant une valeur égale à x\n");
        printf("16. Nombre de cellules contenant une valeur supérieure à x\n");
        printf("17. Nombre de cellules contenant une valeur inférieure à x\n");
        printf("18. Quitter\n");
        printf("Choix: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                df = create_dataframe();
                if (df == NULL) {
                    printf("Erreur lors de la creation du CDataframe.\n");
                } else {
                    printf("CDataframe créé.\n");
                }
                break;
            case 2:
            {
                int column_count, row_count;
                printf("Nombre de colonnes: ");
                scanf("%d", &column_count);
                printf("Nombre de lignes: ");
                scanf("%d", &row_count);
                fill_dataframe_from_user_input(df);
            }
                break;
            case 3:
                fill_dataframe_hardcoded(df);
                printf("CDataframe rempli en dur.\n");
                break;
            case 4:
                print_dataframe(df);
                break;
            case 5:
            {
                int column_count = df->num_columns;
                int values[column_count];
                printf("Entrez les valeurs de la nouvelle ligne:\n");
                for (int i = 0; i < column_count; i++) {
                    printf("Valeur pour la colonne %s: ", df->columns[i]->title);
                    scanf("%d", &values[i]);
                }
                add_row(df, values);
                printf("Ligne ajoutée.\n");
            }
                break;
            case 6:
            {
                int row;
                printf("Indice de la ligne à supprimer: ");
                scanf("%d", &row);
                remove_row(df, row);
                printf("Ligne supprimée.\n");
            }
                break;
                // Additional cases for other options should be implemented here
            case 18:
                printf("Programme terminé.\n");
                break;
            default:
                printf("Choix invalide.\n");
                break;
        }
    } while (choice != 18);

    // Libération de la mémoire
    for (int i = 0; i < df->num_columns; i++) {
        free(df->columns[i]->title);
        free(df->columns[i]->data);
        free(df->columns[i]);
    }
    free(df->columns);
    free(df);

    return 0;
}
