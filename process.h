#ifndef _PROCESS_H_
#define _PROCESS_H_
#include <string>
#include <iostream>
using namespace std;
struct PCB
{
	string _name; //进程名
	int _arrtime; //到达时间
	int _sertime; //服务时间
	int _finishtime; //完成时间
	int _turntime;	//周转时间
	double _dqturntime; //带权周转时间
	int _beginrun;//开始执行时间

	PCB(string name="",int arrname=0,int sertime=0,int finishtime=0,int turntime=0,double dqturntime=0.0,int beginrun=0):
		_name(name),
		_arrtime(arrname),
		_sertime(sertime),
		_finishtime(finishtime),
		_turntime(turntime),
		_dqturntime(dqturntime),
		_beginrun(beginrun)
		{}
};
class MyProcess
{
public:
	MyProcess()
	{
		cout<<"进程数：";
		int num;
		cin>>num;
		if (num<1||num>65000)
		{
			cout<<"输入错误！"<<endl;
			exit(-1);
		}
		_size=num;
		_process=new PCB[num];
		string name="";
		int arrname;
		int sertime;
		cout<<"输入进程信息:"<<endl;
		int i=0;
		while (num--)
		{
			cout<<i<<"进程名 到达时间 服务时间\n";
			cin>>name>>arrname>>sertime;
			//PCB tmp(name,arrname,sertime);
			_process[i]._name=name;
			_process[i]._arrtime=arrname;
			_process[i]._sertime=sertime;
			cout<<"进程名:"<<_process[i]._name<<endl;
			cout<<"到达时间:"<<_process[i]._arrtime<<endl;
			cout<<"服务时间:"<<_process[i]._sertime<<endl;
			if (i!=0)
			{
				int j=0;
				for (int k=0;k<i;k++)
				{
					for(int g=0;g<i;g++)
					if (_process[g]._arrtime>_process[g+1]._arrtime)
					{
						PCB tmp;
						tmp=_process[g];
						_process[g]=_process[g+1];
						_process[g+1]=tmp;
					}	
				}
			}
			i++;
		}
	}
	void ShowProcessqueue();
	void ShowProcessname();
	void ShowFinsh(int num);
	void RemoveProcess(PCB *_process,int index);
	void TimeRun();

private:
	PCB *_process;
	int _size;
};
#endif