#ifndef  _MACRO_H_
#define  _MACRO_H_

#define SWAP_INT8(a,b)   {  int8  t = a; a = b; b = t; }
#define SWAP_INT16(a,b)  {  int16 t = a; a = b; b = t; }
#define SWAP_INT32(a,b)  {  int32 t = a; a = b; b = t; }
#define SWAP_UINT8(a,b)  { uint8  t = a; a = b; b = t; }
#define SWAP_UINT16(a,b) { uint16 t = a; a = b; b = t; }
#define SWAP_UINT32(a,b) { uint32 t = a; a = b; b = t; }
#define SWAP_VEC2I(a,b)  { Vec2i  t = a; a = b; b = t; }
#endif // _MACRO_H_