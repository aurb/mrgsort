/*  Merge sort C function
    Copyright (C) 2024 Andrzej Urbaniak

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>. */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdint.h>

#include "mrgsort.h"

typedef struct {
    int index;
    int value;
} SORT_CONTAINER;

int *rand_sequence = NULL;

SORT_CONTAINER *sort_buffer_a_cont = NULL;
SORT_CONTAINER *sort_buffer_b_cont = NULL;

int comp_cont(const void *a, const void *b) {
    return ((SORT_CONTAINER*)a)->value <= ((SORT_CONTAINER*)b)->value;
}

//Test function checking correctness of sorting results
void test_result_cont(SORT_CONTAINER *in, int *orig_seq, const int in_length) {
    for (int i = 0; i < in_length; i++) {
        if (in[i].value != orig_seq[in[i].index]) {
            printf("Container index mismatch: in[%d].index=%d, in[%d].value=%d orig_seq[%d]=%d\n", i, in[i].index, i, in[i].value, in[i].index, orig_seq[in[i].index]);
            return;
        }
    }
    for (int i = 1; i < in_length; i++) {
        if (in[i].value < in[i-1].value) {
            printf("Container wrong sorted values order: in[%d]=%d, in[%d]=%d\n", i-1, in[i-1].value, i, in[i].value);
            return;
        }
        else if (in[i].value == in[i-1].value && in[i].index < in[i-1].index) {
            printf("Container sort unstability: in[%d].index=%d, in[%d].index=%d\n", i-1, in[i-1].index, i, in[i].index);
            return;
        }
    }
}

long long currentTimeMillis() {
    struct timeval time;
    gettimeofday(&time, NULL);
    return (long long)time.tv_sec * 1000 + time.tv_usec / 1000;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Call %s max_seq_size test_iterations\n", argv[0]);
        exit(1);
    }
    int buf_length = atoi(argv[1]);
    int iterations = atoi(argv[2]);
    long long startTime, endTime;

    rand_sequence = calloc(buf_length, sizeof(int));

    sort_buffer_a_cont = calloc(buf_length, sizeof(SORT_CONTAINER));
    sort_buffer_b_cont = calloc(buf_length, sizeof(SORT_CONTAINER));


    int seq_length = buf_length;
    for (int i=0; i<seq_length; i++) {
        rand_sequence[i] = rand()%1000000;
    }

    printf("iteration sorting_time[ms]\n");
    for (int iter = 0; iter<iterations; iter++) {
        for (int i=0; i<seq_length; i++) {
            sort_buffer_a_cont[i].index = i;
            sort_buffer_a_cont[i].value = rand_sequence[i];
        }
        startTime = currentTimeMillis();
        merge_sort(sort_buffer_a_cont, sort_buffer_b_cont, seq_length, sizeof(SORT_CONTAINER), comp_cont);
        endTime = currentTimeMillis();

        //Below commented-out code introduces errors into sorted data.
        //It was used to to verify operation of test_result_cont.
        //Now it's redundant, but decided to keep it, in case such verification is needed again.

        //simulate wrong sorted values order 
        //sort_buffer_a_cont[1000].value = sort_buffer_a_cont[2000].value; 
        //sort_buffer_a_cont[1000].index = sort_buffer_a_cont[2000].index; 

        //simulate index mismatch
        //sort_buffer_a_cont[1000].value = sort_buffer_a_cont[2000].value; 

        #if 0
            //simulate unstability
            for (int i=1; i<seq_length; i++) {
                if (sort_buffer_a_cont[i-1].value == sort_buffer_a_cont[i].value && sort_buffer_a_cont[i-1].index < sort_buffer_a_cont[i].index) {
                    int t = sort_buffer_a_cont[i-1].index;
                    sort_buffer_a_cont[i-1].index = sort_buffer_a_cont[i].index;
                    sort_buffer_a_cont[i].index = t;
                    break;
                }
            }
        #endif
        printf("%d %lld\n", iter, endTime-startTime);
        test_result_cont(sort_buffer_a_cont, rand_sequence, seq_length);
    }

    free(rand_sequence);

    free(sort_buffer_a_cont);
    free(sort_buffer_b_cont);

    return 0;
}