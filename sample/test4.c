#include <stdio.h>

char a = 'a';
int b = 10;
float c = 2.30;

int fun1(){
    int d = 10;
    return c*d;
}

// int fun2(){
//     int i = 5;
//     while(i< 10){
//         printf("Hello %d", b);
//         i++;
//     }
//     return 0;
// }

int main(){
    fun1();
    //fun2();
    printf("%f", c);
}