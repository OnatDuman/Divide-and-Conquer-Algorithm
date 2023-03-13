//
//  main.c
//  AlgoritmaAnalizi_Odev-2
//
//  Created by Onat Duman on 5.11.2022.
//

#include <stdio.h>
#include <stdlib.h>
int* inputArray(int* n, int* array){
    int i;
    printf("\nKac adet sayi gireceksiniz: ");
    scanf(" %d", n);
    array = (int*)malloc(sizeof(int)*(*n));
    for (i=0; i<*n; i++) {
        printf("\n%d. sayiyi giriniz: ", i+1);
        scanf(" %d", &array[i]);
    }
    return array;
}

void bruteForce(int n, int* array, int* start, int* finish){
    int i, j;
    int sum = 0;
    int bigger = array[0];
    int biggest = bigger;
    for (i=0; i<n; i++) {
        sum = array[i];
        for (j=i+1; j<n; j++) {
            sum = sum + array[j];
            if(bigger < sum){
                bigger = sum;
                *finish = j;
            }
        }
        if(biggest < bigger){
            biggest = bigger;
            *start = i;
        }
    }
    printf("\nEn yuksek kazanc: %d", biggest);
    printf("\nKazilmasi gereken kesintisiz blok butunu: %d-%d\n", *start, *finish);
}

int* divideAndConquer(int n, int* array, int start, int finish, int biggest[3], int holder[3]){
    int result1[3], result2[3];
    int *tmp;
    int sum, i;
    
    
    
    if(n>1){
        tmp = divideAndConquer(n/2,array, 0+start, n/2-1+start,biggest,holder);
        result1[0] = tmp[0];
        result1[1] = tmp[1];
        result1[2] = tmp[2];
        tmp = divideAndConquer(n-n/2, array, n/2+start, n-1+start,biggest,holder);
        result2[0] = tmp[0];
        result2[1] = tmp[1];
        result2[2] = tmp[2];
        
        //printf("\nDIVIDED!  %d  %d", result1[0], result2[0]);
    }
        
        
    
    if(n<=1){
        if(array[start] > biggest[0]){
            biggest[0] = array[start];
            biggest[1] = start;
            biggest[2] = finish;
            return biggest;
        }else{
            holder[0] = array[start];
            holder[1] = start;
            holder[2] = finish;
            return holder;
        }
        
    }
    
    sum = 0;
    for (i=0; i<result2[1] - result1[2] - 1; i++) {
        sum = sum + array[i + result1[2] + 1];
    }
    sum =  result1[0] + result2[0] + sum;
    if(sum > result1[0] && sum > result2[0]){
        biggest[0] = sum;
        biggest[1] = result1[1];
        biggest[2] = result2[2];
    }else{
        if(result1[0] > result2[0]){
            biggest[0] = result1[0];
            biggest[1] = result1[1];
            biggest[2] = result1[2];
        }else{
            biggest[0] = result2[0];
            biggest[1] = result2[1];
            biggest[2] = result2[2];
        }
    }
    
    
    return biggest;
}

int main(int argc, const char * argv[]) {
    int n;
    int* array = NULL;
    int* tmp;
    int start = 0;
    int finish = 0;
    int biggest[3];
    int holder[3];
    int unique = 1;
    while(unique != 3){
        printf("\nLutfen kullanmak istediginiz yontemi seciniz.\nBrute Force-(1)");
        printf("\nDivide and Conquer-(2)\nCikis-(3)\n");
        scanf(" %d", &unique);
        if(unique == 1){
            array = inputArray(&n, array);
            bruteForce(n, array, &start, &finish);
        }else if (unique == 2){
            array = inputArray(&n, array);
            tmp = divideAndConquer(n, array, 0, n-1, biggest, holder);
            printf("\nEn yuksek kazanc: %d", tmp[0]);
            printf("\nKazilmasi gereken kesintisiz blok butunu: %d-%d\n", tmp[1], tmp[2]);
        }
        printf("\n");
    }
    
    return 0;
}
