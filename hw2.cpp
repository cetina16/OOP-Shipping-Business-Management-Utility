/*
Ayse Betul Cetin
150180730

g++ -Wall -Werror hw.cpp -o hw
*/

#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

class Person{   // base class
	protected:
	string name;
	string surname;
	public:
	Person(){};
	~Person(){}; 
};

class Owner : public Person{  //subclass of Person class
	double ownership; // amount of ownership as percentage.
	public:
	// necessary getter and setter methods
	string getOwnerName(){return name;}
	string getOwnerSurname(){return surname;}
	void setOwnership(double per){ownership = per;}
	double getOwnership(){return ownership;}
	Owner(); //default constructor
	Owner(string t_name, string t_surname); // constructor with parameters
	~Owner(){};  // destructor
};
Owner::Owner(){
	//cout << "Constructor:Default owner "<< endl;
	name = " ";
	surname = " ";
	ownership = 0;
}
Owner::Owner(string t_name, string t_surname){
	//cout << "Constructor:Owner "<< endl;
	name = t_name;
	surname = t_surname;
	ownership=0;
}

class Courier : public Person{  //subclass of Person class
	string vehicle; // car-motorcycle-bicycle
	int transportation_capacity;  // 200-35-10 kg 
	public:
	Courier* next; 
	// necessary getter and setter methods
	string getVehicle(){return vehicle;}
	int getTrCapacity(){return transportation_capacity;}
	string getCourierName(){return name;}
	string getCourierSurname(){return surname;}
	Courier();
	Courier(string name, string surname, string vehicle);
	int operator ==(Courier c_obj);  
	~Courier(){};  // destructor
};
Courier::Courier(){ // default constructor
	name = " ";
	surname = " ";
	vehicle = " ";
	next = NULL;
	//cout << "Constructor: Default courier" << endl;
}
Courier::Courier(string t_name, string t_surname, string t_vehicle){
	name = t_name;
	surname = t_surname;
	vehicle = t_vehicle;

	if(vehicle == "car"){
		transportation_capacity = 200;
	}else if(vehicle == "motorcycle"){
		transportation_capacity = 35;
	}else if(vehicle =="bicycle"){
		transportation_capacity= 10;	
	}
	next = NULL;
	//cout << "Constructor: courier" << endl;
}
int Courier::operator ==(Courier c_obj){
	int result = 1;
	if( name != c_obj.name  || (surname != c_obj.surname) || (vehicle != c_obj.vehicle)){
		result = 0;
	}
	return result;
}

