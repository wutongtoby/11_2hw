#include <stdio.h>

#define N 4
#define NUM (N * N + 1) * N / 2
int sol = 0;
int k = 0;
void find_ms(int ms[N * N], int zero_entry[N * N], int list[N * N], int number, int start);
int check(int ms[N * N]);
void print(int ms[N * N], int length);

int main(void)
{
    int i, j; // loop index
    int ms[N * N]; // to  read in the data
    int zero_entry[N * N]; // record the place that is empty at first
    int record[N * N];
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

    find_ms(ms, zero_entry, list, j, 0);
    printf("sol is %d\n", sol);
    return 0;
}


void find_ms(int ms[N * N], int zero_entry[N * N], int list[N * N], int number, int start)
{
    int i, j; // loop index
    int temp;

    if (number == start) {
       //print(ms, N * N);
       //printf("\n");
       sol++;
    }
    else  {
        for (i = start; i < number; i++) {
            // swap list[i] and list[start]
            temp = list[start];
            list[start] = list[i];
            list[i] = temp;
            //printf("XXX%dXXX\n", k++);
            //printf("start: %d, number: %d\n", start, number);
            //print(list, 5);
            //printf("\n");
            ms[zero_entry[start]] = list[start];
            //print(ms, N * N);
            
            if (check(ms) == 1)
                find_ms(ms, zero_entry, list, number, start + 1);
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
        if (has_zero == 0 && (sum != NUM))
            return 0;
        else if (sum > NUM)
            return 0;
    }


    // check column
    for (i = 0; i < N; i++) {
        for (j = 0, has_zero = 0, sum = 0; j < N; j++) {
            sum += ms[j * N + i];
            if (ms[j * N + i] == 0)
                has_zero == 1;
        }
        if (has_zero == 0 && (sum != NUM))
            return 0;
        else if (sum > NUM)
            return 0;
    }

    // check diagonal
    for (i = 0, has_zero = 0, sum = 0; i < N; i++) {
        sum += ms[i + i * N];
        if (ms[i + i * N] == 0)
            has_zero = 1;
    }
    if (has_zero == 0 && (sum != NUM))
        return 0;
    else if (sum < NUM)
        return 0;
   
    for (i = 0, has_zero = 0, sum = 0; i < N; i++) {
        sum += ms[(N - 1) * (i + 1)];
        if (ms[(N - 1) * (i + 1)] == 0)
            has_zero = 1;
    }
    if (has_zero == 0 && (sum != NUM))
        return 0;
    else if (sum < NUM)
        return 0;

    return 1;
} 

void print(int ms[N * N],int length) 
{
    int i;
    for (i = 0; i < length; i++) {
        printf("%4d", ms[i]);
        if ((i + 1)% N  == 0)
            printf("\n");
    }
}