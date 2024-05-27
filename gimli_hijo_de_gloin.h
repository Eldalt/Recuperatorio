#pragma once
#include <stdlib.h>
#include <stdint.h>
//declaraciones OP
void show_bin32(uint32_t x);
uint32_t carry_rotate32(uint32_t data,int N);
uint32_t extract_segment(uint32_t data, int start, int end);
//declaraciones array 
int* concat(int* vec_left,int left_size,int* vec_right,int right_size);
int comparacion(int a,int b);
int *resize(int *old_vector,int old_size,int new_size);