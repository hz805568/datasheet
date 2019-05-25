/*NewWay 循迹模块专用程序*/
/*简单循迹程序，此程序能让小车沿着黑线移动*/
/*你可以任意使用、修改该程序，如果你要把该程序用于商业，请与我联系，不然一切后果自己承担*/
/*作者：刘伟*/
/*联系方式：13770950403*
/*联系邮箱：liuwei_victory@yahoo.cn*/
/*当你看到这个程序的时候，请注意，这个程序是不能直接使用的，你要自己实现小车的向前，向后，向左，向右,及其延时的子程序*/
#include <REGX52.H>
void CarGo();
void CarBack();
void CarTurnLeft();
void CarTurnRight();
void Delayms();
void CarStop();

/*定义循迹传感器管脚*/
sbit CLP=P1^0;
sbit SS1=P1^1;
sbit SS2=P1^2;
sbit SS3=P1^3;
sbit SS4=P1^4;
sbit SS5=P1^5;
sbit Near=P1^6;

void main(void)
{  
	  CarGo();
	  while(1)
	  {  
	    if(SS2==0) 
		{ 
		 	CarTurnLeft();
		}
		else
		{
	    if(SS4==0) 
		{  
		  CarTurnRight();
		}
		else 
		{  
		 CarGo();
		}
		}
	  }
}