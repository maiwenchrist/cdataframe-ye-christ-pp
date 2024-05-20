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
        printf("1. Creer un CDataframe vide\n");
        printf("2. Remplir le CDataframe a partir de saisies utilisateurs\n");
        printf("3. Remplir le CDataframe en dur\n");
        printf("4. Afficher tout le CDataframe\n");
        printf("5. Afficher une partie des lignes du CDataframe\n");
        printf("6. Afficher une partie des colonnes du CDataframe\n");
        printf("7. Ajouter une ligne\n");
        printf("8. Supprimer une ligne\n");
        printf("9. Ajouter une colonne\n");
        printf("10. Supprimer une colonne\n");
        printf("11. Renommer une colonne\n");
        printf("12. Verifier l'existence d'une valeur\n");
        printf("13. Acceder/remplacer une valeur\n");
        printf("14. Afficher les noms des colonnes\n");
        printf("15. Afficher le nombre de lignes\n");
        printf("16. Afficher le nombre de colonnes\n");
        printf("17. Nombre de cellules contenant une valeur egale à x\n");
        printf("18. Nombre de cellules contenant une valeur superieure à x\n");
        printf("19. Nombre de cellules contenant une valeur inferieure à x\n");
        printf("20. Quitter\n");
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
                printf("Entrez la limite de lignes : ");
                int limite_lignes;
                scanf("%d", &limite_lignes);
                print_partial_dataframe(df, limite_lignes);
                break;
            case 6:
                printf("Entrez la limite de colonnes : ");
                int limite_colonnes;
                scanf("%d", &limite_colonnes);
                print_partial_columns(df, limite_colonnes);
                break;
            case 7:
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
            case 8:
            {
                int row;
                printf("Indice de la ligne à supprimer: ");
                scanf("%d", &row);
                remove_row(df, row);
                printf("Ligne supprimée.\n");
            }
                break;
            case 9:
                printf("Titre de la nouvelle colonne : ");
                char title[50];
                scanf("%s", title);
                COLUMN *new_column = create_column(title);
                add_column_to_dataframe(df, new_column);
                printf("Colonne ajoutée.\n");
                break;
            case 10:
                printf("Indice de la colonne à supprimer : ");
                int col_index;
                scanf("%d", &col_index);
                remove_col(df, col_index);
                printf("Colonne supprimée.\n");
                break;
            case 11:
                printf("Indice de la colonne à renommer : ");
                int col_idx;
                scanf("%d", &col_idx);
                printf("Nouveau titre : ");
                char new_title[50];
                scanf("%s", new_title);
                rename_col(df->columns[col_idx], new_title);
                printf("Colonne renommée.\n");
                break;
                // Additional cases for other options should be implemented here
            case 20:
                printf("Programme terminé.\n");
                break;
            default:
                printf("Choix invalide.\n");
                break;
        }
    } while (choice != 20);

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
