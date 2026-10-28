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

#include <stddef.h>
#include <stdint.h>
#include <string.h>

static inline void merge_sort_member_copy(void *dst, void* src, size_t size) {
    for (int i = 0; i < size; i++)
        ((uint8_t*)dst)[i] = ((uint8_t*)src)[i];
}

void merge_sort_iteration(void *out, void* in, size_t nmemb, const int block_memb, size_t size, int (*compar)(const void *, const void*)) {
    int h; //start offset of currently processed block
    int i; //store offset for output data
    int j; //read offset for lower half-block of input data
    int k; //read offset for upper half-block of input data
    //sort full blocks
    int block_size = block_memb*size;
    for (h = 0; h < (nmemb - nmemb%block_memb)*size; h+= block_size) {
        j = h;
        k = h + block_size/2;
        for (i = h; i < h + block_size; i += size) {
            if (j < h + block_size/2) {
                if (k < h + block_size) {
                    if (compar(in+j, in+k)) {
                        merge_sort_member_copy(out+i, in+j, size);
                        j += size;
                    }
                    else {
                        merge_sort_member_copy(out+i, in+k, size);
                        k += size;
                    }
                }
                else {
                    merge_sort_member_copy(out+i, in+j, size);
                    j += size;
                }
            }
            else {
                merge_sort_member_copy(out+i, in+k, size);
                k += size;
            }
        }
    }

    //No partial(unsorted) block at the end of the input.
    //Sorting completed in this case. Return from the function.
    if (nmemb%block_memb == 0)
        return;

    //sort last remaining (partial) block
    h = (nmemb - nmemb%block_memb)*size;
    j = h;
    k = nmemb*size < h + block_size/2 ? nmemb*size : h + block_size/2;
    int j_max = nmemb*size < h + block_size/2 ? nmemb*size : h + block_size/2;
    int k_max = nmemb*size < h + block_size   ? nmemb*size : h + block_size;
    for (i = h; i < nmemb*size; i += size) {
        if (j < j_max) {
            if (k < k_max) {
                if (compar(in+j, in+k)) {
                    merge_sort_member_copy(out+i, in+j, size);
                    j += size;
                }
                else {
                    merge_sort_member_copy(out+i, in+k, size);
                    k += size;
                }
            }
            else {
                merge_sort_member_copy(out+i, in+j, size);
                j += size;
            }
        }
        else {
            merge_sort_member_copy(out+i, in+k, size);
            k += size;
        }
    }
}

void merge_sort(void *base, void *sort_buffer, size_t nmemb, size_t size, int (*compar)(const void *, const void*)) {
    void *in_buf = base;
    void *out_buf = sort_buffer;
    for (int block_memb = 2; block_memb < 2*nmemb; block_memb *= 2) {
        merge_sort_iteration(out_buf, in_buf, nmemb, block_memb, size, compar);
        void *tmp = in_buf; in_buf = out_buf; out_buf = tmp;
    }
    if (in_buf != base)
        memcpy(base, in_buf, nmemb*size);
}

