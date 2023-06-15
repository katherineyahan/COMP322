//implement linked list
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <sstream>
class Node{
    public:
     std::string content = "";
     Node* next=NULL;
     int version =0;
    
};
Node* list=NULL;
Node* tail=NULL;

//add to the linked list
void appendContent(Node** list, Node** tail, std::string newcontent){
    Node* n=new Node;
    n->content = newcontent;
    if(*tail==NULL){
        n->version=1;
    }else{
      n->version=(*tail)->version+1;
    }
    n->next=NULL;

    if(!(*list)){
        *list=n;
        *tail=n;
    }else{
        (*tail)->next = n;
        *tail=n;
    }

}

int size(){
    int size=0;
    Node *current=list;
    while(current != nullptr){
       size=size+1;
       current=current->next;
       
    }
    return size;
}
std::size_t hash_it(std::string someString){
  std::size_t h1=std::hash<std::string>{}(someString);
  return h1;
}
//add current file to the tracking system
void add(){
    //first extract the content of the file
    std::string file = "./file.txt";
    //open and read the file
    std::ifstream infile(file);
    std::string fileContents((std::istreambuf_iterator<char>(infile)), (std::istreambuf_iterator<char>()));
    infile.close();
    std::size_t h2=hash_it(fileContents);
    //compare if there are existing ones in the system
    Node *current=list;
    while(current != nullptr){
       std::string content=current->content;
       std::size_t h1=hash_it(content);

       if(h1 == h2){
        std::cout << "git322 did not detect any change to your file and will not create a new version." << std::endl;
         return;
       }
       current=current->next;
    }
   
    //add it to the tracking system
    appendContent(&list, &tail, fileContents);
    std::cout << "Your content has been added successfully." << std::endl;
    
}
//hash can be done in print
void print(){
    //loop through the tracking system
   Node *current=list;
    while(current != nullptr){
        //print number of versions
        int versions=size();
        std::cout << "Number of versions: "<< std::to_string(versions) << std::endl;
       //print version number
       int version=current->version;
       std::cout << "Version number: "<< std::to_string(version) << std::endl;
       //print the hash value
       std::string content=current->content;
       size_t hash = std::hash<std::string>()(content);
       std::cout << "Hash value: " << std::to_string(hash) << std::endl;
       //print the content
       std::cout << "Content: "<< content << std::endl;
       current=current->next;      
    }
    
}
//check the entered number is valid and load it
void load(int version){  
        //iterate through the list to find the desired version number
    Node *current=list;
        while(current != nullptr){
            if(current->version == version){
                //write this version to the editor
                std::cout << "Version " << std::to_string(version) << " loaded successfully. Please refresh your text editor to see changes." << std::endl;
                std::ofstream outputFile;
                outputFile.open("./file.txt");
                outputFile << current->content << std::endl;
                outputFile.close();
                
                
                //break;
                return;
            }
            current=current->next;
        }
        
    std::cout << "Please enter a valid version number. If you are not sure please press 'p' to list all valid version numbers." << std::endl;
    
}



int countLines(std::string content){
    std::istringstream iss(content);
    int count = 0;
    std::string line;
    while (std::getline(iss, line)) {
        ++count;
    }
    return count;
}


void compare(int version1, int version2){
  //first find the two contents
  Node *current=list;
  std::string content1;
  std::string content2;
  while(current!=NULL){
    if(current->version==version1){
        content1=current->content;
    }else if(current->version==version2){
        content2=current->content;
    }
    current=current->next;
  }
  int content1Lines=countLines(content1);
  int content2Lines=countLines(content2);
  //iterate through each line in the two contents
  std::istringstream isscontent1(content1);
  std::string line1;
  std::istringstream isscontent2(content2);
  std::string line2;
  int line=0;
  bool eof_reached=false;
  //if content 1 is longer
  if(content1Lines>content2Lines){   
    while (std::getline(isscontent1, line1)) {
        if (!eof_reached && !std::getline(isscontent2, line2)) {
                line2 = "";
                eof_reached = true; // set flag to true when the end of isscontent2 is reached
            }
        line++;
        //hash each line and compare
        std::size_t h1=std::hash<std::string>{}(line1);
        std::size_t h2=std::hash<std::string>{}(line2);
        if(h1!=h2){
            if(line2!=""){
              std::cout <<"Line "<<std::to_string(line)<<": "<<line1<<" <<>> "<<line2<<std::endl;
            }else{
                std::cout << "Line "<<std::to_string(line)<<": "<<line1<<" <<>> <Empty line>"<< std::endl;
            }
        }else{
            std::cout <<"Line "<<std::to_string(line)<<": <Identical>" <<std::endl;
        }
       
    }
    //if content2 is longer
  }else if(content2Lines>content1Lines){
    while (std::getline(isscontent2, line2)) {
        if(!eof_reached && !std::getline(isscontent1, line1)){
        
            line1="";
            eof_reached = true;
        }
        line++;
        //hash each line and compare
        std::size_t h1=std::hash<std::string>{}(line1);
        std::size_t h2=std::hash<std::string>{}(line2);
        if(h1!=h2){
            if(line1!=""){
              std::cout <<"Line "<<std::to_string(line)<<": "<<line1<<" <<>> "<<line2<<std::endl;
            }else{
                std::cout << "Line "<<std::to_string(line)<<": <Empty line>"<<" <<>> "<<line2<< std::endl;
            }
        }else{
            std::cout <<"Line "<<std::to_string(line)<<": <Identical>" <<std::endl;
        }
    }
    //if the two contents have the same length
  }else{
    while(!isscontent2.eof()&&!isscontent1.eof()){
        std::getline(isscontent1,line1);
        std::getline(isscontent2,line2);
        line++;
        std::size_t h1=std::hash<std::string>{}(line1);
        std::size_t h2=std::hash<std::string>{}(line2);
        if(h1!=h2){
            std::cout <<"Line "<<std::to_string(line)<<": "<<line1<<" <<>> "<<line2<<std::endl;
        }else{
            std::cout <<"Line "<<std::to_string(line)<<": <Identical>" <<std::endl;
        }
    }
  }

}

