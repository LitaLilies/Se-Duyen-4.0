#ifndef LIST_H 
#define LIST_H 
 
#define MAX_NAME 50 
 
typedef struct Node { 
    int id; 
    char name[MAX_NAME]; 
    char birth[11]; 
    struct Node *next; 
} Node; 
 
Node* createNode(int id, const char *name, const char *birth); 
void addLast(Node **head, Node *p); 
void traverseList(Node *head); 
Node* searchNode(Node *head, int id); 
Node* getNodeAt(Node *head, int index); 
void updateNode(Node *p, const char *name, const char *birth); 
void deleteNode(Node **head, int id); 
void freeList(Node **head); 
int listLength(Node *head); 
int maxId(Node *head); 
 
#endif