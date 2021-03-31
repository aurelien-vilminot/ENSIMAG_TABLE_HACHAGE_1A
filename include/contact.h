#ifndef _CONTACT_H_
#define _CONTACT_H_

#include <stdint.h>

/*
  Un contact représente une association {nom, numéro}.
*/
struct contact;

extern void insert(struct contact **lc, const char *name, const char *num);

extern void replace(struct contact **lc, const char *name, const char *num);

extern const char * find(struct contact **lc, const char *name);

extern void delete_elem(struct contact **lc, const char *name);

extern void free_list(struct contact *lc);

extern void display(struct contact *lc);

extern uint32_t get_len_list(struct contact *lc);

extern struct contact * get_elem_i(struct contact **lc, uint32_t i);

extern const char * get_name(struct contact *m_contact);

extern const char * get_num(struct contact *m_contact);

#endif /* _CONTACT_H_ */
