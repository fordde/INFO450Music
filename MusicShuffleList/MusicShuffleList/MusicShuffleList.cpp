// MusicShuffleList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class MusicShuffle
{
private:


	int counter;
	string Artist;
	string Song;
	MusicShuffle * nextEntry;

public:
	class MusicShuffle() { Artist = ""; Song = ""; counter = 0; }
	void setMusic(string a, string s, int thecounter) { Artist = a; Song = s; counter = thecounter; }
	void showArtist() { cout << "Artist: " + Artist; }
	void showSong() { cout<<"Song: " + Song << endl; }
	
	friend class MusicShuffleList;
};
class MusicShuffleList
{
private:
	int check=0;
	int filesize;
	MusicShuffle * beginning; 
	MusicShuffle * end;
public:
	MusicShuffleList() { beginning = NULL; end = NULL; }
	int returnCheck() { return check; }
	int ReturnFileSize(string filename) { ifstream infile(filename, ios::in); while (!infile.eof()) { filesize++; } return filesize; }
	void Play(MusicShuffle * playsong) { cout << "Play " + playsong->Song << endl; }
	int Quit(MusicShuffle * quitsong) { quitsong->counter = -3; return -3; }
	MusicShuffle * Skip(int skip) {
		MusicShuffle *temp;
		temp = beginning;

		while (temp != NULL && temp->counter < skip)
		{
			temp = temp->nextEntry;
		}
		return temp;
		
	}
	int getList(string filename) 
	{
		
		string artist, song;
		int acounter=1;
		ifstream infile(filename, ios::in);
		if (!infile)
		{
			cout << "File could not be opened for reading" << endl;
			return -1;
		}


		while (!infile.eof())
		{

			getline(infile, artist, ',');
			if (!artist.empty())
			{
				getline(infile, song);
				

				MusicShuffle * newmusic = new MusicShuffle();
				newmusic->setMusic(artist, song, acounter);
				
				Insert(newmusic);
				
				acounter++;
			}
		}

		infile.close();
		return 0;
		
		
	}
	void Insert(MusicShuffle * newEntry) { if (beginning == NULL) { beginning = newEntry; end = newEntry; } else { end->nextEntry = newEntry; end = newEntry; } 
	}
	void Delete(int num) 
	{
		MusicShuffle *temp = beginning;
		if (temp == NULL) { cout << "= Music can not be deleted from an empty list" << endl; }
		if (beginning->counter == num) {
			if (beginning = end) { beginning = NULL; end = NULL; }
			else  beginning = beginning->nextEntry;
			delete temp;
		}
		while (temp != NULL) {
			if (temp->nextEntry && (temp->nextEntry)->counter == num) {
				if (temp == temp->nextEntry) {
					end = temp; MusicShuffle* one = temp->nextEntry; temp->nextEntry = (temp->nextEntry)->nextEntry; delete one;
				}
			}
			temp = temp->nextEntry;
		}
	}
	int displayList(string filename) 
	{
		
		string choice;
		
		string skipvalue;

		MusicShuffle *temp;
		temp = beginning;

		cout << "Music List" << endl;
		cout << " " << endl;
		


		if (temp == NULL)
		{
			cout << "list is empty " << endl;
			return 0;
		}
	
		int skipcondition = end->counter;


      
		
			while ((temp != NULL) && (temp->counter != 0))
			{
				cout << "Current Artist and Song on this line are" << endl;
				temp->showArtist();
				temp->showSong();

				cout << "would you like to play, skip, delete or quit ";
				getline(cin, choice);
				if (choice == "q") { Quit(temp); }
				if (choice == "s") { cout << "How many times would you like to skip"; getline(cin, skipvalue);   int askipvalue = stoi(skipvalue); int theskipvalue = (temp->counter) + askipvalue; if (skipcondition > theskipvalue) { cout << "Skip happend from " + temp->Song; temp = Skip(theskipvalue); } else { cout << "Could not preform skip would you like to quit" << endl; getline(cin, choice); if (choice != "n" && choice != "N") { Quit(temp); } else { cout << " The listing will continue" << endl; cout << " " << endl; } } }
				if (choice == "d") { Delete(temp->counter); cout << " " << endl;}
				if (choice == "p") { Play(temp); cout << " " << endl; }

				if (temp->counter == -3)
				{
					return -3;
				}
				else
				{
					temp = temp->nextEntry;
				}

			}
		
		return -3;
	}
	
	void freeMemory() 
	{
		MusicShuffle *temp = beginning;
		while (temp != NULL)
		{
			beginning = temp->nextEntry;
			delete temp;
			temp = beginning;
		}
	}

};
int main()
{
	int gama = 0;
	string choice;
	string afilename = "c:\\users\\mrdar\\desktop\\MyMusic.txt";
	MusicShuffleList  a; 

	a.getList(afilename);

	while (gama != -4) {
		cout << "Would you like to begin the shuffle or end entire shuffle (y to beginning and any other letter to end )" << endl;
		getline(cin, choice);
		cout << " " << endl;

		if (choice == "y" || choice == "Y")
		{
			a.displayList(afilename);
			gama = -3;
		}
		else { gama = -4; }
	}
	
	a.freeMemory();
	return 0;
}

