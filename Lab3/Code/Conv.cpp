#include "Conv.h"

float weight[9],input[9],bias;
float temp=0;
int i=0;

void Conv::run() {
	// vvvvv put your code here vvvvv


    int j,data_out_signal_temp;
    
    
     rom_rd=1;
     rom_addr=i;
     
     
     if(i>=1&&i<10)
       input[i-1]=data_in;
     else if(i>=10&&i<19)
       weight[i-10]=data_in;
     else if(i==19)
       bias = data_in;
     if(i==19)
     {
     rom_rd=0;
        for(j=0;j<9;j++)
     {
       temp = temp + input[j]*weight[j];
     }
       data_out_signal=1;
       data_out.write(temp+bias);
      }
      
     
     i++;
     
	// ^^^^^ put your code here ^^^^^
}


/*
#include "Conv.h"

void Conv::run() {
	// vvvvv put your code here vvvvv
	if(i<=9 && k==0)
  {
   hold1 = data_in.read();
   //cout << hold1 << endl;
   result = result + hold * hold1;
   if(i==9)
     rom_rd=0;
   else
     rom_rd=1;
   rom_addr=i;
   i++;
   k=1;
  }
  else if(j<=17 && k==1)
  {
    hold = data_in.read();
    //cout << hold << endl;
    rom_rd=1;
    rom_addr=j;
    j++;
    k=0;
  }
  else if(j==18 && k==1)
  {
    rom_rd=1;
    rom_addr=18;
    j++;
  }
  else if(j==19 && k==1)
  {
    rom_rd=0;
    rom_addr=j;
    //cout << " ksjfsjfnsjn \n";
    //cout << data_in.read() << endl;
    result = result + data_in.read();
    
    j++;
  }
  else
  {
    data_out_signal=1;
  }
  data_out=result;
  //cout << hold << " " << hold1 << " " << result << endl;
	// ^^^^^ put your code here ^^^^^
}
*/


