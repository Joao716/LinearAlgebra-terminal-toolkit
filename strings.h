#ifndef _STRINGS_H
#define _STRINGS_H
#include <string.h>
#include <stdlib.h>
#include "types.h"
typedef struct String{
    longChar*ptr;
    size_t length;
}String;
typedef struct StringHashMap{
    String first;
    String second;
}StringHashMap;
String String_new(){
    String result;
    result.ptr=malloc(sizeof(longChar)*1);
    longChar aux[]={'0','\0'};
    strcpy(result.ptr,aux);
    result.length=1;
    return result;
}
void String_setStr(String*obj,const longChar*value,size_t length){
    obj->ptr=malloc(sizeof(longChar)*(length+1));
    strcpy(obj->ptr,value);
    obj->length=length;
    obj->ptr[obj->length]='\0';
}
void String_append(String*obj,const longChar*added,size_t length){
    obj->ptr=realloc(obj->ptr,sizeof(longChar)*(obj->length+length+1));
    strcat(obj->ptr,added);
    obj->length+=length;
    obj->ptr[obj->length]='\0';
}
void String_insertInIndex(String*obj,const longChar*block,size_t length,size_t index){
    size_t i;
    String left=String_new(),rigth=String_new();
    String_setStr(&left,&obj->ptr[0],1);String_setStr(&rigth,&obj->ptr[index+1],1);
    for(i=1;i<index+1;i++){
        String_append(&left,&obj->ptr[i],1);
    }
    for(i=index+1;i<obj->length;i++){
        String_append(&rigth,&obj->ptr[i],1);
    }
    String new=String_new();
    String_setStr(&new,left.ptr,left.length);
    String_append(&new,block,length);
    String_append(&new,rigth.ptr,rigth.length);
    *obj=new;
}
/// @brief 
/// @param obj -> origin 
/// @param lowerBound -> index where it starts 
/// @param upperBound -> index where it ends
/// @return string contained in bounds
String String_extractInBounds(String*obj,size_t lowerBound,size_t upperBound){
    String result=String_new();
    String_setStr(&result,&obj->ptr[lowerBound],1);
    size_t i;
    for(i=lowerBound+1;i<=upperBound;i++){
        String_append(&result,&obj->ptr[i],1);
    }
    return result;
}
/// @brief 
/// @param obj -> origin
/// @param lowerBound ->index where it starts 
/// @param upperBound ->index where it ends
void String_purgeInBounds(String*obj,size_t lowerBound,size_t upperBound){
    String left=String_new(),rigth=String_new();
    String_setStr(&left,&obj->ptr[0],1);String_setStr(&rigth,&obj->ptr[upperBound+1],1);
    size_t i;
    for(i=1;i<lowerBound;i++){
        String_append(&left,&obj->ptr[i],1);
    }
    for(i=upperBound+2;i<obj->length;i++){
        String_append(&rigth,&obj->ptr[i],1);
    }
    String_append(&left,rigth.ptr,rigth.length);
    *obj=left;
}
StringHashMap String_split(String*str,longChar split){
    StringHashMap result;
    String_setStr(&result.first,&str->ptr[0],1);
    size_t i;
    for(i=1;i<str->length && str->ptr[i]!=split;i++){
        String_append(&result.first,&str->ptr[i],1);
    }
    i++;
    String_setStr(&result.second,&str->ptr[i],1);
    for(i=i+1;i<str->length;i++){
        String_append(&result.second,&str->ptr[i],1);
    }
    return result;
}
void String_deleteChar(String*str,longChar c){
    String result=String_new();
    size_t i;
    bool first=true;
    for(i=0;i<str->length;i++){
        if(str->ptr[i]!=c){
            if(first){
                String_setStr(&result,&str->ptr[i],1);
                first=false;
            }else{
                String_append(&result,&str->ptr[i],1);
            }
        }
    }
    *str=result;
}
u8 String_containsChar(String*str,longChar c){
    u8 frequency=0;
    size_t i;
    for(i=0;i<str->length;i++){
        frequency=(str->ptr[i]==c)?frequency+1:frequency;
    }
    return frequency;
}
#endif