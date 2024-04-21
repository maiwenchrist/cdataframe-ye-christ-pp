# cdataframe-ye-christ-pp

# CDataframe

CDataframe est un projet en langage C qui permet de stocker des données dans une structure composée d'un ensemble 
de colonnes, chaque colonne ayant un titre et stockant un nombre indéfini de données de même type.

## Structure du Projet

Le projet est divisé en plusieurs fichiers :

* column.h : Définit la structure et les opérations sur une colonne.
* column.c : Implémente les opérations sur une colonne.
* cdataframe.h : Définit la structure et les opérations sur un CDataframe (ensemble de colonnes).
* cdataframe.c : Implémente les opérations sur un CDataframe.

## Fonctionnalités Implémentées

### Gestion des Colonnes (column.h, column.c)

* Création d'une colonne : Column *create_column(char *title)
* Insertion d'une valeur dans une colonne : int insert_value(Column *col, int value)
* Libération de l'espace alloué par une colonne : void delete_column(Column **col)
* Affichage du contenu d'une colonne : void print_col(Column *col)
* Nombre d'occurrences d'une valeur dans une colonne : int count_occurrences(Column *col, int x)
* Récupération de la valeur à une position donnée dans une colonne : int get_value_at_position(Column *col, int x)
* Nombre de valeurs supérieures à une valeur donnée dans une colonne : int count_values_greater_than_x(Column *col, int x)
* Nombre de valeurs inférieures à une valeur donnée dans une colonne : int count_values_less_than_x(Column *col, int x)
* Nombre de valeurs égales à une valeur donnée dans une colonne : int count_values_equal_to_x(Column *col, int x)

### Gestion du CDataframe (cdataframe.h, cdataframe.c)

* Création d'un CDataframe vide : CDataframe* create_dataframe()
* Remplissage du CDataframe à partir de saisies utilisateur : void fill_dataframe_from_user_input(CDataframe *df)
* Remplissage en dur du CDataframe : void fill_dataframe_hardcoded(CDataframe *df)
* Ajout d'une colonne au CDataframe : void add_column_to_dataframe(CDataframe *df, Column *col)
* Affichage de tout le CDataframe : void print_dataframe(CDataframe *df)
* Affichage d'une partie des lignes du CDataframe selon une limite donnée : void print_partial_dataframe(CDataframe *df, int limite)
* Affichage d'une partie des colonnes du CDataframe selon une limite donnée : void print_partial_columns(CDataframe *df, int limite)
* Suppression du CDataframe et libération de la mémoire : void delete_dataframe(CDataframe **df)

## Comment Utiliser

1. Inclure les fichiers d'en-tête nécessaires dans votre programme.
2. Créer une colonne à l'aide de create_column.
3. Manipuler la colonne en utilisant les fonctions disponibles dans column.h et column.c.
4. Créer un CDataframe à l'aide de create_dataframe.
5. Ajouter des colonnes au CDataframe à l'aide de add_column_to_dataframe.
6. Manipuler le CDataframe en utilisant les fonctions disponibles dans cdataframe.h et cdataframe.c.