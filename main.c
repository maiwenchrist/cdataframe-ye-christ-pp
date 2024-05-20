#include <stdio.h>
#include "cdataframe.h"

int main() {
    printf("Bienvenue dans le excel en CDataframe.\n");

    CDataframe *df = create_dataframe();
    if (df == NULL) {
        printf("Erreur lors de la creation du CDataframe.\n");
        return 1;
    }
    int choice;
    do {
        printf("\nMenu:\n\n");

        printf("--- Alimentation ---\n\n");

        printf("1. Creer un CDataframe vide\n");
        printf("2. Remplir le CDataframe a partir de saisies utilisateurs\n");
        printf("3. Remplir le CDataframe en dur\n\n");

        printf("--- Affichage ---\n\n");

        printf("4. Afficher tout le CDataframe\n");
        printf("5. Afficher une partie des lignes du CDataframe\n");
        printf("6. Afficher une partie des colonnes du CDataframe\n\n");

        printf("--- Operations usuelles ---\n\n");

        printf("7. Ajouter une ligne\n");
        printf("8. Supprimer une ligne\n");
        printf("9. Ajouter une colonne\n");
        printf("10. Supprimer une colonne\n");
        printf("11. Renommer une colonne\n");
        printf("12. Verifier l'existence d'une valeur\n");
        printf("13. Acceder/remplacer une valeur\n");
        printf("14. Afficher les noms des colonnes\n\n");

        printf("--- Analyse et statistiques ---\n\n");

        printf("15. Afficher le nombre de lignes\n");
        printf("16. Afficher le nombre de colonnes\n");
        printf("17. Nombre de cellules contenant une valeur egale a x\n");
        printf("18. Nombre de cellules contenant une valeur superieure a x\n");
        printf("19. Nombre de cellules contenant une valeur inferieure a x\n");
        printf("20. Quitter\n");
        printf("\n");
        printf("Choix: ");
        scanf("%d", &choice);

        // Vérification de la validité du choix
        if (choice < 1 || choice > 20) {
            printf("Choix invalide. Veuillez saisir un nombre entre 1 et 20.\n");
            continue; // Passer à l'itération suivante de la boucle do-while
        }

        switch (choice) {
            case 1:
                df = create_dataframe();
                if (df == NULL) {
                    printf("Erreur lors de la creation du CDataframe.\n");
                } else {
                    printf("CDataframe cree.\n");
                }
                break;
            case 2:
                fill_dataframe_from_user_input(df);
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
                int limit;
                printf("Limite de lignes a afficher: ");
                scanf("%d", &limit);
                print_partial_dataframe(df, limit);
            }
                break;
            case 6:
            {
                int limit;
                printf("Limite de colonnes a afficher: ");
                scanf("%d", &limit);
                print_partial_columns(df, limit);
            }
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
                printf("Ligne ajoutee.\n");
            }
                break;
            case 8:
            {
                int row;
                printf("Indice de la ligne a supprimer: ");
                scanf("%d", &row);
                remove_row(df, row);
                printf("Ligne supprimee.\n");
                break; // Ajoute cette instruction pour sortir du switch après avoir supprimé la ligne
            }

            case 9:
            {
                // Saisir le nom de la nouvelle colonne
                char new_column_name[100];
                printf("Nom de la nouvelle colonne: ");
                scanf("%s", new_column_name);

                // Créer une nouvelle colonne
                COLUMN *new_column = create_column(new_column_name);
                if (new_column == NULL) {
                    printf("Erreur lors de la creation de la colonne.\n");
                    break;
                }

                // Ajouter la colonne au CDataframe
                add_column_to_dataframe(df, new_column);

                // Saisir le nombre de lignes pour la nouvelle colonne
                int num_rows;
                printf("Nombre de lignes pour la nouvelle colonne: ");
                scanf("%d", &num_rows);

                // Saisir les valeurs pour la nouvelle colonne
                int value;
                for (int i = 0; i < num_rows; i++) {
                    printf("Valeur pour la ligne %d: ", i + 1);
                    scanf("%d", &value);
                    insert_value(new_column, value); // Insère la valeur dans la nouvelle colonne
                }

                printf("Colonne ajoutee avec les valeurs.\n");
            }
                break;
            case 10:
            {
                // Afficher les noms des colonnes pour que l'utilisateur puisse choisir
                printf("Colonnes existantes :\n");
                for (int i = 0; i < df->num_columns; i++) {
                    printf("%d. %s\n", i + 1, df->columns[i]->title);
                }

                int column_index;
                printf("Indice de la colonne a supprimer (entre 1 et %d): ", df->num_columns);
                scanf("%d", &column_index);

                // Vérifier si l'indice est valide
                if (column_index < 1 || column_index > df->num_columns) {
                    printf("Indice de colonne invalide.\n");
                    break;
                }

                // Appel de la fonction remove_column pour supprimer la colonne
                remove_column(df, column_index - 1);

                printf("Colonne supprimee.\n");
            }
                break;

            case 11:
            {
                // Afficher les noms des colonnes pour que l'utilisateur puisse choisir
                printf("Colonnes existantes :\n");
                for (int i = 0; i < df->num_columns; i++) {
                    printf("%d. %s\n", i + 1, df->columns[i]->title);
                }

                int column_index;
                printf("Indice de la colonne a renommer (entre 1 et %d): ", df->num_columns);
                scanf("%d", &column_index);

                // Vérifier si l'indice est valide
                if (column_index < 1 || column_index > df->num_columns) {
                    printf("Indice de colonne invalide.\n");
                    break;
                }

                // Saisir le nouveau titre pour la colonne
                char new_title[100];
                printf("Nouveau titre pour la colonne : ");
                scanf("%s", new_title);

                // Appel de la fonction rename_column pour renommer la colonne
                rename_column(df, column_index - 1, new_title);

                printf("Colonne renommee.\n");
            }
                break;

            case 12:
            {
                int value;
                printf("Valeur a verifier : ");
                scanf("%d", &value);

                // Appel de la fonction value_exists pour vérifier si la valeur existe dans le dataframe
                if (value_exists(df, value)) {
                    printf("La valeur %d existe dans le CDataframe.\n", value);
                } else {
                    printf("La valeur %d n'existe pas dans le CDataframe.\n", value);
                }
            }
                break;

            case 13:
            {
                int row, col_index, new_value;
                printf("Indice de la ligne : ");
                scanf("%d", &row);

                printf("Indice de la colonne : ");
                scanf("%d", &col_index);

                printf("Nouvelle valeur : ");
                scanf("%d", &new_value);

                if (row < 1 || row > num_rows(df) || col_index < 1 || col_index > num_cols(df)) {
                    printf("Indices de ligne ou de colonne invalides.\n");
                } else {
                    // Utiliser row - 1 et col_index - 1 car les indices commencent à partir de 0 dans le code
                    // mais l'utilisateur saisit les indices à partir de 1
                    set_value(df, row - 1, col_index - 1, new_value);
                    printf("La valeur a ete remplacee avec succes.\n");
                }
                break;
            }


            case 14:
                print_column_titles(df);
                break;

            case 15:
                printf("Nombre de lignes: %d\n", num_rows(df));
                break;


            case 16:
                printf("Nombre de colonnes: %d\n", num_cols(df));
                break;

            case 17:
            {
                int x;
                printf("Entrez la valeur x : ");
                scanf("%d", &x);
                int count_equal = count_cells_equal_to_x(df, x);
                printf("Nombre de cellules contenant la valeur %d : %d\n", x, count_equal);
                break;
            }

            case 18:
            {
                int x;
                printf("Entrez la valeur x : ");
                scanf("%d", &x);
                int count_greater = count_cells_greater_than_x(df, x);
                printf("Nombre de cellules contenant une valeur superieure a %d : %d\n", x, count_greater);
                break;
            }
            case 19:
            {
                int x;
                printf("Entrez la valeur x : ");
                scanf("%d", &x);
                int count_less = count_cells_less_than_x(df, x);
                printf("Nombre de cellules contenant une valeur inferieure a %d : %d\n", x, count_less);
                break;
            }

                // Cases supplémentaires pour les autres options
            case 20:
                printf("Programme termine.\n");
                break;
            default:
                printf("Choix invalide.\n");
                break;
        }

    } while (choice != 20);

    // Libération de la mémoire
    delete_dataframe(&df);

    return 0;
}


