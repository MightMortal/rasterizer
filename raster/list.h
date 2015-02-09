#ifndef _DYN_LIST_H_
#define _DYN_LIST_H_
#include "types.h"
#include "macro.h"

typedef void* DynList;
typedef void* DynListElement;

DynList dynlist_init();
void dynlist_destroy(DynList list);
void dynlist_clear(DynList list);
DynListElement dynlist_get_element(DynList list, int index);
uint dynlist_size(DynList list);
void dynlist_set_element(DynList list, int index, DynListElement element); // Don't set to auto variables, only dynamic allocated
void dynlist_push_back(DynList list, DynListElement element); // Don't set to auto variables, only dynamic allocated
void dynlist_remove(DynList list, uint index);

#endif
