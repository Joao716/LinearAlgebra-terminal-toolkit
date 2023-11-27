#include "types.h"
#include "fractions.h"
#include "matrix.h"
#include "polynomial.h"
#include <stdio.h>
//WORKS!!!
void stringSplit_works(){
    String value=String_new();
    longChar*string="-12.89";
    String_setStr(&value,string,sizeof(string)/sizeof(longChar));
    StringHashMap res=String_split(&value,'.');
    printf("\n%s - %s",res.first.ptr,res.second.ptr);
}
bool isFraction_simplify(){
    Fraction test={-36,48};
    Fraction_simplify(&test);
    return test.num==-3 && test.denom==4;
}
bool isPower(){
    u64 var1=10;
    u64 var2=3;
    u64 result=power(var1,var2);
    return result==1000;
}
bool isNumFigs(){
    u64 var=67;
    u64 result=numOfFigs(var);
    return result==2;
}
bool isFraction_pow(){
    Fraction test={-3,5};
    Fraction_pow(&test,7);
    return test.num==-2187 && test.denom==78125;
}
bool isFraction_add(){
    Fraction test={-4,5};
    Fraction_add(&test,(Fraction){60,9});
    return test.num==88 && test.denom==15;
}
bool isFraction_div(){
    Fraction test={-3,4};
    Fraction_div(&test,(Fraction){-5,3});
    return test.num==9 && test.denom==20;
}
bool isFraction_invert(){
    Fraction test={-1,3};
    Fraction_invert(&test);
    return test.num==-3 && test.denom==1;
}
bool isGetAbs(){
    int a=-1,b=2;
    return getAbs(a)==1 && getAbs(b)==2;
}
String matrix_toString(size_t lines,size_t columns,Fraction**matrix){
    String result=String_new();
    String aux=String_new();
    aux=Fraction_toString(&matrix[0][0]);
    String_setStr(&result," ",1);
    size_t i,j;
    for(i=0;i<lines;i++){
        for(j=0;j<columns;j++){
            aux=Fraction_toString(&matrix[i][j]);
            String_append(&result," | ",3);
            String_append(&result,aux.ptr,aux.length);
        }
        String_append(&result,"\n",1);
    }
    return result;
}
void main(){
    printf((isFraction_simplify())?"\nFraction_simplify works":"\nFraction_simplify does not work");
    printf((isFraction_add())?"\nFraction_add works":"\nFraction_add does not work");
    printf((isFraction_div())?"\nFraction_div works":"\nFraction_div does not work");
    printf((isFraction_invert())?"\nFraction_invert works":"\nFraction_invert does not work");
    printf((isGetAbs())?"\ngetAbs works":"\ngetAbs does not work");printf("\n");
    printf(isFraction_pow()?"\nFraction_pow works":"\nFraction_pow doesnt work");
    printf(isNumFigs()?"\nNumOfFigs works":"\nNumOfFigs doesnt work");
    printf(isPower()?"\nPower works":"\nPower doesnt work");
    stringSplit_works();
}