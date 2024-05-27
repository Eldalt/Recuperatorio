#pragma once
#include <stdlib.h>
#include <stdint.h>
//declaraciones OP
/**
 * @brief Show_bin32
 * este procedimiento retorna una variable de tipo uint32 y te la convierte a binario para su manipulacion
 * sirve mucho para mostrar variables de 32 bits muchos mas comodo para su interpretacion 
 * 
 * 
 *  
 * 
 */
void show_bin32(uint32_t x);
/**
 * @brief carry_rotate 32
 * esta funcion retorna una variable uint32 su funcionamiento trata de rotar una variable n veces y los bits 
 * MSB  y LSB  no se pierden si no se insertan de nuevo en la variable pero al lado contrario 
 * @param data  como parametro es de tipo uint32_t 
 * @param N cantidad de veces que quieras rotar 
 * @return uint32_t  lo que retorna 
 */
uint32_t carry_rotate32(uint32_t data,int N);
/**
 * @brief extract_segemente
 * Esta funcion extrae un segmento de una variable de 32 bits y llevandola a la posicion 0 (lsb)
 * para un funcionamiento mas sencillo
 * @param data como parametro de la variable de 32 bits 
 * @param start como parametro inicial del segmento 
 * @param end como parametro final del segmento 
 * 
 */
uint32_t extract_segment(uint32_t data, int start, int end);
//declaraciones array 
int* concat(int* vec_left,int left_size,int* vec_right,int right_size);
int comparacion(int a,int b);
int *resize(int *old_vector,int old_size,int new_size);
int buscarMayor(int* vector, int tamaño) ;
void ordenarVector(int* vector, int tamaño);
int buscarMenor(int* vector, int tamaño);