//Sobel.h
#include <systemc.h>

// vvvvv put your code here vvvvv
SC_MODULE( Sobel ) {
	sc_in_clk clock;
	sc_in < bool > rst;
	sc_in < sc_int<9> > Pixel;
	sc_out < sc_int<9> > result;
	sc_out < sc_uint<16> > i_addr;
	sc_out < bool > i_rd;
	sc_out < bool > output_valid;
	
	void run();
	SC_CTOR( Sobel )
	{	
		SC_METHOD( run );
		sensitive << rst.pos() << clock.pos();
	}
};
// ^^^^^ put your code here ^^^^^
