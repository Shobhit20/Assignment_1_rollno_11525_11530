#include <iostream>
#include <cstring>
#include<iostream>
#include<fstream>
#include <sstream>
using namespace std;

void preKMP(string pattern, int pre_table[])
{
    int i=0;
	int j=0;
	pre_table[0] = 0;	
	for(i=1; i<pattern.length();i++)
	{
		if(pattern[i]==pattern[j])
		{
			pre_table[i] = j+1;
			j++;
		}
		else{
			while(pattern[i] != pattern[j] && j!=0)
			{
			  j=pre_table[j-1];	
			}
			if(pattern[i]==pattern[j]){
				pre_table[i] = j+1;
			    j++;
			}
			else if(j==0 && pattern[i]!=pattern[j])
			{
				pre_table[i]=0;
			}
		}
	}
}

int KMP(int index,string substring, string para)
{
    int m = substring.length();
    int n = para.length();
    int prefix_table[m];     
    preKMP(substring, prefix_table);     
    int k = 0;        
    while (index < n)
    {
        if (para[index] == substring[k])
        {
            index++;
            k++;
            if (k == m)
                return index-k+1;
        }
        else if (k == 0)
        {
            index++;
        }
        else
            k = prefix_table[k];
    }
    return -2;
}

void word(int subs_word){
	ifstream file("cic.txt");
	int word_count=0;
	string word;
	while(!file.eof())
    {               
        file >> word; 
        word_count++;
    }
	string index_word[word_count];
	ifstream file1("cic.txt");
    if(file1.is_open())
    {
        for(int i = 0; i < word_count; i++)
        {
            file1 >> index_word[i];
        }
    }
    cout<<index_word[subs_word]<<endl;
} 

int main()
{   
	int present_index=0;
	int KMP_ret=0;
	
	ifstream file("cic.txt");
	stringstream buffer;
    buffer << file.rdbuf();
    string textfile = buffer.str();
    string substring;
    cout << textfile<<endl;
    int choice=1;
    int para=1;
    while(choice==1){
    	cout<<endl;
    	cout<<endl;
    	cout<<"Press 1 to find the number of paragraphs in the file"<<endl;
    	cout<<"Press 2 for dictionary search"<<endl;
    	int ch;
    	cin>>ch;
    	switch(ch){
    		case 1:
    			for(int k=0;k<textfile.length();k++)
    			{
					if(textfile[k]=='\n' && textfile[k+1]=='\n')
					{
						para++;
					}
				}
				cout<<"the number of paragraphs in the file is "<<para<<endl;
				cout<<endl;
				break;
			case 2:
				cout<<"Enter substring"<<endl;
    			cin>>substring;
    			while(present_index<textfile.length() && present_index>=0)
				{
				    int KMP_ret=KMP(present_index,substring,textfile);
				    int count=0;
				    KMP_ret++;
				    present_index=KMP_ret;
				    if(present_index!=-1)
					{
				    	for (int j= 0; j <present_index-1; j++)
						{
				            if (textfile[j] == ' '||(textfile[j]=='\n' && textfile[j+1]=='\n')){
				                	count++;
				            }
						}
						cout<<"The substring starts at "<<present_index-1<<" and the word is ";
						word(count);
					}
				}
				break;  
			default:
				cout<<"INVALID ENTRY"<<endl;
				exit(0);
		}
		cout<<"Press 1 to continue"<<endl;
		cin>>choice;
	}
}
