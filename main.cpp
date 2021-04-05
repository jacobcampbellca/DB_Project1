#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <string>
#include <list>

using namespace std;

// constuct nodes to be used in linked lists
class Node
{
public:
    Node* next;
    
    //add car
    string VIN;
    int miles;
    string dealership;
    int price;
    
    //add model
    string code;
    string manufacturer;
    
    //add dealership
    string name;
    int zip;
    string phoneNumber;
    
};

//construct linked list and functions to be used by lists
class LinkedList
{
public:
    Node* head;
    LinkedList* here;
    
    //functions to add data
    void addCar(string VIN, int miles, string dealership, int price);
    void addManufacturer(string code, string manufacturer);
    void addDealership(string name, int zip, string phoneNumber);
    
    //functions to print car data and store in a file
    void printCar();
    void writeCarsToFile();
    
    //functions to print manufacturer data and store in a file
    void printManufacturer();
    void writeManufacturersToFile();
    
    //functions to print dealerships data and store in a file
    void printDealership();
    void writeDealershipsToFile();
    
    //functions to return manufacturer code, and print cars made by manufacturer
    string getManufacturerCode(string manufacturer);
    void printCarsByManufacturer(string manufacturerName, string manufacturerCode);
    
    void printCarsByZip(int zip);
    
    //delete desired list
    void deleteList(LinkedList* head_ref);
};

LinkedList* cars = new LinkedList();
LinkedList* manufacturers = new LinkedList();
LinkedList* dealerships = new LinkedList();


//add a car to the linked list 'cars'
void LinkedList::addCar(string v, int m, string d, int p) {
    Node* node = new Node();
    Node* current = head;
    
    //if user trys to enter duplicate car, print error
    //dont add duplicate car
    while(current) {
        if(current->VIN == v) {
            cout <<"ERROR: duplicate car" << endl;
            return;
        }
        current = current->next;
    }
    node->VIN = v;
    node->miles = m;
    node->dealership = d;
    node->price = p;
    node->next = this->head;
    this->head = node;
}


//add a manufacturer to the linked list 'manufacturers'
void LinkedList::addManufacturer(string c, string m) {
    Node* node1 = new Node();
    node1->code = c;
    node1->manufacturer = m;
    node1->next = this->head;
    this->head = node1;
}

//add a dealership to linked list 'dealerships'
void LinkedList::addDealership(string n, int z, string p) {
    Node* node2 = new Node();
    Node* current = head;
    
    //if user trys to enter duplicate dealership, print error
    //dont add duplicate dealership
    while(current) {
        if(current->name == n && current->zip == z) {
            cout <<"ERROR: duplicate dealership" << endl;
            return;
        }
        current = current->next;
    }
    node2->name = n;
    node2->zip = z;
    node2->phoneNumber = p;
    node2->next = this->head;
    this->head = node2;
}

//print cars stored in linked list 'cars'
void LinkedList::printCar() {
    Node* head = this->head;
    
    //while there are still nodes in the list...
    while(head){
        cout << head->VIN << " " << head->miles << " " << head->dealership << " " << head->price << endl;
        head = head->next;
    }
}

//store added cars in an external file
void LinkedList::writeCarsToFile() {
    Node* head = this->head;
    
    //create an external file called 'cars.txt'
    ofstream writeCars("cars.txt");
    
    //while there are still nodes in the list...
    while(head){
        writeCars << head->VIN << " " << head->miles << " " << head->dealership << " " << head->price << endl;
        head = head->next;
    }
}

//print cars stored in linked list 'manufacturers'
void LinkedList::printManufacturer() {
    Node* head1 = this->head;
    
    //while there are still nodes in the list...
    while(head1){
        cout << head1->code << " " << head1->manufacturer << endl;
        head1 = head1->next;
    }
}

