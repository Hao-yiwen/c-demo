#include <stdio.h>
#include "library.h"
#include <stddef.h>

void hello(void) {
    printf("Hello, World!\n");
    int x = 1;
}

int doStuff(int a, unsigned char b) {
    return a + b;
}

void increament(int* p){
    *p = *p + 1;
}

//int main() {
//    hello();
//    printf("There are %i apples\n", 3);
////    char ch;
////    top:
////    ch = getchar();
////    if (ch == 'q') {
////        goto top;
////    }
//    int doStuff(int, unsigned char);
//
//    char m = 42;
//    unsigned short n = 43;
//    long long int c = doStuff(m, n);
//    printf("Result: %lld\n", c);
//
//    int x = 10;
//    increament(&x);
//    printf("x %p\n", &x);
//    printf("x = %i\n", x);
//
//    // 指针初始化
//    int *p = NULL;
//    int i = 10;
//    printf("p = %p\n", p); // p = 0x0
//    p = &i;
//    *p = 20;
//    printf("i = %i\n", i);
//
//    short* j;
//    j = (short*)0x13243;
//    j = j +1;
//    printf("j = %p\n", j);
//
//    short* j1;
//    short* j2;
//
//    j1 = (short*)0x1234;
//    j2 = (short*)0x1236;
//
//    ptrdiff_t dist = j2 - j1;
//    printf("%td\n", dist); // 1
//
//}
