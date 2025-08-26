#include "song.h"

using namespace std;

// removes garbage characters
void SkipBOM(std::ifstream& in)
{
	char test[3] = { 0 };
	in.read(test, 3);
	if ((unsigned char)test[0] == 0xEF &&
		(unsigned char)test[1] == 0xBB &&
		(unsigned char)test[2] == 0xBF)
	{
		return;
	}
	in.seekg(0);
}


// returns a clean string without any punctuations. This is done to lyrics and user
// text to make querying easier
static string toRemove = ",.!?'";
string cleanString(string& toClean) {
	bool addToClean;
	string cleanString = "";
	for (char let : toClean) {
		addToClean = true;
		for (char i : toRemove) {
			if (let == i) {
				addToClean = false;
			}
		}
		if (addToClean) {
			cleanString = cleanString + let;
		}
	}
	return cleanString;
}




// ------SONG FUNCTIONS------
Song::Song(string album, string song, ifstream& songFile) {
	albumName = album;
	songName = song;
	buildSongUnsorted(songFile);

	sortSong();
}


void Song::buildSongUnsorted(ifstream& songFile) {
	SkipBOM(songFile);
	string songInput = "";
	string songTotalLines = "";

	if (!songFile.is_open()) {
		cout << "closed";
	}

	// skips the first two lines of the song file -- the album and song title
	getline(songFile, songInput);
	getline(songFile, songInput);
	while (getline(songFile, songInput)) {
		lineCount++;
		songTotalLines = songTotalLines + songInput + " " + to_string(lineCount) + " ";
		// the line number is add to the end of each line in the cocatenated string
	}

	stringstream s(songTotalLines);
	songInput = "";
	while (s >> songInput) {
		songUnsorted.push_back(cleanString(songInput));
	}
}


void Song::sortSong() {
	for (int i = 0; i < songUnsorted.size(); i++) {
		string currWord = songUnsorted[i];
		transform(currWord.begin(), currWord.end(), currWord.begin(), ::tolower);
		songSorted.push_back(currWord);
		songUnsortedIndices.push_back(i);
	}

	sort(songUnsortedIndices.begin(), songUnsortedIndices.end(),
		[&](int i1, int i2) {return songSorted[i1] < songSorted[i2]; });
	sort(songSorted.begin(), songSorted.end());
}


string Song::printLine(int targetLineNumber) {
	if (targetLineNumber < 1 || targetLineNumber > lineCount) {
		cout << "invalid range";
	}

	// finds the end-of-line number indicator of the previous line and adds 1 to 
	// get the index of the first word in the target line
	int index = findWordIndex(to_string(targetLineNumber - 1));
	index++;

	string theLine = "";
	while (songUnsorted[index] != to_string(targetLineNumber)) { // while we are not at the end-of-line indicator for target line
		theLine = theLine + songUnsorted[index] + " ";
		index++;
	}
	return theLine;
}


int Song::findWordIndex(string targetWord) {
	return findWordIndexHelper(targetWord, 0);
}


int Song::findWordIndexHelper(string targetWord, int startingIndex) {
	transform(targetWord.begin(), targetWord.end(), targetWord.begin(), ::tolower);
	for (int i = startingIndex; i < totalWords(); i++) {
		transform(songUnsorted[i].begin(), songUnsorted[i].end(), songUnsorted[i].begin(), ::tolower);
		if (songUnsorted[i] == targetWord) {
			return i;
		}
	}

	return -1;
}


int Song::findWordIndexSorted(string targetWord) {
	transform(targetWord.begin(), targetWord.end(), targetWord.begin(), ::tolower);
	for (int i = 0; i < totalWords(); i++) {
		transform(songSorted[i].begin(), songSorted[i].end(), songSorted[i].begin(), ::tolower);
		if (songSorted[i] == targetWord) {
			return i;
		}
	}
	return -1;
}


