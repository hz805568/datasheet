 /*NewWay ѭ��ģ��ר�ó���*/
/*��ѭ�����򣬴˳�������С��Ѱ��T��·��ͣ��*/
/*���������ʹ�á��޸ĸó��������Ҫ�Ѹó���������ҵ����������ϵ����Ȼһ�к���Լ��е�*/
/*���ߣ���ΰ*/
/*��ϵ��ʽ��13770950403*/
/*��ϵ���䣺liuwei_victory@yahoo.cn*/
/*���㿴����������ʱ����ע�⣬��������ǲ���ֱ��ʹ�õģ���Ҫ�Լ�ʵ��С������ǰ�������������,������ʱ���ӳ���*/
#include <REGX52.H>
void CarGo();
void CarBack();
void CarTurnLeft();
void CarTurnRight();
void Delayms(unsigned char n);
void CarStop();

/*����ѭ���������ܽ�*/
sbit CLP=P1^0;
sbit SS1=P1^1;
sbit SS2=P1^2;
sbit SS3=P1^3;
sbit SS4=P1^4;
sbit SS5=P1^5;
sbit Near=P1^6;


void CarGoLine()	 //С���غ�����
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
void main()
{  	 
unsigned char flag;
flag=0; 
     while(flag==0)
	 {
	  CarGoLine();
	  if((SS1==0)&&(SS5==0))
	  {  
		 CarGo();
		 Delayms(200);// �жϲ��� ��ʮ�� ���νӿ�  ������ʱʱ�俴С�����ٶȺ�����
		 if(SS3==1) flag=1;
	  }
	 }

   CarStop();

}