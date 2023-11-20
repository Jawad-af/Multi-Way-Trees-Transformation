#include <stdlib.h>
#include <stdio.h>


#define TABLE_SIZE 10

typedef struct DoublyNode {
	int key;
	struct DoublyNode* next;
	struct DoublyNode* previous;
}doubly;

typedef struct Entry {
	int key;
	doubly* value;
}entry;

typedef struct NodesHashTable {
	int size;
	entry* table[];
}hashtable;

typedef struct M_NodesTree {
	doubly* node;
	M_NodesTree* children[];
};

typedef struct DoublysHashTable {
	int size;
	doubly* table[];

}doublyhashtable;


int hashFunction(int key)
{
	return key % TABLE_SIZE;
}

int generateQuadraticIndex(int key, int index)
{
	return (key + (index * index)) % TABLE_SIZE;
}

doubly* createNewDoublyNode(int value)
{
	doubly* newNode = (doubly*)malloc(sizeof(doubly));
	newNode->key = value;
	newNode->next = newNode->previous = NULL;
	return newNode;
}

hashtable* createHashTable()
{
	hashtable* ht = (hashtable*)malloc(sizeof(hashtable));
	ht->size = 0;

	int i = 0;
	while (i < TABLE_SIZE)
	{
		ht->table[i] = NULL;
		i++;
	}
	return ht;
}

doublyhashtable* createDoublyHashTable()
{
	doublyhashtable* ht = (doublyhashtable*)malloc(sizeof(doublyhashtable));
	ht->size = 0;
	for (int i = 0; i < TABLE_SIZE; i++) {
		ht->table[i] = NULL;
	}
	return ht;
}

void hashInsert(hashtable** ht, entry* entry)
{

	if ((*ht)->size >= TABLE_SIZE)
	{
		printf("The table is full");
	}

	int index = hashFunction(entry->key);
	int i = 0;

	while ((*ht)->table[index] != NULL) {
		index = generateQuadraticIndex(index, i);
		i++;
	}

	(*ht)->table[index] = entry;
	//ht->table[index]->parent = parent;
	(*ht)->size++;
	//printf("\nThe element %d has been inserted to the table", key);
}

// to insert doubly nodes in the hash
void hashInsertDoubly(doublyhashtable** ht, doubly* node)
{

	if ((*ht)->size >= TABLE_SIZE)
	{
		printf("The table is full");
	}

	int index = hashFunction(node->key);
	int i = 0;

	while ((*ht)->table[index] != NULL) {
		index = generateQuadraticIndex(index, i);
		i++;
	}

	(*ht)->table[index] = node;
	//ht->table[index]->parent = parent;
	(*ht)->size++;
	//printf("\nThe element %d has been inserted to the table", key);
}

Entry* hashSearch(hashtable** ht, entry* entry)
{
	int index = hashFunction(entry->key);

	if ((*ht)->table[index] == NULL)
	{
		//printf("\nThe element %d is not present in the table", key);
		return NULL;
	}

	int i = 0;
	while ((*ht)->table[index] != NULL)
	{
		if ((*ht)->table[index]->key == entry->key)
		{
			return (*ht)->table[index];
		}
		index = generateQuadraticIndex(entry->key, index);
		i++;
	}
}

//to search doubly nodes in the hash
doubly* hashSearchDoubly(doublyhashtable** ht, doubly* node)
{
	int index = hashFunction(node->key);

	if ((*ht)->table[index] == NULL)
	{
		//printf("\nThe element %d is not present in the table", key);
		return NULL;
	}

	int i = 0;
	while ((*ht)->table[index] != NULL)
	{
		if ((*ht)->table[index]->key == node->key)
		{
			return (*ht)->table[index];
		}
		index = generateQuadraticIndex(node->key, index);
		i++;
	}
}


typedef struct specialStruct {
	int rootValue;
	int* array[3]; // here we have to define as a constant the number of childer 
}specialSt;

typedef struct hashtable {
	int size;
	specialStruct* table[TABLE_SIZE];
}ht;


specialStruct* createSpecialStruct(int rootValue)
{
	specialStruct* newStruct = (specialStruct*)malloc(sizeof(specialStruct));
	newStruct->rootValue = rootValue;

	for (int i = 0; i < 3; i++)
	{
		newStruct->array[i] = NULL;
	}
	return newStruct;
}


ht* createHash()
{
	ht* htable = (ht*)malloc(sizeof(ht));
	htable->size = 0;

	for (int i = 0; i < TABLE_SIZE; i++)
	{
		htable->table[i] = NULL;
	}
	return htable;
}


specialStruct* insertInSpecialhash(ht** ht, int root)
{
	if ((*ht)->size >= TABLE_SIZE)
	{
		return NULL;
	}

}






int main() {

	int arr[] = { 2, 7, 5, 2, 7, 7, -1, 5, 2 };
	int n = sizeof(arr) / sizeof(arr[0]);

	doublyhashtable* ht = createDoublyHashTable();

	doubly* node1 = createNewDoublyNode(1);
	doubly* node2 = createNewDoublyNode(2);
	node1->next = node2;
	hashInsertDoubly(&ht, node2);


	doubly* node2 = hashSearchDoubly(&ht, node2);
	if (node2) {

	}


	return 0;
}