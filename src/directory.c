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
    struct contact **m_tab;
    uint32_t taille;
};

struct dir *dir_create(uint32_t len)
{
    struct contact **m_tab = malloc(len * sizeof(struct contact*));
    for (uint32_t i = 0 ; i  < len ; ++i) {
        m_tab[i] = NULL;
    }
    struct dir *m_dir = malloc(sizeof(struct dir));
    m_dir->m_tab = m_tab;
    m_dir->taille = len;
    return m_dir;
}

/*
  Insère un nouveau contact dans l'annuaire _dir_, construit à partir des nom et
  numéro passés en paramètre. Si il existait déjà un contact du même nom, son
  numéro est remplacé et la fonction retourne une copie de l'ancien numéro.
  Sinon, la fonction retourne NULL.
*/
char *dir_insert(struct dir *dir, const char *name, const char *num)
{
    const char *search_result = dir_lookup_num(dir, name);
    uint32_t index = hash(name) % dir->taille;
    if (search_result == NULL) {
        insert(&(dir->m_tab[index]), name, num);
        return NULL;
    } else {
        replace(&(dir->m_tab[index]), name, num);
        char *old_num = malloc(sizeof(strlen(search_result)));
        strcpy(old_num, search_result);
        return old_num;
    }
}

/*
  Retourne le numéro associé au nom _name_ dans l'annuaire _dir_. Si aucun contact
  ne correspond, retourne NULL.
*/
const char *dir_lookup_num(struct dir *dir, const char *name)
{
    uint32_t index = hash(name) % dir->taille;
    return find(&(dir->m_tab[index]), name);
}

/*
  Supprime le contact de nom _name_ de l'annuaire _dir_. Si aucun contact ne
  correspond, ne fait rien.
*/
void dir_delete(struct dir *dir, const char *name)
{
    if (dir_lookup_num(dir, name) != NULL) {
        uint32_t index = hash(name) % dir->taille;
        delete_elem(&(dir->m_tab[index]), name);
    }
}

/*
  Libère la mémoire associée à l'annuaire _dir_.
*/
void dir_free(struct dir *dir)
{
    for (uint32_t i = 0 ; i < dir->taille ; ++i) {
        free_list(dir->m_tab[i]);
    }
    free(dir->m_tab);
    free(dir);
}

/*
  Affiche sur la sortie standard le contenu de l'annuaire _dir_.
*/
void dir_print(struct dir *dir)
{
    for (uint32_t i = 0 ; i < dir->taille ; ++i) {
        display(dir->m_tab[i]);
    }
}
