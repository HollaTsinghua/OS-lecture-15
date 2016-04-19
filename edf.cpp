/*
  edf��ʵʱ�����㷨
  ��Ҫ����ÿ�����������ʱ�䣬ִ��ʱ�䣬���Խ�ֹʱ��
  input��ʽ�� 
  ��һ��һ������n����ʾһ��n������
  ������n��ÿ����������i,j,k��i��ʾ��������ʱ�䣬j��ʾ����ִ��ʱ�䣬k��ʾ������Խ�ֹʱ��
  �������־��ٶ��趨Ϊ����
*/

#include <cstring>
#include <iostream>
#include <fstream>
#include <cstdio> 
#define maxnum 100
using namespace std;
/*
bool finish[maxnum];
int response[maxnum];
int turnaround[maxnum];
int waittime[maxnum];

int a[maxn];//����ʱ��
int b[maxn];//����ʱ��
int c[maxn];//��Խ�ֹʱ��
int dl[maxn];
*/
struct myquest
{
	int time_r;//����ʱ�� 
	int time_e;//����ʱ�� 
	int time_d;//���Խ�ֹʱ�� 
	
	int time_h;//����ɵ�ʱ�䣬������ռ��Ļ�ԭ 
	int time_f;//������ɵ�ʱ�� 
	 
	int response;//��Ӧʱ��
	int wait;//�ȴ�ʱ��
	int turnaround;//��תʱ�� 
	bool finish;//�Ƿ���� 
};
myquest qlist[maxnum];
int main()
{
	int n;//�������� 
	ifstream fin;
	fin.open("input.txt");
	fin>>n;
	for (int i=0;i<n;i++) 
	{
		fin>>qlist[i].time_r>>qlist[i].time_e>>qlist[i].time_d;
		qlist[i].finish=false;
		qlist[i].time_h=0; 
	}
	fin.close(); 

	int now=0;//��ǰʱ��
	int havedone=0;//������� 
	cout<<"Execution trace:\n";
	int preview=-1;//��ʾ�ϴ�ѡ�������
	int pretime=-1;//��ʾ�ϴ�ѡ���ʱ�� 
	int current=-1;//��ʾ��ǰѡ������� 
	while (havedone<n)
	{
		preview=current;
		current=-1;
		for (int i=0;i<n;i++)//��������ѡ��
		{
			if ((qlist[i].time_r>now)||(qlist[i].finish)) continue;//����δ������������ѽ���
			if ((current==-1)||(qlist[current].time_d>qlist[i].time_d)) current=i;//ѡ����Խ�ֹʱ����С�� 
		}
		if (preview!=current)
		{
			if ((pretime!=-1)&&(preview!=-1))
			{ 
				printf("execute quest[%d] in time [%d,%d), quest length:%d, have done:%d",preview,pretime,now,qlist[preview].time_e,qlist[preview].time_h);
				if (qlist[preview].finish) printf(", quest done");
				else printf(", quest interrupted");
				printf("\n");
			}
			pretime=now;
		}
		if (current==-1) now++;//û�п�ִ������
		else
		{
			if (qlist[current].time_h==0) qlist[current].response=now-qlist[current].time_r;//��һ����Ӧ����¼��Ӧʱ�� 
			now++;
			qlist[current].time_h++;
			if (qlist[current].time_h==qlist[current].time_e)//������ɣ���¼�ȴ�ʱ�����תʱ�� 
			{
				havedone++; 
				qlist[current].finish=true;
				qlist[current].time_f=now;
				qlist[current].wait=qlist[current].time_f-qlist[current].time_e-qlist[current].time_r;
				qlist[current].turnaround=qlist[current].time_f-qlist[current].time_r;
				if (havedone==n) printf("execute quest[%d] in time [%d,%d), quest length:%d, have done:%d, quest done\n",preview,pretime,now,qlist[preview].time_e,qlist[preview].time_h);
			} 
		} 
	}
	cout<<"statistics:\n";
	double r_total=0;
	double t_total=0;
	double w_total=0;
	for (int i=0;i<n;i++)
	{
		r_total+=qlist[i].response;
		t_total+=qlist[i].turnaround;
		w_total+=qlist[i].wait;
		printf("quest[%d]: reponse %d turnaround %d wait %d\n",i,qlist[i].response,qlist[i].turnaround,qlist[i].wait);
	}
	r_total/=double(n);
	t_total/=double(n);
	w_total/=double(n);
	printf("average -- response %.2lf turnaround %.2lf wait %.2lf\n",r_total,t_total,w_total);
	return 0;
}


