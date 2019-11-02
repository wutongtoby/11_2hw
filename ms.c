#include <stdio.h>

#define N 4
#define NUM (N * N + 1) * N / 2

int sol = 0;
void find_ms(int ms[N * N], int zero_entry[N * N], int list[N * N], int start, int end);
int check(int ms[N * N]);
void print(int ms[N * N]);

int main(void)
{
    int i, j; // loop index
    int ms[N * N]; // to  read in the data
    int zero_entry[N * N]; // record the place that is empty at first
    int record[N * N]; // to record which number did appear
    int list[N * N]; // the list of numbers that used to fill in the ms

    for (i = 0; i < N * N; i++)
        record[i] = 0;
    for (i = 0, j = 0; i < N * N; i++) {
        scanf("%d", &ms[i]);
        if (ms[i] == 0) 
            zero_entry[j++] = i; // means the ith entries is empty
        else
            record[ms[i] - 1] = 1; // means the ms[i] entry has showed up
    }
    for (i = 0, j = 0; i < N * N; i++)
        if (record[i] == 0) {// i did't show up 
            list[j++] = i + 1;
        }
    // then j will means the total number of nonzero entries

    find_ms(ms, zero_entry, list,0, j);
    printf("Toltal number of solutions is %d\n", sol);
    return 0;
}

void find_ms(int ms[N * N], int zero_entry[N * N], int list[N * N], int start, int end)
{
    int i; // loop index
    int temp;

    if (start == end) {
        printf("Solution: %d\n", ++sol);
        print(ms);
        printf("\n");
    }
    else  {
        for (i = start; i < end; i++) {
            // swap list[i] and list[start]
            temp = list[start];
            list[start] = list[i];
            list[i] = temp;
    
            ms[zero_entry[start]] = list[start]; // fill in the number
            
            if (check(ms) == 1) // if after filling in is still valid, fill the next in
                find_ms(ms, zero_entry, list, start + 1, end);
            
            // swap list[i] and list[start]
            temp = list[start];
            list[start] = list[i];
            list[i] = temp;
        }
        ms[zero_entry[start]] = 0;
    }
}

int check(int ms[N * N]) 
{
    int i, j;
    int sum;
    int has_zero;
    
    //check row
    for (i = 0; i < N; i++) {
        for (j = 0, has_zero = 0, sum = 0; j < N; j++) { 
            sum += ms[i * N + j];
            if (ms[i * N + j] == 0)
                has_zero = 1;
        }
        if ((has_zero == 0 && sum != NUM) || sum > NUM)
            return 0;
    }


    // check column
    for (i = 0; i < N; i++) {
        for (j = 0, has_zero = 0, sum = 0; j < N; j++) {
            sum += ms[j * N + i];
            if (ms[j * N + i] == 0)
                has_zero = 1;
        }
        if ((has_zero == 0 && sum != NUM) || sum > NUM)
            return 0;
    }

    // check major diagonal
    for (i = 0, has_zero = 0, sum = 0; i < N; i++) {
        sum += ms[i + i * N];
        if (ms[i + i * N] == 0)
            has_zero = 1;
    }
    if ((has_zero == 0 && sum != NUM) || sum > NUM)
            return 0;
    
    // check minor diagonal
    for (i = 0, has_zero = 0, sum = 0; i < N; i++) {
        sum += ms[(N - 1) * (i + 1)];
        if (ms[(N - 1) * (i + 1)] == 0)
            has_zero = 1;
    }
    if ((has_zero == 0 && sum != NUM) || sum > NUM)
            return 0;
    // if col + row + diagonal is okay then is okay
    return 1;
} 

void print(int ms[N * N]) 
{
    int i;
    for (i = 0; i < N * N; i++) {
        printf("%4d", ms[i]);
        if ((i + 1)% N  == 0)
            printf("\n");
    }
}