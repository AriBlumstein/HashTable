#include "HSubject.h"


//method that prints the titles of discussions of the subject passed as a parameter. if the subject was not in the hash table, it prints nothing 
void HSubject::printS(string ky)const
{
	list<string>* curlist = entryData(ky);

	//check if its NULL, if it is, just return
	if (!curlist)
	{
		cout << "ERROR\n";
		return;
	}

	//we found the subject, lets print the titles
	cout << "Subject " << ky << ' ' << curlist->size() << ' ' << "topics:\n";

	for_each(curlist->begin(), curlist->end(), [](string& cur)->void {cout << cur << ' '; });
	cout << endl;

}

//method that prints out the first N titles of a specific subject (prints up to N, if N>size, then it will only print size
void HSubject::printN(string ky, int N)const
{
	list<string>* curlist = entryData(ky);

	//check that we found the key in the hashtable, if not return
	if (!curlist)
	{
		cout << "ERROR\n";
		return;
	}

	//iterate through list

	int x = 0; //to deal with number we are supposed to print
	for (list<string>::iterator cur = curlist->begin(); cur != curlist->end()&& x < N; ++cur, ++x) // stops the end of the list or when we printed N items, whichever comes first
	{
		cout << *cur << ' ';
	}

	cout << endl;

}

//method that prints all subjects with all their titles in lexographic order
void HSubject::print()const
{   
	cout << "All subjects and titles:\n";

	//lets create a seperate vector to deal with sorting, reason for using vector is to give us something with random access iterators for sort
	vector<Item<list<string>, string>> sorted;

	//only push onto the vector the places that are full
	for (int x = 0; x < size; x++)
	{
		if (arr[x].flag == full)
		{
			sorted.push_back(arr[x]);
		}
	}

	//let us use the sort alogorithm 
	sort(sorted.begin(), sorted.end(), [](Item<list<string>, string>& first, Item<list<string>, string>& last)->bool {return first.key < last.key; });


	//now lets print everything
	for_each(sorted.begin(), sorted.end(), [](Item<list<string>, string>& cur)->void
		{
			cout << cur.key << ": ";
			
			//use inner for_each for the list itself
			for_each(cur.data.begin(), cur.data.end(), [](string& dat)->void
				{
					cout << dat << ' ';
				});

			cout << endl;
		});

	sorted.clear();

	/*
	//lets iterate throughout all of the  hash table and find where it's marked as full
	for (int x = 0; x < size; ++x)
	{
		
		
		//check the current index is not deleted or empty
		if (arr[x].flag == empty || arr[x].flag == deleted)
		{
			continue;
		}

		//now we can print
		cout << arr[x].key << ": ";

		for_each(arr[x].data.begin(), arr[x].data.end(), [](string& cur)->void {cout << cur << ' '; });
		cout << endl;

	}
	 */
}

//method that starts a new hash table, clears all lists, assigns everything to empty
void HSubject::startNewTable()
{
	for (int x = 0; x < size; x++)
	{
		//clear the list and set the flag to empty
		arr[x].data.clear();
		arr[x].flag = empty;
	}
}

//method that adds a subject and title to the hash table, is the subject already exists, we add the subject to that list, if not we make a new entry
void HSubject::addSubjectAndTitle(string s, string t)
{
	int index = search(s);

	//if its not negative 1, pushfront onto list
	if (index != -1)
	{
		arr[index].data.push_front(t);
		return;
	}

	//now we need to add it
	list<string> newlist;
	
	newlist.push_front(t);

	add(s, newlist);

	return;
}

//remove method, removes data from the hash table based on the key
//will use the parent class method, but here we will be able to save memory
int HSubject::remove(string key)
{
	//get the index that was removed from the parent class remove function
	int index = HashTable::remove(key);

	//if the index returned is greater than -1, we can clear the list to save memory
	if (index > -1)
	{
		arr[index].data.clear();
	}

	return index;
}
