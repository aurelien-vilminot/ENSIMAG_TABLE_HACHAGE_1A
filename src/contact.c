#include <stdlib.h>
#include <stdio.h>

#include <contact.h>

/*
 * Structure contact sous forme de liste chaînée
 */
struct contact {
    const char *name;
    const char *num;
    struct contact *suiv;
};

/*
 * Insert en queue un contact dans la liste chaînée _lc_
 */
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

/*
 * Remplace un contact existant par son nouveau numéro de téléphone
 */
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

/*
 * Cherche un contact _name_ dans la liste chaînée _lc_ et renvoie son numéro ou NULL si pas trouvé
 */
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

/*
 * Supprime un contact _name_ et libère la mémoire
 */
void delete_elem(struct contact **lc, const char *name) {
    struct contact *first = *lc;

    if ((*lc)->name == name) {
        struct contact *to_suppr = *lc;
        *lc = (*lc)->suiv;
        free(to_suppr);
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

/*
 * Libère la mémoire de chaque contact
 */
void free_list(struct contact *lc) {
    struct contact *next_contact = lc;
    while (lc != NULL) {
        next_contact = next_contact->suiv;
        free(lc);
        lc = next_contact;
    }
}

/*
 * Affiche chaque contact d'une liste _lc_
 */
void display(struct contact *lc) {
    while (lc != NULL) {
        printf("[%s : %s], ", lc->name, lc->num);
        lc = lc->suiv;
    }
}

/*
 * Retourne le nombre d'éléments contenus dans la liste chaînée _lc_
 */
uint32_t get_len_list(struct contact *lc) {
    uint32_t len_linked_list = 0;
    while (lc != NULL) {
        ++len_linked_list;
        lc = lc->suiv;
    }
    return len_linked_list;
}

/*
 * Retourne le ième contact de la liste chaînée _lc_
 * La valeur de retour est une structure contact
 */
struct contact * get_elem_i(struct contact **lc, uint32_t i) {
    struct contact *first = *lc;
    uint32_t compt = 0;

    if (i == 0) {
        return *lc;
    } else {
        while (*lc != NULL) {
            if (compt == i) {
                struct contact *tmp = *lc;
                *lc = first;
                return tmp;
            }
            ++compt;
            *lc = (*lc)->suiv;
        }
        *lc = first;
    }
    return NULL;
}

/*
 * Retourne le nom associé à un contact
 */
const char * get_name(struct contact *m_contact) {
    return m_contact->name;
}

/*
 * Retourne le numéro associé à un contact
 */
const char * get_num(struct contact *m_contact) {
    return m_contact->num;
}