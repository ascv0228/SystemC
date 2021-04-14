#include "systemc.h"
#include "Neuron_arg.h"

SC_MODULE( Neural_Network ) {
    sc_in < float > input1, input2;
    sc_out < float > output;
    Neuron *neuron_1, *neuron_2, *neuron_3;  
    sc_signal < float > n1,n2;  
    
    void SetValue_neuron(){
      (*neuron_1).SetValue(10,-10,-5);  //b1
      (*neuron_2).SetValue(-10,10,-5);  //b2
      (*neuron_3).SetValue(10,10,-5);   //b3
    }
    
    SC_CTOR( Neural_Network ) {
		
    // vvvvv put your code here vvvvv
    neuron_1 = new Neuron("neuron_1");
    neuron_2 = new Neuron("neuron_2");
    neuron_3 = new Neuron("neuron_3");
    
    (*neuron_1)(input1, input2, n1);
    (*neuron_2)(input1, input2, n2);
    (*neuron_3)(n1, n2, output);
    
    SC_METHOD( SetValue_neuron );
    sensitive << input1 << input2 ; 
   
		// ^^^^^ put your code here ^^^^^
    }
};