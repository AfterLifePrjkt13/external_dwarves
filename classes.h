#ifndef _PAHOLE_CLASSES_H_
#define _PAHOLE_CLASSES_H_ 1
/* 
  Copyright (C) 2006 Mandriva Conectiva S.A.
  Copyright (C) 2006 Arnaldo Carvalho de Melo <acme@mandriva.com>

  This program is free software; you can redistribute it and/or modify it
  under the terms of version 2 of the GNU General Public License as
  published by the Free Software Foundation.
*/


#include <stdint.h>

#include "list.h"

struct cu {
	struct list_head node;
	struct list_head classes;
	unsigned int	 id;
};

struct class {
	struct list_head node;
	struct list_head members;
	char		 name[32];
	unsigned long	 size;
	unsigned int	 id;
	unsigned int	 type;
	unsigned int	 tag;		/* struct, union, base type, etc */
	uintmax_t	 nr_entries;	/* For arrays */
	uintmax_t	 low_pc;
	uintmax_t	 high_pc;
	const char	 *decl_file;
	unsigned int	 decl_line;
	unsigned short	 nr_holes;
	unsigned short	 padding;
	unsigned short	 inlined;
};

struct class_member {
	struct list_head node;
	char		 name[32];
	unsigned int	 type;
	unsigned int	 offset;
	unsigned int	 bit_size;
	unsigned int	 bit_offset;
	unsigned short	 hole;		/* If there is a hole before the next
					   one (or the end of the struct) */
};

extern void class__find_holes(struct class *self, const struct cu *cu);
extern void class__print(struct class *self, const struct cu *cu);

extern int	    classes__load(const char *filename);
extern struct cu    *cus__find_by_id(const unsigned int type);
extern struct class *cu__find_by_id(struct cu *cu, const unsigned int type);
extern struct class *cu__find_by_name(struct cu *cu, const char *name);
extern void	    classes__print(const unsigned int tag);
extern void	    classes__for_each(int (*iterator)(struct class *class,
						      struct cu *cu,
						      void *cookie),
				      void *cookie);

#endif /* _PAHOLE_CLASSES_H_ */