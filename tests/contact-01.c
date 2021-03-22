/*
  Test du module contact.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <contact.h>

int main(void)
{
    struct contact *contacts = NULL;

    const char *names[4] = {
            "Jean",
            "Eude",
            "xXHardcoreXx13",
            "c'est un test"
    };

    const char *nums[4] = {
            "0624515789",
            "0218532147",
            "0313648925",
            "0415203286"
    };

    /* Test insertion */

    for (int i = 0; i < 4; i++) {
        insert(&contacts, names[i], nums[i]);
    }

    printf("La liste complète est : \n");
    display(contacts);

    /* Test du find */

    const char * found = find(&contacts, "c'est un test");
    const char * not_found = find(&contacts, "oupsi");

    printf("\nLe résultat doit retourner quelque chose : %s", found);
    printf("\nLe résultat ne doit pas retourner quelque chose : %s\n\n", not_found);

    /* Test remplacement */

    replace(&contacts, "Jean", "0101010101");
    printf("Remplacement du numéro de Jean par 0101010101 :\n");
    display(contacts);

    /* Test suppression et libération de la mémoire */

    srand(time(NULL));

    while (contacts != NULL) {
        delete_elem(&contacts, names[rand() % 4]);
        printf("\nUn élément a été supprimé :\n");
        display(contacts);
    }
    free_list(contacts);

    return EXIT_SUCCESS;
}

