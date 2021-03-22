#include <stdlib.h>
#include <stdio.h>

#include <contact.h>

struct contact {
    const char *name;
    const char *num;
    struct contact *suiv;
};

void insert(struct contact **lc, const char *name, const char *num) {
    struct contact *new_contact = malloc(sizeof(struct contact));
    struct contact *first = *lc;
    new_contact->suiv = NULL;
    new_contact->name = name;
    new_contact->num = num;

    if (*lc != NULL) {
        while ((*lc)->suiv != NULL) {
            *lc = (*lc)->suiv;
        }
        (*lc)->suiv = new_contact;
        *lc = first;
    } else {
        *lc = new_contact;
    }
}

void replace(struct contact **lc, const char *name, const char *num) {
    struct contact *first = *lc;

    if (*lc != NULL) {
        while ((*lc)->suiv != NULL) {
            if ((*lc)->name == name) {
                (*lc)->num = num;
                *lc = first;
                return;
            }
            *lc = (*lc)->suiv;
        }
        *lc = first;
    }
}

const char * find(struct contact **lc, const char *name) {
    struct contact *first = *lc;
    const char *num = NULL;

    if ((*lc) != NULL) {
        while ((*lc) != NULL) {
            if ((*lc)->name == name) {
                num = (*lc)->num;
                break;
            }
            *lc = (*lc)->suiv;
        }
        *lc = first;
    }

    return num;
}

void delete_elem(struct contact **lc, const char *name) {
    struct contact *first = *lc;

    if ((*lc)->name == name) {
        *lc = (*lc)->suiv;
    } else {
        while ((*lc)->suiv != NULL) {
            if (((*lc)->suiv)->name == name) {
                struct contact *to_suppr = (*lc)->suiv;
                (*lc)->suiv = ((*lc)->suiv)->suiv;
                free(to_suppr);
                break;
            }
            *lc = (*lc)->suiv;
        }
        *lc = first;
    }
}

void free_list(struct contact *lc) {
    struct contact *next_contact = lc;
    while (lc != NULL) {
        next_contact = next_contact->suiv;
        free(lc);
        lc = next_contact;
    }
}

void display(struct contact *lc) {
    while (lc != NULL) {
        printf("%s : %s\n", lc->name, lc->num);
        lc = lc->suiv;
    }
}