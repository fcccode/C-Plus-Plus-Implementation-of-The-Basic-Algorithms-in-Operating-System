#include<time.h>
#include <stdio.h> 
#include<memory.h>
#include<iostream>

#if !defined(BB)
#define BB
bool static pi[101];
 #endif  
 


class node
{
public:
	int  pid;//���̱��
	int  status;//�Ƿ��������б�־
	int  priority;//���ȼ�
	int  life;//��������
	node *next;//ָ��ָ����һ���ڵ�
	
	//bool static pi[101];


	node()//��ʼ��
	{
		srand( (unsigned)time(NULL));//srand()��������һ���Ե�ǰʱ�俪ʼ���������.Ӧ�÷���for��ѭ�����ǰ�� ��ȻҪ�ܳ�ʱ��ȴ�
		while(1)
		{
			int p=rand()%101;//����������̱��
			if(p!=0)
			if(!pi[p])
			{
				pid=p;
				pi[p]=true;
				break;
			}
		}
		status=0;//��־λ��������
		priority=rand()%50;//����������ȼ�
		life=0;
		while(life==0)//���������������
		{
			life=rand()%6;
		}
		next=0;
	}
};


/*void setPid()
{
	memset(node.pi,0,101);
}
*/


