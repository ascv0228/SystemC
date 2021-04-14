#include "ALU.h"
/*
sc_logic AND_(bool *c_out,bool a,bool b)
{
  c_out=a & b;
}*/
void ALU::run()
{
	// vvvvv put your code here vvvvv
  uint8_t Temp;
  switch(Temp=OpCode.read().to_uint())
  {
    case 0://AND
      Result.write(A.read() & B.read());
      Zero=0, Overflow=0;
      break;
    case 1://OR
      Result.write(A.read() | B.read());
      Zero=0, Overflow=0;
      break;
    case 2://ADD
      Result.write(A.read() + B.read());
      if ((A.read() + B.read())>32767||(A.read() + B.read())<-32768)
        Overflow=1;
      else 
        Overflow=0;
      Zero=((A.read() + B.read())==0) ? 1 : 0;
      break;
    case 3://SUB
      Result.write(A.read() + ~(B.read())+1);
      if ((A.read() + ~(B.read())+1)>32767|| (A.read() + ~(B.read())+1) < (-32768))
        Overflow=1;
      else 
        Overflow=0;
      Zero=((A.read() + (65536-B.read())+1)==0) ? 1 : 0;
      break;
    case 4://set-on-less-than
      Result.write(A.read() < B.read());
      Zero=!(A.read() < B.read()), Overflow=0;
      break;
    case 5://NOR
      Result.write(~A.read() & ~B.read());
      Zero=0, Overflow=0;
      break;
  }
	// ^^^^^ put your code here ^^^^^
}