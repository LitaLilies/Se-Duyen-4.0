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