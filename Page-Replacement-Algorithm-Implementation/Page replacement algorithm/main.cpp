#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h> 
//#include <memory.h>
#include <iomanip>
using namespace std;


int aa[320];
int bb[320];
int cc[320]={7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
int dd[32][2];
double opt,fifo,lru;
double  interrupt1,interrupt2,interrupt3;
void setInstruction()
{
	int n;
	srand(time(NULL));
	//����320��ָ��
	for(int i=0;i<320;i++)
	{
		n=320;
		aa[i]=rand()%n+1;//�������ָ��
		if(aa[i]==319)//˳��ִ��һ��ָ��
			aa[i+1]=aa[i];
		else
			aa[i+1]=aa[i]+1;
		//��ǰ������ָ��
		n=aa[i+1];
		i=i+2;
		aa[i]=rand()%n+1;
		if(aa[i]==319)//˳��ִ��һ��ָ��
			aa[i+1]=aa[i];
		else
			aa[i+1]=aa[i]+1;
		i=i+2;
		//����������һ��ָ��
		while(1)
		{
			aa[i]=rand()%320+1;
			if(aa[i]>aa[i-2]+2)
				break;
		}

	}
	return ;
}
void setPage(int n)//ͨ������ֵȷ��������ҳ��ֵ
{
	for(int i=0;i<320;i++)
		bb[i]=aa[i]/(n*10)+1;
	return ;
}
int reduced()
{
	int i,n=1,c;
	//�ϲ�������ֵͬ
	cc[0]=c=bb[0];
	for(i=0;i<320;i++)
	{
		if(c!=bb[i])
		{
			cc[n]=c=bb[i];
			n++;
		}
	}
	return n;
}
void OPT(int num,int Bnum)
{
	opt=0;
	int i=0,j,k=0,l,max,m;
	bool flag;
	memset(dd,0,sizeof(dd));
	while(i<Bnum)//ͨ��Bnum���ܵ��ڴ������
	{
		flag=false;
		for(j=0;j<i;j++)
		{
			if(dd[j][0]==cc[k])//�ж��Ƿ��Ѵ������ڴ����
			{
				flag=true;
				break;
			}
		}
		if(!flag)//��������д��
		{
			dd[i][0]=cc[k];
			opt++;//��¼ȱҳ�ж�
			for(l=k+1;l<num;l++)//�ҳ���ҳ�������λ��
			{
				if(cc[l]==dd[i][0])
				{
					dd[i][1]=l;
					break;
				}
				if(cc[l]!=dd[i][0]&&l==num-1)
				{
					dd[i][1]=500;
				}
			}
			i++;
		}
		else
		{
			for(l=k+1;l<num;l++)//�����������޸ģ��ҳ���ҳ���µ������λ��
			{
				if(cc[l]==dd[i][0])
				{
					dd[i][1]=l;
					break;
				}
				if(cc[l]!=dd[i][0]&&l==num-1)
				{
					dd[i][1]=500;
				}
			}
		}
		k++;
	}
	//�ڴ���Ѿ������Ժ�Ĳ���
	for(;k<num;k++)
	{
		//�ж��Ƿ��Ѵ������ڴ����
		max=-1;
		flag=false;
		for(j=0;j<Bnum;j++)
		{
			if(dd[j][0]==cc[k])
			{
				flag=true;
				//�����������޸ģ��ҳ���ҳ���µ������λ��
				for(l=k+1;l<num;l++)
				{
					if(cc[l]==dd[j][0])
					{
						dd[j][1]=l;
						break;
					}
					if(cc[l]!=dd[j][0]&&l==num-1)
					{
						dd[j][1]=500;
					}
				}
				break;
			}
		}
		if(!flag)//���������û�ҳ��
		{
			opt++;//��¼ȱҳ�ж�
			for(i=0;i<Bnum;i++)//�ҳ���Զ���ᱻ���õ�ҳ��
			{
				if(dd[i][1]>max)
				{
					max=dd[i][1];
					m=i;
				}
			}
			dd[m][0]=cc[k];//�����û�
			for(l=k+1;l<num;l++)//�ҳ���ҳ���µ������λ��
			{
				if(cc[l]==dd[m][0])
				{
					dd[m][1]=l;
					break;
				}
				if(cc[l]!=dd[m][0]&&l==num-1)
				{
					dd[m][1]=500;
				}
			}

		}
	}
	interrupt1=opt/num*100;//������ȱҳ�ж���
	return ;

}
void FIFO(int num,int Bnum)
{
	fifo=0;
	int i=0,j,k=0,m;
	bool flag;
	memset(dd,0,sizeof(dd));
	while(i<Bnum)//ͨ��Bnum���ܵ��ڴ������
	{
		flag=false;
		for(j=0;j<i;j++)
		{
			if(dd[j][0]==cc[k])//�ж��Ƿ��Ѵ������ڴ����
			{
				flag=true;
				break;
			}
		}
		if(!flag)//��������д��
		{
			dd[i][0]=cc[k];
			fifo++;//��¼ȱҳ�ж�
			i++;
		}
		k++;
	}
	m=0;//��¼��ǰ���翪ʼ���ڴ��
	for(;k<num;k++)
	{
		flag=false;
		for(j=0;j<Bnum;j++)
		{
			if(dd[j][0]==cc[k])//�ж��Ƿ��Ѵ������ڴ����
			{
				flag=true;
				break;
			}
		}
		if(!flag)//���������û�
		{
			fifo++;//��¼ȱҳ�ж�
			dd[m][0]=cc[k];//�����û�
			m++;//ȷ���µ����翪ʼ���ڴ��
			m=m%Bnum;
		}
	}
	interrupt2=fifo/num*100;//������ȱҳ�ж���
	return ;
}
void LRU(int num,int Bnum)
{
	int i=0,j,k=0,min,m;
	bool flag;
	lru=0;
	memset(dd,0,sizeof(dd));
	while(i<Bnum)//ͨ��Bnum���ܵ��ڴ������
	{
		flag=false;
		for(j=0;j<i;j++)
		{
			if(dd[j][0]==cc[k])//�ж��Ƿ��Ѵ������ڴ����
			{
				dd[j][1]=k;//�޸ĵ�ǰִ��λ��
				flag=true;
				break;
			}
		}
		if(!flag)//��������д��
		{
			dd[i][0]=cc[k];
			dd[i][1]=k;//��¼��ǰִ��λ��
			lru++;//��¼ȱҳ�ж�
			i++;
		}
		k++;
	}
	//�ڴ���Ѿ������Ժ�Ĳ���
	for(;k<num;k++)
	{
		min=500;
		flag=false;
		for(j=0;j<Bnum;j++)//�ж��Ƿ��Ѵ������ڴ����
		{
			if(dd[j][0]==cc[k])//�����������޸ģ���¼�䵱ǰִ��λ��
			{
				dd[j][1]=k;
				flag=true;
				break;
			}
		}
		if(!flag)//���������û�ҳ��
		{
			lru++;//��¼ȱҳ�ж�
			for(i=0;i<Bnum;i++)
			{
				if(dd[i][1]<min)//�ҳ����δ��ִ�еĿ��ڴ�
				{
					min=dd[i][1];
					m=i;
				}
			}
			dd[m][0]=cc[k];//�����û�����
			dd[m][1]=k;//��¼��ǰִ��λ��
		}
	}
	interrupt3=lru/num*100;//����ȱҳ�ж���
	return ;
}
int main()
{
	int  i,n,num,Bnum;
	
	num=20;
	Bnum=3;
	n=0;
	OPT(num,Bnum);
	FIFO(num,Bnum);
	LRU(num,Bnum);
	cout<<"Verify the correctness of the test data:\n";
	cout<<"\nThe total number of page calls is:"<<num<<", the number of memory blocks allocated to the program is:"<<Bnum<<"\n";
	cout<<"The number of missing pages of the algorithm OPT is"<<(int)opt<<", the page fault interrupt rate is:"<<setprecision(2)<<interrupt1<<"%��\n";
	cout<<"The number of pages missing in algorithm FIFO is"<<(int)fifo<<", the page fault interrupt rate is:"<<setprecision(2)<<interrupt2<<"%��\n";
	cout<<"The number of missing pages of the algorithm LRU is"<<(int)lru<<", the page fault interrupt rate is:"<<setprecision(2)<<interrupt3<<"%��\n\n\n\n";
	//�������ָ��
	memset(aa,0,sizeof(aa));
	setInstruction();
	cout<<"Display instruction address:\n";
	for(i=0;i<320;i++)
	{
		if(i%5==0&&i!=0)
			if(i%10==0)
				cout<<endl;
			else
				cout<<"      ";
		cout<<setw(4)<<aa[i]<<" ";
		
	}
	//��������ҳ���Сȷ��ָ������ҳ��
	cout<<"\nPlease enter page size:";
	cin>>n;
	setPage(n);
	cout<<"\nThe page number of each instruction is:\n";
	for(i=0;i<320;i++)
	{
		if(i%5==0&&i!=0)
			if(i%10==0)
				cout<<endl;
			else
				cout<<"      ";
		cout<<setw(4)<<bb[i]<<" ";
		
	}
	//�ϲ�������ͬҳ��
	cout<<endl;
	num=reduced();
	cout<<"\nCombined results:\n";
	for(i=0;i<num;i++)
	{
		if(i%5==0&&i!=0)
			if(i%10==0)
				cout<<endl;
			else
				cout<<"      ";
		cout<<setw(4)<<cc[i]<<" ";
	}
	cout<<endl;
	//�����ڴ���С������ȱҳ�ж���
	cout<<"\nPlease enter the size of the block:";
	cin>>Bnum;
	OPT(num,Bnum);
	FIFO(num,Bnum);
	LRU(num,Bnum);
	//������Խ��
	cout<<"\nPage size:"<<n<<"K. The total number of pages is"<<num<<", the number of memory blocks allocated to the program is:"<<Bnum<<"\n";
	cout<<"The number of missing pages of the algorithm OPT is"<<(int)opt<<", the page fault interrupt rate is:"<<setprecision(2)<<interrupt1<<"%��\n";
	cout<<"The number of pages missing in algorithm FIFO is"<<(int)fifo<<", the page fault interrupt rate is:"<<setprecision(2)<<interrupt2<<"%��\n";
	cout<<"The number of pages missing in algorithm LRU is"<<(int)lru<<", the page fault interrupt rate is:"<<setprecision(2)<<interrupt3<<"%��\n";

	return 0;
}