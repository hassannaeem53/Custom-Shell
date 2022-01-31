#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<iostream>
#include <string>
using namespace std;
//Muhammad Hassan Naeem


char** token(char* tempp, int& wordcount) {   //THIS FUNCTION TOKENIZES USER QUERY AND RETURN A 2D ARRRAY WITH WORDCOUNT(NO OF WORDS)
	int size = strlen(tempp);
	wordcount = 0;
	for (int i = 0; i < size; i++) {
	
		if (tempp[i] == 32) {
			wordcount++;
		}
		
	}
	
	wordcount = wordcount + 1;
	char** token;
	token = new char* [wordcount+1];
	int letters = 0;
	int m = 0;

	for (int j = 0; j < wordcount; j++) {
		letters = 0;
		for (int i = m; tempp[i] != ' ' && tempp[i] != '\0'; i++) {
			letters++;
			m++;

		}
		m++;

		if (letters != 0) {
			token[j] = new char[letters + 1];
		}
	}
	m = 0;
	int l = 0;
	int s = 0;
	for (int i = 0; i < wordcount; i++) {
		for (l = s; tempp[l] != ' ' && tempp[l] != '\0'; l++, m++) {
			token[i][m] = tempp[l];

		}
		token[i][m] = '\0';

		m = 0;
		l++;
		s = l;
	}
	token[wordcount]=NULL;
	return token;
}

int main(){
char arr[256];
while(strcmp(arr,"exit")!=0){
	cout<<"Hassan's Shell: ";
	cin.getline(arr,256);
	int cpid=fork();
	if (cpid==0){
		//child process

		int words=0;

		char** tokenized = token(arr, words);

		if(execvp(tokenized[0],tokenized)==-1){
		_exit(0);
		
		}
		


	}

	else if(cpid>0){
	//parent process
		wait(NULL);

	}
}
return 0;

}
