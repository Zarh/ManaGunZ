/*
* Copyright (c) 2011-2013 by naehrwert
* This file is released under the GPLv2.
*/

#include <stdlib.h>

#include "types.h"
#include "list.h"

list_t *list_create()
{
	list_t *res;
	
	if((res = (list_t *)malloc(sizeof(list_t))) == NULL)
		return NULL;
	
	res->head = NULL;
	res->count = 0;
	
	return res;
}

void list_destroy(list_t *l)
{
	if(l == NULL)
		return;
	
	lnode_t *iter = l->head, *tmp;
	
	while(iter != NULL)
	{
		tmp = iter;
		iter = iter->next;
		free(tmp);
	}
	
	free(l);
}

BOOL list_isempty(list_t *l)
{
	if(l == NULL)
		return FALSE;
	
	if(l->count == 0)
		return TRUE;
	return FALSE;
}

unsigned int list_count(list_t *l)
{
	if(l == NULL)
		return 0;
	
	return l->count;
}

BOOL list_push(list_t *l, void *value)
{	
	if(l == NULL)
		return FALSE;
	
	lnode_t *_new;
	
	//Allocate new node.
	if((_new = (lnode_t *)malloc(sizeof(lnode_t))) == NULL)
		return FALSE;
	
	//Insert.
	_new->value = value;
	_new->next = l->head;
	l->head = _new;
	l->count++;
	
	return TRUE;
}

void *list_pop(list_t *l)
{	
	if(l == NULL)
		return NULL;
	
	lnode_t *tmp;
	void *res = NULL;
	
	if(l->head != NULL)
	{
		res = l->head->value;
		tmp = l->head;
		l->head = l->head->next;
		free(tmp);
		l->count--;
	}
	
	return res;
}

BOOL list_add_back(list_t *l, void *value)
{	
	if(l == NULL)
		return FALSE;
	
	lnode_t *n, *_new;
	
	//Allocate new node.
	if((_new = (lnode_t *)malloc(sizeof(lnode_t))) == NULL)
		return FALSE;
	
	_new->value = value;
	_new->next = NULL;
	
	if(l->head == NULL)
		l->head = _new;
	else
	{
		//Move to the list end.
		for(n = l->head; n->next != NULL; n = n->next);
		
		//Add.
		n->next = _new;
		l->count++;
	}
	
	return TRUE;
}

void *list_get(list_t *l, unsigned int idx)
{
	if(l == NULL)
		return NULL;
	
	lnode_t *iter;
	void *res = NULL;
	
	for(iter = l->head; idx-- != 0 && iter != NULL; iter = iter->next);
	
	if(iter == NULL)
		res = NULL;
	else
		res = iter->value;
	
	return res;
}

lnode_t *list_get_node(list_t *l, unsigned int idx)
{
	if(l == NULL)
		return NULL;
	
	lnode_t *iter;
	
	for(iter = l->head; idx-- != 0 && iter != NULL; iter = iter->next);
	
	return iter;
}

BOOL list_remove_node(list_t *l, lnode_t *node)
{	
	if(l == NULL)
		return FALSE;
	
	lnode_t *iter;
	
	if(l->head == node)
	{
		l->head = l->head->next;
		free(node);
		l->count--;
		
		return TRUE;
	}
	
	iter = l->head;
	while(iter->next != NULL)
	{
		if(iter->next == node)
		{
			iter->next = iter->next->next;
			free(node);
			l->count--;
			
			return TRUE;
		}
		iter = iter->next;
	}
	
	return FALSE;
}

BOOL list_remove_value(list_t *l, void *value)
{	
	if(l == NULL)
		return FALSE;
	
	lnode_t *tmp, *iter;
	
	if(l->head->value == value)
	{
		tmp = l->head;
		l->head = l->head->next;
		free(tmp);
		l->count--;
		
		return TRUE;
	}
	
	iter = l->head;
	while(iter->next != NULL)
	{
		if(iter->next->value == value)
		{
			tmp = iter->next;
			iter->next = iter->next->next;
			free(tmp);
			l->count--;
			
			return TRUE;
		}
		iter = iter->next;
	}
	
	return FALSE;
}
