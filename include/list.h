#ifndef LIST_H
#define LIST_H

#define MAX_NAME 50

typedef struct Node
{
    int id;
    char name[MAX_NAME];
    char birth[11];
    struct Node *next;
} Node;

Node *createNode(int id, const char *name, const char *birth);
void addLast(Node **head, Node *p);
void traverseList(Node *head);
Node *searchNode(Node *head, int id);
Node *getNodeAt(Node *head, int index);
void updateNode(Node *p, const char *name, const char *birth);
void deleteNode(Node **head, int id);
void freeList(Node **head);
int listLength(Node *head);
int maxId(Node *head);

/* ─── Danh sach ket qua ────────────────────────────────────── */
/*
 * ResultNode luu ket qua xet cua 1 nguoi:
 *   - Ho ten va ngay sinh cua nguoi duoc xet
 *   - So chu dao cua ho
 *   - Ten + % hop cua nguoi hop nhat (top 1)
 */
typedef struct ResultNode
{
    char name[MAX_NAME];    /* ten nguoi duoc xet      */
    char birth[11];         /* ngay sinh                */
    int soChudao;           /* so chu dao               */
    char topName[MAX_NAME]; /* nguoi hop nhat           */
    int topPct;             /* % tuong hop              */
    struct ResultNode *next;
} ResultNode;

ResultNode *createResultNode(const char *name, const char *birth, int soChudao, const char *topName, int topPct);
void addLastResult(ResultNode **head, ResultNode *p);
void traverseResultList(ResultNode *head);
void freeResultList(ResultNode **head);

#endif