#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <string>
using namespace std;

//Muhammad Hassan Naeem 


char **token(char *tempp, int &wordcount)
{ //THIS FUNCTION TOKENIZES USER QUERY AND RETURN A 2D ARRRAY WITH WORDCOUNT(NO OF WORDS)
	int size = strlen(tempp);
	wordcount = 0;
	for (int i = 0; i < size; i++)
	{

		if (tempp[i] == 32)
		{
			wordcount++;
		}
	}

	wordcount = wordcount + 1;
	char **token;
	token = new char *[wordcount + 1];
	int letters = 0;
	int m = 0;

	for (int j = 0; j < wordcount; j++)
	{
		letters = 0;
		for (int i = m; tempp[i] != ' ' && tempp[i] != '\0'; i++)
		{
			letters++;
			m++;
		}
		m++;

		if (letters != 0)
		{
			token[j] = new char[letters + 1];
		}
	}
	m = 0;
	int l = 0;
	int s = 0;
	for (int i = 0; i < wordcount; i++)
	{
		for (l = s; tempp[l] != ' ' && tempp[l] != '\0'; l++, m++)
		{
			token[i][m] = tempp[l];
		}
		token[i][m] = '\0';

		m = 0;
		l++;
		s = l;
	}
	token[wordcount] = NULL;
	return token;
}

char **tokenonpipes(char *tempp, int &wordcount)
{ //THIS FUNCTION TOKENIZES USER QUERY AND RETURN A 2D ARRRAY WITH WORDCOUNT(NO OF WORDS)
	int size = strlen(tempp);
	wordcount = 0;
	for (int i = 0; i < size; i++)
	{

		if (tempp[i] == '|')
		{
			wordcount++;
		}
	}

	wordcount = wordcount + 1;
	char **token;
	token = new char *[wordcount + 1];
	int letters = 0;
	int m = 0;

	for (int j = 0; j < wordcount; j++)
	{
		letters = 0;
		for (int i = m; tempp[i] != '|' && tempp[i] != '\0'; i++)
		{

			letters++;
			m++;
		}
		m += 2;

		if (letters != 0)
		{
			token[j] = new char[letters + 1];
		}
	}
	m = 0;
	int l = 0;
	int s = 0;
	for (int i = 0; i < wordcount; i++)
	{
		for (l = s; tempp[l] != '|' && tempp[l] != '\0'; l++, m++)
		{
			token[i][m] = tempp[l];
		}
		if (token[i][m - 1] == ' ')
			m--;
		token[i][m] = '\0';

		m = 0;
		l += 2;
		s = l;
	}
	token[wordcount] = NULL;
	return token;
}

bool checkout(char *arr)
{
	for (int i = 0; i < strlen(arr); i++)
	{
		if (arr[i] == '>')
		{
			return true;
		}
	}
	return false;
}

bool checkin(char *arr)
{
	for (int i = 0; i < strlen(arr); i++)
	{
		if (arr[i] == '<')
		{
			return true;
		}
	}
	return false;
}

bool checkbothinout(char *arr){
bool in=false;
bool out=false;
	for (int i = 0; i < strlen(arr); i++)
	{
		if (arr[i] == '>')
		{
			out=true;
		}
	}
		for (int i = 0; i < strlen(arr); i++)
	{
		if (arr[i] == '<')
		{
			in=true;
		}
	}
	
	if(in==true && out==true){
	return true;
	}
       
        return false;
   

}
bool checknormal(char *arr)
{
	for (int i = 0; i < strlen(arr); i++)
	{
		if (arr[i] == '>' || arr[i] == '<' || arr[i] == '|')
		{
			return false;
		}
	}
	return true;
}


void previous(char *arr)
{
	int words = 0;
	char **tokenized = token(arr, words);
	int stat=fork();
	if(stat==0){
	
	if(execvp(tokenized[0], tokenized)==-1){
	
	_exit(0);
	}
	}
	else if (stat>0){
		wait(NULL);
		//_exit(0);
	}
}

int noofpipes(char *arr)
{
	int count = 0;
	for (int i = 0; i < strlen(arr); i++)
	{
		if (arr[i] == '|')
		{
			count++;
		}
	}
	return count;
}

void outputfunction1(char *arr)
{
	char temp1[20];
	int j = 0;
	int i = 0;
	while (arr[i] != '>')
	{
		temp1[j] = arr[i];
		j++;
		i++;
	}
	i += 2;
	j--;
	temp1[j] = '\0';
	

	int words = 0;
	char filename[20];
	j = 0;
	while (arr[i] != '\0')
	{
		filename[j] = arr[i];
		j++;
		i++;
	}
	filename[j] = '\0';
	//cout << filename << endl;

	int fd1 = open(filename, O_CREAT | O_WRONLY, 0666);
	if (fd1 == -1)
	{
		perror("Failed to open file");
	}
	int backupt1 = dup(1);
	dup2(fd1, 1);
	close(fd1);
	previous(temp1);
	dup2(backupt1, 1);
	close(backupt1);
}

