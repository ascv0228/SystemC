#include "LeNet.h"
// vvvvv put your code here vvvvv

DATA_TYPE all_array[45210];
DATA_TYPE Conv_1_weight[6][26];			//156=6*(1*5*5+1)
DATA_TYPE Conv_2_weight[16][151]; 	//2416=16*(6*5*5+1)
DATA_TYPE Dense_1_weight[120][257];	//30840=120*(256+1)
DATA_TYPE Dense_2_weight[84][121];	//10614=84*(120+1)
DATA_TYPE Dense_3_weight[10][85];		//850=10*(84+1)

DATA_TYPE input[1][784];							//1*28*28
DATA_TYPE Output_Conv_1[6][576]={0};	//6*24*24
DATA_TYPE Output_Conv_2[16][64]={0};	//16*8*8
DATA_TYPE Output_Max_1[6][144]={0};		//6*12*12
DATA_TYPE Output_Max_2[16][16]={0};		//16*4*4
DATA_TYPE Output_Dense_1[120]={0};		
DATA_TYPE Output_Dense_2[84]={0};		
DATA_TYPE Output_Dense_3[10]={0};	
DATA_TYPE flatten[256];
int i=0;
template<size_t _Array_1_,size_t _Array_2_>

void Set_Weight_Array(DATA_TYPE (&output_array)[_Array_1_][_Array_2_],int _First_)
{
	for(int FOR_i=0;FOR_i<_Array_1_;FOR_i++)
	{
		for(int FOR_j=0;FOR_j<_Array_2_;FOR_j++)
		{
			output_array[FOR_i][FOR_j]=all_array[FOR_i*_Array_2_+FOR_j+_First_];
		}
	}
}
DATA_TYPE ReLU(DATA_TYPE temp_test,DATA_TYPE bias)
{
	if(temp_test+bias>=0)
		return temp_test+bias;
	else
		return 0;
}
#define Output_Conv_DEF(output_name, _output_1_, _output_23_,input_name, _input_1_, _input_23_, weight_name) \
{ \
	for(int FOR_i=0;FOR_i<_output_1_;FOR_i++)  \
	{ \
		for(int FOR_j=0;FOR_j< _output_23_;FOR_j++) \
		{ \
			for(int FOR_k=0;FOR_k< _output_23_;FOR_k++) \
			{ \
				DATA_TYPE Xtemp = 0; \
				for(int FOR_l=0;FOR_l<_input_1_;FOR_l++)   \
				{ \
					for(int FOR_m=0;FOR_m<25;FOR_m++) \
					{ \
						Xtemp=Xtemp+input_name[FOR_l][(FOR_j+FOR_m/5)*_input_23_+(FOR_k+FOR_m%5)]*weight_name[FOR_i][FOR_l*25+FOR_m]/1024; \
					} \
				} \
				output_name[FOR_i][FOR_j* _output_23_+FOR_k]=ReLU(Xtemp,weight_name[FOR_i][_input_1_*25]); \
			} \
		} \
	} \
}
#define MAXpooling_DEF(output_name, _output_1_, _output_23_, input_name) \
{ \
	for(int FOR_i=0;FOR_i<_output_1_;FOR_i++) \
	{ \
		for(int FOR_j=0;FOR_j<_output_23_;FOR_j++) \
		{ \
			for(int FOR_k=0;FOR_k<_output_23_;FOR_k++) \
			{ \
				DATA_TYPE temp1 = input_name[FOR_i][FOR_j*2*(2*_output_23_)+FOR_k*2]; \
				DATA_TYPE temp2 = input_name[FOR_i][FOR_j*2*(2*_output_23_)+FOR_k*2+1]; \
				DATA_TYPE temp3 = input_name[FOR_i][(FOR_j*2+1)*(2*_output_23_)+FOR_k*2]; \
				DATA_TYPE temp4 = input_name[FOR_i][(FOR_j*2+1)*(2*_output_23_)+FOR_k*2+1]; \
				if(temp1>=temp2&&temp1>=temp3&&temp1>=temp4) \
					output_name[FOR_i][FOR_j*_output_23_+FOR_k] = temp1; \
				else if(temp2>=temp1&&temp2>=temp3&&temp2>=temp4) \
					output_name[FOR_i][FOR_j*_output_23_+FOR_k] = temp2; \
				else if(temp3>=temp1&&temp3>=temp2&&temp3>=temp4) \
					output_name[FOR_i][FOR_j*_output_23_+FOR_k] = temp3; \
				else if(temp4>=temp1&&temp4>=temp2&&temp4>=temp3) \
					output_name[FOR_i][FOR_j*_output_23_+FOR_k] = temp4; \
			} \
		} \
	} \
}
#define Output_Dense_DEF(isReLU, output_name, _output_len_,  input_name, _input_len_, weight_name) \
{ \
	for(int FOR_i=0; FOR_i < _output_len_; FOR_i++){ \
		DATA_TYPE Xtemp = 0; \
		for(int FOR_j=0; FOR_j < _input_len_;FOR_j++){ \
			Xtemp=Xtemp+ input_name [FOR_j]* weight_name [FOR_i][FOR_j]/1024; \
		} \
    if (isReLU)output_name [FOR_i]= ReLU ( Xtemp , weight_name [FOR_i][_input_len_]); \
    if (!isReLU)output_name [FOR_i]= Xtemp + weight_name [FOR_i][_input_len_]; \
	} \
}

void LeNet::run() {
	ram_wr.write(1);
	if(i<=45213)  //set input array
	{
		if(i>=2){
			rom_rd.write(1);
			rom_addr.write(i-2);
      if(i>=4)
				all_array[i-4]=rom_data_out.read();
		}
		i++;
		output_valid.write(0);
    }
	else if(i==45214)  //set weight
	{
		Set_Weight_Array(Conv_1_weight, 0);
		Set_Weight_Array(Conv_2_weight, 156);
		Set_Weight_Array(Dense_1_weight, 2572);
		Set_Weight_Array(Dense_2_weight, 33412);
		Set_Weight_Array(Dense_3_weight, 43576);
		Set_Weight_Array(input, 44426);
		i++;
	}
	else if(i==45215)  //set Output array
	{
		Output_Conv_DEF(Output_Conv_1, 6, 24, input, 1, 28, Conv_1_weight)
		MAXpooling_DEF(Output_Max_1, 6, 12, Output_Conv_1);
		Output_Conv_DEF(Output_Conv_2, 16, 8, Output_Max_1, 6, 12, Conv_2_weight)
		MAXpooling_DEF(Output_Max_2, 16, 4, Output_Conv_2);
		for(int FOR_i=0;FOR_i<16;FOR_i++)
		{
			for(int FOR_j=0;FOR_j<16;FOR_j++)
			{
				flatten[FOR_i*16+FOR_j]=Output_Max_2[FOR_j][FOR_i];
			}
		}
		Output_Dense_DEF(1, Output_Dense_1, 120, flatten, 256, Dense_1_weight);
		Output_Dense_DEF(1, Output_Dense_2, 84, Output_Dense_1, 120, Dense_2_weight);
		Output_Dense_DEF(0, Output_Dense_3, 10, Output_Dense_2, 84, Dense_3_weight);
		i++;
	}
	else if(i>45215) //output
	{
		output_valid.write(true);
		result.write(Output_Dense_3[i-45216]);
		i++;
	}
}

/*
0: -6.13672!
1: 1.44434!
2: -4.41699!
3: 1.85547!
4: -9.71387!
5: -0.980469!
6: -10.2959!
7: 14.8623!
8: -4.5459!
9: -1.62402!
*/