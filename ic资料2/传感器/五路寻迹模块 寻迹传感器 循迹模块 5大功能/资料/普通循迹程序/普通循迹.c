/*NewWay ѭ��ģ��ר�ó���*/
/*��ѭ�����򣬴˳�������С�����ź����ƶ�*/
/*���������ʹ�á��޸ĸó��������Ҫ�Ѹó���������ҵ����������ϵ����Ȼһ�к���Լ��е�*/
/*���ߣ���ΰ*/
/*��ϵ��ʽ��13770950403*
/*��ϵ���䣺liuwei_victory@yahoo.cn*/
/*���㿴����������ʱ����ע�⣬��������ǲ���ֱ��ʹ�õģ���Ҫ�Լ�ʵ��С������ǰ�������������,������ʱ���ӳ���*/
#include <REGX52.H>
void CarGo();
void CarBack();
void CarTurnLeft();
void CarTurnRight();
void Delayms();
void CarStop();

/*����ѭ���������ܽ�*/
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