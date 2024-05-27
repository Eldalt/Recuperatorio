#include "gimli_hijo_de_gloin.h"
#include <stdint.h>
#include <stdio.h>

struct network
{
    uint64_t id;//total de id 
    uint64_t type;
    uint64_t info ;
    uint64_t t_lower;//total de equipos (lower)
    uint16_t *id_vec ;//vector dinamico de id 
    uint64_t  upper_leve;
};





main ()
{    
    FILE *f=fopen("C:\\Users\\juaan\\Desktop\\TIRANDO CODIGOS\\network_structure.dat","rb");
    int cond=1;//contador de lower level jiji
    uint64_t x;
    int c=0;
    while(fread( &x , sizeof(uint64_t), 1, f)!=0)
  {  
    cond=extract_segment(x,32,47);
    fseek(f,cond*sizeof(uint16_t),SEEK_CUR);

     c++;
  }
rewind(f);
struct network *v=new network[c];
printf("\n %d",c);
for(int i=0;i<c;i++)
{  fread(&x,sizeof(uint64_t),1,f);
   v[i].id =extract_segment(x,48,63);
   v[i].t_lower=extract_segment(x,32,47);
   v[i].id_vec= new uint16_t [v[i].t_lower];
   fread(&x,sizeof(uint32_t),1,f);
   v[i].upper_leve=extract_segment(x,0,15);
   v[i].info=extract_segment(x,16,23);
   v[i].type=extract_segment(x,24,31);
   fread(v[i].id_vec,sizeof(uint16_t),(v[i].t_lower),f);
   
}





}