#ifndef _FRACTIONS_H
#define _FRACTIONS_H
#include <stdlib.h>
#include <stdio.h>
#include "mathutils.h"
#include "strings.h"
typedef struct Fraction{
    i64 num;
    u64 denom;
}Fraction;
Fraction Fraction_new();
size_t getAbs(i64 num);
void Fraction_simplify(Fraction*obj);
void Fraction_add(Fraction*obj,Fraction add);
void Fraction_swapSignal(Fraction*obj);
void Fraction_invert(Fraction*obj);
void Fraction_sub(Fraction*obj,Fraction sub);
void Fraction_mul(Fraction*obj,Fraction mul);
void Fraction_div(Fraction*obj,Fraction div);
void Fraction_pow(Fraction*obj,u8 pow);
Fraction Fraction_toLiteral(const longChar*text,size_t length);
String Fraction_toString(Fraction*obj);
Fraction Fraction_new(){
    Fraction result;
    result.num=0,result.denom=1;
}
size_t getAbs(i64 num){
    return (num<0)?-num:num;
}
void Fraction_simplify(Fraction*obj){
    bool isNeg=(obj->num<0);
    obj->num=getAbs(obj->num),obj->denom=getAbs(obj->denom);
    size_t small=(obj->num<obj->denom)?obj->num:obj->denom;
    size_t i=small;
    place:
    i=small;
    for(i=i;i>1;i--){
        if(obj->num%i==0 && obj->denom%i==0){
            obj->num/=i,obj->denom/=i;
            small=(obj->num<obj->denom)?obj->num:obj->denom;
            goto place;
        }
    }
    obj->num=(isNeg)?(obj->num)*(-1):getAbs(obj->num);
    obj->denom=(obj->num==0)?1:obj->denom;
}
void Fraction_swapSignal(Fraction*obj){
    obj->num=-obj->num;
}
void Fraction_sub(Fraction*obj,Fraction sub){
    Fraction aux=sub;
    Fraction_swapSignal(&aux);
    Fraction_add(obj,aux);
}
void Fraction_add(Fraction*obj,Fraction add){
    Fraction aux=*obj;
    obj->denom*=add.denom;
    obj->num=obj->num*add.denom+add.num*aux.denom;
    obj->denom=(obj->num==0)?1:obj->denom;
    Fraction_simplify(obj);
}
void Fraction_invert(Fraction*obj){
    bool isNeg=(obj->num<0);
    Fraction aux=Fraction_new();
    aux.num=getAbs(obj->denom),aux.denom=getAbs(obj->num);
    aux.num=(isNeg)?-aux.num:aux.num;
    *obj=aux;
}
void Fraction_div(Fraction*obj,Fraction div){
    Fraction aux=div;
    Fraction_invert(&aux);
    Fraction_mul(obj,aux);
}
void Fraction_mul(Fraction*obj,Fraction mul){
    obj->num*=mul.num;
    obj->denom*=mul.denom;
    obj->denom=(obj->num==0)?1:obj->denom;
    Fraction_simplify(obj);
}
void Fraction_pow(Fraction*obj,u8 power){
    if(power==0){
        *obj=(Fraction){1,1};
        return;
    }
    Fraction copy=*obj;
    size_t i;
    for(i=1;i<power;i++){
        Fraction_mul(&copy,*obj);
    }
    *obj=copy;
}
//DEBUGGED
Fraction Fraction_toLiteral(const longChar*text,size_t length){
    Fraction result=Fraction_new();
    String aux=String_new();
    String_setStr(&aux,text,length);
    String_deleteChar(&aux,' ');
    longChar sep=0;
    sep=(String_containsChar(&aux,'.')==1)*('.')+(String_containsChar(&aux,'/')==1)*('/');
    i64 aux_int=0,aux_int2=0;
    StringHashMap auxSplit;
    if(sep!=0){
        auxSplit=String_split(&aux,sep);
        sscanf(auxSplit.first.ptr,i64_str,&aux_int);
        sscanf(auxSplit.second.ptr,i64_str,&aux_int2);
    }else{
        sscanf(aux.ptr,i64_str,&aux_int);
    }
    if(sep=='/'){
        result.num=(aux_int*aux_int2>=0)?getAbs((i64)aux_int):-getAbs((i64)aux_int);
        result.denom=getAbs((i64)aux_int2);
    }else if(sep=='.'){
        bool isNeg=false;
        Fraction temp;
        result.num=aux_int,result.denom=1;
        temp.num=aux_int2;temp.denom=power(10,numOfFigs(temp.num));
        if(result.num<0){Fraction_swapSignal(&result);isNeg=true;}
        Fraction_add(&result,temp);
        if(isNeg){Fraction_swapSignal(&result);}
    }else{
        result.num=aux_int;
        result.denom=1;
    }
    Fraction_simplify(&result);
    return result;
}
String Fraction_toString(Fraction*obj){
    String result=String_new();
    longChar numerator[50],denominator[50];
    sprintf(numerator,i64_str,obj->num);
    sprintf(denominator,u64_str,obj->denom);
    String_setStr(&result,numerator,strlen(numerator));
    String_append(&result,"/",1);
    String_append(&result,denominator,strlen(denominator));
    return result;
}
#endif
