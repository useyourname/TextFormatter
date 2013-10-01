#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <cstdlib>

using namespace std;

int checkCommand(vector<string> v, string command, int sindex, int findex); //returns index of where command is found, else returns -1;
void printCenteredLine(string line, int N);
void printJustifiedLine(string line, vector<string> &word, int startIndex, int endIndex, int wordsPerLine, int N);
void raggedRight(int N, vector<string> &word, vector<string> &line, vector<int> &wordsPerLine, ifstream &input);

void print(vector<string> &line, vector<string> &word, vector<int> &wordsPerLine, int N, bool rr, bool rl, bool c, bool j, bool f, bool r);
void k(int lineNumber, vector<string> &line, vector<string> &word, vector<int> &wordsPerLine, int N, bool rr, bool rl, bool c, bool j, bool f, bool r);
void s(string fnord, vector<string> &line, vector<string> &word, vector<int> &wordsPerLine, int N, bool rr, bool rl, bool c, bool j, bool f, bool r);

int main(){
	bool rr = true;
	bool rl = false;
	bool c = false;
	bool j = false;
	bool f = true;
	bool r = false;
	int N;

	if( !(cin >> N) || N <= 0){
		cerr << "Error, line length must be positive." << endl;
		return 0;
	}
	cin.get();

	string textFileName;
	cin >> textFileName;
	cin.get();	

	ifstream input(textFileName.c_str());
	if(input.fail()){
		cerr << "Error, can't open specified text file." << endl;
		return 0;	
	}

	vector<string> word;
	vector<string> line;	
	vector<int> wordsPerLine;

	raggedRight(N, word, line, wordsPerLine, input);
	string buffer = "";

	while(cin >> buffer){
		if(!buffer.compare("q")){
			exit(0);
		}

		if(!buffer.compare("p")){
			print(line, word, wordsPerLine, N, rr, rl, c, j, f, r);				
		}

		if(!buffer.compare("k")){ //IF YOU TYPE K AND THEN A LETTER AND THEN PRESS ENTER, THE ERROR MESSAGE POPS UP BEFORE EOF
			int lineNumber = 0;
			if( !(cin >> lineNumber) ){
				// illegalCommand = true;
				// cerr << "Error, illegal command." << endl;
				cout << endl;
				exit(0);
			}
			// k.push_back(lineNumber);

			//print out the line
			else if(lineNumber >= 1 && lineNumber - 1 < line.size()){
				k(lineNumber, line, word, wordsPerLine, N, rr, rl, c, j, f, r);
			}
			else{
				cout << endl;
			}
		}

		else if(!buffer.compare("s")){
			string fnord = "";
			cin >> fnord;
			// s.push_back(temp);
			s(fnord, line, word, wordsPerLine, N, rr, rl, c, j, f, r);
		}

		//checks if command is illegal as user is inputting them
		else if(buffer.compare("rr") && buffer.compare("j") && buffer.compare("rl") && buffer.compare("c") && buffer.compare("f") &&
		 buffer.compare("r") &&	buffer.compare("g") && buffer.compare("p") && buffer.compare("q") && buffer.compare("k") &&
		  buffer.compare("s")){
			// illegalCommand = true;
			cerr << "Error, illegal command." << endl;
			exit(0);		
		}

		if(!buffer.compare("rl")){
			rl = true;
			rr = j = c = false;
		}
		else if(!buffer.compare("j")){
			j = true;
			rr = rl = c = false;
		}
		else if(!buffer.compare("c")){
			c = true;
			rr = rl = j = false;
		}
		else if(!buffer.compare("rr")){
			rr = true;
			rl = j = c = false;
		}

		if(!buffer.compare("f")){
			f = true;
			r = false;
		}
		else if(!buffer.compare("r")){
			r = true;
			f = false;
		}
	}//end of while(take in command)*/
	cin.get();
	exit(0);
}

int checkCommand(vector<string> v, string command, int sindex, int findex){
	for(int i = sindex; i <= findex; i++){
		if(!v.at(i).compare(command)){
			return i;
		}
	}
	return -1;
}

void printCenteredLine(string line, int N){
	int emptySpaces = N - line.length();
	int leftSpaces = (int) ceil((float)emptySpaces / 2.f);

	for(int i = 1; i <= leftSpaces; i++){
		cout << " ";
	}

	cout << left << setw(N - leftSpaces) << line << endl;
}//end of printCentered line


