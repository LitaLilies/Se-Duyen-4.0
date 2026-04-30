#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h> 
#include "../include/seduyen.h" 


/* saveToFile: Luu danh sach nguoi vao file*/
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

/* loadFromFile: Doc danh sach nguoi tu file*/
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

//LOGIC:

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

//Bang tuong hop giua cac so
static const int COMPAT[9][9] = { 
/*       1    2    3    4    5    6    7    8    9  */ 
/* 1 */ {80,  60,  70,  50,  75,  65,  55,  70,  60}, 
/* 2 */ {60,  80,  65,  70,  60,  75,  65,  55,  70}, 
/* 3 */ {70,  65,  80,  55,  75,  70,  60,  65,  60}, 
/* 4 */ {50,  70,  55,  80,  55,  75,  65,  70,  65}, 
/* 5 */ {75,  60,  75,  55,  80,  60,  70,  65,  70}, 
/* 6 */ {65,  75,  70,  75,  60,  80,  60,  65,  75}, 
/* 7 */ {55,  65,  60,  65,  70,  60,  80,  55,  70}, 
/* 8 */ {70,  55,  65,  70,  65,  65,  55,  80,  60}, 
/* 9 */ {60,  70,  60,  65,  70,  75,  70,  60,  80}, 
}; 

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

//FEATURE CHÍNH:

void handleCompatibility(Node *head, ResultNode **resultHead) { 

    printf("\n--- SO CHU DAO & TOP 3 TUONG HOP ---\n"); 
    int id = inputId("  Nhap ID nguoi can xet: "); 
    Node *target = searchNode(head, id);

    if (!target)
    { 
        printf("  [Loi] Khong tim thay ID %d!\n", id);
        return;
    } 

    //Thong tin nguoi duoc xet
    int myNum = lifePathNumber(target->birth); 
    printf("  %s (sinh %s) -> So chu dao: %d\n", target->name, target->birth, myNum); 


    /* Tim top 3: luu id + % hop */ 
    int top3Id[3]   = {-1, -1, -1}; 
    int top3Pct[3]  = { 0,  0,  0}; 
    int top3Num[3]  = { 0,  0,  0}; 

 

    for (Node *cur = head; cur; cur = cur->next) 
    { 
        //Neu gap chinh minh thi bo qua
        if (cur->id == id)
        {
            continue;  /* bo qua chinh minh */ 
        }
        int theirNum = lifePathNumber(cur->birth); 
        int pct = compatibility(myNum, theirNum); 

 

        /* Chen vao top 3 neu lon hon phan tu nho nhat */ 
        for (int i = 0; i < 3; i++) 
        { 
            if (pct > top3Pct[i]) 
            { 
                // Đẩy các phần tử phía sau xuống
                for (int j = 2; j > i; j--) 
                { 
                    top3Id[j]  = top3Id[j-1]; 
                    top3Pct[j] = top3Pct[j-1]; 
                    top3Num[j] = top3Num[j-1]; 
                } 

                top3Id[i]  = cur->id; 
                top3Pct[i] = pct; 
                top3Num[i] = theirNum; 
                break; 
            } 
        } 
    } 


    printf("\n  Top 3 nguoi hop nhat:\n"); 
    printf("  %-4s %-25s %-12s %-10s %-8s\n", "STT", "Ho ten", "Ngay sinh", "So ChuDao", "% Hop"); 
    printf("  %s\n", "------------------------------------------------------------"); 
    int found = 0; //truth: khong tim thay ai trong danh sach de so sanh

    for (int i = 0; i < 3; i++) 
    { 
        if (top3Id[i] == -1)
        {
            continue;
        }

        Node *p = searchNode(head, top3Id[i]); 
        if (!p) continue; 
        printf("  %-4d %-25s %-12s %-10d %d%%\n", i+1, p->name, p->birth, top3Num[i], top3Pct[i]); 
        found++; 

    } 
    if (!found)
    {
        printf("  Khong co ai trong danh sach de so sanh.\n"); 
    }
 

    /* Luu ket qua vao danh sach ket qua (dung top 1) */ 
    if (top3Id[0] != -1)
    { 
        Node *best = searchNode(head, top3Id[0]); 
        if (best) 
        { 
            //Tao ban ghi ket qua
            ResultNode *r = createResultNode( target->name, target->birth, myNum, best->name, top3Pct[0]); 

            if (r)
            {
                addLastResult(resultHead, r); 
                printf("  [Da luu ket qua vao danh sach ket qua]\n"); 
            }
        } 
    } 
} 

