#include "gimli_hijo_de_gloin.h"
#include <stdint.h>
#include <stdio.h>



int main()
{   
    uint16_t idd;//con esta variable voy a leer los id 
    uint16_t lldc;// con esta variable guardo el total de los equipos que se conectan al inferior(abajo) de la red 
    uint16_t id;//con esta variable guardo los id 
    uint8_t type;//tipo de equipo que puede ser 
    uint16_t upld;//id del equipo superior al que esta conectado 
    uint8_t info;
    uint16_t lowe_level;
    uint64_t record;
    int x,i=0,total=0;
    int tipo1;
 FILE *f=fopen("C:\\Users\\juaan\\Desktop\\TIRANDO CODIGOS\\network_structure.dat","rb");
  
  if(f==NULL)
  {
    printf("erro open file ");
    return -1;
  } 
  while(fread(&record,sizeof(uint64_t),1,f)!=0)
  {
     uint16_t k= extract_segment(record,32,47);
     fseek(f,k*(sizeof(uint16_t)),SEEK_CUR);
     total ++;
  }
  printf("\n %d",total);

  /*int cant ;
  uint64_t h;
  while(fread(&h, sizeof(uint64_t), 1, f))
    {
        uint16_t Llc = (h << 16) >> 48;
        fseek(f, Llc*(sizeof(uint16_t)), SEEK_CUR);
         cant++;
    }
   printf("\n %d",cant);*/
  x=total;
  rewind(f);

   while(i<x)
   {
    fread(&idd,sizeof(uint16_t),1,f);
    id=idd;
    printf("\n %d",id);
    fread(&lldc,sizeof(uint16_t),1,f);
    printf("\n %d",lldc);
    fread(&type,sizeof(uint8_t),1,f);
    fread(&info,sizeof(uint8_t),1,f);
    fread(&upld,sizeof(uint16_t),1,f);
    printf("\n %d",upld);
    fseek(f,lldc*(sizeof(uint16_t)),SEEK_CUR);
    tipo1=extract_segment(record,24,25);
    if(tipo1==0)
    {
        printf("\n el equipo es un cpu");
    }
    if(tipo1==1)
    {
        printf("\n el equipo es un sensor");
    }
    if(tipo1==2)
    {
        printf("\n el equipo es un actuador");
    }
    if(tipo1==3)
    {
        printf("\n el equipo es un concentrador");
    }
    i++;
    
   }


 fclose(f);

   
 
 


    return 0;

}