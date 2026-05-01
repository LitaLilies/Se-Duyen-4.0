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

 

void handleViewResults(ResultNode *head) 
{ 
    printf("\n--- DANH SACH KET QUA DA XET ---\n"); 
    traverseResultList(head); 
} 

 
/* 
 * Lam sach: xoa trang data.txt, xoa trang results.txt, 
 * va xoa tat ca nguoi da them (chi giu lai people.txt trong RAM). 
 * Hoi xac nhan truoc khi thuc hien. 
 */ 

void handleCleanData(ResultNode **resultHead) 
{ 
    printf("\n--- XOA DANH SACH KET QUA ---\n"); 
    printf("  Ban co chac muon xoa toan bo ket qua da xet khong? (y/n): "); 
    char buf[8]; 

    if (!fgets(buf, sizeof(buf), stdin)) 
    {
        return;
    } 
    if (buf[0] != 'y' && buf[0] != 'Y') 
    { 
        printf("  Da huy.\n"); 
        return; 
    } 

    /* Xoa trang results.txt */ 
    FILE *f = fopen(RESULT_FILE, "w"); 
    if (f) 
    {
        fclose(f); 
    }

    /* Xoa danh sach ket qua trong RAM */ 
    freeResultList(resultHead); 
    printf("  Da xoa toan bo ket qua!\n"); 

} 

//Menu & Handlers

void printMenu(void) { 
    printf("\n============ SE DUYEN 4.0 ============\n"); 
    printf("  1. Hien thi danh sach\n"); 
    printf("  2. Them nguoi dung\n"); 
    printf("  3. Tim kiem theo ID\n"); 
    printf("  4. Cap nhat thong tin\n"); 
    printf("  5. Xoa nguoi dung\n"); 
    printf("  6. So chu dao & Top 3 tuong hop\n"); 
    printf("  7. Xem danh sach ket qua\n"); 
    printf("  8. Xoa danh sach ket qua\n"); 
    printf("  0. Thoat\n"); 

    printf("======================================\n"); 
    printf("  Chon: "); 
} 

 

void handleAdd(Node **head) 
{ 
    printf("\n--- THEM NGUOI DUNG ---\n"); 
 
    /* Tu dong gan ID tiep theo, khong can nguoi dung nhap */ 
    int id = maxId(*head) + 1; 
    printf("  ID tu dong: %d\n", id); 
    char name[MAX_NAME], birth[11]; 
    inputStr("  Ho ten: ", name, MAX_NAME); 

    if (strlen(name) == 0) { printf("  [Loi] Ten khong duoc trong!\n"); return; } 
 
    while (1) 
    { 
        inputStr("  Ngay sinh (DD/MM/YYYY, Enter de huy): ", birth, 11); 
        if (strlen(birth) == 0) { printf("  Da huy them nguoi dung.\n"); return; } 
        if (isValidDate(birth)) break; 

        printf("  [Loi] Dinh dang ngay khong hop le (VD: 01/01/2000)!\n"); 

    } 


    Node *p = createNode(id, name, birth); 
    if (!p) 
    { 
        printf("  [Loi] Khong du bo nho!\n"); 
        return; 
    } 
    addLast(head, p); 

    printf("  Da them thanh cong!\n"); 

} 

void handleDelete(Node **head) 
{ 
    printf("\n--- XOA NGUOI DUNG ---\n"); 
    int id = inputId("  Nhap ID can xoa: "); 
    if (!searchNode(*head, id))
    { 
        printf("  [Loi] Khong tim thay ID %d!\n", id); 
        return; 
    } 

    deleteNode(head, id); 
    reindexIds(*head); 

    printf("  Da xoa ID %d. Danh sach da duoc cap nhat lai so thu tu.\n", id); 

} 

void handleUpdate(Node **head) {
    printf("\n--- CAP NHAT THONG TIN ---\n");
    int id = inputId("  Nhap ID can cap nhat: ");
    Node *p = searchNode(*head, id);
    if (!p) { printf("  [Loi] Khong tim thay ID %d!\n", id); return; }

    printf("  Ten hien tai: %s\n", p->name);
    char name[MAX_NAME], birth[11];
    inputStr("  Ho ten moi: ", name, MAX_NAME);
    if (strlen(name) == 0) { printf("  [Loi] Ten khong duoc trong!\n"); return; }

    printf("  Ngay sinh hien tai: %s\n", p->birth);
    while (1) {
        inputStr("  Ngay sinh moi (DD/MM/YYYY, Enter de huy): ", birth, 11);
        if (strlen(birth) == 0) { printf("  Da huy cap nhat.\n"); return; }
        if (isValidDate(birth)) break;
        printf("  [Loi] Dinh dang ngay khong hop le!\n");
    }

    updateNode(p, name, birth);
    printf("  Cap nhat thanh cong!\n");
}

void handleSearch(Node *head) {
    printf("\n--- TIM KIEM ---\n");
    int id = inputId("  Nhap ID can tim: ");
    Node *p = searchNode(head, id);
    if (!p) { printf("  Khong tim thay ID %d.\n", id); return; }
    printf("  %-5s %-25s %-12s\n", "ID", "Ho ten", "Ngay sinh");
    printf("  %-5d %-25s %-12s\n", p->id, p->name, p->birth);
}
