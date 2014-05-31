#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <cstring>
#include "plays.h"
using namespace std;
Plays::Plays(){}
Plays::Plays(string line)
{
	relnum = 0;
	callnum = 0;
	string delimiter = ",";
	size_t pos = 0;
	string token;
	int i = 1;
	

	int year;
	char yearholder[3];
	line.copy(yearholder, 4);
	string yearholder2(yearholder);
	year = atoi(yearholder2.c_str());


	//COMMA PARSING BELOW
	while ((pos = line.find(delimiter)) != string::npos)
	{
		token = line.substr(0, pos);
		line.erase(0, pos + delimiter.length()); 
		if (i == 2)
		{
			qtr = atoi(token.c_str());
		}
		if (i == 3)
		{
			min = atoi(token.c_str()); 
		}
		if (i == 5)
		{
			off = token.c_str();
		} 
		if (i == 6)
		{ 
			def = token.c_str();
		}
		if (i == 7)
		{
			down = atoi(token.c_str());
		}
		if (i == 8)
		{
			togo = atoi(token.c_str());
		}
		if (i == 9)
		{
			ydline = atoi(token.c_str());
		}
		if (i == 10)
		{
			descriptionlist = token.c_str();
			string finalD = PType(descriptionlist);
			descriptionlist = finalD;
		}
		i++;
	}
}

string Plays::PType(string data) //reads description and sets identifying play type
{
	const string Deep = "deep";
	const string Short = "short";
	const string Left = "left";
	const string Middle = "middle";
	const string Right = "right";
	const string Pass = "pass";
	const string Field = "field";
	const string Goal = "goal";
	const string Punt = "punts";
	size_t local1;
	size_t local2;
	size_t local3;

	local1 = data.find(Pass); if (local1  != string::npos)
	{
		local2 = data.find(Deep); if (local2  != string::npos)
		{
			local3 = data.find(Left); if (local3  != string::npos)
			{ return "Pass Deep Left"; }
			local3 = data.find(Middle); if (local3  != string::npos)
			{ return "Pass Deep Middle"; }
			local3 = data.find(Right); if (local3  != string::npos)
			{ return "Pass Deep Right"; }
		}
		local2 = data.find(Short); if (local2  != string::npos)
		{
			local3 = data.find(Left); if (local3  != string::npos)
			{ return "Pass Short Left"; }
			local3 = data.find(Middle); if (local3  != string::npos)
			{ return "Pass Short Middle"; }
			local3 = data.find(Right); if (local3  != string::npos)
			{ return "Pass Short Right"; }		
		}
	}
	local1 = data.find(Field); if (local1  != string::npos)
	{
		local2 = data.find(Goal); if (local2  != string::npos)
		{  return "Field Goal"; }
	}
	local1 = data.find(Punt); if (local1  != string::npos)
	{ return "Punt"; }
	
	local1 = data.find(Pass); if (local1  == string::npos)
	{
		local2 = data.find(Left); if (local2  != string::npos)
		{ return "Run Left"; }
		local2 = data.find(Middle); if (local2  != string::npos)
		{ return "Run Middle"; }
		local2 = data.find(Right); if (local2  != string::npos)
		{ return "Pass Right"; }
	}
	return "Null";
}

int Plays::returnQtr() const
{
	return qtr;
}
int Plays::returnMin() const
{
	return min;
}
string Plays::returnOff() const
{
	return off;
}
string Plays::returnDeff() const
{
	return def;
}
int Plays::returnDown() const
{
	return down;
}
int Plays::returnTogo() const
{
	return togo;
}
int Plays::returnydline() const
{
	return ydline;
}
string Plays::returndesc() const
{
	return descriptionlist;
}
void Plays::setrelevance(float x)
{
	relnum = x;
}
float Plays::returnRele() const
{
	return relnum;
}
int Plays::returnCalln() const
{
	return callnum;
}
void Plays::incCalln()
{
	callnum = callnum +1;
}
int Plays::returnYear() const
{
	return year;
}
void Plays::setOrder(int x)
{
	fileorder = x;
}
int Plays::returnOrder() const
{
	const int x = fileorder;
	return x;
}
Plays& Plays::operator= (Plays& ply)
{
	qtr = ply.returnQtr();
	min = ply.returnMin();
	off = ply.returnOff();
	def = ply.returnDeff();
	down = ply.returnDown();
	togo = ply.returnTogo();
	ydline = ply.returnydline();
	descriptionlist = ply.returndesc();
	relnum = ply.returnRele();
	callnum = ply.returnCalln();
	year = ply.returnYear();
	fileorder = ply.returnOrder();
}
void Plays::setQtr(int x)
{
	qtr = x;
}
void Plays::setMin(int x)
{
	min = x;
}
void Plays::setOff(string x)
{
	off = x;
}
void Plays::setDeff(string x)
{
	def = x;
}
void Plays::setDown(int x)
{
	down = x;
}
void Plays::setTogo(int x)
{
	togo = x;
}
void Plays::setYdline(int x)
{
	ydline = x;
}
void Plays::setDesc(string x)
{
	descriptionlist = x;
}
void Plays::setYear(int x)
{
	year = x;
}