#include <iostream>
#include <fstream>
#include <streambuf>
#include <sstream>
using namespace std;

/* ������ 12 
���� ���������� ���� f. �������� � ����� ��� ���������� 
����� � ���� ��������� ���������� �������� � ���� g. */

int main()
{
	ifstream file;
	file.open("file.txt");
	
	int pos = 0;
	string buffer, delimiter, result;
	delimiter = " ";
	
	stringstream strStream;
	strStream << file.rdbuf();
	buffer = strStream.str();

	string token;
	while ((pos = buffer.find(delimiter)) != string::npos) {
		token = buffer.substr(0, pos);
		
		if (token.length() < 2)
		{
			token = "";
			
		}
		
		result.append(token);
		if (token != "")
		{
			result.append(" ");
		}
		buffer.erase(0, pos + delimiter.length());
	}
	cout << result;

	ofstream resultFile;
	resultFile.open("text_edit.txt");
	resultFile << result;
	
	file.close();
	resultFile.close();
}