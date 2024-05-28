#include "gimli_hijo_de_gloin.h"
#include <stdint.h>
#include <stdio.h>

struct type
{   
    uint64_t cpu;
    uint64_t sensor;
    uint64_t actuador;
    uint64_t concentrador;
    uint64_t flow;
    uint64_t temp;
    uint64_t presure;
    uint64_t level;
    uint64_t valve;
    uint64_t motor;
   

};

struct network
{
    uint64_t id;//total de id 
    struct type k;
    uint64_t info ;
    uint64_t t_lower;//total de equipos (lower)
    uint16_t *id_vec ;//vector dinamico de id 
    uint64_t  upper_leve;
    int tipo1;
    int tipo2;
    int tipo3 ;
};





main ()
{   
    FILE *f=fopen("C:\\Users\\juaan\\Desktop\\TIRANDO CODIGOS\\network_structure.dat","rb");
    int cond=1;//contador de lower level 
    uint64_t x;
    int c=0;
    //int tipo1,tipo2,tipo3;
    //recorro el archivo
    while(fread( &x , sizeof(uint64_t), 1, f)!=0)
  {  
    cond=extract_segment(x,32,47);
    fseek(f,cond*sizeof(uint16_t),SEEK_CUR);

     c++;// cuento el archivo 
  }
 rewind(f);
 struct network *v=new network[c];//extructura dinamica 
 printf("\n %d",c);
 for(int i=0;i<c;i++)
 {
      fread(&x,sizeof(uint64_t),1,f);
    v[i].id =extract_segment(x,48,63);//extraigo mi id 
    v[i].t_lower=extract_segment(x,32,47);//extraigo el total 
    v[i].id_vec= new uint16_t [v[i].t_lower];
   //fread(&x,sizeof(uint32_t),1,f);
   v[i].upper_leve=extract_segment(x,0,15);
  // v[i].info=extract_segment(x,16,23);
   v[i].tipo1=extract_segment(x,24,25);
   if(v[i].tipo1==0)
   { 
     v[i].k.cpu=extract_segment(x,24,31);
   }
   if(v[i].tipo1==1)
   {
     v[i].k.sensor=extract_segment(x,24,31);
   }
   if(v[i].tipo1==2)
   { 
     v[i].k.actuador=extract_segment(x,24,31);
   }
   if(v[i].tipo1==3)
   {
     v[i].k.concentrador=extract_segment(x,24,31);
   }
    v[i].tipo2=extract_segment(x,20,21);
    if(v[i].tipo2==0)
    {   v[i].info=extract_segment(x,16,23);
        v[i].k.flow=extract_segment(x,24,31);
    }
    if(v[i].tipo2==1)
    {   v[i].info=extract_segment(x,16,23);
      v[i].k.temp=extract_segment(x,24,31);
    }
    if(v[i].tipo2==2)
    {    v[i].info=extract_segment(x,16,23);
        v[i].k.presure=extract_segment(x,24,31);
        //printf("\n el equipo es un sensor de presure %d",v[i].k.presure);
    }
    if(v[i].tipo2==3)
    {   v[i].info=extract_segment(x,16,23);
        v[i].k.level=extract_segment(x,24,31);
        //printf("\n el equipo es un sensor de level %d",v[i].k.level);
    }
    v[i].tipo3=extract_segment(x,23,23);
    if(v[i].tipo3==0)
    {
        v[i].k.valve=extract_segment(x,24,31);
    } 
    if(v[i].tipo3==1)
    {
        v[i].k.motor=extract_segment(x,24,31);
    }
    fread(v[i].id_vec,sizeof(uint16_t),(v[i].t_lower),f);
 } 


 for(int i=0;i<c;i++)
  {   
    printf("\n-------------\n");
    printf("\n El id=%u",v[i].id);
     printf("\n-------------\n");
    printf("\n total de equipos= %u",v[i].t_lower);
    printf("\n id del equipo nivel superior donde estoy conectado= %u",v[i].upper_leve);
    printf("\n-------------\n");
    printf(".....\n cantidad de equipos\n......");
    for(int j=0;j<v[i].t_lower;j++)
    {
        printf("\n lower level id %u",v[i].id_vec[j]);
    }
    
    if(v[i].tipo1==0)
   {  printf("\n el equipo es un cpu %u\n",v[i].k.cpu);
     //v[i].k.cpu=tipo1;
   }
   if(v[i].tipo1==1)
   {  
     printf("\n el equipo es un sensor %u\n",v[i].k.sensor);
     // v[i].k.sensor=tipo1;
   }
   if(v[i].tipo1==2)
   { printf("\n el equipo es un actuador %u\n",v[i].k.actuador);
     //v[i].k.actuador=tipo1;
   }
   if(v[i].tipo1==3)
   { printf("\n el equipo es un concentrador %u\n",v[i].k.concentrador);
     //v[i].k.concentrador=tipo1;
   }
   if(v[i].tipo2==0)
    {   
        printf("\n el equipo es un sensor de flow %u",v[i].k.flow);
        //v[i].k.flow=tipo2;
    }
    if(v[i].tipo2==1)
    {   printf("\n el equipo es un sensor de temp %u",v[i].k.temp);
        
        //v[i].k.temp=tipo2;
    }
    if(v[i].tipo2==2)
    {   printf("\n el equipo es un sensor de presure %u",v[i].k.presure);
        //v[i].k.presure=tipo2;
    }
    if(v[i].tipo2==3)
    {  printf("\n el equipo es un sensor de level %u",v[i].k.level);
        //v[i].k.level=tipo2;
    }
    if(v[i].tipo3==0)
    {   
        printf("\n el equipo es un actuador valve %u",v[i].k.valve);
        //v[i].k.valve=tipo3;
    } 
    if(v[i].tipo3==1)
    {    
        printf("\n el equipo es un actuador motor %u",v[i].k.motor);
       // v[i].k.motor=tipo3;
    }
  }
 
    delete [] v[c].id_vec;
    delete[]v;
    fclose(f);
   return 0;
}
