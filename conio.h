#ifndef _CONIO_H
#define _CONIO_H
#include <termios.h>
static struct termios old, current;

void initTermios(int echo)   
{
  tcgetattr(0,&old); 
  current=old; 
  current.c_lflag&=~ICANON;
  if(echo){
    current.c_lflag|=ECHO;
  }else{
    current.c_lflag&=~ECHO;
  }
  tcsetattr(0,TCSANOW,&current);
}


void resetTermios(void) 
{
  tcsetattr(0,TCSANOW,&old);
}
char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch=getchar();
  resetTermios();
  return ch;
}
char getch(void) 
{
  return getch_(0);
}
#endif