void printJustifiedLine(string line, vector<string> &word, int startIndex, int endIndex, int wordsPerLine, int N){
	if(wordsPerLine == 1){
		cout << left << setw(N) << word.at(startIndex) << endl;
		return;
	}

	int emptySpaces = N - line.length();
	int spacesSpreadOut = emptySpaces / (wordsPerLine - 1);
	int extraSpaces = emptySpaces % (wordsPerLine - 1);

	cout << word.at(startIndex);
	for(int i = startIndex + 1; i <= endIndex; i++){
		cout << " ";
		for(int x = 1; x <= spacesSpreadOut; x++){
			cout << " ";
		}

		if(i < extraSpaces + startIndex + 1){
			cout << " ";
		}

		cout << word.at(i);
	}
	cout << endl;
}//end of printJustifiedLine

void raggedRight(int N, vector<string> &word, vector<string> &line, vector<int> &wordsPerLine, ifstream &input){
	string buffer = "";
	int cursor = 0; 
	int lineCounter = 0; 
	line.push_back(""); 
	wordsPerLine.push_back(0);

	while(input >> buffer){
		word.push_back(buffer);
	}
	input.get();

	if(word.size() == 1){
		word.at(0) = word.at(0).substr(0, N);
		line.at(0).append(word.at(0));
		wordsPerLine.at(0) = 1;	
		return;
	}	

	for(int i = 0; i < word.size(); i++){
		if(word.at(i).length() >= N){ //if the word is huge
			if(cursor == 0){ //if you're at the beginning of the line just print the word
				word.at(i) = word.at(i).substr(0, N);
				line.at(lineCounter).append(word.at(i).substr(0, N));
				wordsPerLine.at(lineCounter)++;
				line.push_back("");
				wordsPerLine.push_back(0);
				lineCounter++;
			}
			else{ //if ur at the middle of a line just go to the next line and print the big word
				word.at(i) = word.at(i).substr(0, N);
				line.push_back(word.at(i).substr(0, N));
				wordsPerLine.push_back(1);
				line.push_back("");
				wordsPerLine.push_back(0);
				lineCounter += 2;
				cursor = 0;
			}
		}
		else if(cursor + word.at(i).length() <= N){ //if there's room for atleast the current word
			line.at(lineCounter).append(word.at(i));
			wordsPerLine.at(lineCounter)++;

			cursor += word.at(i).length();

			if( (i <= word.size() - 2) && cursor + word.at(i+1).length() + 1 <= N){ //if there's room for another word print a space
				line.at(lineCounter).append(" ");
				cursor++;
			}
			else{	//since there's no room for another word after the one we just printed, just end the line
				line.push_back("");
				wordsPerLine.push_back(0);
				lineCounter++;
				cursor = 0;
			}
		}
		else{ // there's no room to print even the current word so just end the line by decrementing i so that we dont miss the current word which wasnt printed
			line.push_back("");
			wordsPerLine.push_back(0);
			lineCounter++;
			cursor = 0;
			i--;
		}
	}
	wordsPerLine.pop_back();
	line.pop_back();
}//end of ragged right

void print(vector<string> &line, vector<string> &word, vector<int> &wordsPerLine, int N, bool rr, bool rl, bool c, bool j, bool f, bool r){
	if(rr){
		if(f){		
			for(int i = 0; i < line.size(); i++){
				cout << line.at(i) << endl;
			}
		}
		else if(r){
			for(int i = line.size() - 1; i >= 0; i--){
				cout << line.at(i) << endl;
			}
		}		
	}	

	if(rl){
		if(f){		
			for(int i = 0; i < line.size(); i++){
				cout << right << setw(N) << line.at(i) << endl;
			}
		}
		else if(r){
			for(int i = line.size() - 1; i >= 0; i--){
				cout << right << setw(N) << line.at(i) << endl;
			}
		}		
	}	

	if(c){
		if(f){		
			for(int i = 0; i < line.size(); i++){
				printCenteredLine(line.at(i), N);
			}
		}
		else if(r){
			for(int i = line.size() - 1; i >= 0; i--){
				printCenteredLine(line.at(i), N);				
			}
		}			
	}	

	if(j){
		if(f){		
			int cursor = 0; 
			for(int i = 0; i < line.size(); i++){
				printJustifiedLine(line.at(i), word, cursor, cursor + wordsPerLine.at(i) - 1, wordsPerLine.at(i), N);
				cursor += wordsPerLine.at(i);
			}
		}
		else if(r){
			int cursor = word.size() - 1; 
			for(int i = line.size() - 1; i >= 0; i--){
				printJustifiedLine(line.at(i), word, cursor - wordsPerLine.at(i) + 1, cursor, wordsPerLine.at(i), N);
				cursor -= wordsPerLine.at(i);
			}
		}		
	}	
}//end of print


