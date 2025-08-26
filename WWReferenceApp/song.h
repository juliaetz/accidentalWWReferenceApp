#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <queue>
#include <numeric>

using namespace std;


class Song {
private:
	string file;
	string songName;
	string albumName;
	vector<string> songUnsorted;
	vector<string> songSorted;
	vector<int> songUnsortedIndices;
	int lineCount = 0;
	Song() {}
	// song lyrics will be stored as both unsorted (the original order) and sorted
	// (in alphabetical order). The unsorted song data will be used to print lyrics
	// while the sorted song data will be used to quickly find all the instances of a
	// word
	void buildSongUnsorted(ifstream& file);
	void sortSong();
	int findWordIndexHelper(string w, int startingIndex);
public:
	Song(string album, string song, ifstream& songFile);
	
	string getName() { return songName; };
	string getAlbum() { return albumName; };
	vector<string> getSongUnsorted() { return songUnsorted; };
	vector<string> getSongSorted() { return songSorted; };
	vector<int> getUnsortedIndices() { return songUnsortedIndices; };
	
	string printLine(int i);
	int totalWords() { return songUnsorted.size(); };
	int totalLines() { return lineCount; };
	string printWord(int num);
	int findWordIndex(string w);
	int findWordIndexSorted(string w);
};




class Playlist {
private:
	vector<Song> playlist;
	vector<string> songFiles;
	Playlist() {}
public:
	// constructor that takes in file, makes new song element and calls buildSongU
	Playlist(vector<string> f);
	string wwReference(string str);
	vector<Song> getPlaylist();
};