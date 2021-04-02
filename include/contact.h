#ifndef _CONTACT_H_
#define _CONTACT_H_

#include <stdint.h>

/*
 * Structure contact sous forme de liste chaînée
 */
struct contact;

/*
 * Insert en queue un contact dans la liste chaînée _lc_
 */
extern void insert(struct contact **lc, const char *name, const char *num);

/*
 * Remplace un contact existant par son nouveau numéro de téléphone
 */
extern void replace(struct contact **lc, const char *name, const char *num);

/*
 * Cherche un contact _name_ dans la liste chaînée _lc_ et renvoie son numéro ou NULL si pas trouvé
 */
extern const char * find(struct contact **lc, const char *name);

/*
 * Supprime un contact _name_ et libère la mémoire
 */
extern void delete_elem(struct contact **lc, const char *name);

/*
 * Libère la mémoire de chaque contact
 */
extern void free_list(struct contact *lc);

/*
 * Affiche chaque contact d'une liste _lc_
 */
extern void display(struct contact *lc);

/*
 * Retourne le nombre d'éléments contenus dans la liste chaînée _lc_
 */
extern uint32_t get_len_list(struct contact *lc);

/*
 * Retourne le ième contact de la liste chaînée _lc_
 * La valeur de retour est une structure contact
 */
extern struct contact * get_elem_i(struct contact **lc, uint32_t i);

/*
 * Retourne le nom associé à un contact
 */
extern const char * get_name(struct contact *m_contact);

/*
 * Retourne le numéro associé à un contact
 */
extern const char * get_num(struct contact *m_contact);

#endif /* _CONTACT_H_ */
