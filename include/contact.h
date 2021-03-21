#ifndef _CONTACT_H_
#define _CONTACT_H_

/*
  Un contact représente une association {nom, numéro}.
*/
struct contact;

/* TOUT DOUX: à compléter */
/* Profitez de cette période sombre pour braver les interdits et rétablir le contact. */

extern void insert(struct contact **lc, const char *name, const char *num);

extern void replace(struct contact **lc, const char *name, const char *num);

extern const char * find(struct contact **lc, const char *name);

extern void delete_elem(struct contact **lc, const char *name);

extern void display(struct contact *lc);

#endif /* _CONTACT_H_ */
