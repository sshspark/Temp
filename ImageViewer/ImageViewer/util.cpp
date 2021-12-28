#include "stdafx.h"
#include "util.h"

#include <set>

string strip(const string str, string wc)
{
	int length = str.size();
	int i = 0; 
	int first_pos = 0;
	int last_pos = length - 1;
	set<char> white_char; 
	for(i = 0; i<wc.size(); i++){
		white_char.insert(wc[i]); 
	}

	// 앞에서 가면서 [wc]에 없는 것이 나오는 첫 번째 위치 탐색. 
	for(i = 0; i<length; i++){
		// white character가 아니면 계속 탐색. 
		if(white_char.find(str[i]) != white_char.end()) continue; 
		if(white_char.find(str[i]) == white_char.end()){
			first_pos = i;
			//cout << "f" << first_pos << endl; 
			break;
		}
	}
	// 뒤에서 앞으로 오면서 [wc]에 없는 것이 나오는 첫 번째
	// 위치 탐색. 
	for(i = length - 1; i>=0; i--){
		if(white_char.find(str[i]) != white_char.end()) continue; 
		if(white_char.find(str[i]) == white_char.end()){
			last_pos = i; 
			break; 
		}
	}

	if(first_pos > last_pos){
		first_pos = 0; 
		last_pos = length - 1;
	}

	return str.substr(first_pos, last_pos - first_pos + 1); 
}

double string2double::operator ()(const string& str)
{
	return atof(str.c_str()); 
}
string string2string::operator ()(const string& str)
{
	return str; 
}
int string2int::operator ()(const string& str)
{
	return atoi(str.c_str()); 
}


