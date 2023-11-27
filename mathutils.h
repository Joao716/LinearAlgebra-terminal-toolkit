#ifndef _MATHUTILS_H
#define _MATHUTILS_H
#include "types.h"
u64 getBiggest(u64 num1,u64 num2){
    return (num1>num2)?num1:num2;
}
u64 getSmallest(u64 num1,u64 num2){
    return (num1<num2)?num1:num2;
}
u64 power(u64 num,u8 power){
    if(power==0){return 1;}
    u64 copy=num;
    u64 i;
    for(i=1;i<power;i++){
        copy*=num;
    }
    return copy;
}
u8 numOfFigs(u64 num){
    u64 copy=num;
    u8 result=0;
    if(num==0){return 1;}
    while(copy>0){
        copy/=10;
        result++;
    }
    return result;
}
#endif