#include "gimli_hijo_de_gloin.h"




int main ()
{  FILE *f=fopen("C:\\Users\\juaan\\Desktop\\TIRANDO CODIGOS\\network_structure.dat","rb");
   if(f==NULL)
   {
    printf("ERROR OPEN FILE");
    return -1;
   }
    int c=countDevices(f);
    printf("\n numero de registro %d",c);
    net *v=new net[c];
    for (int i = 0; i < c; i++) {
        fread(&v[i], sizeof(net), 1, f);
    }
    mostras_archivo(f,v,c);
    
    uint16_t id;
    printf("\n Ingresar ID para ver su secuencia de conexion\n");
    scanf("%hu",&id);
    Search_Top_ID(f,v,c,id);
    Number_of_teams(f,v,c);
    rewind(f);
  return 0;

}