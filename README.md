# cdataframe-ye-christ-pp

# Description du projet CDataframe

Ce projet est une implémentation d'un tableau de données (DataFrame) en langage C. Il permet de créer, manipuler, afficher et analyser des tableaux de données similaires à ceux utilisés dans des logiciels comme Excel ou des bibliothèques Python comme Pandas.

## Structure du Projet

Le projet est divisé en plusieurs fichiers :

* column.h : Définit la structure et les opérations sur une colonne.
* column.c : Implémente les opérations sur une colonne.
* cdataframe.h : Définit la structure et les opérations sur un CDataframe (ensemble de colonnes).
* cdataframe.c : Implémente les opérations sur un CDataframe.

## Compilation

Pour compiler le projet, assurez-vous d'avoir un compilateur C installé sur votre machine. Utilisez la commande suivante pour compiler tous les fichiers source et générer un exécutable :

        *gcc -o dataframe main.c cdataframe. column.c
        
Cette commande créera un exécutable nommé dataframe.

## Exécution

Pour exécuter le programme, utilisez la commande suivante :

        *./dataframe

## Utilisation

Le programme offre un menu interactif qui vous permet de choisir parmi différentes options pour manipuler le DataFrame. Voici les options disponibles :

###Alimentation

 *Créer un DataFrame vide : Crée un DataFrame sans colonnes ni lignes.
 *Remplir le DataFrame à partir de saisies utilisateur : Permet de créer des colonnes et d'y ajouter des valeurs via des saisies utilisateur.
 *Remplir le DataFrame en dur : Remplit le DataFrame avec des valeurs prédéfinies (hardcoded).
        
###Affichage

*Afficher tout le DataFrame : Affiche toutes les données contenues dans le DataFrame.
*Afficher une partie des lignes du DataFrame : Affiche un nombre spécifié de lignes du DataFrame.
*Afficher une partie des colonnes du DataFrame : Affiche un nombre spécifié de colonnes du DataFrame.
        
###Opérations usuelles

        *Ajouter une ligne : Ajoute une nouvelle ligne au DataFrame.
        *Supprimer une ligne : Supprime une ligne spécifiée du DataFrame.
        *Ajouter une colonne : Ajoute une nouvelle colonne au DataFrame.
        *Supprimer une colonne : Supprime une colonne spécifiée du DataFrame.
        *Renommer une colonne : Renomme une colonne spécifiée du DataFrame.
        *Vérifier l'existence d'une valeur : Vérifie si une valeur spécifiée existe dans le DataFrame.
        *Accéder/remplacer une valeur : Accède ou remplace une valeur spécifiée dans le DataFrame.
        *Afficher les noms des colonnes : Affiche les noms de toutes les colonnes du DataFrame.
        
###Analyse et statistiques

        *Afficher le nombre de lignes : Affiche le nombre de lignes dans le DataFrame.
        *Afficher le nombre de colonnes : Affiche le nombre de colonnes dans le DataFrame.
        *Nombre de cellules contenant une valeur égale à x : Compte le nombre de cellules contenant une valeur égale à une valeur spécifiée.
        *Nombre de cellules contenant une valeur supérieure à x : Compte le nombre de cellules contenant une valeur supérieure à une valeur spécifiée.
        *Nombre de cellules contenant une valeur inférieure à x : Compte le nombre de cellules contenant une valeur inférieure à une valeur spécifiée.
        *Quitter : Quitte le programme.

###Navigation dans le menu

        *Utilisez les numéros affichés dans le menu pour choisir une option. Par exemple, pour créer un DataFrame vide, entrez 1 et appuyez sur Entrée.

##Exemples

Voici quelques exemples d'utilisation des options du menu :

        *Pour créer un DataFrame vide, choisissez l'option 1.
        *Pour ajouter une colonne, choisissez l'option 9 et suivez les instructions à l'écran pour entrer le nom de la colonne et ses valeurs.
        *Pour afficher tout le DataFrame, choisissez l'option 4.
        
##Libération de la mémoire

Le programme prend soin de libérer la mémoire allouée pour le DataFrame avant de quitter. Si vous rencontrez des problèmes de mémoire, assurez-vous que le programme se termine             correctement.

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
