#ifndef _VECTOR_H
#define _VECTOR_H
#include "types.h"
#include <stdlib.h>
#include <stdbool.h>
typedef struct Vector{
    bool initialized;
    size_t size;
    void*ptr;
    size_t length;
}Vector;
Vector Vector_new(size_t size);
Vector Vector_new(size_t size){
    Vector result;
    result.size=size;
    result.initialized=false;
    result.ptr=malloc(size*1);
    result.length=1;
    return result;
}
void*Vector_get(Vector*obj,size_t position){
    return (void*)((char*)obj->ptr+position*obj->size);
}
void Vector_push(Vector*obj,void*value){
    if(obj->initialized){
        obj->ptr=realloc(obj->ptr,obj->size*(obj->length+1));
        memcpy((char*)obj->ptr+obj->length*obj->size,value,obj->size);
        obj->length++;
    }else{
        memcpy(obj->ptr,value,obj->size);
        obj->initialized=true;
    }
}
#endif