void k(int lineNumber, vector<string> &line, vector<string> &word, vector<int> &wordsPerLine, int N, bool rr, bool rl, bool c, bool j, bool f, bool r){
	if(rr){
		if(f){		
			cout << line.at(lineNumber - 1) << endl;
		}
		else if(r){
			cout << line.at(line.size() - lineNumber) << endl;
		}		
	}	

	if(rl){
		if(f){		
			cout << right << setw(N) << line.at(lineNumber - 1) << endl;
		}
		else if(r){
			cout << right << setw(N) << line.at(line.size() - lineNumber) << endl;
		}		
	}	

	if(c){
		if(f){		
			printCenteredLine(line.at(lineNumber - 1), N);
		}
		else if(r){
			printCenteredLine(line.at(line.size() - lineNumber), N);
		}			
	}	

	if(j){
		if(f){		
			int sindex = 0;
			for(int i = 0; i < lineNumber - 1; i++){
				sindex += wordsPerLine.at(i);
			}			
			printJustifiedLine(line.at(lineNumber - 1), word, sindex, sindex + wordsPerLine.at(lineNumber - 1) - 1, wordsPerLine.at(lineNumber - 1), N);
		}
		else if(r){
			int sindex = 0;
			int reverseLineNumber = line.size() - lineNumber + 1;
			for(int i = 0; i < reverseLineNumber - 1; i++){
				sindex += wordsPerLine.at(i);
			}
			printJustifiedLine(line.at(reverseLineNumber - 1), word, sindex, sindex + wordsPerLine.at(reverseLineNumber - 1) - 1, wordsPerLine.at(reverseLineNumber - 1), N);
		}
	}	
}//end of k

void s(string fnord, vector<string> &line, vector<string> &word, vector<int> &wordsPerLine, int N, bool rr, bool rl, bool c, bool j, bool f, bool r){
	bool stuffPrinted = false;
	if(rr){
		if(f){		
			for(int i = 0; i < line.size(); i++){
				if(line.at(i).find(fnord) != std::string::npos){
					cout << line.at(i) << endl;
					stuffPrinted = true;
				}
			}
		}
		else if(r){
			for(int i = line.size() - 1; i >= 0; i--){
				if(line.at(i).find(fnord) != std::string::npos){
					cout << line.at(i) << endl;
					stuffPrinted = true;
				}
			}
		}		
	}	

	if(rl){
		if(f){		
			for(int i = 0; i < line.size(); i++){
				if(line.at(i).find(fnord) != std::string::npos){
					cout << right << setw(N) << line.at(i) << endl;
					stuffPrinted = true;
				}
			}
		}
		else if(r){
			for(int i = line.size() - 1; i >= 0; i--){
				if(line.at(i).find(fnord) != std::string::npos){
					cout << right << setw(N) << line.at(i) << endl;
					stuffPrinted = true;
				}
			}
		}		
	}	

	if(c){
		if(f){		
			for(int i = 0; i < line.size(); i++){
				if(line.at(i).find(fnord) != std::string::npos){
					printCenteredLine(line.at(i), N);
					stuffPrinted = true;
				}
			}
		}
		else if(r){
			for(int i = line.size() - 1; i >= 0; i--){
				if(line.at(i).find(fnord) != std::string::npos){
					printCenteredLine(line.at(i), N);
					stuffPrinted = true;
				}				
			}
		}			
	}	

	if(j){
		if(f){		
			int cursor = 0; 
			for(int i = 0; i < line.size(); i++){
				if(line.at(i).find(fnord) != std::string::npos){
					printJustifiedLine(line.at(i), word, cursor, cursor + wordsPerLine.at(i) - 1, wordsPerLine.at(i), N);
					stuffPrinted = true;
				}
				cursor += wordsPerLine.at(i);
			}
		}
		else if(r){
			int cursor = word.size() - 1; 
			for(int i = line.size() - 1; i >= 0; i--){
				if(line.at(i).find(fnord) != std::string::npos){
					printJustifiedLine(line.at(i), word, cursor - wordsPerLine.at(i) + 1, cursor, wordsPerLine.at(i), N);
					stuffPrinted = true;
				}
				cursor -= wordsPerLine.at(i);
			}
		}		
	}

	if(!stuffPrinted){
		cout << endl;
	}
}//end of s