class Business{
	string businessName;
	string address;
	int number_of_owners;
	Owner* owner_array;
	Courier *courier_array;
	public:
	Business(string t_name, string t_address, Owner* t_arr, int t_number_of_owners);
	void hire_courier(Courier c_obj);   // inserts a Courier object to courier list/array.
	void fire_courier(Courier &c_obj);  //searches the courier and removes it from the list/array. 
	void list_couriers()const; //prints all information (name, surname, vehicle_type) about all couriers to screen.
	void list_owners ()const; // prints all information (name, surname, ownership) about all owners to screen.
	int calculate_shipment_capacity(); // sum up total transportation capacity.
	void operator()() const; // print name, address, owners, couriers. 
	const Courier& operator[](int index) const;  
	~Business();  // destructor
};
Business::Business(string t_name, string t_address, Owner* t_arr, int t_number_of_owners){
	//cout << "Business constr invoked..." << endl;
	businessName = t_name;
	address = t_address;
	courier_array = NULL;
	number_of_owners = t_number_of_owners;
	owner_array = t_arr;
	for(int i=0;i<number_of_owners;i++){
		owner_array[i] = t_arr[i];
	}
	double per = 100 / (double)number_of_owners;
	
	for (int i=0;i<number_of_owners;i++){
		owner_array[i].setOwnership(per);
	}
}
void Business::list_owners() const
{
	double owner_s = owner_array[0].getOwnership();
	for(int i=0;i<number_of_owners;i++){
		string name_print = owner_array[i].getOwnerName();
		cout << name_print << " " << owner_array[i].getOwnerSurname()<< " " << owner_s <<  endl;
	}
}
void Business::list_couriers() const
{
	Courier* traverse = courier_array;
	
	while(traverse){
		string vehicle_g = traverse->getVehicle();
		string name_print = traverse->getCourierName();
		cout << name_print <<" " <<traverse->getCourierSurname()<< " " << vehicle_g <<endl;
		traverse = traverse->next;
	}
}
void Business::hire_courier(Courier c_obj){
	string name_taken = c_obj.getCourierName();
	string surname_taken = c_obj.getCourierSurname();
	string vehicle_taken = c_obj.getVehicle();
	// control vehicle type
	if(vehicle_taken != "car" && vehicle_taken != "motorcycle" && vehicle_taken != "bicycle"){
		cout << "Error... not valid vehicle" << endl;
	}else{
		Courier* new_c = new Courier(name_taken,surname_taken,vehicle_taken);
		
		if(courier_array == NULL){   // if it is first courier
			courier_array = new_c;
		}else{
			Courier* traverse = courier_array;
			while(traverse){
				if(traverse->next == NULL){
					traverse->next = new_c;
					break;
				}
				traverse = traverse->next;	
			}
		}
	}
}
void Business::fire_courier(Courier &c_obj){ 

	Courier* traverse = courier_array;
	Courier* tail = courier_array; 
	if(c_obj == *courier_array && courier_array->next == NULL){
		delete traverse;
		courier_array = NULL;
	}else{
		while(traverse){
			if(*traverse == c_obj){
				if(traverse == courier_array){   //first courier deleted
					courier_array = courier_array->next;
					delete traverse;
					break;
				}else{
					tail->next = traverse->next;
					delete traverse;
					break;
				}
			
		}
		tail = traverse;
		traverse = traverse->next;
		}
		if(traverse == NULL){   // courier does not exist 
			cout << "Error, courier does not exist" << endl;
		}
	}


}
int Business::calculate_shipment_capacity(){
	int sum =0;
	Courier* traverse = courier_array;
	while (traverse){
		int transportation_c = traverse->getTrCapacity();
		sum = sum + transportation_c;
		traverse = traverse->next;
	}
	return sum;
}
void Business::operator()() const
{
	cout <<  businessName << " " << address << endl ;
	list_owners();
	list_couriers();
}
const Courier& Business::operator[](int index) const
{
	//it returns courier with the given index. If the index is invalid, it should print an error message.
	if(courier_array == NULL){
		cout << "Error, empty" << endl;
	    exit(EXIT_FAILURE);;
	}
	Courier* traverse = courier_array;
	if(index < 0){
		cout << "Error, invalid index" << endl;
	    exit(EXIT_FAILURE);;
	}
	if(index == 0){
		return *traverse;
	}
	for(int i=0;i<index;i++){
		traverse = traverse->next;
		if(traverse == NULL){
			cout << "Error, invalid index" << endl;
			exit(EXIT_FAILURE);;
		}
	}
	return *traverse;
}
Business::~Business(){   
//cout << "business destructor"<<endl;
	delete [] owner_array;
	owner_array = NULL;
	if(courier_array != NULL){
		if(courier_array->next == NULL){
			delete courier_array;
		}else{
			Courier* traverse = courier_array;
			while(traverse){
				courier_array = courier_array->next;
				delete traverse;
				traverse = courier_array;
			}
		}
	}

}

int main(){
   // Create owners of the business
    //Constructor parameters: name, surname
    Owner o1 = Owner("Owner_name1", "surname1");
    Owner o2 = Owner("Owner_name2", "surname2");
    Owner* owner_arr = new Owner[2];
    owner_arr[0] = o1;
    owner_arr[1] = o1;    

    //Crete the business itself
    //Constructor parameters: name, address, owner_array, number_of_owners
    Business atlas = Business("Atlas", "Maslak Istanbul/Turkey", owner_arr, 2);
    
    // Print owner info to screen: name, surname, ownership
    atlas.list_owners();

    // Add new employees
    // Constructor parameters: name, surname, vehicle_type
    Courier c1 = Courier("Courier", "surname1", "car");
    Courier c2 = Courier("Courier", "surname2", "motorcycle");
    Courier c3 = Courier("Courier", "surname3", "motorcycle");    

    atlas.hire_courier(c1);
    atlas.hire_courier(c2);
    atlas.hire_courier(c3);


    // Print business info to screen
    // Name, address, owners, couriers
    atlas();

    // Get courier with index 1 and remove it from the list/array
    Courier cour = atlas[1];
    atlas.fire_courier(cour);
    
    // Print remaining couriers
    atlas.list_couriers();
    
    // Print current maximum shipment capacity
    std::cout << atlas.calculate_shipment_capacity() << std::endl;
    return 0;

}
	
