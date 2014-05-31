#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include "plays.h"
#include "doublylinkedlist.h"
#include <sys/time.h>
#include <iomanip>
#include <stdio.h>
#include <unistd.h>
#include <functional>
#include <tr1/unordered_set> // g++ main.cpp doublylinkedlist.h plays.cpp -std=gnu++0x used to compile!

using namespace std;
using namespace tr1;

double Tdlltime = 0; double dlltemp1 = 0; double dlltemp2 = 0; double dllMIN = 0; double dllMAX = 0; double dlllistAVG = 0; double dlltemp3 = 0; double Tdlllist = 0;
double Thashtime = 0; double hashtemp1 = 0; double hashtemp2 = 0; double hashMIN = 0; double hashMAX = 0; double hashlistAVG = 0; double hashtemp3 = 0; double Thashlist = 0;

//unsigned int Hash(const Plays&);
vector <Plays> summaryprint;

struct myhash
{
	size_t operator() (const Plays &obj) const
	{ 
		int x = obj.returnOrder();
		return x;
	}
};

double cputime(void);
void Summary(string, int, int, int);
void List(int, int, string, string, int, int, int);
void CommandRead();
doublylinkedlist MyDLL;
unordered_set<Plays, myhash> myUS;

int main(int argc, const char * argv[])
{
	if(argc <2)
	{
		cout <<"Usage:<executable file> <filename>" << endl;
		exit(1);
	}
	int counter = 1;
	int filecounting = 1;
	while (counter != argc)
	{
		string line = "";
		const char * const fname = argv[counter];
		char ffname[7] = "";
		strcat(ffname,fname);
		strcat(ffname, ".csv");
		ifstream infile(ffname);
 		if(!infile)
		{
			cout <<"Failed to open File" << endl;
		}
		if(infile)
		{
			getline(infile,line);
			while (!infile.eof())
			{
				getline(infile,line);
				if (strlen(line.c_str()) > 1)
				{
					Plays thisplay(line);
					if (thisplay.returndesc() != "Null")
					{
						thisplay.setOrder(filecounting);
						filecounting++;
						dlltemp1 = cputime();
						MyDLL.storeback(thisplay);
						dlltemp2 = cputime();
						Tdlltime = Tdlltime + (dlltemp2 - dlltemp1);

						hashtemp1 = cputime();
						myUS.insert(thisplay);
						hashtemp2 = cputime();
						Thashtime = Thashtime + (hashtemp2 - hashtemp1);
					}
				}
			}
		}
		infile.close();
		counter++;
		strcpy(ffname, "");
	}
	CommandRead();
	return 0;
}
void Summary(string team, int d, int tg, int yd)
{
	double dpr = 0;
	double dpm = 0;
	double dpl = 0;
	double spr = 0;
	double spm = 0;
	double spl = 0;
	double rr = 0;
	double rm = 0;
	double rl = 0;
	double fg = 0;
	double p = 0;
	double total = 0;

	for (MyDLL.iterator = MyDLL.front; MyDLL.iterator != NULL; MyDLL.iteratorInc())
	{
		if ((team == MyDLL.iterator->data.returnOff()) && (d == MyDLL.iterator->data.returnDown()))
		{
			if ((tg == MyDLL.iterator->data.returnTogo()) || (tg+1 == MyDLL.iterator->data.returnTogo()) || (tg-1 == MyDLL.iterator->data.returnTogo()))
			{
				if (((yd*.90) <= MyDLL.iterator->data.returnydline()) && ((yd*1.10) >= MyDLL.iterator->data.returnydline()))
				{	
					if (MyDLL.iterator->data.returndesc() == "Pass Deep Right")
						dpr++;
					if (MyDLL.iterator->data.returndesc() == "Pass Deep Middle")
						dpm++;
					if (MyDLL.iterator->data.returndesc() == "Pass Deep Left")
						dpl++;
					if (MyDLL.iterator->data.returndesc() == "Pass Short Right")
						spr++;
					if (MyDLL.iterator->data.returndesc() == "Pass Short Middle")
						spm++;
					if (MyDLL.iterator->data.returndesc() == "Pass Short Left")
						spl++;
					if (MyDLL.iterator->data.returndesc() == "Run Left")
						rl++;
					if (MyDLL.iterator->data.returndesc() == "Run Middle")
						rm++;
					if (MyDLL.iterator->data.returndesc() == "Run Right")
						rr++;
					if (MyDLL.iterator->data.returndesc() == "Field Goal")
						fg++;
					if (MyDLL.iterator->data.returndesc() == "Punt")
						p++;
					total++;
				}
			}
		}
	}

	if (total == 0)
	{
		cout << "No similar play exists" << endl;
		return;
	}
	cout << "Pass Deep Right: " << (dpr/total) * 100 << "%" <<endl;
	cout << "Pass Deep Middle: " << (dpm/total) * 100 << "%" <<endl;
	cout << "Pass Deep Left: " << (dpl/total) * 100 << "%" <<endl;
	cout << "Pass Short Right: " << (spr/total) * 100 << "%" <<endl;
	cout << "Pass Short Middle: " << (spm/total) * 100 << "%" <<endl;
	cout << "Pass Short Left: " << (spl/total) * 100 << "%" <<endl;
	cout << "Run Left: " << (rl/total) * 100 << "%" <<endl;
	cout << "Run Right: " << (rr/total) * 100 << "%" <<endl;
	cout << "Run Middle: " << (rm/total) * 100 << "%" <<endl;
	cout << "Field Goal: " << (fg/total) * 100 << "%" <<endl;
	cout << "Punt: " << (p/total) * 100 << "%" <<endl;
}

