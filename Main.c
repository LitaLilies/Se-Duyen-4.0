#include <stdio.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/list.h"
#include "include/seduyen.h"

int main(void) {
    Node *head = NULL;
    ResultNode *resultHead = NULL;

    /* Tai danh sach co san tu people.txt */
    loadFromFile(&head, PEOPLE_FILE);
    printf("  Da tai %d nguoi tu danh sach co san tu people.txt! \n", listLength(head));

    /* Tai them nguoi dung tu data.txt (bo qua ID trung voi people.txt) */
    int before = listLength(head);
    loadFromFile(&head, DATA_FILE);
    int added = listLength(head) - before;
    if (added > 0)
        printf("  Da tai them %d nguoi tu data.txt.\n", added);

    /* Tai danh sach ket qua tu file */
    loadResultFromFile(&resultHead, RESULT_FILE);

    char buf[16];
    int choice;

    do {
        printMenu();
        if (!fgets(buf, sizeof(buf), stdin)) break;
        if (sscanf(buf, "%d", &choice) != 1) { choice = -1; }

        system("cls");

        switch (choice) {
            case 1: printf("\n--- DANH SACH ---\n"); traverseList(head); break;
            case 2: handleAdd(&head);    break;
            case 3: handleSearch(head);  break;
            case 4: handleUpdate(&head); break;
            case 5: handleDelete(&head); break;
            case 6: handleCompatibility(head, &resultHead);
                    saveResultToFile(resultHead, RESULT_FILE);
                    break;
            case 7: handleViewResults(resultHead); break;
            case 8: handleCleanData(&resultHead); break;
            case 0: break;
            default: printf("  [Loi] Lua chon khong hop le!\n");
        }
    } while (choice != 0);

    /* Luu du lieu khi thoat */
    saveToFile(head, DATA_FILE);
    saveToFile(head, PEOPLE_FILE);
    saveResultToFile(resultHead, RESULT_FILE);
    freeList(&head);
    freeResultList(&resultHead);

    printf("\nTam biet! Hen gap lai\nMong ban se tim duoc doi tuong phu hop cho minh\n");
    return 0;
}