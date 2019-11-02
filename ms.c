#include <stdio.h>

#define N 4

void find_ms(int ms[N * N], int zero_entry[N * N], int list[N * N], int number, int start);
int check(int ms[N * N]);


int main(void)
{
    int i, j; // loop index
    int number; // the total number of numbers needed to filled in
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
            record[ms[i]] = 1; // means the ms[i] entry has showed up
    }
    for (i = 0, j = 0; i < N * N; i++)
        if (record[i] == 0) // i did't show up
            list[j++] = i;
    j = number;
    // then j will means the total number of nonzero entries
    find_ms(ms, zero_entry, list, number, 0);

    return 0;
}


void find_ms(int ms[N * N], int zero_entry[N * N], int list[N * N], int number, int start)
{
    int i, j; // loop index
    if (number == start)
       show_result(ms);
    else  {
        for (i = start; i < number; i++) {
            swap(list[start], list[i]);
            ms[zero_entry[start]] = list[start];
            if (check_row(ms) && check_col(ms) && check_diagonal(ms)
                find_ms(ms, zero_entry, list, number, start + 1);
            swap(list[start], list[i]);
        }
    }
}