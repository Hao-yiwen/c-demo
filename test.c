//
// Created by 郝宜文 on 2024/6/5.
//
#include <stdio.h>

int main() {
    printf("There are %i apples\n", 3);
    int value = 100;
    int *ptr1 = &value; // 指向整数的指针
    int **ptr2 = &ptr1; // 指向ptr1的指针（即二级指针）
//    int ***ptr3 = &ptr2; // 指向ptr2的指针（即三级指针）

    printf("Value = %d\n", value);      // 输出100
    printf("Value using ptr1 = %d\n", *ptr1);  // 输出100
    printf("Value using ptr2 = %d\n", **ptr2); // 输出100
//    printf("Value using ptr3 = %d\n", ***ptr3); // 输出100

    return 0;
}