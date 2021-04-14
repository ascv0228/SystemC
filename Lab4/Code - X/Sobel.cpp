//Sobel.cpp
#include "Sobel.h"
// vvvvv put your code here vvvvv
sc_int<9> image_enlarge[258][258]={0};
int Y_weight[3][3]={{-1,0,1},{-2,0,2},{-1,0,1}};
int X_weight[3][3]={{1,2,1},{0,0,0},{-1,-2,-1}};
int image_temp;
int i=-3,j=0;
void Sobel::run() 
{
	// vvvvv put your code here vvvvv
	if(i<=65536)
	{
		i_rd=1;
		i_addr=i;
		if(i>0&&i<=65536)
		{
			image_enlarge[(i-1)/256+1][(i-1)%256+1]=Pixel;
		}
		i++;
	}
	else
	{
		for(int k=0;k<9;k++)
		{
			image_temp = image_temp+(image_enlarge[j/258+(k/3)][j%258+(k%3)] * (X_weight)[k/3][k%3]);
			//image_temp = image_temp+(image_enlarge[j/258+(k/3)][j%258+(k%3)] * (Y_weight)[k/3][k%3]);
			//image_temp = image_enlarge[j/258+1][j%258+1];
		}
		image_temp = (image_temp < 128) ? 0 : 255;
		output_valid = 1;
		result = image_temp;
		image_temp = 0;
		j++;
		if (j%258==256)
		{
			j+=2;
		}
	}
}
// ^^^^^ put your code here ^^^^^