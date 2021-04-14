#include "Neuron_arg.h"

void Neuron::neuron() {
 
	// vvvvv put your code here vvvvv
  float x, temp1, temp2;
  
	x = input1 * w1 + input2 * w2 + b;
	temp1 = 0.5 + 0.25*x - 1./48.*x*x*x + 1./480.*x*x*x*x*x;
 
  if (temp1<=0){
    temp2 = 0;
  }
  else if (temp1>=1){
    temp2 = 1;
  }
  else {
    temp2 = temp1;
  }
  output.write(temp2);  
  // ^^^^^ put your code here ^^^^^
}