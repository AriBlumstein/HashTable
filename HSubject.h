#pragma once
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;
#include "HashTable.h"

const int MAX = 1000;



class HSubject :public HashTable<list<string>, string>
{
	//private:
	int key(string s)const { return (int)s[0] + (int)s[1] + (int)s[s.length() - 1]; }

public:
	HSubject(int n) :HashTable <list<string>, string>(n) {}
	int h1(string s)const override { return key(s) % size; }
	int h2(string s)const override { return (key(s) % (size - 1) + 1) % size; }
	void printS(string ky)const;
	void printN(string ky, int N)const;
	void print()const override;
	void startNewTable();
	void addSubjectAndTitle(string s, string t);
	int remove(string key) override;
	
};
