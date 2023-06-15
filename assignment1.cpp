#include <iostream>
#include <string.h>
#include <fstream>
#include <bits/stdc++.h>
#include <filesystem>
using namespace std;
//Q1
bool word_diff(std::string word1, std::string word2){
    if (word1==word2)
      return true;
    else
      return false;
        
}
//Q2 read their content word by word and compare them until a first mismatch occur
bool classical_file_diff(std::string file1, std::string file2){
  //read the content 
  ifstream file_1(file1);
  ifstream file_2(file2);
   
  
  string word1;
  string word2;
  
  while(!file_1.eof()&&!file_2.eof()){
    file_1 >> word1;
    file_2 >> word2;
       if(!word_diff(word1,word2)){
         return false;
      }
    
  }
  //if one file is longer than the other
    return file_1.eof()&&file_2.eof();
}
//Q3
std::size_t hash_it(std::string someString){
  std::size_t h1=std::hash<std::string>{}(someString);
  return h1;
}
//Q4
bool enhanced_file_diff(std::string file1, std::string file2){
  //convert each string to hash value and compare

  ifstream file_1(file1);
  ifstream file_2(file2);

  string word1;
  string word2;
  
  while(!file_1.eof() &&!file_2.eof()){
    file_1 >> word1;
    file_2 >> word2;
    size_t hash1=hash_it(word1);
    size_t hash2=hash_it(word2);
    if(hash1 != hash2){
      return false;
    }
  }

  return file_1.eof()&&file_2.eof();
}

//Q5
void read_line(list<string> list_file1, list<string> list_file2,string file1_name,string file2_name){//helper function
  while(!list_file1.empty()||!list_file2.empty()){
    if(list_file1.empty()){ //if they are different length
       string sentence2=list_file2.front();
        cout <<file1_name+": " << endl;       
        cout << file2_name+": ";
        cout << sentence2 << endl;
        list_file2.pop_front();
    }else if(list_file2.empty()){
      string sentence1=list_file1.front();
      cout << file1_name+": ";
      cout << sentence1 << endl;
      cout << file2_name+": "<< endl;
      list_file1.pop_front();
    }else{//if they are same length
    string sentence1=list_file1.front();
    string sentence2=list_file2.front();
    //parse the sentnece into words
    stringstream s1(sentence1);
    stringstream s2(sentence2);
    string word1;
    string word2;
    //hash the words and compare the hash value
    if(sentence1.length()==sentence2.length()){
     while(s1 >> word1 && s2 >> word2){
      size_t hash_word1=hash_it(word1);
      size_t hash_word2=hash_it(word2);

      if(hash_word1 != hash_word2){
        cout <<file1_name+": ";
        cout << sentence1 << endl;
        cout << file2_name+": ";
        cout << sentence2 << endl;
        break;
      } 
     }
    }else if(sentence1.length()!=sentence2.length()){//sentences are not the same length
        cout <<file1_name+": ";
        cout << sentence1 << endl;
        cout << file2_name+": ";
        cout << sentence2 << endl;
    }
    

    list_file1.pop_front();
    list_file2.pop_front();
  }
    read_line(list_file1,list_file2,file1_name,file2_name);
    return;
  
  }
}

void list_mismatched_lines(std::string file1,std::string file2){//Need to get the name of the file
  std::filesystem::path path(file1);
  std::string file1_name = path.filename().string();
  std::filesystem::path path2(file2);
  std::string file2_name = path2.filename().string();
  ifstream file_1(file1);
  ifstream file_2(file2);
  list<string> list_file1;
  list<string> list_file2;
  while(!file_1.eof()|| !file_2.eof()){
        string line1;
        string line2;
      if(!file_1.eof()){
        getline(file_1,line1);
        list_file1.push_back(line1);
      }
      if(!file_2.eof()){
        getline(file_2,line2);

        list_file2.push_back(line2);
      }
  }

  read_line(list_file1,list_file2,file1_name,file2_name);
  file_1.close();
  file_2.close();
}


