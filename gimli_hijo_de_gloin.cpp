#include "gimli_hijo_de_gloin.h"
// herramientas OP
void show_bin32(uint32_t x)
{
    uint32_t mask = 0x80000000;
    for (int i = 0; i < 32; i++)
    {
        if (x & mask)
        {
            printf("1");
        }
        else
        {
            printf("0");
        }
        mask = mask >> 1;
        if ((i + 1) % 4 == 0 && i != 31)
        {
            printf(" ");
        }
    }
    printf("\n");
}
// shifteo y guardo el bit mas significativo msb lsb
uint32_t carry_rotate32(uint32_t data, int N)
{

    if (N == 0)
    {
        return data;
    }

    if (N > 0)
    {
        for (int i = 0; i < N; i = i + 1)
        {

            uint32_t bit_carry = (data >> 31) & 0x01;
            // Desplaza data una posicionn a la izquierda
            data = data << 1;
            // Inserta el bit de acarreo en el LSB
            data = data | bit_carry;
        }
    }
    else
    {
        N = -N;
        for (int i = 0; i < N; i++)
        {
            // ya tengo el lsb ahora lo tengo que llevar para la izquierda
            uint32_t bit_carry = data & 0x01;
            bit_carry = (0x01 << 31); // ya esta mi mascara
            // roto data para 1 para sacar el bit de msb y insertar mi bit que quiero
            data = (data >> 1);
            // inserto el bit de acarreo
            data = data | bit_carry;
        }
    }
    return data;
}
// extrar(cambiarlo ) un segemnto de una variable uint32 y llevarlo a la posiciob [0]
uint16_t extract_segment(uint16_t data, int start, int end)
{
    uint16_t mask = ((uint16_t(0x01) << (end - start + 1)) - uint16_t(0x01)) << start;
    return (data & mask) >> start;
}
// FUNCIONES VECTORES DINAMICOS
// funcion que concatena 2 vectores dinamico
int *concat(int *vec_left, int left_size, int *vec_right, int right_size)
{
    int *aux = new int[left_size + right_size];
    for (int i = 0; i < left_size; i++)
    {
        aux[i] = vec_left[i];
    }

    for (int i = 0; i < right_size; i++)
    {
        aux[left_size + i] = vec_right[i];
    }
    return aux;
}
// comparacion basic de 2 parametros
int comparacion(int a, int b) // comparo el tamaño nuevo y el tamaño viejo
{
    if (a < b)
    {
        return a;
    }
    else
    {
        return b;
    }
}
// esta funcion resize te varia el tamaño del vector a mas grande o mas pequeño
int *resize(int *old_vector, int old_size, int new_size)
{
    int *aux = new int[new_size]; // creo un vector de un x tamañano
    int smaller = comparacion(old_size, new_size);
    for (int i = 0; i < smaller; i++)
    {
        aux[i] = old_vector[i];
    }
    delete[] old_vector; // libero la memoria del antiguo vector
    return aux;          // retorno el nuevo vector
}
// mayor elemento de un vector
int buscarMayor(int *vector, int tamaño)
{
    if (tamaño == 0)
    {
        printf("\n ERROR\n");
        return -1;
    }

    int mayor = vector[0];
    for (int i = 1; i < tamaño; ++i)
    {
        if (vector[i] > mayor)
        {
            mayor = vector[i];
        }
    }
    return mayor;
}

// ordenar un vector procedimiento
void ordenarVector(int *vector, int tamaño)
{
    for (int i = 0; i < tamaño - 1; ++i)
    {
        for (int j = 0; j < tamaño - i - 1; ++j)
        {
            if (vector[j] > vector[j + 1])
            {
                // Intercambia vector[j] y vector[j + 1]
                int temp = vector[j];
                vector[j] = vector[j + 1];
                vector[j + 1] = temp;
            }
        }
    }
}
// MENOR ELEMENTO DE UN VECTOR
int buscarMenor(int *vector, int tamaño)
{
    if (tamaño == 0)
    {
        printf("\ERROR");
        return -1;
    }

    int menor = vector[0];
    for (int i = 1; i < tamaño; ++i)
    {
        if (vector[i] < menor)
        {
            menor = vector[i];
        }
    }
    return menor;
}
//-------------------------------------------------------------------------------------------------------------
//FUNCIONES Y PROCEDIMIENTOS PARCIAL NETWORK 
int countDevices(FILE *f)
{
    uint16_t header1;
    uint16_t header2;
    uint16_t header3;
    int count; // guardo los lower level devices count
    int c = 0;
    while (fread(&header1, sizeof(uint16_t), 1, f))
    {
        count = extract_segment(header1, 0, 5);
        fread(&header2,sizeof(uint16_t),1,f);
        fread(&header3,sizeof(uint16_t),1,f);
        fseek(f, count * sizeof(uint16_t), SEEK_CUR);
        c++;
    }
    rewind(f);
    return c;
}

