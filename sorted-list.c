#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorted-list.h"

SortedListPtr SLCreate(CompareFuncT cf, DestructFuncT df)
{
	// Allocate memory for sorted list
	SortedListPtr slp = malloc(sizeof(struct SortedList));
	slp->head = NULL;
	slp->counter = 0;

	// Clear memory
	memset(slp, 0, sizeof(struct SortedList));

	// Function pointers point to passed methods
	slp->compare = cf;
	slp->destruct = df;

	return slp;
}

void SLDestroy(SortedListPtr list)
{
	// Traverse to end up list while deallocating memory
	while(list->head != NULL)
	{
		// TempNode points to current and current points to next node
		SortedNodePtr tempNode = list->head;
		list->head = tempNode->link;

		// Free data if need be
		list->destruct(tempNode->value);

		// Free the node
		free(tempNode);
	}

	// Free everything else in list
	free(list->head);
	free(list);
}

int SLInsert(SortedListPtr list, void *newObj)
{
	// Create node cast link as a self referential node
	SortedNodePtr newItem = malloc(sizeof(struct SortedNode));

	// Set new item values
	newItem->value = newObj;
	newItem->count = 1;
	newItem->link = NULL;
	
	// Temp node to traverse through list
	SortedNodePtr current = list->head;

	// Insert
	if(current == NULL)
	{
		// Point to new item and increment size of list
		list->head = newItem;
		list->counter++;

		return 1;
	}
	else
	{
		if(list->compare(current->value, newObj) != 0)
		{
			if(list->compare(current->value, newObj) < 0)
			{
				// Add new item to front
				newItem->link = list->head;
				list->head = newItem;

				//Increment size of list
				list->counter++;

				return 1;
			}

			// Sort and add
			sort(list, newItem);

			return 1;
		}
	}

	// ERROR
	free(newItem);
	return 0;
}

// Sort 
void *sort(SortedListPtr list, SortedNodePtr newItem)
{
	// Get current and previous
	SortedNodePtr current = list->head->link, previous = list->head;

	// Keep traversing til sorted
	for(;;)
	{
		// If node is null, than previous node points to new object
		if(!current) 
		{
			// Add right before end of the list then increment size of list
			previous->link = newItem;
			list->counter++;

			return free;
		}
		// New value is bigger than current value
		else if(list->compare(current->value, newItem->value) < 0) 
		{
			// Move new node to the left
			newItem->link = current;

			// Move old node to the right then increment size of list
			previous->link = newItem;
			list->counter++;

			// BE FREE!
			return free;
		}
		// Value in node and new value are the same
		else if(list->compare(current->value, newItem->value) == 0)
		{
			// Deallocate memory of the new node
			free(newItem);
			return free - 1;
		}

		// Move to next node!
		previous = current;
		current = current->link;
	}

	return free - 1;
}

int SLRemove(SortedListPtr list, void *newObj)
{
	SortedNodePtr current = list->head, previous = NULL;

	while(current->link != NULL && list->compare(current->value, newObj) != 0)
	{
		// Store current node into previous
		previous = current;

		// Move to next node
		current = current->link;
	}

	// Only remove if count on node is one or lower
	if(previous == NULL && current->count <= 1)
	{
		list->head = current->link;
		list->destruct(current->value);
		free(current);
		
		// Decrement list size
		list->counter--;

		return 1;
	}
	else if(current->count <= 1)
	{
		// Previous points to node after the one being deleted
		previous->link = current->link;

		// Free the memory
		list->destruct(current->value);
		free(current);

		// Decrement list size
		list->counter--;

		return 1;
	}
	else
	{
		// Make reference count go down by one
		current->count--;
	}

	// Couldn't remove
	return 0;
}

SortedListIteratorPtr SLCreateIterator(SortedListPtr list)
{
	// Allocate memory for iterator
	SortedListIteratorPtr itr = malloc(sizeof(struct SortedListIterator));

	/* Make Node in iterator point to first node
	** Counter has number of nodes in list
	** Increment reference count of node
	** Steve is a tracker with +9 to dexterity */
	itr->item = list->head;
	itr->counter = list->counter;
	itr->steve = 0;

	// If list is NULL 
	if(!itr)
		return NULL;

	return itr;
}

void SLDestroyIterator(SortedListIteratorPtr iter)
{
	free(iter);
}

void * SLNextItem(SortedListIteratorPtr iter)
{
	// End of list
	if(iter->steve == iter->counter)
		return NULL;

	// Increment tracker
	iter->steve++;

	// Get value of node and reference count goes down by 1
	void* temp = iter->item->value;
	iter->item->count--;

	if(iter->item->link != NULL)
	{
		// Move to next node and increment reference count by 1
		iter->item = iter->item->link;
		iter->item->count++;
	}

	return temp;
}

void * SLGetItem(SortedListIteratorPtr iter)
{
	// Return data that iterator is pointing to
	return iter->item->value;
}