//store added manufacturers in an external file
void LinkedList::writeManufacturersToFile() {
    Node* head1 = this->head;
    
    //create an external file called 'manufcturers.txt'
    ofstream writeManufacturers("manufacturers.txt");
   
    //while there are still nodes in the list...
    while(head1){
        writeManufacturers << head1->code << " " << head1->manufacturer << endl;
        head1 = head1->next;
    }
}

//print dealerships stored in linked list 'dealerships'
void LinkedList::printDealership() {
    Node* head2 = this->head;
    
    //while there are still nodes in the list...
    while(head2){
        cout << head2->name << " " << head2->zip << " " << head2-> phoneNumber << " " << endl;
        head2 = head2->next;
    }
}

//write dealerships to an external file
void LinkedList::writeDealershipsToFile() {
    Node* head2 = this->head;
   
    //create external file called 'dealerships.txt'
    ofstream writeDealerships("dealerships.txt");
    
    //while there are still nodes in the list...
    while(head2){
        writeDealerships << head2->name << " " << head2->zip << " " << head2-> phoneNumber << " " << endl;
        head2 = head2->next;
    }
}

//get the code of the manufacturer that user is looking for
string LinkedList::getManufacturerCode(string m) {
    string desiredCode;
    Node* current = head; // Initialize current
  
    //while there are still nodes in the list...
    while (current)
    {
        //return code of desired manufacturer
        if (current->manufacturer == m){
            desiredCode = current->code;
            return desiredCode;
        }
        current = current->next;
    }
    return desiredCode;
}



//list all cars made by manufacturer
//determined by user input
void LinkedList::printCarsByManufacturer(string MN, string MC) {
    Node* current = head;
   
    //while there are still nodes in the list...
    while(current) {
        
        //if first three characters of car VIN match that of the desired manufacturer code,
        //print car
        if(current->VIN.substr(0,3) == MC && current->miles != 0) {
            
            
            cout << MN << ":" << current->miles << " miles, $" << current->price << ": " << current->dealership << "["  << current->phoneNumber << "]" << endl;
        }
        current = current->next;
    }
}

void LinkedList::printCarsByZip(int z) {
    Node* current = head;
    
    //while there are still nodes in the list...
    while(current) {
        
        //if car is in user specidied zip code,
        //print car
        if(current->zip == z) {
            cout << current->manufacturer << ":" << current->miles << " miles, $" << current->price << ": " << current->name << "["  << current->phoneNumber << "]" << endl;
        }
        current = current->next;
    }
}

//delete linked list
void LinkedList::deleteList(LinkedList *head_ref) {
    LinkedList* current = head_ref;
    LinkedList* next;
    
    while(current != NULL) {
        next = current->here;
        current = here;
    }
    head_ref = NULL;
}