string Playlist::wwReference(string userText) {
	string message = "no";
	string userTextCopy = userText;
	userTextCopy = cleanString(userTextCopy);
	vector<string> userTextToSearch;
	string wordInUserText = "";
	stringstream s(userTextCopy);
	while (s >> wordInUserText) {
		userTextToSearch.push_back(wordInUserText);
	}

	// starting searching at index 0
	int userTextToSearchIndex = 0;
	bool foundString = false;
	int currentSongIndex = 0;
	int indexOfTheFirstWordOfReferenceInSong = 0;
	while (!foundString && currentSongIndex < playlist.size()) {
		// only search if there are four words ahead of the word we are searching
		// if there are less then four words ahead and no reference has been found thusfar, then none will			
		// be found since we cannot get a string of five words
		userTextToSearchIndex = 0;
		while (userTextToSearchIndex + 4 < userTextToSearch.size() && !foundString) {
			queue<int> indicesOfWordInSong;
			
			int songWordIndex = 0; // begin search at the start of the song
			int referencedSongWordIndex_Sorted = playlist[currentSongIndex].findWordIndexSorted(userTextToSearch[userTextToSearchIndex]);
			if (referencedSongWordIndex_Sorted != -1) { // the current user's word occurs at least once in the current song
				songWordIndex = playlist[currentSongIndex].getUnsortedIndices()[referencedSongWordIndex_Sorted];
				indicesOfWordInSong.push(songWordIndex);
				
				// when a match is found between a word in the user's text and a word in the
				// current song, the alphabetically sorted song vector "songSorted" is used to
				// quickly find all other (if any) occurances of the same word in the song
				// the original positions of those words are referenced with "getUnsortedIndices"
				while (playlist[currentSongIndex].getSongSorted()[referencedSongWordIndex_Sorted + 1] == userTextToSearch[userTextToSearchIndex]) {
					referencedSongWordIndex_Sorted++;
					songWordIndex = playlist[currentSongIndex].getUnsortedIndices()[referencedSongWordIndex_Sorted];
					indicesOfWordInSong.push(songWordIndex);
				}
			}


			int cycles = 0;
			// if a string moves from one line in the song to the next, bypass the line counter element
			// by adding "lineCountCorrection" when calculating the index of the next word in the song
			int lineCountCorrection = 0;
			while (!indicesOfWordInSong.empty() && (cycles < 4)) {
				cycles++;
			
				int i = 0;
				int numberOfCurrWordOccurances = indicesOfWordInSong.size();
				// for every time the word to search for in the string matched a word in the song
				while (i < numberOfCurrWordOccurances) {
					int nextWordInUserTextIndex = userTextToSearchIndex + cycles;
					int nextWordInSongIndex = indicesOfWordInSong.front() + cycles + lineCountCorrection;
	
					// if the index of the current word in the song actually lands on the line counter element
					// at the end of a line, add 1 to the correction variable and skip to the next word
					vector<string> currSong = playlist[currentSongIndex].getSongUnsorted();
					if (all_of(currSong[nextWordInSongIndex].begin(), currSong[nextWordInSongIndex].end(), ::isdigit)) {
						lineCountCorrection++;
						nextWordInSongIndex++;
					}

					
					// for each occurance of the current user's word in the song, subsequent words
					// in the song are checked in an attempt to find a referenced string of length = 5
					string nextWordInSong = playlist[currentSongIndex].getSongUnsorted()[nextWordInSongIndex];
					transform(nextWordInSong.begin(), nextWordInSong.end(), nextWordInSong.begin(), ::tolower);
					if (userTextToSearch[nextWordInUserTextIndex] != nextWordInSong) {
						// remove the word if it doesn't match
						indicesOfWordInSong.pop();
						lineCountCorrection = 0;
					}
					else { // if they match, move the word to the end for the next cycle
						int tempCurrSongWordIndex = indicesOfWordInSong.front();
						indicesOfWordInSong.pop();
						indicesOfWordInSong.push(tempCurrSongWordIndex);
					}
					i++;
				}
			}
			// ends when the chain of matching user words in the song breaks or when the cycle >= 4,
			// indicating the five words in a row match (an accidental reference was found)


			if (indicesOfWordInSong.empty()) { // case 1: no reference -> search new word, bypassing bad ones
				if (cycles == 0) { // no subsequent song words matched the subsequent user words
					cycles++;
				}
				userTextToSearchIndex = userTextToSearchIndex + cycles; 
				// the next word to cross-reference should not include words already checked in partial 
				// references (substrings length < 5)
			}
			else { // case 2: loop broke because 5 matches were found (reference)
				foundString = true;
				indexOfTheFirstWordOfReferenceInSong = indicesOfWordInSong.front();
			}
		}


		if (!foundString) {
			currentSongIndex++; // begin cross-referencing the user's text with the next song in the playlist
		}
		else { 
			string thePhrase = "";
			for (int i = userTextToSearchIndex; i < userTextToSearchIndex + 5; i++) {
				thePhrase = thePhrase + " " + userTextToSearch[i];
			}
			message = thePhrase + ". " + thePhrase + "?\n";

			vector<string> referenceSong = playlist[currentSongIndex].getSongUnsorted();
			// calculating the line number of the reference (or of the first word in the reference if it takes up multiple lines)
			int lineNum = indexOfTheFirstWordOfReferenceInSong;
			while (!(all_of(referenceSong[lineNum].begin(), referenceSong[lineNum].end(), ::isdigit))) {
				lineNum++;
			}

			// when an accidental reference is made, the song lyrics before and after 
			// the reference (if they exist) should be displayed
			int lineBeforeNum = stoi(referenceSong[lineNum]) - 1;
			int lineAfterNum = stoi(referenceSong[lineNum]) + 1;
			if (lineBeforeNum > 0) {
				message = message + playlist[currentSongIndex].printLine(lineBeforeNum) + "\n";
			}
			message = message + playlist[currentSongIndex].printLine(lineBeforeNum + 1) + "\n";
			if (lineAfterNum < playlist[currentSongIndex].totalLines()) {
				message = message + playlist[currentSongIndex].printLine(lineAfterNum);
			}

			message = message + "\n\n";
			message = message + playlist[currentSongIndex].getName() + "\n" + playlist[currentSongIndex].getAlbum();
		}
	}
	return message;
}
// ----- END OF SONG FUNCTIONS -----






// ----- PLAYLIST FUNCTIONS -----
Playlist::Playlist(vector<string> files) {
	for (int i = 0; i < files.size(); i++) {
		songFiles.push_back(files[i]);
	}
	for (string file : songFiles) {
		ifstream currSongFile;
		currSongFile.open(file);
		string album, name;
		getline(currSongFile, album);
		getline(currSongFile, name);
		Song currSong(album, name, currSongFile);
		playlist.push_back(currSong);
		currSongFile.close();
	}
}

vector<Song> Playlist::getPlaylist() {
	return playlist;
}
// ----- END OF PLAYLIST FUNCTIONS -----


