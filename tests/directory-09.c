/*
  Test du module directory.

  Ajout d'un contact déjà existant.
 */

#include <stdlib.h>
#include <stdio.h>

#include <directory.h>

int main(void)
{
    struct dir *dir = dir_create(10);
    dir_insert(dir, "Colonel Moutarde", "06789435351");
    dir_insert(dir, "Caporal Ketchup", "0678346533");
    dir_insert(dir, "Sergent Mayo", "06723236533");
    dir_print(dir);

    const char *names[4] = {
            "Tartempion",
            "Caporal Ketchup",
            "0110656189",
            "0619819841"
    };

    for (size_t id = 0; id < 2; id++) {
        char * return_of_insertion = dir_insert(dir, names[id], names[id + 2]);
        printf("La fonction d'insertion pour %s a retournée la valeur/numéro suivant.e : %s\n", names[id], return_of_insertion);
    }

    dir_print(dir);

    dir_free(dir);

    return EXIT_SUCCESS;
}