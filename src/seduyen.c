#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h> 
#include "../include/seduyen.h" 

int lifePathNumber(const char *birth)
{
    int sum = 0; 
    for (int i = 0; birth[i]; i++)//birth[i] ma khong phai gia tri thi dung
    {
        if (birth[i] >= '0' && birth[i] <= '9')
        {
            sum += birth[i] - '0'; //chuyen ky tu thanh so nguyen
        }
    }

    /* Reduce xuong 1 chu so: vd 16->1+6=7 */ 

    while (sum > 9)  //16
    { 
        int tmp = 0; 
        while (sum > 0)
        {
            tmp += sum % 10; //tmp= tmp+ 16%10= 0 + 6
            sum /= 10; //sum=16/10=1 (bo phan du vi la int)
        } 

        sum = tmp; 
    } 
    return sum == 0 ? 9 : sum; 
} 

//ham kiem tra muc do hop nhau
int compatibility(int n1, int n2)//nhan so chu dao cua 2 nguoi
{ 
    if (n1 < 1 || n1 > 9 || n2 < 1 || n2 > 9)
    {
        return 0;
    }
    return COMPAT[n1-1][n2-1];//tra ma tan bang do hop nhau + tru 1 vi mang bat dau la 0
//compatibility(6, 1)
// → tra vào COMPAT[5][0]
// → ví dụ trả về 85 (điểm tương hợp 85%)
} 
// ...existing code...

/* saveToFile
   Luu danh sach nguoi vao file
*/
void saveToFile(Node *head, const char *filename)
{
    FILE *f = fopen(filename, "w");

    if (f == NULL)
    {
        printf("Khong mo duoc file!\n");
        return;
    }

    Node *cur = head;

    while (cur != NULL)
    {
        fprintf(f, "%d|%s|%s\n",
                cur->id,
                cur->name,
                cur->birth);

        cur = cur->next;
    }

    fclose(f);

    printf("Da luu file thanh cong!\n");
}

/* loadFromFile
   Doc danh sach nguoi tu file
*/
void loadFromFile(Node **head, const char *filename)
{
    FILE *f = fopen(filename, "r");

    if (f == NULL)
    {
        printf("Khong tim thay file!\n");
        return;
    }

    int id;
    char name[MAX_NAME];
    char birth[11];

    while (fscanf(f,
           "%d|%49[^|]|%10[^\n]\n",
           &id,
           name,
           birth) == 3)
    {
        Node *p = createNode(id, name, birth);

        if (p != NULL)
            addLast(head, p);
    }

    fclose(f);

    printf("Da tai du lieu tu file!\n");
}
