#ifndef NEURON_H
#define NEURON_H

#include "systemc.h"

SC_MODULE( Neuron ) {
  public:
    sc_in < float > input1, input2;
	  sc_out < float > output;
	
    SC_HAS_PROCESS( Neuron );

	// vvvvv put your code here vvvvv
  void SetValue(int W1, int W2, int B)
  {
    w1 = W1;
    w2 = W2;
    b = B;
  }
    Neuron( sc_module_name name ) :
            sc_module( name )
    {
		SC_METHOD( neuron );
		sensitive << input1 << input2;
    } 
	// ^^^^^ put your code here ^^^^^
  
  private :
    void neuron();
	float w1;
	float w2;
	float b;
};
#endif

