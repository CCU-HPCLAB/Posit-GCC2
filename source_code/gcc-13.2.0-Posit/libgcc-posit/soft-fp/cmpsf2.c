#include"cmpsf2.h"

CMPtype __cmpsf2(SFtype a,SFtype b){

    CMPtype r;
    posit32_t p32a=*((posit32_t*)&a);
    posit32_t p32b=*((posit32_t*)&b);
    
    if(p32_eq(p32a,p32b)){
        r=0;
    }
    else if(p32_lt(p32a,p32b)){
        r=-1;
    }
    else{
        r=1;
    }

    return r;
}