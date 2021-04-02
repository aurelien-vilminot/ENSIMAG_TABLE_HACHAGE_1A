# TP Fil Rouge
***
Introduction aux tables de hachage

##Tests
* contact-01.c permet de tester le bon fonctionnement de la liste chaînée de la structure contact sans être dépendant du code de directory.c
* directory-08.c teste le rétrécissement du directory sur une table de hachage initiale de taille impaire.
* directory-09.c teste l'ajout d'un contact déjà existant dans la table de hachage. Cela permet de tester le bon retour de l'ancien numéro.

##Compilation & Exécution

Se rendre sur terminal Unix, dans le répertoire racine :
$ make clean && make && ./tests/nom_fichier_test

Exécution avec Valgrind :
$ make clean && make && valgrind -s ./tests/nom_fichier_test

##Remerciements
Merci à toi futur.e relecteur.rice !
Profite de ce moment unique pour relire ce sublime code et bon courage :)