void inputfunction1(char *arr)
{
	char temp1[20];
	int j = 0;
	int i = 0;
	while (arr[i] != '<')
	{
		temp1[j] = arr[i];
		j++;
		i++;
	}
	i += 2;
	j--;
	temp1[j] = '\0';
	//cout << temp1 << endl;

	int words = 0;
	char filename[20];
	j = 0;
	while (arr[i] != '\0')
	{
		filename[j] = arr[i];
		j++;
		i++;
	}
	filename[j] = '\0';
	

	int fd1 = open(filename, O_RDONLY, 0);
	if (fd1 == -1)
	{
		perror("Failed to open file");
	}
	int backupt1 = dup(0);
	dup2(fd1, 0);
	close(fd1);
	previous(temp1);
	dup2(backupt1, 0);
	close(backupt1);
}


void function(char *a)
{
	previous(a);
}

int main()
{
	char arr[256];
	int backup = dup(1);
	int backup2 = dup(0);
	while (strcmp(arr, "exit") != 0)
	{
		cout << "Hassan's Shell: ";
		cin.getline(arr, 256);
		int cpid = fork();
		if (cpid == 0)
		{
			//child process
			if (!checknormal(arr))
			{

				int pipes = 0;
				char **tokenized = tokenonpipes(arr, pipes);
				
				
				if(noofpipes(arr)==0){
				
				if(checkbothinout(arr)){
				
				int y=0;
				char temp[20];
				while(tokenized[0][y]!='>'){
				temp[y]=tokenized[0][y];
				y++;
				}
				y--;
				temp[y]='\0';
				y=y+3;
				char filename[20];
				int k=0;
				while(tokenized[0][y]!='\0'){
				filename[k]=tokenized[0][y];
				k++;
				y++;
				}
				if(filename[k-1]==' '){
				k--;
				}
				filename[k]='\0';
				
				int pip[2];
				pipe(pip);
				dup2(pip[1], 1);
				inputfunction1(temp);
				close(pip[1]);
				dup2(backup, 1);
				
				int fd1 = open(filename, O_CREAT | O_WRONLY, 0666);
				if (fd1 == -1)
				{
					perror("Failed to open file");
				}
				
				
				int size=10000;
				char* buffer=new char [size];
				int r=read(pip[0],buffer,size);
				buffer[r]='\0';
				write(fd1,buffer,r);
				
				
				}
				else if(checkin(tokenized[0])){
				inputfunction1(tokenized[0]);
				}
				else if(checkout(tokenized[0])){
				outputfunction1(tokenized[0]);
				}
				
				}
			  else{
				int **pipesarr = new int *[pipes - 1];
				for (int i = 0; i < pipes - 1; i++)
				{
					pipesarr[i] = new int[2];
				}
				for (int i = 0; i < pipes - 1; i++)
				{
					pipe(pipesarr[i]);
				}
				for (int i = 0; i < pipes; i++)
				{
					if (i != pipes - 1)
					{
						dup2(pipesarr[i][1], 1);
						
						bool checkforinput=false;
					        for(int j=0;j<strlen(tokenized[i]);j++){
					        if(tokenized[i][j]=='<'){
					        checkforinput=true;
					        }
					        }
					        if(checkforinput==true){
					        inputfunction1(tokenized[i]);
					        }
					        else{
						
						previous(tokenized[i]);
						
						}
						dup2(backup, 1);
						close(pipesarr[i][1]);
						dup2(pipesarr[i][0], 0);
					}
					else
					{      
					       bool checkforoutput=false;
					        for(int j=0;j<strlen(tokenized[i]);j++){
					        if(tokenized[i][j]=='>'){
					        checkforoutput=true;
					        }
					        }
					        if(checkforoutput==true){
					        outputfunction1(tokenized[i]);
					        }
					        else{
					        
					     
						previous(tokenized[i]);

						}
						close(pipesarr[i][1]);
						close(pipesarr[i][0]);
						dup2(backup2, 0);
						dup2(backup, 1);
					}
				}
			     }
			}
			else 
			{
				previous(arr);
			}
			return 0;
		}
		else if (cpid > 0)
		{
			wait(NULL);
		//_exit(0);
		}
	}
	return 0;
}