void showlDs(FILE *f, net *v)
{   rewind(f);
    int c = countDevices(f);
    for (int i = 0; i < c; i++)
    {
        fread(&v[i].ID, sizeof(uint16_t), 1, f);
        printf("\n ID de los equipos -> %d", v[i].ID);
        fread(&v[i].LLDC, sizeof(uint16_t), 1, f);
        fread(&v[i].TYPE, sizeof(uint8_t), 1, f);
        fread(&v[i].INFO, sizeof(uint8_t), 1, f);
        fread(&v[i].UPLID, sizeof(uint16_t), 1, f);
        fseek(f, v[i].LLDC * sizeof(uint16_t), SEEK_CUR);
    }
}

net getRegister(FILE *f, uint16_t ID)
{
    uint16_t *x;
    int c = countDevices(f);
    net v[c];
    int i = 0;
    int tipo;
    int info1;
    uint16_t LLDC1;
    while (i < c)
    {
        fread(&v[i].ID, sizeof(uint16_t), 1, f);
        fread(&v[i].LLDC, sizeof(uint16_t), 1, f);
        LLDC1 = v[i].LLDC;
        fread(&v[i].TYPE, sizeof(uint8_t), 1, f);
        tipo = extract_segment(v[i].TYPE, 0, 1);
        fread(&v[i].INFO, sizeof(uint8_t), 1, f);
        info1 = extract_segment(v[i].INFO, 4, 5);
        fread(&v[i].UPLID, sizeof(uint16_t), 1, f);
        x = new uint16_t[LLDC1];
        for (int j = 0; j < LLDC1; j++)
        {
            fread(&x[j], sizeof(uint16_t), 1, f);
        }

        if (v[i].ID == ID)
        {
            printf("\n ID ->%d", v[i].ID);
            printf("\n cantidad de dispositvos que estan conectados a la capa inferior=%d\n", v[i].LLDC);
            printf("\n ID del equipo superior = %d", v[i].UPLID);
            for (int j = 0; j < LLDC1; j++)
            {

                printf("\n Lower level device ID =%d", x[j]);
            }
        }
        i++;
    }
    return v[i];
}

