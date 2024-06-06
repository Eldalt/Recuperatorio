#pragma once
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
struct network 
{  
    uint16_t ID;//ID
    uint16_t LLDC;//contador de dispostivos conectados en el nivel inferior
    uint8_t TYPE;//tipo de dispositvo
    uint8_t INFO;//info solo para sensores y actudores 
    uint16_t UPLID;//ID del equipo superior 

    
};
typedef struct network net;
void showlDs( FILE *f, net *v);
int countDevices(FILE *f);
net getRegister(FILE *f, uint16_t  ID);
int  busqueda_lineal(FILE *f,net *v,uint16_t id);
void mostras_archivo(FILE*f,net *v,int c);
void Search_Top_ID(FILE *f,net *v,int c,uint16_t id);
/**
 * @brief Number_of_teams
 * este procedimiento te dice la cantidad total del tipo de dispositivo que tengo en la conexion
 * 
 * @param f //manipulador del archivo
 * @param v //estructura de tipo net 
 * @param c //tope de la estructura 
 */
void Number_of_teams(FILE *f,net *v,int c);


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
 * Esta funcion extrae un segmento de una variable de 64 y llevandola a la posicion 0 (lsb)
 * para un funcionamiento mas sencillo
 * @param data como parametro de la variable de 64
 * @param start como parametro inicial del segmento 
 * @param end como parametro final del segmento 
 * 
 */
uint16_t extract_segment (uint16_t data, int start, int end);
//declaraciones array 
int* concat(int* vec_left,int left_size,int* vec_right,int right_size);
int comparacion(int a,int b);
int *resize(int *old_vector,int old_size,int new_size);
int buscarMayor(int* vector, int tamaño) ;
void ordenarVector(int* vector, int tamaño);
int buscarMenor(int* vector, int tamaño);




//----------------------------------------------------------------
int total_archivos(FILE *f);