#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <sstream>
#include <vector>
#include <filesystem>

//TO DO:
// make mylist to be protected
//change the long inline methods to outside of the class

class LinkedList{
    //innerclass Node
 class Node{
    public:
     std::string content = "";
     Node* next=NULL;
     int version =0;
    
    };
 //global variables of LinkedList
 private:
    Node* list;
    Node* tail;
    std::size_t hash_it(std::string someString){
        std::size_t h1=std::hash<std::string>{}(someString);
        return h1;
    }

  //some methods of LinkedList
 public:
    LinkedList();
    ~LinkedList();
    void appendContent(std::string newcontent, int version_number=0);
    int size();
    bool find_same(std::size_t hash_value);
    void traverse();
    std::vector<int> return_versions();
    std::string find(int version);
    void remove_list(int version);
    void search_list(std::string keyword);

};
    //constructor
    LinkedList::LinkedList():list(NULL),tail(NULL)
    {
        //list=NULL;
        //tail=NULL;
    }
    LinkedList::~LinkedList(){
        delete this->list;
        delete this->tail;
    }
    //adding
    void LinkedList::appendContent(std::string newcontent, int version_number){
        Node* n=new Node;
        n->content = newcontent;
        if(this->tail==NULL){
            n->version=1;
        }else{
        n->version=(this->tail)->version+1;
        }
        n->next=NULL;

        if(!(this->list)){
            this->list=n;
            this->tail=n;
        }else{
            (this->tail)->next = n;
            this->tail=n;
        }

        if(version_number !=0){
            n->version=version_number;
        }
    } 
    //getting the size of the list
    int LinkedList::size(){
        int size=0;
        Node *current=this->list;
        while(current != nullptr){
           size=size+1;
           current=current->next;
       
        }
        return size;
    }
    //find if there is existing version in the list
    bool LinkedList::find_same(std::size_t hash_value){
        Node *current=this->list;
        while(current != nullptr){
            std::string content=current->content;
            std::size_t h1=hash_it(content);

            if(h1 == hash_value){
                std::cout << "git322 did not detect any change to your file and will not create a new version." << std::endl;
                return false;
             }
            current=current->next;
        }
        return true;
    }

    void LinkedList::traverse(){
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

    //return a list of current versions
    std::vector<int> LinkedList::return_versions(){
            std::vector<int> versions;
            Node *current=list;
            while(current != nullptr){
                versions.push_back(current->version);
                current=current->next;
            }
            return versions;
    } 
    //find certain version
    std::string LinkedList::find(int version){
        Node *current=this->list;
        while(current != nullptr){
                if(current->version == version){
                                
                        //return the content;
                        return current->content;
                 }
                    current=current->next;
        }
        std::cout << "Please enter a valid version number. If you are not sure please press 'p' to list all valid version numbers." << std::endl;
        return "";
        
    }

    void LinkedList::remove_list(int version){
        if (this->list == NULL) { // if list is empty
                return;
        }
        Node* current = this->list;
        Node* previous = NULL;
        while (current != NULL) {
            if (current->version == version) { // if found the node to delete
                if (previous == NULL) { // if the node is the head of the list
                    this->list = current->next;
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

    void LinkedList::search_list(std::string keyword){
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
   


//class of Git
class Git322
{
    private:
    //LinkedList mylist;
    //hash the file
    std::size_t hash_it(std::string someString){
        std::size_t h1=std::hash<std::string>{}(someString);
        return h1;
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

    protected:
      LinkedList mylist;
    
    public:

    Git322();
    virtual ~Git322();
    LinkedList& getLinkedList() {
        return mylist;
    }
    void add();
    void print();
    void load(int version);
    void compare(int version1, int version2);
    void remove(int version);
    void search(std::string keyword);

};
        
        Git322::Git322(){
            
            std::cout << "Git322 is created" << std::endl;
        }

        Git322::~Git322(){
            std::cout << "Git322 destructor" << std::endl;
        }

        //add current file to the tracking system
        void Git322::add(){
            //first extract the content of the file
            std::string file = "./file.txt";
            //open and read the file
            std::ifstream infile(file);
            std::string fileContents((std::istreambuf_iterator<char>(infile)), (std::istreambuf_iterator<char>()));
            infile.close();
            std::size_t h2=hash_it(fileContents);
            //if there are no existing ones in the system
            if(mylist.find_same(h2)==true){
                //add it to the tracking system
                mylist.appendContent(fileContents);
                std::cout << "Your content has been added successfully." << std::endl;
            }
      
        }

        void Git322::print(){
           mylist.traverse();
    
        }

        //check the entered number is valid and load it
        void Git322::load(int version){  
        //if the version is in the list
                if(mylist.find(version)!=""){
                        //write this version to the editor
                        std::cout << "Version " << std::to_string(version) << " loaded successfully. Please refresh your text editor to see changes." << std::endl;
                        std::ofstream outputFile;
                        outputFile.open("./file.txt");
                        outputFile << mylist.find(version) << std::endl;
                        outputFile.close();           
                        //break;
                        return;
                 }
        }
        //compare the content of the two versions
        void Git322::compare(int version1, int version2){
            //first find the two contents
            std::string content1=mylist.find(version1);
            std::string content2=mylist.find(version2);
        
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

        void Git322::remove(int version){
            mylist.remove_list(version);
        }

        void Git322::search(std::string keyword){
            mylist.search_list(keyword);
        }



//all versions should be saved in memory
class EnhancedGit322: public Git322{
    private:
    LinkedList myenhancedlist;

    std::size_t hash_it(std::string someString){
        std::size_t h1=std::hash<std::string>{}(someString);
        return h1;
    }
    //helper function to store the current files into a directory
    void store_versions_to_dir(std::string content, std::string dir,std::string filename){
        std::filesystem::create_directory(dir);
    
        // Create the full file path
        std::string filepath = dir + "/" + filename;
    
        // Open the file and write the string to it
        std::ofstream file;
        file.open(filepath);
        file << content;
        file.close();
    }

    public:
    EnhancedGit322();
    ~EnhancedGit322();
};
      EnhancedGit322::EnhancedGit322(){
        std::cout << "EnhancedGit322 is created" <<std::endl;
        //reload the versions == add the versions into the list and remove the directory
        
        //first check if the directory exists and is empty
        std::string directory = "current_versions";
        if(std::filesystem::exists(directory) && std::filesystem::is_directory(directory) && !std::filesystem::is_empty(directory)){
            //iterate through the directory
          for(const auto& entry : std::filesystem::directory_iterator(directory)){
            if(std::filesystem::is_regular_file(entry)){
                //get the file name which is the version number
                std::string filename = entry.path().filename().string();
                //std::cout << filename << std::endl;
                std::ifstream file(entry.path().string());
                std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
                //add it to the list
                int version_num = std::stoi(filename);
                getLinkedList().appendContent(content,version_num);
            }
        
         }
         
       }
      }

      EnhancedGit322::~EnhancedGit322(){
        std::filesystem::remove_all("current_versions");
        myenhancedlist=getLinkedList();
        std::cout << "EnhancedGit322 destructor" << std::endl;
        //save all current versions
        std::vector<int> versions=myenhancedlist.return_versions();
        for(int i = 0; i < versions.size(); i++){
            std::string content=myenhancedlist.find(versions[i]);
            std::string dir="current_versions";
            store_versions_to_dir(content,dir,std::to_string(versions[i]));
        }
      }




int main(){
    
    std::cout <<"Welcome to the Comp322 file versioning system" << std::endl;
    std::cout << "Would you like to work with Git or Enhanced Git?" << std::endl;
    std::string git_system;
    std::cin >> git_system;
    Git322* git=NULL;
    if(git_system=="Git"){
        git=new Git322();
    }else{
        git=new EnhancedGit322();
    }
    std::cin.ignore(); 
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
            git->add();
        }else if(input=="p"){
            git->print();
        }else if(input=="l"){
            std::cout << "Which version would you like to load?" << std::endl;
            int version;
            std::cin >> version;
            std::cin.ignore();
            git->load(version);
        }else if(input=="c"){
            std::cout << "Please enter the number of the first version to compare: " << std::endl;
            int version1;
            std::cin >> version1;
            std::cin.ignore();
            std::cout << "Please enter the number of the second version to compare: " << std::endl;
            int version2;
            std::cin >> version2;
            std::cin.ignore();
            git->compare(version1,version2);
        }else if(input=="r"){
            std::cout << "Enter the number of the version that you want to delete: " << std::endl;
            int version;
            std::cin >> version;
            std::cin.ignore();
            git->remove(version);
        }else if(input=="s"){
            std::cout << "Please enter the keyword that you are looking for: " << std::endl;
            std::string keyword;
            std::cin >> keyword;
            std::cin.ignore();
            git->search(keyword);
        }
        
        std::cin >> input;
    }
    delete git;
    return 0;
}