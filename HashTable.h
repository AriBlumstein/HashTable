#pragma once
#include <iostream>
#include <cmath>
using namespace std;



template <typename T, typename K>
class HashTable
{
protected:

	enum state { empty, full, deleted };
	template <typename U, typename V>
	class Item
	{
	public:
		U data;
		V key;
		state flag;
		Item() {}
		Item(U d, V  k, state f) { data = d; key = k; flag = f; }
	};


	int size;
	Item<T, K>* arr;
	bool prime(int n);
	int hash(K key, int i)const;
	virtual int h1(K key)const = 0;
	virtual int h2(K key)const = 0;
public:
	HashTable(int m = 10);
	~HashTable();
	void add(K& key, T& dat);
	virtual int remove(K key);
	int search(K key)const;
	T* entryData(K i)const
	{
		int ind = search(i);
		if (ind == -1)
			return NULL;
		else
			return &(arr[ind].data);
	}
	void virtual print()const=0; //must be pure virtual, no real way to print a unknown class
};


//constructor, recieves a int as the starting size, will set the size to the first number greater than or equal to the int passed
template <class T, class K>
HashTable<T, K>::HashTable(int _size)
{
	for(int x= _size;; ++x)
	{
		if (prime(x))
		{
			size = x;
			arr = new Item<T, K>[size];
			
			//now we want to say that all the items in arr are empty 
			for (int y = 0; x < size; ++y)
			{
				arr[y].flag = empty;
			}
			break;
		}
	}
}

//method to determine if a number is prime, recieves a int, if it is prime it returns true, else false
template <class T, class K>
bool HashTable<T, K>::prime(int num)
{
	//lets first check if the number is <=1, if it is, the number is not prime for our purposes
	if (num <= 1)
	{
		return false;
	}

	//we need to check if the squareroot is a multiple of the number passed if it is, the number is not a prime number
	for (int x = 2; x <= sqrt(num); ++x)
	{
		if (!(num % x))
		{
			return false;
		}
	}
	
	//we exited the for loop, the number must be prime 
	return true;
}

//method that returns the position in the table for a key K with a step (int)i
template <class T, class K>
int HashTable<T, K>::hash(K key, int i)const
{   
	//use the h1 and step h2 multiplied by i
	return (h1(key) + (i * h2(key)))%size;
}


//destructor for hashtable, deletes dynamic area
template <class T, class K>
HashTable<T, K>::~HashTable()
{
	delete[] arr;
	arr = NULL;
}

//method to add a new entry to a table, only adds if the table is not full (i.e., we eventually find a place that has a flag of empty or deleted)
template <class T, class K>
void HashTable<T, K>::add(K& key, T& dat)
{
	//for loop that will use the the hash function to return a palce in the table for the item, it will do so up to 'size' times
	//will only insert the key into a place that is marked deleted or empty
	int check;
	
	for (int x = 0; x < size; ++x)
	{
		check = hash(key, x);
		if (arr[check].flag == deleted || arr[check].flag == empty)
		{
			arr[check].key = key;
			arr[check].data = dat;
			arr[check].flag = full;
			return;
		}
	}

}

//method to search for a given key in the table, returns the index that key is in (only if at the index we did not have a delete), otherwise, we returns -1
template <class T, class K>
int HashTable<T, K>::search(K key)const
{
	int check;
	int i = 0;

	//continue checking until we find a item with a state of empty or i=size
	do
	{
		check = hash(key, i);

		if (arr[check].key == key)
		{
			//check if it was deleted, if it was, return -1
			if (arr[check].flag == deleted)
			{
				return -1;
			}

			//at this point we found what we were looking for
			return check;
		}

		++i;

	} while (arr[check].flag != empty && i < size);


	//at this point we went over all of arr and didn't find our key 
	return -1;
}

//method that removes an entry with a given key from the table, sets its flag to deleted, returns the index of arr that was deleted
template<class T, class K>
int HashTable<T, K>::remove(K key)
{
	int check;
	int i = 0;

	//continue checking until we find a item with a state of empty or i=size
	do
	{
		check = hash(key, i);

		if (arr[check].key == key)
		{
			//set the flag to deleted
			arr[check].flag = deleted;
			return check;
		}

		++i;

	} while (arr[check].flag != empty && i < size);


	//at this point we went over all of arr and didn't find our key 
	return -1;
	
}





