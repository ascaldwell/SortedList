#include <stdio.h>
#include <string.h>
#include "sorted-list.h"

int compareIntegers(void *objOne, void *objTwo)
{
	// 1st value is smaller
	if(*(int*)objOne < *(int*)objTwo)
		return -1;
	// 2nd value is smaller
	else if(*(int*)objOne > *(int*)objTwo)
		return 1;

	// Both are equal
	return 0;
}

int compareDoubles(void *objOne, void *objTwo)
{
	// 1st value is smaller
	if(*(double*)objOne < *(double*)objTwo)
		return -1;
	// 2nd value is smaller
	else if(*(double*)objOne > *(double*)objTwo)
		return 1;

	// Both are equal
	return 0;
}

int compareStrings(void *objOne, void *objTwo)
{
	return strcmp(objOne, objTwo);
}

void destroyList(void *value)
{
	// Only free if not NULL
	if(!value)
		free(value);
}

void printIntegers(SortedListIteratorPtr itr)
{
	void *value;

 	do {
 		value = SLNextItem(itr);

 		if(value != NULL)
 			printf("%d, ", *(int*)value);
 	
 	} while(value != NULL);
}

void printDoubles(SortedListIteratorPtr itr)
{
	void *value;

 	do {
 		value = SLNextItem(itr);

 		if(value != NULL)
 			printf("%.1f, ", *(double*)value);
 	
 	} while(value != NULL);
}

void printChars(SortedListIteratorPtr itr)
{
	void *value;

 	do {
 		value = SLNextItem(itr);

 		if(value != NULL)
 			printf("%c, ", *(char*)value);
 	
 	} while(value != NULL);
}

void printStrings(SortedListIteratorPtr itr)
{
	void *value;

	do {
		value = (char*) SLNextItem(itr);

		if(value != NULL)
			printf("%s, ", value);
	
	} while(value != NULL);
}

int main(int argc, char *argv[])
{
	// Lists
	SortedListPtr integers = SLCreate(compareIntegers, destroyList);
	SortedListPtr doubles = SLCreate(compareDoubles, destroyList);
	SortedListPtr characters = SLCreate(compareStrings, destroyList);
	SortedListPtr strings = SLCreate(compareStrings, destroyList);
	
	// Insertions
	int a = 7, b = 7, c = 8, d = 1;
	double h = 22.3, i = 98.2, j = 1.2;
	char s = 's', w = 'a', v = 'c';
	char word1[10] = "Hello";
	char word2[10] = "World";

	
	// ========================== Case 1 ========================== 
	printf("\nIntegers:\n");
	SLInsert(integers, (void*)&a);
	SLInsert(integers, (void*)&b);
	SLInsert(integers, (void*)&c);
	SLInsert(integers, (void*)&d);

	SortedListIteratorPtr itr1 = SLCreateIterator(integers);
	printIntegers(itr1);
	printf("\n");

	SLRemove(integers, (void*)&c);

	SortedListIteratorPtr itr2 = SLCreateIterator(integers);
	printIntegers(itr2);
	printf("\n");

	// ========================== Case 2 ========================== 
	printf("\nDoubles:\n");
	SLInsert(doubles, (void*)&h);
	SLInsert(doubles, (void*)&i);
	SLInsert(doubles, (void*)&j);

	SortedListIteratorPtr itr3 = SLCreateIterator(doubles);
	printDoubles(itr3);
	printf("\n");
	
	SLRemove(doubles, (void*)&h);

	SortedListIteratorPtr itr4 = SLCreateIterator(doubles);
	printDoubles(itr4);
	printf("\n");

	// ========================== Case 3 ========================== 
	printf("\nCharacters:\n");
	SLInsert(characters, (void*)&s);
	SLInsert(characters, (void*)&w);
	SLInsert(characters, (void*)&v);

	SortedListIteratorPtr itr5 = SLCreateIterator(characters);
	printChars(itr5);
	printf("\n");
	
	SLRemove(characters, (void*)&v);
	SLRemove(characters, (void*)&s);

	SortedListIteratorPtr itr6 = SLCreateIterator(characters);
	printChars(itr6);
	printf("\n");

	// ========================== Case 4 ========================== 
	printf("\nStrings:\n");
	SLInsert(strings, (void*)word1);
	SLInsert(strings, (void*)word2);

	SortedListIteratorPtr itr7 = SLCreateIterator(strings);
	printStrings(itr7);
	printf("\n");
	
	SLRemove(strings, (void*)word1);

	SortedListIteratorPtr itr8 = SLCreateIterator(strings);
	printStrings(itr8);
	printf("\n\n");

	return 0;
}
