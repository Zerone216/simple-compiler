#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class STT
{
private:
	vector<vector<char>> stt; //status trans table

public:
	void initStt();
	void deleteConment(ifstream &fin, ofstream &fout);
};

vector<char> vecnew(int size, char val)
{
	vector<char> charr(size, val);
	return charr;
}

//init status trans table
void STT::initStt()
{
	stt.push_back(vecnew(128, 0));
	stt.push_back(vecnew(128, 0));
	stt.push_back(vecnew(128, 2));
	stt.push_back(vecnew(128, 3));
	stt.push_back(vecnew(128, 3));
	stt.push_back(vecnew(128, 5));
	stt.push_back(vecnew(128, 5));
	stt.push_back(vecnew(128, 0));

	stt[0]['/'] = 1;
	stt[0]['"'] = 5;
	stt[1]['/'] = 2;
	stt[1]['*'] = 3;
	stt[1]['"'] = 5;
	stt[2]['\n'] = 7;
	stt[3]['*'] = 4;
	stt[4]['/'] = 7;
	stt[4]['*'] = 4;
	stt[5]['"'] = 0;
	stt[5]['\\'] = 6;
	stt[7]['/'] = 1;
	stt[7]['"'] = 5;
}

void STT::deleteConment(ifstream &fin, ofstream &fout)
{
	char ch;
	int state = 0;
	string line = "";

	while (fin.get(ch))
	{
		state = stt[state][ch]; //next state;
		line += ch;				//make a record of one line code;
		switch (state)
		{
		case 0:
			fout << line; //not comments, just write into a output file;
			line = "";	//reset the string line;
			break;

		case 7:
			line = ""; //delete the comment when the state equals to 7;
			if (ch == '\n')
				fout << "\r\n";
			break;
		}
	}
}

int main(int argc, char **argv)
{
	STT stt;
	stt.initStt();

	ifstream fin;
	fin.open(argv[1]);

	ofstream fout;
	fout.open(argv[2]);

	stt.deleteConment(fin, fout);

	fout.close();
	fin.close();

	return 0;
}
