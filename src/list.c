#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/list.h"

Node *createNode(int id, const char *name, const char *birth)
{
    Node *p = (Node *)malloc(sizeof(Node));
    if (!p)
        return NULL;
    p->id = id;
    strncpy(p->name, name, MAX_NAME - 1);
    p->name[MAX_NAME - 1] = '\0';
    strncpy(p->birth, birth, 10);
    p->birth[10] = '\0';
    p->next = NULL;
    return p;
}

void addLast(Node **head, Node *p)
{
    if (!*head)
    {
        *head = p;
        return;
    }
    Node *cur = *head;
    while (cur->next)
        cur = cur->next;
    cur->next = p;
}

void traverseList(Node *head)
{
    if (!head)
    {
        printf("  (Danh sach trong)\n");
        return;
    }
    printf("  %-5s %-25s %-12s\n", "ID", "Ho ten", "Ngay sinh");
    printf("  %-5s %-25s %-12s\n", "-----", "-------------------------", "----------");
    for (Node *cur = head; cur; cur = cur->next)
        printf("  %-5d %-25s %-12s\n", cur->id, cur->name, cur->birth);
}

Node *searchNode(Node *head, int id)
{
    for (Node *cur = head; cur; cur = cur->next)
        if (cur->id == id)
            return cur;
    return NULL;
}

Node *getNodeAt(Node *head, int index)
{
    int i = 0;
    for (Node *cur = head; cur; cur = cur->next, i++)
        if (i == index)
            return cur;
    return NULL;
}

void updateNode(Node *p, const char *name, const char *birth)
{
    if (!p)
        return;
    strncpy(p->name, name, MAX_NAME - 1);
    p->name[MAX_NAME - 1] = '\0';
    strncpy(p->birth, birth, 10);
    p->birth[10] = '\0';
}

void deleteNode(Node **head, int id)
{
    if (!*head)
        return;
    if ((*head)->id == id)
    {
        Node *tmp = *head;
        *head = (*head)->next;
        free(tmp);
        return;
    }
    for (Node *cur = *head; cur->next; cur = cur->next)
    {
        if (cur->next->id == id)
        {
            Node *tmp = cur->next;
            cur->next = tmp->next;
            free(tmp);
            return;
        }
    }
}

void freeList(Node **head)
{
    Node *cur = *head;
    while (cur)
    {
        Node *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    *head = NULL;
}

int listLength(Node *head)
{
    int count = 0;
    for (Node *cur = head; cur; cur = cur->next)
        count++;
    return count;
}

int maxId(Node *head)
{
    int max = 0;
    for (Node *cur = head; cur; cur = cur->next)
        if (cur->id > max)
            max = cur->id;
    return max;
}