int busqueda_lineal(FILE *f, net *v, uint16_t id)
{  
    
    int c;
    c = countDevices(f);
    for (int i = 0; i < c; i++)
    {
        if (v[i].ID == id)
        {
           return i;
        }
        
    }
    return -1;
    
}
void mostras_archivo(FILE *f, net *v, int c)
{
    rewind(f);
    int i = 0;
    int j = 0;
    uint16_t header1;
    uint16_t header2;
    uint16_t header3;
    uint16_t typeNL=0;
    uint16_t typeNH=0;
    uint16_t LLDC1;
    uint16_t *x;
    uint16_t tipo;
    uint16_t info1;
    uint64_t tipo1;
    while (i < c)
    {
        printf("\n--------------------------\n");
        fread(&header1,sizeof(uint16_t),1,f);
        v[i].LLDC=extract_segment(header1,0,5);
          LLDC1 = v[i].LLDC;

        v[i].ID=extract_segment(header1,6,15);
        printf("\n ID %d",v[i].ID);
        fread(&header2,sizeof(uint16_t),1,f);

        typeNL=extract_segment(header2,3,3);
        typeNH=extract_segment(header2,12,12);
      

        info1=extract_segment(header2,8,9);
        tipo1=extract_segment(header2,6,6);

        fread(&header3,sizeof(uint16_t),1,f);

        v[i].UPLID=extract_segment(header3,3,12);
        printf("\n ID del equipo superior %d",v[i].UPLID);

        
        LLDC1 = v[i].LLDC;
        
        x = new uint16_t[LLDC1];
        uint16_t aux;
        for (j = 0; j < LLDC1; j++)
        {
            fread(&aux, sizeof(uint16_t), 1, f);

            x[j] = aux;
            printf("\n Lower level device ID =%d", x[j]);
        }

        if (typeNH==0 && typeNL==0)
        {
            printf("\n el equipo es un cpu\n");
            printf("\n la cantidad de equipos en la capa inferior =%d",v[i].LLDC);
        }
        if (typeNH==0 && typeNL==1)
        {
            printf("\n el equipo es un sensor\n");
            if (info1 == 0)
            {
                printf("\n sensor flow\n");
            }
            if (info1 == 1)
            {
                printf("\n sensor tempe\n");
            }
            if (info1 == 2)
            {
                printf("\n sensor presure\n");
            }
            if (info1 == 3)
            {
                printf("\n sensor level\n");
            }
        }
        if (typeNH == 1 && typeNL==0)
        {
            printf("\n el equipo es un actuador\n");
            if (tipo1 == 0)
            {
                printf("\n actudador valve");
            }
            if (tipo1 == 1)
            {
                printf("\n actuador motor\n");
            }
        }
        if (typeNH==1 && typeNL==1)
        {

            printf("\n el equipo concetrador ");
            printf("\n la cantidad de equipos en la capa inferior =%d",v[i].LLDC);
        }
        printf("\n--------------------------\n");
        i++;

        // printf("\n--------------------------\n");
    }
    delete[] x;
}
void Search_Top_ID(FILE *f, net *v, int c, uint16_t id)
{   
    int total_devis = countDevices(f);

    int j = 0;                           // tamaño para mi vector dinamico
    int pos = busqueda_lineal(f, v, id); // busco la posicion del id que ingreso el usuario
    
    while (v[pos].UPLID != 1023)
    {
        j++; // bucleo y aumento mi contador para el vector de ulplid
        
        pos= busqueda_lineal(f, v, v[pos].UPLID);
        if(pos==-1)
        {
            break;
        }
    }
    int *x = new int[j + 1];
    pos=busqueda_lineal(f,v,id);
    for(int i=0;i<=j;i++)
    {
        x[i]=v[pos].ID;
        pos=busqueda_lineal(f,v,v[pos].UPLID);
    }
    printf("\n");
    for(int i=j;i>=0;i--)
    {
        printf("id %d",x[i]);
       if(i>0)
       {
          printf("->");
       }
        
    }
    printf("\n");
    delete[]x;
};
void Number_of_teams(FILE *f,net *v,int c)
{
    rewind(f);
    int i = 0;
    int j = 0;
    uint16_t header1;
    uint16_t header2;
    uint16_t header3;
    uint16_t typeNL=0;
    uint16_t typeNH=0;
    uint16_t LLDC1;
    uint16_t *x;
    uint16_t tipo;
    uint16_t info1;
    uint16_t tipo1;
    int cont_cpu=0;
    int cont_concentrador=0;
    int temp_sensor=0;
    int valve=0;
    while (i < c)
    {
        

        fread(&header1,sizeof(uint16_t),1,f);
        v[i].LLDC=extract_segment(header1,0,5);
          LLDC1 = v[i].LLDC;
        v[i].ID=extract_segment(header1,6,15);

        fread(&header2,sizeof(uint16_t),1,f);
        typeNL=extract_segment(header2,3,3);
        typeNH=extract_segment(header2,12,12);
     

        info1=extract_segment(header2,8,9);

        fread(&header3,sizeof(uint16_t),1,f);
        v[i].UPLID=extract_segment(header3,3,12);
        LLDC1 = v[i].LLDC;
        
        x = new uint16_t[LLDC1];
        uint16_t aux;
        for (j = 0; j < LLDC1; j++)
        {
            fread(&aux, sizeof(uint16_t), 1, f);

            x[j] = aux;
         
        }

        if (typeNH == 1 && typeNL==0)
        {
            
           cont_cpu=cont_cpu+1;
           
        }
        if (typeNH==0 && typeNL==1)
        {   temp_sensor=temp_sensor+1;
           
           
        }
        if (typeNH == 1 && typeNL==0)
        {    
             valve=valve+1;
           
        }
        if (typeNH==1 && typeNL==1)
        {
            cont_concentrador=cont_concentrador+1;
           
           
        }
        
        i++;

        // printf("\n--------------------------\n");
    }
    delete[] x;
    printf("\n La cantidad total de cada dispositivo \n");
    printf("\n CPU =%d",cont_cpu);
    printf("\n CONCENTRATOR =%d",cont_concentrador);
    printf("\n TEMPE SENSOR =%d",temp_sensor);
    printf("\n VALVE =%d",valve);


    
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

