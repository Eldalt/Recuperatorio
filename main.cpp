#include "gimli_hijo_de_gloin.h"
#include <stdint.h>
#include <stdio.h>

struct network
{
    uint32_t id ;
    uint32_t type;
    uint32_t info ;
  //  *lower level ;
    //uint32_t upper level;
};





main ()
{    
    FILE *f=fopen("C:\\Users\\juaan\\Desktop\\TIRANDO CODIGOS\\network_structure.dat","rb");
    int cond=1;//contador de lower level jiji
    uint32_t x;
    uint32_t x1;
    int c=0;
    while(fread( &x , sizeof(uint32_t), 1, f)!=0)
  {  
    cond=extract_segment(x,0,15);
    fseek(f,sizeof(uint32_t),SEEK_CUR);
   fseek(f,cond*sizeof(uint16_t),SEEK_CUR);

     c++;
  }
rewind(f);
struct network *v=new network[c];
printf("\n %d",c);
for(i=0;i<c;i++)
{
    
}


}