/*
  edf是实时调度算法
  需要给出每个任务的请求时间，执行时间，绝对截止时间
  input格式： 
  第一行一个数字n，表示一共n个任务
  接下来n行每行三个数字i,j,k，i表示任务请求时间，j表示任务执行时间，k表示任务绝对截止时间
  所有数字均假定设定为整数
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

int a[maxn];//请求时间
int b[maxn];//运行时间
int c[maxn];//相对截止时间
int dl[maxn];
*/
struct myquest
{
	int time_r;//请求时间 
	int time_e;//运行时间 
	int time_d;//绝对截止时间 
	
	int time_h;//已完成的时间，用于抢占后的还原 
	int time_f;//最终完成的时间 
	 
	int response;//响应时间
	int wait;//等待时间
	int turnaround;//周转时间 
	bool finish;//是否完成 
};
myquest qlist[maxnum];
int main()
{
	int n;//任务总数 
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

	int now=0;//当前时间
	int havedone=0;//完成总数 
	cout<<"Execution trace:\n";
	int preview=-1;//表示上次选择的任务
	int pretime=-1;//表示上次选择的时间 
	int current=-1;//表示当前选择的任务 
	while (havedone<n)
	{
		preview=current;
		current=-1;
		for (int i=0;i<n;i++)//进行任务选择
		{
			if ((qlist[i].time_r>now)||(qlist[i].finish)) continue;//任务还未到达或者任务已结束
			if ((current==-1)||(qlist[current].time_d>qlist[i].time_d)) current=i;//选择绝对截止时间最小的 
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
		if (current==-1) now++;//没有可执行任务
		else
		{
			if (qlist[current].time_h==0) qlist[current].response=now-qlist[current].time_r;//第一次响应，记录响应时间 
			now++;
			qlist[current].time_h++;
			if (qlist[current].time_h==qlist[current].time_e)//任务完成，记录等待时间和周转时间 
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