void List(int discount, int m, string oteam, string dteam, int d, int t, int y)
{
	float five = 5.000;
	float three = 3.000;
	float none = -1.000;
	float relevance=0;

////////////////////////////////
//DLL LIST BELOW
////////////////////////////////
	doublylinkedlist summary;
	vector<float>relnum;
//////////~~~~~~~~~~~~~~~~~~~~~	
		dlltemp1 = cputime();//start counter
//////////^^^^^^^^^^^^^^^^^^^^^^	
	for (MyDLL.iterator = MyDLL.front; MyDLL.iterator != NULL; MyDLL.iteratorInc())
	{
		if ((oteam == MyDLL.iterator->data.returnOff()) && (d == MyDLL.iterator->data.returnDown()))
		{
			if ((t == MyDLL.iterator->data.returnTogo()) || (t+1 == MyDLL.iterator->data.returnTogo()) || (t-1 == MyDLL.iterator->data.returnTogo()))
			{
				if (((y*.90) <= MyDLL.iterator->data.returnydline()) && ((y*1.10) >= MyDLL.iterator->data.returnydline()))
				{
					summary.storeback(MyDLL.iterator->data);
					MyDLL.iterator->data.incCalln();
				}
			}
		}
	}
	
	if (summary.back == summary.front)
	{
		cout << "No similar play" << endl;
		return;
	}

	for (summary.iterator = summary.front; summary.iterator != NULL; summary.iteratorInc())
	{
		float fm = summary.iterator->data.returnMin();
		float ftogo = summary.iterator->data.returnTogo();
		float fyline = summary.iterator->data.returnydline();
		
		float part1 = abs(m-fm);
		float part2 = abs(t-ftogo);
		float part3 = abs(y-fyline);
		relevance = (none*((part1)*(five/three) + part2 + part3));
		
		if (dteam == summary.iterator->data.returnDeff())
		{
			relevance = relevance + 100;
		}
		summary.iterator->data.setrelevance(relevance);
		relnum.push_back(relevance);
//////////~~~~~~~~~~~~~~~~~~~~~	
		dlltemp2 = cputime();//end counter
		dlltemp3 = (dlltemp2 - dlltemp1);
		Tdlllist = (Tdlllist + dlltemp3);
		//cout << dlltemp3 << endl;
			if ((dllMAX == 0) && (dllMIN == 0))
			{
				dllMAX = dlltemp3;
				dllMIN = dlltemp3;
			}
			if (dlltemp3 > dllMAX)
				dllMAX = dlltemp3;
			if ((dlltemp3 < dllMIN) && (dlltemp3 > 0))
				dllMIN = dlltemp3;
//////////^^^^^^^^^^^^^^^^^^^^^^
	}
//////////~~~~~~~~~~~~~~~~~~~~~	
		dlllistAVG = (Tdlllist / (relnum.size()));//calculate average
//////////^^^^^^^^^^^^^^^^^^^^^^


	/*self reorganization
	for (MyDLL.iterator = MyDLL.front; MyDLL.iterator != NULL; MyDLL.iteratorInc())
	{
		if (MyDLL.iterator->data.returnCalln() >= 4)
			MyDLL.iteratorM2F();
	}*/


///////////////////////////////////////////////////////
//DLL ABOVE!!!!! UNORDERED_SET BELOW!!!!! PRINTS WILL FOLLOW
//////////////////////////////////////////////////////
	
	unordered_set<Plays, myhash> mySummary;
	
	for (auto itr = myUS.begin(); itr != myUS.end(); ++itr)
	{
		if ((oteam == itr->returnOff()) && (d == itr->returnDown()))
		{
			if ((t == itr->returnTogo()) || (t+1 == itr->returnTogo()) || (t-1 == itr->returnTogo()))
			{
				if (((y*.90) <= itr->returnydline()) && ((y*1.10) >= itr->returnydline()))
				{
					Plays temp;
					temp.setQtr(itr->returnQtr());
					temp.setMin(itr->returnMin());
					temp.setOff(itr->returnOff());
					temp.setDeff(itr->returnDeff());
					temp.setDown(itr->returnDown());
					temp.setTogo(itr->returnTogo());
					temp.setYdline(itr->returnydline());
					temp.setDesc(itr->returndesc());
					temp.setrelevance(itr->returnRele());
					temp.setYear(itr->returnYear());
					temp.setOrder(itr->returnOrder());
					mySummary.insert(temp);
				}
			}
		}
	}

//////////~~~~~~~~~~~~~~~~~~~~~	
		hashtemp1 = cputime();//start counter
//////////^^^^^^^^^^^^^^^^^^^^^^

	vector<float> relnum2;
	doublylinkedlist holderDLL;
	
	for (auto itr = mySummary.begin(); itr != mySummary.end(); ++itr)
	{
		Plays temp;
		temp.setQtr(itr->returnQtr());
		temp.setMin(itr->returnMin());
		temp.setOff(itr->returnOff());
		temp.setDeff(itr->returnDeff());
		temp.setDown(itr->returnDown());
		temp.setTogo(itr->returnTogo());
		temp.setYdline(itr->returnydline());
		temp.setDesc(itr->returndesc());
		temp.setrelevance(itr->returnRele());
		temp.setYear(itr->returnYear());
		temp.setOrder(itr->returnOrder());


		float fm = temp.returnMin();
		float ftogo = temp.returnTogo();
		float fyline = temp.returnydline();
		
		float part1 = abs(m-fm);
		float part2 = abs(t-ftogo);
		float part3 = abs(y-fyline);
		relevance = (none*((part1)*(five/three) + part2 + part3));

		if (dteam == temp.returnDeff())
		{
			relevance = relevance + 100;
		}
		temp.setrelevance(relevance);
		holderDLL.storeback(temp);
		relnum2.push_back(relevance);
//////////~~~~~~~~~~~~~~~~~~~~~	
		hashtemp2 = cputime();//end counter
		hashtemp3 = (hashtemp2 - hashtemp1);
		Thashlist = (Thashlist + hashtemp3);
			if ((hashMAX == 0) && (hashMIN == 0))
			{
				hashMAX = hashtemp3;
				hashMIN = hashtemp3;
			}
			if (hashtemp3 > hashMAX)
				hashMAX = hashtemp3;
			if ((hashtemp3 < hashMIN) && (hashtemp3 > 0))
				hashMIN = hashtemp3;
//////////^^^^^^^^^^^^^^^^^^^^^^
	}
//////////~~~~~~~~~~~~~~~~~~~~~	
	hashlistAVG = (Thashlist / (relnum2.size()));//calculate average
//////////^^^^^^^^^^^^^^^^^^^^^^


////////////////////////////////
//DLL LIST's "PRINT" BELOW
////////////////////////////////

	sort(relnum.begin(), relnum.end(), greater<float>());
	vector<float>::iterator itrel = relnum.begin();
	for (int k = 0; k != discount; k++)
	{
		for (summary.iterator = summary.front; summary.iterator != NULL; summary.iteratorInc())
		{
			if ( (*itrel) == summary.iterator->data.returnRele())
			{
				if (summary.iterator->data.returnRele() != 0)
				{
				cout << summary.iterator->data.returndesc() << " " << summary.iterator->data.returnMin() << " " << summary.iterator->data.returnOff() << " " <<
					summary.iterator->data.returnDeff() << " " << summary.iterator->data.returnTogo() << " " << summary.iterator->data.returnydline() << " " <<
					summary.iterator->data.returnRele() << endl;
				summary.iterator->data.setrelevance(0);
				}
			}
		}
		++itrel;
	}

	cout << endl;
////////////////////////////////
//HASH LIST's "PRINT" BELOW
////////////////////////////////

	sort(relnum2.begin(), relnum2.end(), greater<float>());
	vector<float>::iterator itrel2 = relnum2.begin();
	for (int k = 0; k != discount; k++)
	{
		for (holderDLL.iterator = holderDLL.front; holderDLL.iterator != NULL; holderDLL.iteratorInc())
		{
			if ( (*itrel2) == holderDLL.iterator->data.returnRele())
			{
				if (holderDLL.iterator->data.returnRele() != 0)
				{
					cout << holderDLL.iterator->data.returndesc() << " " << holderDLL.iterator->data.returnMin() << " " << holderDLL.iterator->data.returnOff() << " " <<
						holderDLL.iterator->data.returnDeff() << " " << holderDLL.iterator->data.returnTogo() << " " << holderDLL.iterator->data.returnydline() << " " <<
						holderDLL.iterator->data.returnRele() << endl;
					holderDLL.iterator->data.setrelevance(0);
				}
			}
		}
		++itrel2;
	}
}

