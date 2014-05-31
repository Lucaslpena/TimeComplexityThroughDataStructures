#ifndef PLAYS_H
#define PLAYS_H
#include <string>
#include <cstring>
using namespace std;

class Plays
{
public:
	
	Plays();
	Plays(string x); //constructor passed line of play
	string PType(string description);
	//accessors below
	int returnQtr() const;
	int returnMin() const;
	string returnOff() const;
	string returnDeff() const;
	int returnDown() const;
	int returnTogo() const;
	int returnydline() const;
	string returndesc() const;
	float returnRele() const;
	int returnCalln() const;
	int returnYear() const;
	int returnOrder() const;
	//mutators below
	void setrelevance(float);
	void incCalln();
	void setOrder(int);
	void setQtr(int);
	void setMin(int);
	void setOff(string);
	void setDeff(string);
	void setDown(int);
	void setTogo(int);
	void setYdline(int);
	void setDesc(string);
	void setYear(int);

	
	Plays& operator= (Plays& ply);
	bool operator== (const Plays& ply) const
	{
		if (returnOrder() == ply.returnOrder())
			return true;
		else return false;
	}

private:
	int qtr;
	int min;
	string off;
	string def;
	int down;
	int togo;
	int ydline;
	string descriptionlist;
	float relnum;
	int callnum;
	int year;
	int fileorder;
};
#endif 