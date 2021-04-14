#include "Conv.h"

float weight[9],input[100],bias;
int  i=0;
sc_int <19> temp=0;

void Conv::run() {
	// vvvvv put your code here vvvvv

	if(i<112)
	{
		data_out_signal = 0;
		rom_rd = 1;
		rom_addr = i;
		if (i>=2 && i<102)
		{
			input[i-2] = data_in;
		}
		else if (i<111)
		{
			weight[i-102] = data_in;
		}
		else if (i==111)
		{
			bias = data_in;
		}
		i++;
	}
	else
	{
    for(int k=0;k<9;k++)
    {
		  temp = temp+(input[(i-112)+10*(k/3)+(k%3)] * weight[k]);
    }
		temp = (temp+bias <= 0) ? 0 : temp + bias;
		data_out_signal = 1;
		data_out = temp;
		temp = 0;
    
    i++;
    if ((i-112)%10==7)
		{
			i+=2;
		}
	}
	// ^^^^^ put your code here ^^^^^
}