#ifndef SEDUYEN_H
#define SEDUYEN_H

#include "list.h"

#define DATA_FILE    "data/data.txt"
#define RESULT_FILE  "data/results.txt"
#define PEOPLE_FILE  "data/people.txt"

/* File I/O - danh sach nguoi dung */
void saveToFile(Node *head, const char *filename);
void loadFromFile(Node **head, const char *filename);

/* File I/O - danh sach ket qua */
void saveResultToFile(ResultNode *head, const char *filename);
void loadResultFromFile(ResultNode **head, const char *filename);

/* Menu & UI */
void printMenu(void);
void handleAdd(Node **head);
void handleDelete(Node **head);
void handleUpdate(Node **head);
void handleSearch(Node *head);
void handleSort(Node **head);
void handleViewResults(ResultNode *head);
void handleCleanData(ResultNode **resultHead);

/* Than so hoc */
int  lifePathNumber(const char *birth);
int  compatibility(int n1, int n2);
void handleCompatibility(Node *head, ResultNode **resultHead);

/* Input helpers */
int  inputId(const char *prompt);
void inputStr(const char *prompt, char *buf, int maxLen);
int  isValidDate(const char *date);

#endif
