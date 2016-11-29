#ifndef _PROCESS_H_
#define _PROCESS_H_
#include <string>
#include <iostream>
using namespace std;
struct PCB
{
	string _name; //������
	int _arrtime; //����ʱ��
	int _sertime; //����ʱ��
	int _finishtime; //���ʱ��
	int _turntime;	//��תʱ��
	double _dqturntime; //��Ȩ��תʱ��
	int _beginrun;//��ʼִ��ʱ��

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
		cout<<"��������";
		int num;
		cin>>num;
		if (num<1||num>65000)
		{
			cout<<"�������"<<endl;
			exit(-1);
		}
		_size=num;
		_process=new PCB[num];
		string name="";
		int arrname;
		int sertime;
		cout<<"���������Ϣ:"<<endl;
		int i=0;
		while (num--)
		{
			cout<<i<<"������ ����ʱ�� ����ʱ��\n";
			cin>>name>>arrname>>sertime;
			//PCB tmp(name,arrname,sertime);
			_process[i]._name=name;
			_process[i]._arrtime=arrname;
			_process[i]._sertime=sertime;
			cout<<"������:"<<_process[i]._name<<endl;
			cout<<"����ʱ��:"<<_process[i]._arrtime<<endl;
			cout<<"����ʱ��:"<<_process[i]._sertime<<endl;
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