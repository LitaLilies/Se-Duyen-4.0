#ifndef SEDUYEN_H
#define SEDUYEN_H

#include "list.h"

#define MAX_PAIR 500

typedef struct {
int id1;
int id2;
char name1 [MAX_NAME];
char name2[MAX_NAME];
float score;
} Pair;

float calcScore (Node *a, Node *b);
void addPair(Node *head, int index1, int index2,
Pair pairs, int *count);
void sortPairs Desc(Pair pairs[], int count);

#endif
