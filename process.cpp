#include "process.h"
#include <list>
#include<algorithm>
void MyProcess::ShowProcessqueue()
{
	cout<<"************ShowAllProcess*************"<<endl;
	for (int i=0;i<_size;i++)
	{
		cout<<"������:"<<_process[i]._name<<endl;
		cout<<"����ʱ��:"<<_process[i]._arrtime<<endl;
		cout<<"����ʱ��:"<<_process[i]._sertime<<endl;
	}
	cout<<"*************************"<<endl;
}
void MyProcess::ShowProcessname()
{
	cout<<"�����б�:";
	for (int i=0;i<_size;i++)
	{
		cout<<_process[i]._name<<" ";
	}
	cout<<endl;

}
void MyProcess::ShowFinsh(int num)
{
	cout << "******************************************************		" << endl;	
	cout << "������" << " " << "����ʱ��" << " " << "����ʱ��" << " " 
	<< "���ʱ��" << " "  << "��תʱ��" << " " <<"��Ȩ��תʱ��"<<endl;

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
	const int ptime=1;  //ȷ��ʱ��Ƭ��1
	int time=0;         //ȷ������ʱ���0��ʼ
	ShowProcessqueue();
	int processertime[100]={0};
	for (int i=0;i<_size;i++)
	{
		processertime[i]=_process[i]._sertime;
	}


	list<PCB> lis1;    //����������Ž��̶���
	list<PCB>::iterator it; 

	int arrtime0=_process[0]._arrtime; //��һ�����̵ĵ���ʱ��
	
	int inlispcount=0;//���������Ľ�����;
	int const processnum=_size;
	int beginrun[100]={};
	int i=0;
	int j=0;//��ʼִ��ʱ��
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
		
		cout<<"���̾�������: ";
		for(it=lis1.begin();it!=lis1.end();it++)
		{
			cout<<it->_name<<" ";
		}
		it=lis1.begin();
		cout<<endl;
		cout<<"����ִ�н��̣�"<<it->_name<<endl;
		cout<<"ʣ�����ʱ�䣺"<<it->_sertime-1<<endl;
		cout<<"ϵͳʱ�䣺"<<time<<endl;
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
			cout<<"����"<<it->_name<<"���"<<endl;
			cout<<"��ʱ��"<<time+1<<endl;
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
	cout<<"���̵�����ϣ�"<<endl;
}
