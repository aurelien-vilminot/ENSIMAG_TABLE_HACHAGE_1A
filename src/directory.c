#include <stdlib.h>
#include <stdio.h>

#include <directory.h>
#include <contact.h>
#include <hash.h>

/*
  Crée un nouvel annuaire contenant _len_ listes vides.
*/
struct dir {
    struct contact *tab_list[0];
    uint32_t taille;
};

struct dir *dir_create(uint32_t len)
{
    struct contact *m_tab[len];
    struct dir *m_dir = {m_tab, len};
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
    char *search_result = dir_lookup_num(dir, name);
    uint32_t index = hash(name) % dir->taille;
    if (search_result == NULL) {
        insert(&(dir->tab_list[index]), name, num);
        return NULL;
    } else {
        replace(&(dir->tab_list[index]), name, num);
        return search_result;
    }
}

/*
  Retourne le numéro associé au nom _name_ dans l'annuaire _dir_. Si aucun contact
  ne correspond, retourne NULL.
*/
const char *dir_lookup_num(struct dir *dir, const char *name)
{
    uint32_t index = hash(name) % dir->taille;
    return find(&(dir->tab_list[index]), name);
}

/*
  Supprime le contact de nom _name_ de l'annuaire _dir_. Si aucun contact ne
  correspond, ne fait rien.
*/
void dir_delete(struct dir *dir, const char *name)
{
    if (dir_lookup_num(dir, name) != NULL) {
        uint32_t index = hash(name) % dir->taille;
        delete(&(dir->tab_list[index]), name);
    }
}

/*
  Libère la mémoire associée à l'annuaire _dir_.
*/
void dir_free(struct dir *dir)
{
    (void)dir;
}

/*
  Affiche sur la sortie standard le contenu de l'annuaire _dir_.
*/
void dir_print(struct dir *dir)
{
    for (uint32_t i = 0 ; i < dir->taille ; ++i) {
        display(dir->tab_list[i]);
    }
}
