#include <string.h>
#include <stdio.h>
#include <ctype.h>
int main()
{
   char str[80] = "Hoc C - co ban va nang cao - tai VietJack";
   const char s[2] = "-";
   char *token;
   
   /* lay token dau tien */
   token = strtok(str, s);
   
   /* duyet qua cac token con lai */
   while( token != NULL ) 
   {
      printf( " %s\n", token );
    
      token = strtok(NULL, s);
   }
   
   return(0);
}

/*
Các hàm trong thư viện string.h
Hàm strlen – hàm lấy chiều dài chuỗi
Hàm strcmp – hàm so sánh 2 chuỗi
Hàm strcat – hàm nối chuỗi
Hàm strcpy – hàm copy chuỗi
Hàm strlwr – Đưa chuỗi về dạng lowercase
Hàm strupr – đưa chuỗi về dạng uppercase
Hàm strrev – hàm đảo ngược chuỗi
Hàm strchr – Trả về vị trí đầu tiên của ký tự cần tìm
Hàm strstr – hàm tìm chuỗi con trong chuỗi
*/
toupper, tolower;