//Q6
//pinpoits the mismatched words together with the line number
void read_lineq6(list<string> list_file1, list<string> list_file2, int line_num,string file1_name,string file2_name){//helper function
 while(!list_file1.empty()||!list_file2.empty()){
    line_num+=1;
    if(list_file1.empty()){ //if they are different length
       string sentence2=list_file2.front();
       stringstream s2(sentence2);
       string word2;
       while(s2 >> word2){
        cout <<file1_name+": ";
        cout << " (line ";
        cout << line_num;
        cout << ")" << endl;
        cout << file2_name+": ";
        cout << word2 ;
        cout << " (line ";
        cout << line_num;
        cout << ")" << endl;
       }
       list_file2.pop_front();
    }else if(list_file2.empty()){
      string sentence1=list_file1.front();
      stringstream s1(sentence1);
      string word1;
      while(s1 >> word1){
        cout <<file1_name+": ";
        cout << word1 ;
        cout << " (line ";
        cout << line_num;
        cout << ")" << endl;
        cout << file2_name+": ";
        cout << " (line ";
        cout << line_num;
        cout << ")" << endl;
      }
       list_file1.pop_front();
    }else{
     string sentence1=list_file1.front();
     string sentence2=list_file2.front();
    //parse the sentnece into words
     stringstream s1(sentence1);
     stringstream s2(sentence2);
     string word1;
     string word2;
   
    
    //hash the words and compare the hash value
      while(s1 >> word1){
        if(s2 >> word2){
       size_t hash_word1=hash_it(word1);
       size_t hash_word2=hash_it(word2);

      if(hash_word1 != hash_word2){
        cout <<file1_name+": ";
        cout << word1 ;
        cout << " (line ";
        cout << line_num;
        cout << ")" << endl;
        cout << file2_name+": ";
        cout << word2 ;
        cout << " (line ";
        cout << line_num;
        cout << ")" << endl;
        
      } 
        }else{
          cout <<file1_name+": ";
         cout << word1 ;
          cout << " (line ";
          cout << line_num;
          cout << ")" << endl;
          cout << file2_name+": ";
          cout << " (line ";
          cout << line_num;
          cout << ")" << endl;
        }
     }
  

     while(s2 >> word2){
        cout <<file1_name+": ";
        cout << " (line ";
        cout << line_num;
        cout << ")" << endl;
        cout << file2_name+": ";
        cout << word2 ;
        cout << " (line ";
        cout << line_num;
        cout << ")" << endl;
     }
    
    
    
    list_file1.pop_front();
    list_file2.pop_front();
    
    
  }
  read_lineq6(list_file1,list_file2,line_num,file1_name,file2_name);
  return;
 }
}

void list_mismatched_words(std::string file1,std::string file2){
  std::filesystem::path path(file1);
  std::string file1_name = path.filename().string();
  std::filesystem::path path2(file2);
  std::string file2_name = path2.filename().string();
  //read the files and store the contents in two lists
  ifstream file_1(file1);
  ifstream file_2(file2);
  list<string> list_file1;
  list<string> list_file2;
  while(!file_1.eof()|| !file_2.eof()){
        string line1;
        string line2;
       if(!file_1.eof()){
        getline(file_1,line1);
        list_file1.push_back(line1);
      }
      if(!file_2.eof()){
        getline(file_2,line2);

        list_file2.push_back(line2);
      }
  }
  int line_num=0;
  read_lineq6(list_file1,list_file2,line_num,file1_name,file2_name);
  file_1.close();
  file_2.close();
}

int main(){
  
    // Q1
   std::string str1 = "Hello World";
   std::string str2 = "hEllO World";
   std::string str3 = "World";
   std::string str4 = "Hello World";
   bool result = word_diff(str1, str2); // False
   result = word_diff(str1, str3); // False
   result = word_diff(str1, str4); // True

   //Q2
   std::string file1 = "./txt_folder/file1.txt";
   std::string file2 = "./txt_folder/file2.txt";
   result = classical_file_diff(file1, file2); //False
   

  //Q3
  std::string mystr = "I love this assignment";
  std::size_t h1 = hash_it(mystr);
  std::cout << h1 << std::endl;

  //Q4
   result=enhanced_file_diff(file1, file2);
  
  //Q5
   list_mismatched_lines(file1, file2);// This should print to the screen the mismatched lines

  //Q6
   list_mismatched_words(file1, file2); // This should print to the screen the mismatched words
}