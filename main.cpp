#include "gimli_hijo_de_gloin.h"
struct M
{   
    uint32_t motor;
    uint32_t t;//torque 
    uint32_t co;//corriente ampers
    uint32_t v;//voltaje en volts
    uint32_t p;//peso en kg
};
main()
{   
   
    int c=0;
  FILE *f=fopen("C:\\Users\\juaan\\Desktop\\TIRANDO CODIGOS\\motors.dat","rb");
  uint32_t x;
  while(fread( &x , sizeof(uint32_t), 1, f)!=0)// cuento la cantidad de motores 
  {  
    
    c++;
  }
  rewind(f);
  printf("%d",c);
 struct M *k= new M[c];
 for (int i = 0; i < c; i++)
 { 
   fread(&x,sizeof(uint32_t),1,f);
   k[i].motor=extract_segment(x,3,4);
    if(k[i].motor==0)
    { //tipo brusheles 
      //extraigo torque 
      k[i].t=extract_segment(x,5,13);
      //extragio corriente 
      k[i].co=extract_segment(x,16,19);
      //extraigo voltaje 
      k[i].v=extract_segment(x,20,27);
      //extraigo el peso 
      k[i].p=extract_segment(x,28,31);


    }
    if(k[i].motor==1)
    { //tipo brusheles 
      //extraigo torque 
      k[i].t=extract_segment(x,5,13);
      //extragio corriente 
      k[i].co=extract_segment(x,16,19);
      //extraigo voltaje 
      k[i].v=extract_segment(x,20,27);
      //extraigo el peso 
      k[i].p=extract_segment(x,28,31);


    }
    if(k[i].motor==2)
    { //tipo brusheles 
      //extraigo torque 
      k[i].t=extract_segment(x,5,13);
      //extragio corriente 
      k[i].co=extract_segment(x,16,19);
      //extraigo voltaje 
      k[i].v=extract_segment(x,20,27);
      //extraigo el peso 
      k[i].p=extract_segment(x,28,31);


    }
    if(k[i].motor==3)
    { //tipo brusheles 
      //extraigo torque 
      k[i].t=extract_segment(x,5,13);
      //extragio corriente 
      k[i].co=extract_segment(x,16,19);
      //extraigo voltaje 
      k[i].v=extract_segment(x,20,27);
      //extraigo el peso 
      k[i].p=extract_segment(x,28,31);


    }
    
    
 }
 for (int i = 0; i < c; i++)
 {

  if(k[i].motor==0)
  {
    printf("\n ES UN MOTOR BRUSHELESS");
    printf("\n Tipo de motor %d",k[i].motor);
    printf("\n--------\n");
    printf("\nTorque= %d",k[i].t);
    printf("\n--------\n");
    printf("\nCorriente =%d",k[i].co);
    printf("\n--------\n");
    printf("\n Voltaje =%d",k[i].v);
    printf("\n--------\n");
    printf("\n Peso=%dkg",k[i].p);
  }
  if(k[i].motor==1)
  {
    printf("\n ES UN MOTOR BRUSHED");
    printf("\n Tipo de motor %d",k[i].motor);
    printf("\n--------\n");
    printf("\nTorque= %d",k[i].t);
    printf("\n--------\n");
    printf("\nCorriente =%d",k[i].co);
    printf("\n--------\n");
    printf("\n Voltaje =%d",k[i].v);
    printf("\n--------\n");
    printf("\n Peso=%dkg",k[i].p);
 }
  if(k[i].motor==2)
  {
    printf("\n ES UN MOTOR INDUCTION ");
    printf("\n Tipo de motor %d",k[i].motor);
    printf("\n--------\n");
    printf("\nTorque= %d",k[i].t);
    printf("\n--------\n");
    printf("\nCorriente =%d",k[i].co);
    printf("\n--------\n");
    printf("\n Voltaje =%d",k[i].v);
    printf("\n--------\n");
    printf("\n Peso=%dkg",k[i].p);
 }
   if(k[i].motor==3)
   {
    printf("\n ES UN MOTOR DC");
    printf("\n Tipo de motor %d",k[i].motor);
    printf("\n--------\n");
    printf("\nTorque= %d",k[i].t);
    printf("\n--------\n");
    printf("\nCorriente =%d",k[i].co);
    printf("\n--------\n");
    printf("\n Voltaje =%d",k[i].v);
    printf("\n--------\n");
    printf("\n Peso=%dkg",k[i].p);
  }
 
}
   
 
 
 
 
 
 fclose(f);










    return 0;

}