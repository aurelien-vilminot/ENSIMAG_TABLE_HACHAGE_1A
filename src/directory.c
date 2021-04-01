#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <directory.h>
#include <contact.h>
#include <hash.h>

/*
  Crée un nouvel annuaire contenant _len_ listes vides.
*/
struct dir {
    struct contact **tab_contacts;
    uint32_t len;
    float nb_contacts;
};

/*
  Effectue un contrôle de la taille de la table de hachage
*/
static void resize_of_table(struct dir *dir);

/*
  Change la taille de la table de hachage
*/
static void change_tab_contact_size(struct dir *dir, uint32_t new_len);

struct dir *dir_create(uint32_t len)
{
    struct contact **tab_contacts = malloc(len * sizeof(struct contact*));
    for (uint32_t i = 0 ; i  < len ; ++i) {
        tab_contacts[i] = NULL;
    }
    struct dir *dir = malloc(sizeof(struct dir));
    dir->tab_contacts = tab_contacts;
    dir->len = len;
    dir->nb_contacts = 0.0;
    return dir;
}

/*
  Insère un nouveau contact dans l'annuaire _dir_, construit à partir des nom et
  numéro passés en paramètre. Si il existait déjà un contact du même nom, son
  numéro est remplacé et la fonction retourne une copie de l'ancien numéro.
  Sinon, la fonction retourne NULL.
*/
char *dir_insert(struct dir *dir, const char *name, const char *num)
{
    ++dir->nb_contacts;
    resize_of_table(dir);

    const char *search_result = dir_lookup_num(dir, name);
    uint32_t index = hash(name) % dir->len;

    char *old_num = NULL;

    if (search_result == NULL) {
        insert(&(dir->tab_contacts[index]), name, num);
    } else {
        replace(&(dir->tab_contacts[index]), name, num);
        old_num = malloc(strlen(search_result) + 1);
        strcpy(old_num, search_result);
    }
    return old_num;
}

/*
  Retourne le numéro associé au nom _name_ dans l'annuaire _dir_. Si aucun contact
  ne correspond, retourne NULL.
*/
const char *dir_lookup_num(struct dir *dir, const char *name)
{
    uint32_t index = hash(name) % dir->len;
    return find(&(dir->tab_contacts[index]), name);
}

/*
  Supprime le contact de nom _name_ de l'annuaire _dir_. Si aucun contact ne
  correspond, ne fait rien.
*/
void dir_delete(struct dir *dir, const char *name)
{
    if (dir_lookup_num(dir, name) != NULL) {
        uint32_t index = hash(name) % dir->len;
        delete_elem(&(dir->tab_contacts[index]), name);
        --dir->nb_contacts;
    }
    resize_of_table(dir);
}

/*
  Libère la mémoire associée à l'annuaire _dir_.
*/
void dir_free(struct dir *dir)
{
    for (uint32_t i = 0 ; i < dir->len ; ++i) {
        free_list(dir->tab_contacts[i]);
    }
    free(dir->tab_contacts);
    free(dir);
}

/*
  Affiche sur la sortie standard le contenu de l'annuaire _dir_.
*/
void dir_print(struct dir *dir)
{
    for (uint32_t i = 0 ; i < dir->len ; ++i) {
        printf("Chaine %u : ", i);
        display(dir->tab_contacts[i]);
        printf("\n");
    }
    printf("\n");
}

/*
  Effectue un contrôle de la taille de la table de hachage
*/
void resize_of_table(struct dir *dir) {
    float occupation = dir->nb_contacts / dir->len;
    if (occupation > 0.75) {
        change_tab_contact_size(dir, dir->len * 2);
    } else if (occupation < 0.15 && dir->len > 10) {
        uint32_t new_len = (dir->len/2) > 10 ? dir->len/2 : 10;
        change_tab_contact_size(dir, new_len);
    }
}

/*
  Change la taille de la table de hachage en récréant tab_contacts
  Récupère l'ensemble des contacts dans chaque liste chaînée et les remet en place dans le nouveau tableau
  Libère de la mémoire des contacts dans l'ancien tableau
*/
void change_tab_contact_size(struct dir *dir, uint32_t new_len) {
    struct contact **tab_contacts = malloc(new_len * sizeof(struct contact*));
    for (uint32_t i = 0 ; i  < new_len ; ++i) {
        tab_contacts[i] = NULL;
    }

    for (size_t i = 0 ; i  < dir->len ; ++i) {
        uint32_t len_linked_list = get_len_list(dir->tab_contacts[i]);
        if (len_linked_list > 0) {
            for (size_t j = 0 ; j < len_linked_list ; ++j) {
                struct contact * m_contact = get_elem_i(&(dir->tab_contacts[i]), j);
                const char * name = get_name(m_contact);
                const char * num = get_num(m_contact);

                uint32_t new_index = hash(name) % new_len;
                insert(&(tab_contacts[new_index]), name, num);
            }
        }
    }

    for (uint32_t i = 0 ; i < dir->len ; ++i) {
        free_list(dir->tab_contacts[i]);
    }
    free(dir->tab_contacts);
    dir->tab_contacts = tab_contacts;
    dir->len = new_len;
}