int main(int argc, char const *argv[]) {
    
    //initialize linked list called 'cars'
    //read in all cars from external file called 'cars.txt'
    string VIN;
    int miles;
    string dealership;
    int price;
    
    ifstream readCars("cars.txt");
    while(readCars >> VIN >> miles >> dealership >> price) {
        cars -> addCar(VIN, miles, dealership, price);
    }
    
    //initialize linked list called 'manufacturers'
    //read in all manufacturers from external file called 'manufcturers.txt'
    string code;
    string manufacturer;

    ifstream readManufacturers("manufacturers.txt");
    while(readManufacturers >> code >> manufacturer) {
        manufacturers -> addManufacturer(code, manufacturer);
    }
    
    //initialize linked list called 'dealerships'
    //read in all dealerships from external file called 'dealerships.txt'
    string name;
    int zip;
    string phoneNumber;
   
    ifstream readDealerships("dealerships.txt");
    while(readDealerships >> name >> zip >> phoneNumber) {
        dealerships -> addDealership(name, zip, phoneNumber);
    }
    
    //user input
    char primaryCommand = NULL;
    char secondaryCommand = NULL;
    
    //while the user does not want to quit the program
    while(primaryCommand != 'q' || primaryCommand != 'Q') {
        
        //get primary command
        cout << ">>> ";
        cin >> primaryCommand;
        
        //quit program if user enters 'q' as primary command
        if(primaryCommand == 'q' || primaryCommand == 'Q') {
            return 0;
        }
        
        //get secondary command
        cin >>secondaryCommand;
        
        //if user wants to add data...
        if(primaryCommand == 'a' || primaryCommand == 'A') {
           
            //add user entered car to linked list and add car to external file
            if(secondaryCommand == 'c' || secondaryCommand == 'C') {
                cin >> VIN >> miles >> dealership >> price;
                cars -> addCar(VIN, miles, dealership, price);
                cars -> writeCarsToFile();
            }
            
            //add user entered manufacturer to linked list and write manufacturer to external file
            else if(secondaryCommand == 'm' || secondaryCommand == 'M') {
                cin >> code >> manufacturer;
                manufacturers -> addManufacturer(code, manufacturer);
                manufacturers -> writeManufacturersToFile();
            }
            
            //add user entered dealership to linked list and add dealership to external file
            else if(secondaryCommand == 'd' || secondaryCommand == 'D') {
                cin >> name >> zip >> phoneNumber;
                dealerships -> addDealership(name, zip, phoneNumber);
                dealerships -> writeDealershipsToFile();
            }
        }
        
        //if user wants to list data...
        else if(primaryCommand == 'l' || primaryCommand == 'L') {
            
            //delete current list 'cars' and recreate
            //read in all data from external file 'cars.txt' to linked list
            //print all data stored in linked list 'cars'
            if(secondaryCommand == 'c' || secondaryCommand == 'C') {
                cars -> deleteList(cars);
                LinkedList* cars = new LinkedList();
                ifstream readCars("cars.txt");
                while(readCars >> VIN >> miles >> dealership >> price) {
                    cars -> addCar(VIN, miles, dealership, price);
                }
                cars -> printCar();
            }
            
            //delete current list 'manufacturers' and recreate
            //read in all data from external file 'manufacturers.txt' to linked list
            //print all data stored in linked list 'manufacturers'
            else if(secondaryCommand == 'm' || secondaryCommand == 'M') {
                manufacturers -> deleteList(manufacturers);
                LinkedList* manufacturers = new LinkedList();
                ifstream readManufacturers("manufacturers.txt");
                while(readManufacturers >> code >> manufacturer) {
                    manufacturers -> addManufacturer(code, manufacturer);
                }
                manufacturers -> printManufacturer();
            }
            
            //delete current list 'dealerships' and recreate
            //read in all data from external file 'dealerships.txt' to linked list
            //print all data stored in linked list 'dealerships'
            else if(secondaryCommand == 'd' || secondaryCommand == 'D') {
                dealerships -> deleteList(dealerships);
                LinkedList* dealerships = new LinkedList();
                ifstream readDealerships("dealerships.txt");
                while(readDealerships >> name >> zip >> phoneNumber) {
                    dealerships -> addDealership(name, zip, phoneNumber);
                }
                dealerships -> printDealership();
            }
        }
        
        //if user wants to find specific data...
        else if(primaryCommand == 'f' || primaryCommand == 'F') {
            
            //find all cars made by a specific manufacturer
            //print cars made by said manufcaturer
            if(secondaryCommand == 'm' || secondaryCommand == 'M') {
                string desiredManufacturer;
                cin >> desiredManufacturer;
                
                string desiredCode = manufacturers -> getManufacturerCode(desiredManufacturer);
                cars -> printCarsByManufacturer(desiredManufacturer, desiredCode);
                
            }
            
            //get desired zip code
            else if(secondaryCommand == 'z' || secondaryCommand == 'Z') {
                int desiredZIP;
                cin >> desiredZIP;
                
                //print cars in user specified zip code
                dealerships -> printCarsByZip(desiredZIP);
            }
        }
    }
}
