// ConsoleApplication21.cpp: определяет точку входа для консольного приложения.
//

// SortBigFiles.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <list>
#include <iterator>
#include <algorithm>
#include <io.h>
#include <stdlib.h>
#include <sstream>


using namespace std;
/*
class fileworking {

public:

private:
fstream myfile;//файл
};
*/



template <typename T>
class SortFile {
public:
	auto Open_Division()->const void;//разделение на блоки исходного файла в соответствии с памятью в буфере
	auto CreateNewFile(int num_)->string;// create Block_File

	SortFile(string name);//открытие файла и вызов open_division
	auto isOpened()->bool;//проверка открылся ли файл
	auto FileSize(string s)->int;//получаем размер файла
	auto Sort(const string file_name)->void;
	auto make_file(const string file_name)->void;


private:
	size_t size_avail_buff;//доступная операционная память 
	fstream file;//файл
	string main_file;//имя исходного файла
	string temprory_files;
	size_t buff;//размер буфера
	list<string> lines;

};




template<typename T>
auto SortFile<T>::Sort(const string file_name)->void {
	string line, temp_line, main_line;
	fstream temp(file_name.c_str());
	while (!temp.eof()) {
		getline(temp, line);
		temp_line = line.substr(0, line.find(' '))+"\n";
		main_line = line;
		lines.push_back(temp_line);
	}
	lines.sort();
	temp.close();
	ofstream my(file_name.c_str(), ios::out);
	copy(lines.begin(), lines.end(), ostream_iterator<string>(my, ""));
	my.close();
	lines.clear();
}


template<typename T>
SortFile<T>::SortFile(string name) : file(name.c_str()), main_file(name), buff(100) {
	if (isOpened() == true) Open_Division();
}

template <typename T>
auto SortFile<T>::isOpened()->bool {
	return file.is_open();
}


template <typename T>
auto  SortFile<T>::FileSize(string s)->int {
	long fsize;
	FILE *o = fopen(s.c_str(), "rb");
	fsize = _filelength(_fileno(o));
	fclose(o);
	return fsize;
}

template<typename T>
auto SortFile<T>::make_file(const string file_name)->void
{
	
	ofstream ofile(file_name.c_str());
	copy(lines.begin(), lines.end(), ostream_iterator<string>(ofile,""));
	ofile.close();
	lines.clear();
	Sort(file_name);
}



template<typename T>
auto SortFile<T>::Open_Division()->const void {
	size_t i = 0;
	size_t SizeOfList=0;
	string line, temp_line;
	while (!file.eof()) {
		
		getline(file, line);
		temp_line = line.substr(0, line.find('\n'));
		SizeOfList += temp_line.size()+2;
		
		if (SizeOfList <= 100) {
			lines.push_back(temp_line);
			lines.push_back("\n");
		}
		else {
			lines.pop_back();
			i++;
			make_file(to_string(i)+".txt");
			lines.push_back(temp_line+"\n");
			SizeOfList = temp_line.size()+2;
			
		}
	}
	
	file.close();
};



int file_exist(const char *filename)
{
	struct stat   buffer;
	return (stat(filename, &buffer) == 0);
}

template<typename T>
auto SortFile<T>::CreateNewFile(int num_)->string{
	
	
	string str2 = "Block_" + to_string(num_) + ".txt";
	
		ofstream fout(str2);
		fout.close();
	
		return str2;
	
}


int main()
{
	SortFile<int> newfile("names.txt");

	system("pause");
	return 0;

}


