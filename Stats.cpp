#include <iomanip>
#include "Stats.h"
#include <math.h>


void Stats::OutputMem(vector<char> memory)
{
	MemMap(memory);         //print memory map
	PercentHoles(memory);   //print percentage of holes in memory map
	return;
}


void Stats::MemMap(vector<char> memory)
{
	
	
	//print memory units 1 - 64
	cout<<"000 ";

	for(int i=0; i<64; i++)
	{
		cout<<memory[i];
	}


	//print memory units 65 - 128
	cout<<"\n064 ";

	for(int i=64; i<128; i++)
	{
		cout<<memory[i];
	}
	

	//print memory units 129 - 192
	cout<<"\n128 ";

	for(int i=128; i<192; i++)
	{
		cout<<memory[i];
	}


	//print memory units 193 - 256
	cout<<"\n192 ";

	for(int i=192; i<256; i++)
	{
		cout<<memory[i];
	}


	cout<<'\n';

	return;
}


void Stats::PercentHoles(vector<char> memory)
{
	const float MEMORY_SIZE = 256.0;     //size of memory in memory units
	float holeCount=0.0;                
	float holePercent=0.0;               
	

	for(int i=0; i<MEMORY_SIZE; i++)     //search through entire memory
	{
		if(memory[i]=='_')
		{
			holeCount++;        //count the number of holes in memory
		}
	}

	holePercent = (holeCount / MEMORY_SIZE) * 100;      //divide number of holes by total number of memory units (256)

	logHolePercent(holePercent);

	cout << setprecision(4) << "Percent Holes: " << holePercent << "%" << endl;	
	
	return;
}

void Stats::logHolePercent(float percentHole)
{
	_percentHoleData.push_back(percentHole);   //add data for percent hole calculation

	return;
}

void Stats::ProcessStates(vector<Job*> Jobs, int clockTime)
{
	cout<<"Job#     |Current | Running | Ready | Waiting | DataSize | Arrival | Complete"<<endl;
	cout<<"         | State  |         |       |         |          |  Time   |   Time  "<<endl;
	cout<<"=========+========+=========+=======+=========+==========+=========+========="<<endl;
	
	//print information for each process
	for(int i=0; i<Jobs.size(); i++)
	{
		if (Jobs[i]->getArrivalTime() <= clockTime)
		{
			cout << "pid" << setw(5) << Jobs[i]->getProcessId() << " |"
				<< setw(7) << Jobs[i]->getCurrentState() << " |"
				<< setw(8) << Jobs[i]->getRunningTime() << " |"
				<< setw(6) << Jobs[i]->getReadyTime() << " |"
				<< setw(8) << Jobs[i]->getWaitingTime() << " |"
				<< setw(9) << Jobs[i]->getDataSize() << " |"
				<< setw(8) << Jobs[i]->getArrivalTime() << " |"
				<< setw(9) << Jobs[i]->getCompletionTime() << endl;
		}
	}

	cout<<"=========+========+=========+=======+=========+==========+=========+========="<<endl;

	return;
}



void Stats::getAvgHolePercent()
{
	float _avgHolePercent=0;

	for(int i=0; i<_percentHoleData.size(); i++)
	{
		_avgHolePercent+=_percentHoleData[i];      //sum all percent hole calculations
	}

	_avgHolePercent/=_percentHoleData.size();       //divide by total to get the average

	cout << setprecision(4) << _avgHolePercent << "%" << endl;

	return;
}


float Stats::getAvgWaitTime(vector<Job*> Jobs)
{
	float _avgWaitTime=0;

	for(int i=0; i<Jobs.size(); i++)
	{
		_avgWaitTime+=(float)Jobs[i]->getWaitingTime();    //sum all wait times
	}

	_avgWaitTime/=(float)Jobs.size();            //divide by total to get the average

	return _avgWaitTime;
}
