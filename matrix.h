#ifndef _MATRIX_H
#define _MATRIX_H
#include "fractions.h"
#include "mathutils.h"
#include "strings.h"
#include <stdio.h>
typedef struct Pair{
    size_t num1;
    size_t num2;
}Pair;
typedef struct DoublePair{
    Pair n1;
    Pair n2;
}DoublePair;

void Matrix_receiveWithFactor(size_t lines,size_t columns,Fraction matrix[][columns],size_t lineReceive,size_t lineSend,Fraction factor);
Fraction Matrix_rowReduct(size_t lines,size_t columns,Fraction matrix[][columns]);
void getNextPairs(size_t lines,DoublePair*pairs);
void Matrix_mulBy(size_t lines,size_t columns,Fraction matrix[][columns],size_t line,Fraction factor);
u8 Matrix_unZero(size_t lines,size_t columns,Fraction matrix[][columns],size_t nth);
bool isZero(const Fraction*fraction);
bool isZero(const Fraction*fraction){
    return fraction->num==0;
}
String Matrix_toString(size_t lines,size_t columns,Fraction matrix[][columns]){
    String result;
    String part=Fraction_toString(&matrix[0][0]);
    String_setStr(&result," ",1);
    size_t i,j;
    for(i=0;i<lines;i++){
        for(j=0;j<columns;j++){
            part=Fraction_toString(&matrix[i][j]);
            String_append(&result,part.ptr,part.length);
            String_append(&result," | ",3);
        }
        String_append(&result,"\n",1);
    }
    return result;
}
u8 Matrix_unZero(size_t lines,size_t columns,Fraction matrix[][columns],size_t nth){
    size_t i;
    Fraction pivot;
    for(i=nth;i<lines;i++){
        pivot=matrix[i][nth];
        if(!isZero(&pivot)){
            break;
        }
    }
    if(i>=lines){
        return 1;
    }else{
        Matrix_receiveWithFactor(lines,columns,matrix,nth,i,(Fraction){1,1});
        return 0;
    }
}
void Matrix_clearColumn(size_t lines,size_t columns,Fraction matrix[][columns],size_t column,size_t position){
    i64 i;Fraction pivot=Fraction_new();
    for(i=position;i<lines;i++){
        if(i==column){
        }else{
            pivot=matrix[position][column];
            Fraction_invert(&pivot);
            Fraction_mul(&pivot,matrix[i][column]);
            Fraction_swapSignal(&pivot);
            Matrix_receiveWithFactor(lines,columns,matrix,i,position,pivot);
        }
    }
    for(i=position;i>=0;i--){
        if(i==column){
        }else{
            pivot=matrix[position][column];
            Fraction_invert(&pivot);
            Fraction_mul(&pivot,matrix[i][column]);
            Fraction_swapSignal(&pivot);
            Matrix_receiveWithFactor(lines,columns,matrix,i,position,pivot);
        }
    }
}
Fraction Matrix_rowReduct(size_t lines,size_t columns,Fraction matrix[][columns]){
    i64 i;Fraction determinant={1,1};u8 status;Fraction aux;
    i64 limit=getSmallest(lines,columns);
    for(i=0;i<limit;i++){
        if(isZero(&matrix[i][i]) && i<limit){
            status=Matrix_unZero(lines,columns,matrix,i);
            i=(status==0)?i-1:i;
        }else{
            Matrix_clearColumn(lines,columns,matrix,i,i);
        }
    }
    for(i=0;i<limit;i++){
        Fraction_mul(&determinant,matrix[i][i]);
        aux=matrix[i][i];Fraction_invert(&aux);
        Matrix_mulBy(lines,columns,matrix,i,aux);
    }
    return determinant;
}
void Matrix_mulBy(size_t lines,size_t columns,Fraction matrix[][columns],size_t line,Fraction factor){
    size_t i;
    for(i=0;i<columns;i++){
        Fraction_mul(&matrix[line][i],factor);
    }
}
bool Pair_equals(Pair*obj,Pair p){return obj->num1==p.num1 && obj->num2==p.num2;}
void getNextPairs(size_t lines,DoublePair*pairs){
    bool exceeds;
    pairs->n2.num1++;
    exceeds=(pairs->n2.num1>=lines); 
    pairs->n1.num1=exceeds?pairs->n1.num1+1:pairs->n1.num1;
    pairs->n1.num2=pairs->n1.num1;
    pairs->n2.num2=pairs->n1.num1;
    pairs->n2.num1=(exceeds)?0:pairs->n2.num1;
    pairs->n2.num1=Pair_equals(&pairs->n1,pairs->n2)?pairs->n2.num1+1:pairs->n2.num1;
}
void Matrix_receiveWithFactor(size_t lines,size_t columns,Fraction matrix[][columns],size_t lineReceive,size_t lineSend,Fraction factor){
    size_t i;
    Fraction prdt;
    for(i=0;i<columns;i++){
        prdt=matrix[lineSend][i];
        Fraction_mul(&prdt,factor);
        Fraction_add(&matrix[lineReceive][i],prdt);
    }
}
#endif
