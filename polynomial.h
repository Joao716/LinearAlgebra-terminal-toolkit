#ifndef _POLYNOMIAL_H
#define _POLYNOMIAL_H
#include "matrix.h"
#include "fractions.h"
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
typedef struct Point{
    Fraction x;
    Fraction y;
}Point;
Point Point_new();
typedef struct PointPoly{
    size_t lines;
    size_t columns;
    Fraction**matrix;
    Vector points;
}PointPoly;
PointPoly PointPoly_new(){
    PointPoly result;
    result.points=Vector_new(sizeof(Point));
    return result;
}
void PointPoly_matrixAlloc(PointPoly*obj){
    obj->matrix=malloc(sizeof(Fraction*)*(obj->points.length));
    obj->lines=obj->points.length;
    size_t i;
    obj->columns=obj->lines+1;
    for(i=0;i<obj->points.length;i++){
        obj->matrix[i]=malloc(sizeof(Fraction)*(obj->points.length+1));
    }
}
void PointPoly_matrixAllocExtra(PointPoly*obj,u8 extra){
    obj->matrix=malloc(sizeof(Fraction*)*(obj->points.length));
    obj->lines=obj->points.length;
    obj->columns=obj->lines+1+extra;
    size_t i;
    for(i=0;i<obj->points.length;i++){
        obj->matrix[i]=malloc(sizeof(Fraction)*(obj->columns));
    }
}
void PointPoly_fillMatrix(PointPoly*obj){
    size_t i,j;
    Point aux;
    for(i=0;i<obj->lines;i++){
        aux=*(Point*)Vector_get(&obj->points,i);
        obj->matrix[i][obj->columns-1]=aux.y;
    }
    size_t cont=obj->columns-2;
    for(i=0;i<obj->lines;i++){
        cont=obj->columns-2;
        for(j=0;j<obj->columns-1;j++){
            aux=*(Point*)Vector_get(&obj->points,i);
            Fraction_pow(&aux.x,cont);
            obj->matrix[i][j]=aux.x;
            cont--;
        }
    }
}
Point Point_new(){
    Point result={{0,1},{0,1}};
    return result;
}
void Point_setX(Point*obj,Fraction val){
    obj->x=val;
}
void Point_setY(Point*obj,Fraction val){
    obj->y=val;
}
#endif