void CommandRead()
{
	string command;
	string offteam;
	string defteam;
	int tg;
	int yd;
	int dwn;
	int min;
	int listn;
	cout << "Please Enter Command: " << endl;
	cin >> command;
	if (command == "summary")
	{
		cin >> offteam;
		cin >> dwn;
		cin >> tg;
		cin >> yd;
		Summary(offteam,dwn,tg,yd);
	}
	if (command == "list")
	{
		cin >> listn;
		cin >> min;
		cin >> offteam;
		cin >> defteam;
		cin >> dwn;
		cin >> tg;
		cin >> yd;
		List(listn, min, offteam, defteam, dwn, tg, yd);
	}
	if (command == "print")
	{
		int number = 0;
		cin >> number;
		MyDLL.print(number);
	}
	if (command == "x")
	{
		cout << "myHash: store: " << std::setprecision(5) << Thashtime << " s, list: min " << std::setprecision(5) << hashMIN
			<< " s, max " << hashMAX << " s, mean " << hashlistAVG << " s" << endl;
		cout << "myDoublyLinkedLined: store: " << std::setprecision(5) << Tdlltime << " s, list: min " << std::setprecision(5) << dllMIN
			<< " s, max " << dllMAX << " s, mean " << dlllistAVG << " s" << endl;
		return;
	}
	else if ((command != "x") && (command != "list") && (command != "summary") && (command != "print"))
	{
		cout << "Invalid Command!" << endl;
		string temp;		//holds garbage at the end of the line
		getline (cin,temp);	//trashes garbage at end of line
	}
	CommandRead();
}

double cputime()
{
	double current_time;
	struct timeval temp;
	gettimeofday(&temp, NULL);
	current_time = temp.tv_sec + 1.0e-6*temp.tv_usec;
	return current_time;
}
/*
unsigned int Hash(Plays& Key)
{
	unsigned int hash = 0;
	int limit = Key.returnOrder();
	for (int j = 0; j != limit; ++j)
		hash++;
	return hash;
}*/