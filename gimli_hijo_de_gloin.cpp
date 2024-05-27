#include "gimli_hijo_de_gloin.h"
#include <stdint.h>
#include <stdio.h>
// herramientas OP
void show_bin32(uint32_t x)
{
    uint32_t mask = 0x80000000;
    for (int i = 0; i < 32; i++)
    {
        if (x&mask)
        {
            printf("1");
        }
        else
        {
          printf("0");
        }
        mask=mask>>1;
        if ((i + 1) % 4 == 0 && i != 31) 
        {
            printf(" ");
        
           
        }
        
    }
    printf("\n");
}
// shifteo y guardo el bit mas significativo msb lsb 
uint32_t carry_rotate32(uint32_t data,int N)
{

    if (N == 0) {
        return data;
    }

    if(N>0)
    { for (int i = 0; i < N; i=i+1) 
     {

       uint32_t bit_carry=(data >> 31) & 0x01;
      // Desplaza data una posicionn a la izquierda
        data = data << 1;
     // Inserta el bit de acarreo en el LSB
        data = data | bit_carry; 
     }  

    }
    else
    {   N=-N;
      for(int i=0;i<N;i++)
      {
        //ya tengo el lsb ahora lo tengo que llevar para la izquierda
        uint32_t bit_carry=data&0x01;
        bit_carry=(0x01<<31);//ya esta mi mascara 
        //roto data para 1 para sacar el bit de msb y insertar mi bit que quiero 
        data=(data>>1);
        //inserto el bit de acarreo 
        data=data|bit_carry;
      } 
       
    }
    return data;
}
//extrar(cambiarlo ) un segemnto de una variable uint32 y llevarlo a la posiciob [0]
 uint32_t extract_segment(uint32_t data, int start, int end){
    uint32_t mask = ((0x01 << (end - start + 1)) - 0x01) << start;
    return (data & mask) >> start;

 }
//FUNCIONES VECTORES DINAMICOS 
//funcion que concatena 2 vectores dinamico 
int* concat(int* vec_left,int left_size,int* vec_right,int right_size)
{
  int *aux=new int[left_size+right_size];
  for (int i = 0; i < left_size; i++)
  {
    aux[i]=vec_left[i];
  }
  
  for (int i = 0; i < right_size; i++)
  {
    aux[left_size+i]=vec_right[i];
  }
  return aux;
}
//comparacion basic de 2 parametros 
int comparacion(int a,int b)//comparo el tamaño nuevo y el tamaño viejo 
{
    if (a<b)
    {
        return a;

    }
    else
    {
        return b;
    } 

    
}
//esta funcion resize te varia el tamaño del vector a mas grande o mas pequeño 
int *resize(int *old_vector,int old_size,int new_size)
{
    int *aux=new int[new_size];//creo un vector de un x tamañano 
    int smaller=comparacion(old_size,new_size);
    for (int i = 0; i < smaller; i++)
    {
        aux[i]=old_vector[i];
        
    }
    delete[]old_vector;//libero la memoria del antiguo vector
   return aux;//retorno el nuevo vector
}
// mayor elemento de un vector 
int buscarMayor(int* vector, int tamaño) 
{
    if (tamaño == 0) {
        printf("\n ERROR\n");
        return -1; 
    }
    
    int mayor = vector[0];
    for (int i = 1; i < tamaño; ++i) {
        if (vector[i] > mayor) {
            mayor = vector[i];
        }
    }
    return mayor;
}

//ordenar un vector procedimiento 
void ordenarVector(int* vector, int tamaño) {
    for (int i = 0; i < tamaño - 1; ++i) {
        for (int j = 0; j < tamaño - i - 1; ++j) {
            if (vector[j] > vector[j + 1]) {
                // Intercambia vector[j] y vector[j + 1]
                int temp = vector[j];
                vector[j] = vector[j + 1];
                vector[j + 1] = temp;
            }
        }
    }
}
//MENOR ELEMENTO DE UN VECTOR 
int buscarMenor(int* vector, int tamaño) {
    if (tamaño == 0) {
       printf("\ERROR");
        return -1; 
    }
    
    int menor = vector[0];
    for (int i = 1; i < tamaño; ++i) {
        if (vector[i] < menor) {
            menor = vector[i];
        }
    }
    return menor;
}
