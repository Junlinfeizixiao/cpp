#include "process.h"
#include <list>
#include<algorithm>
void MyProcess::ShowProcessqueue()
{
	cout<<"************ShowAllProcess*************"<<endl;
	for (int i=0;i<_size;i++)
	{
		cout<<"进程名:"<<_process[i]._name<<endl;
		cout<<"到达时间:"<<_process[i]._arrtime<<endl;
		cout<<"服务时间:"<<_process[i]._sertime<<endl;
	}
	cout<<"*************************"<<endl;
}
void MyProcess::ShowProcessname()
{
	cout<<"进程列表:";
	for (int i=0;i<_size;i++)
	{
		cout<<_process[i]._name<<" ";
	}
	cout<<endl;

}
void MyProcess::ShowFinsh(int num)
{
	cout << "******************************************************		" << endl;	
	cout << "进程名" << " " << "到达时间" << " " << "服务时间" << " " 
	<< "完成时间" << " "  << "周转时间" << " " <<"带权周转时间"<<endl;

    for (int i = 0; i < num; ++i)
	{
		cout << _process[i]._name << "     ";
		cout << _process[i]._arrtime << "	";
		cout << _process[i]._sertime << "	     ";
		cout << _process[i]._finishtime << "	      ";
		cout << _process[i]._turntime << "     ";
		cout << _process[i]._dqturntime << "		";
		cout<<endl;
	}
}
void MyProcess::RemoveProcess(PCB *_process,int index)
{
	for (int i=index;i<_size-1;i++)
	{
		_process[i]=_process[i+1];
	}
	_size-=1;
}
void delay()
{
	for (int i=0;i<20000;i++)
		for (int j=0;j<10000;j++)
			;
}
void MyProcess::TimeRun()
{	
	const int ptime=1;  //确定时间片是1
	int time=0;         //确定公共时间从0开始
	ShowProcessqueue();
	int processertime[100]={0};
	for (int i=0;i<_size;i++)
	{
		processertime[i]=_process[i]._sertime;
	}


	list<PCB> lis1;    //容器用来存放进程队列
	list<PCB>::iterator it; 

	int arrtime0=_process[0]._arrtime; //第一个进程的到达时间
	
	int inlispcount=0;//进入容器的进程数;
	int const processnum=_size;
	int beginrun[100]={};
	int i=0;
	int j=0;//开始执行时间
	while(_size)
	{
		//delay();
		if (arrtime0==time)
		{
			lis1.push_back(_process[i]);
			inlispcount++;
			beginrun[j]=time;
			j++;
		}
		
		cout<<"进程就绪队列: ";
		for(it=lis1.begin();it!=lis1.end();it++)
		{
			cout<<it->_name<<" ";
		}
		it=lis1.begin();
		cout<<endl;
		cout<<"正在执行进程："<<it->_name<<endl;
		cout<<"剩余服务时间："<<it->_sertime-1<<endl;
		cout<<"系统时间："<<time<<endl;
		cout<<"*************************"<<endl;
		if(it->_sertime<=ptime)
		{
			for (int i=0;i<processnum;i++)
			{
				if (_process[i]._name==it->_name)
				{
					_process[i]._finishtime=time+1;
				}
			}
			cout<<"进程"<<it->_name<<"完成"<<endl;
			cout<<"用时："<<time+1<<endl;
			cout<<"*************************"<<endl;
			lis1.pop_front();
			it=lis1.begin();
			_size--;
			time++;
			continue;
		}
		else if(inlispcount<_size) 
		{
			for (int m=0;m<_size;m++)
			{	
				if (_process[m]._arrtime==time+1)
				{
					lis1.push_back(_process[m]);
					//_process[m]._sertime-=ptime;

					it=lis1.begin();
					(*it)._sertime-=ptime;
					lis1.push_back(*it);
					lis1.pop_front();
					inlispcount++;
					//i++;
				}	
			}
		}	
		else
		{
			it=lis1.begin();
			(*it)._sertime-=ptime;
			it=lis1.begin();
			lis1.push_back(*it);
			lis1.pop_front();
		}
		time++;
	}
	for(int i=0;i<processnum;i++)
	{
		_process[i]._sertime=processertime[i];
	}
	for (int i=0;i<processnum;i++)
	{
		_process[i]._turntime = _process[i]._finishtime - _process[i]._arrtime;
		_process[i]._dqturntime =
		_process[i]._turntime / (double)(_process[i]._sertime);
	}
	ShowFinsh(processnum);
	cout<<"进程调度完毕！"<<endl;
}
