/**
    NLP Assignment
    KMP1.cpp
    Purpose: counts the no. of paragraphs in a text file and implements dictionary search using KMP algorithm

    @author Rddhima(roll no. 11525), Shobhit(roll no. 11530)
    @version 1.1 6/9/16
    ****  Make sure that the text file you choose is in the same folder as that of the algorithm else specify the complete path ****
*/

#include <iostream>
#include <cstring>
#include<iostream>
#include<fstream>
#include <sstream>
using namespace std;

/**
    Constructs a prefix table of given string.

    @param {string} pattern the string whose prefix table is to be constructed
    @param {array} pre_table the prefix table of the string

    Description: given any string pattern, pre_table[i] refers to the length of the longest suffix
    of substring pattern[0,i-1] that matches its prefix.
*/
void preKMP(string pattern, int pre_table[])
{
  	int i=0;
	int j=0;
	pre_table[0] = 0;	 //i=0 hence pattern[0,-1] is an empty substring; therefore can't contain any suffix
	for(i=1; i<pattern.length();i++)
	{
		if(pattern[i]==pattern[j])
		{
			pre_table[i] = j+1;
			j++;
    	}
		else
		{
			while(pattern[i] != pattern[j] && j!=0)//since j!=0, we go back to the starting position of longest matching suffix
			{
			  j=pre_table[j-1];
			}
			if(pattern[i]==pattern[j])//if both are equal, i and j get incremented by 1
			{
				pre_table[i] = j+1;
			    j++;
			}
			else if(j==0 && pattern[i]!=pattern[j])//if both are unequal but j=0, we can't decrement j further
				pre_table[i]=0; //since no matching suffix was found
		}
	}
}

/**
    Searches for all occurances of the given substring in a string.

    @param {int} index :position from which search in paragraph should begin
    @param {string} substring :the pattern that we are searching for inside the string
    @param {string} para :string in which patterns are being searched

    @return {int} index: position at which substring was found; returns -2 if not found

*/
int KMP(int index,string substring, string para)
{
    int m = substring.length();
    int n = para.length();
    int prefix_table[m]; //prefix table is as long as the substring we want to search
    preKMP(substring, prefix_table);//now prefix_table contains the prefix table of substring
    int k = 0;
    while (index < n)
    {
        if (para[index] == substring[k])
        {
            index++;
            k++;
            if (k == m) //if all the m comparisons made between para and substring were equal,substring found
                return index-k+1;// returning position of substring in para
        }
        else if (k == 0) //keep incrementing index till para[index] matches with the first letter in substring
        {
            index++;
        }
        else
            k = prefix_table[k];
    }
    return -2;
}

/**
    Given any text file t, this function writes  the ith word of t into index_word[i].

    @param {int} subs_word: the position of the word that contains reqd. substring
    @param {string} text: name of the text file to be executed
*/
void word(string text,int subs_word){
	ifstream file;
	file.open(text.c_str());
	int word_count=0;
	string word;
	while(!file.eof())  //contine reading till end-of-file has not been reached
    {
        file >> word;
        word_count++;//counting no. of words in text file
    }
	string index_word[word_count];//creating an array to store one word in each element
	ifstream file1;
	file1.open(text.c_str());
    if(file1.is_open())
    {
        for(int i = 0; i < word_count; i++)
        {
            file1 >> index_word[i];//writing ith word of text file into ith element of index_word
        }
    }
    cout<<index_word[subs_word]<<endl;
}

int main()
{
	int present_index=0;
	int KMP_ret=0;
	string text;
	cout<<"Enter the file name in .txt format for example-filename.txt"<<endl;
	cin>>text;
	ifstream file;  
	file.open(text.c_str());
	stringstream buffer;
    buffer << file.rdbuf();
    string textfile = buffer.str(); //textfile stores the entire text content of cic.txt as a string
    string substring; //substring stores the word we want to search in dictionary
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
					if(textfile[k]=='\n' && textfile[k+1]=='\n') // 2 consecutive newlines implies start of new paragraph
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
				    int KMP_ret=KMP(present_index,substring,textfile); //KMP_ret stores position at which substring was found
				    int count=0;
				    KMP_ret++;
				    present_index=KMP_ret;
				    if(present_index!=-1)
					{
				    	for (int j= 0; j <present_index-1; j++)
						{
                    //counting the number of spaces or paras before position KMP_ret
                    // n spaces before position KMP_ret means that the nth word in our text file contains reqd substring
				            if (textfile[j] == ' '||(textfile[j]=='\n' && textfile[j+1]=='\n')){
				                	count++;
				            }
						}
						cout<<"The substring starts at "<<present_index-1<<" and the word is ";
						word(text,count);
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
