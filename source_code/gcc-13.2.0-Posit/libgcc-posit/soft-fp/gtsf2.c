#include "cmpsf2.h"
#include "SoftPosit-master/internals.h"
#include "SoftPosit-master/platform.h"
//#include <stdio.h>

CMPtype
__gtsf2 (SFtype a, SFtype b)
{
  CMPtype r;
  r = __cmpsf2(a,b);
  //printf("gtsf2\n");
  return r;
}