void remove(int version){
  if (list == NULL) { // if list is empty
        return;
    }
    Node* current = list;
    Node* previous = NULL;
    while (current != NULL) {
        if (current->version == version) { // if found the node to delete
            if (previous == NULL) { // if the node is the head of the list
                list = current->next;
            } else {
                previous->next = current->next;
            }
            delete current;
            std::cout << "Version " << std::to_string(version) << " deleted successfully. "<< std::endl;
            return;
        }
        previous = current;
        current = current->next;
    }
        
    std::cout << "Please enter a valid version number. " << std::endl;
}

void search(std::string keyword){
   int a=0;
   Node* current = list;
   while(current != nullptr){
     std::string current_content=current->content;
     size_t pos = current_content.find(keyword);
     if (pos != std::string::npos) {
        std::cout << "The keyword '"+ keyword +"' has been found in the following versions:" << std::endl;
       //print version number
       int version=current->version;
       std::cout << "Version number: "<< std::to_string(version) << std::endl;
       //print the hash value
       std::string content=current->content;
       size_t hash = std::hash<std::string>()(content);
       std::cout << "Hash value: " << std::to_string(hash) << std::endl;
       //print the content
       std::cout << "Content: "<< content << std::endl;
       a=a+1;
   }
   current=current->next;
 }
 if(a == 0){
    std::cout << "Your keyword '"+keyword+"' was not found in any version." << std::endl;
 }
}
//might froze, please re-enter the input if nothing happens
int main(){
    std::cout <<"Welcome to the Comp322 file versioning system" << std::endl;
    std::cout << "To add the content of your file to version control press 'a' "<<std::endl;
    std::cout <<"To remove a version press 'r'"<<std::endl;
    std::cout <<"To load a version press 'l'"<<std::endl;
    std::cout << "To print to the screen the detailed list of all versions press 'p'"<<std::endl;
    std::cout <<"To compare any 2 versions press 'c'"<<std::endl;
    std::cout <<"To search versions for a keyword press 's'" <<std::endl;
    std::cout <<"To exit press 'e'" << std::endl;
    std::string input;
    std::cin >> input;
    while(input != "e"){ 
        std::cin.ignore();       
        if(input=="a"){
            add();
        }else if(input=="p"){
            print();
        }else if(input=="l"){
            std::cout << "Which version would you like to load?" << std::endl;
            int version;
            std::cin >> version;
            std::cin.ignore();
            load(version);
        }else if(input=="c"){
            std::cout << "Please enter the number of the first version to compare: " << std::endl;
            int version1;
            std::cin >> version1;
            std::cin.ignore();
            std::cout << "Please enter the number of the second version to compare: " << std::endl;
            int version2;
            std::cin >> version2;
            std::cin.ignore();
            compare(version1,version2);
        }else if(input=="r"){
            std::cout << "Enter the number of the version that you want to delete: " << std::endl;
            int version;
            std::cin >> version;
            std::cin.ignore();
            remove(version);
        }else if(input=="s"){
            std::cout << "Please enter the keyword that you are looking for: " << std::endl;
            std::string keyword;
            std::cin >> keyword;
            std::cin.ignore();
            search(keyword);
        }
        std::cin >> input;
    }
    delete list;
    delete tail;
    
    return 0;
}