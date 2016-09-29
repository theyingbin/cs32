#include "Multiset.h"

/*
    Default Constructor
	Creates an empty LinkedList
*/
Multiset::Multiset(){
	head = nullptr;
	tail = nullptr;
}


/*
    Copy Constructor
	Creates a LinkedList based on the LinkedList passed into the argument
*/
Multiset::Multiset(const Multiset& copy){
	Node* traverser = copy.head;  // Node that traverses copy's LinkedList
	Node* lastItem = nullptr;     // Node that comes before traverser
	head = nullptr;               // Reset head
	tail = nullptr;               // Reset tail
	while (traverser != nullptr){
		Node* item = new Node;					// Creates a new Node
		item->value = traverser->value;			// Copys the value of the Node traverser is pointing to into the new Node
		item->numItems = traverser->numItems;   // Copys numItems of the Node traverser is pointing to into the new Node
		item->next = nullptr;				
		item->prev = lastItem;					// Links item with the previous Node
		if (lastItem != nullptr){				
			lastItem->next = item;				// Links lastItem with item
		}
		if (traverser->prev == nullptr){
			head = item;						// Checks to see if item should be the head pointer
		}
		if (traverser->next == nullptr){
			tail = item;						// Checks to see if item should be the tail pointer
		}
		lastItem = item;						// Updates lastItem
		traverser = traverser->next;			// Updates traverser
	}
}

/*
    Destructor
	Deletes all the Nodes in the LinkedList
*/
Multiset::~Multiset(){
	Node* traverser = head;
	while (traverser != nullptr){
		Node* killMe = traverser;
		traverser = traverser->next;
		delete killMe;
	}
}

/*
    Assignment Operator
	Copies all the content of the parameter into the current LinkedList
*/
Multiset& Multiset::operator=(const Multiset& other){
	// Checks for aliasing
	if (this == &other)
		return *this;

	// Deletes all the content in the current LinkedList and sets head and tail to nullptr
	Node* traverser = head;
	while (traverser != nullptr){
		Node* killMe = traverser;
		traverser = traverser->next;
		delete killMe;
	}
	head = nullptr;
	tail = nullptr;


	traverser = other.head;							// Node that traverses copy's LinkedList
	Node* lastItem = nullptr;						// Node that comes before traverser
	while (traverser != nullptr){
		Node* item = new Node;						// Creates a new Node
		item->value = traverser->value;				// Copies traverser's value into item's value
		item->numItems = traverser->numItems;		// Copies traverser's numItems into item's numItems
		item->prev = lastItem;						// Links item with lastItem
		item->next = nullptr;
		if (lastItem != nullptr){
			lastItem->next = item;					// Links lastItem with item
		}
		if (traverser->prev == nullptr){
			head = item;							// Checks to see if item should be the head pointer
		}
		if (traverser->next == nullptr){
			tail = item;							// Checks to see if item should be the tail pointer
		}
		lastItem = item;							// Updates lastItem
		traverser = traverser->next;				// Updates traverser
	}
	return (*this);
}

/*
	Checks if LinkedList is empty
	Returns true if it is and false otherwise
*/
bool Multiset::empty() const{
	if (head == nullptr && tail == nullptr){		// Checks if head and tail are nullptr
		return true;							
	}
	else{
		return false;
	}
}

/*
	Gives the size of the LinkedList
	Returns an int representing the number values (not distinct) in the LinkedList
*/
int Multiset::size() const{
	Node* p = head;
	int items = 0;									// Counter that increments everytime we hit a Node
	while (p != nullptr){
		items += p->numItems;						// Add numItems to the counter
		p = p->next;								// Update p
	}
	return items;
}

/*
	Gives the unique size of the LinkedList
	Returns an int representing the number of Nodes (distinct) in the LinkedList
*/
int Multiset::uniqueSize() const{
	Node* p = head;
	int uniqueItems = 0;							// Counter that increments everytime we hit a Node
	while (p != nullptr){
		uniqueItems++;								// Increments counter by 1
		p = p->next;								// Updates p
	}
	return uniqueItems;
}

/*
	Does one of two things:
	-Inserts into LinkedList a new Node whose value is given by the parameter
	-Increments numItems of an existing Node if it's value is the same as that of the parameter
	If a new Node is added, it is added to the front of the LinkedList
	Always returns true
*/
bool Multiset::insert(const ItemType& value){
	Node* traverser = head;
	
	// Checks to see if there is an existing Node whose value is equal to the parameter
	// If so, increment numItems and exit the function
	while (traverser != nullptr){
		if (traverser->value == value){
			traverser->numItems++;
			return true;
		}
		traverser = traverser->next;				
	}

	Node* p = new Node;								// Creates a new Node
	p->value = value;								// Sets the Node's value to be the parameter of the function
	p->numItems = 1;								// Sets the Node's numItems to be 1
	p->next = head;									// Links the Node with the Node that head is pointing to
	p->prev = nullptr;								
	if (head != nullptr){
		head->prev = p;								// Links the Node head is pointing to with the new Node
	}
	head = p;										// Updates head
	if (tail == nullptr){
		tail = p;									// Sets tail to p if tail points to nullptr
	}
	return true;
}

/*
	Checks to see if there is a Node with the same value as the parameter
	If so do one of two things:
	-Decrement numItems in the Node
	-Delete the Node
	Returns the number that was erased (either 1 or 0)
*/
int Multiset::erase(const ItemType& value){
	return doErase(false, value);					// Calls the Helper Function doErase
}

/*
	Checks to see if there is a Node with the same value as the parameter
	If so delete the Node
	Returns the number that was erased
*/
int Multiset::eraseAll(const ItemType& value){
	return doErase(true, value);					// Calls the Helper Function doErase
}

/*
	Checks to see if the passed in parameter is in the LinkedList
	If so, return true, otherwise, return false
*/
bool Multiset::contains(const ItemType& value) const{
	Node* traverser = head;
	while (traverser != nullptr){					// Traverse through the LinkedList until nullptr is hit
		if (traverser->value == value){				// Checks if the value of the Node is the same as the parameter
			return true;
		}
		traverser = traverser->next;				// Updates traverser
	}
	return false;
}

/*
	Checks to see if the passed in parameter is in the LinkedList
	Returns an int representing the number of items in the Node with the same value as the passed in parameter
*/
int Multiset::count(const ItemType& value) const{
	Node* traverser = head;						
	while (traverser != nullptr){					// Traverses Through the LinkedList
		if (traverser->value == value){				// Checks if the value of the Node is the same as the parameter
			return traverser->numItems;				// Return numItems of that Node
		}
		traverser = traverser->next;				// Updates traverser
	}
	return 0;										// Returns 0 if value was not found in any Node
}

/*
	Modifies value to be the i-th element in the LinkedList
	Returns the number of items in the i-th element
*/
int Multiset::get(int i, ItemType& value) const{
	// Checks to see if i is an element in the LinkedList that will not go out-of-bounds
	if (i < 0 || i >= uniqueSize()){
		return 0;
	}
	int counter = 0;								// Declares an integer representing the element of the LinkedList that is being observed
	Node* traverser = head;
	while (traverser != nullptr){
		if (counter == i){
			break;									// If i equals counter, we break from the loop
		}
		traverser = traverser->next;				// Update traverser
		counter++;									// Update counter
	}
	value = traverser->value;						// Modifies value to be traverser's value
	return traverser->numItems;						// Returns numItems of the Node we are looking at
}

/*
	Takes in a reference to a Multiset named other
	Swaps the contents of this Multiset and other
*/
void Multiset::swap(Multiset& other){
	if (this == &other){
		return;										// Although this is not needed, we check for aliasing
	}
	Multiset temp = (*this);						// Uses copy constructor to copy the value of this Multiset into temp
	(*this) = other;								// Sets This Multiset to other
	other = temp;									// Sets other to tmep
}

/*
	Helper Function
	Since erase and eraseAll do very similar task, this helper function was made to reduce repetition
	If all is true, delete the Node rather than decrement it
*/
int Multiset::doErase(bool all, const ItemType& value){
	Node* traverser = head;
	bool deleted = false;							// Indicates whether or not to delete a Node later
	int numDeleted = -1;							// Represents the number of items deleted. Initialized to -1 to allow for better debugging
	while (traverser != nullptr){					// Loop through the LinkedList	
		if (traverser->value == value){				// Checks if value is equal to the parameter
			if (!all){													
				numDeleted = 1;						
				traverser->numItems--;				// Decrements numItems
			}
			else{
				numDeleted = traverser->numItems;
				traverser->numItems = 0;			// Sets numItems to zero
			}
			deleted = true;							// Changes deleted to true
			break;									// Break from the loop. Unnecessary but makes the code run a little faster
		}
		traverser = traverser->next;				// Update traverser
	}
	traverser = head;								// Reset traverser

	// The following code checks to see if numItems in any Node is equal to zero. If so, delete that Node
	while (traverser != nullptr){
		if (traverser->numItems == 0){				// Checks if numItems is zero
			Node* before = traverser->prev;			// Create a Node pointer representing prev and next
			Node* after = traverser->next;
			if (before != nullptr){
				before->next = after;				// Links before with after
			}
			if (after != nullptr){
				after->prev = before;				// Links after with before
			}
			if (traverser == head){
				head = after;						// Updates head if traverser is head
			}
			if (traverser == tail){
				tail = before;						// Updates tail if traverser is tail
			}
			delete traverser;						// Delete traverser
			break;									// Break from the loop
		}
		traverser = traverser->next;				// Update traverser
	}

	if (deleted){
		return numDeleted;							// If a Node was deleted, return numDeleted
	}
	else{
		return 0;
	}
}

/*
	Takes in three Multisets in the parameter
	Copies the content of ms1 and ms2 and combines them to put it in result
*/
void combine(const Multiset& ms1, const Multiset& ms2, Multiset& result){
	Multiset copy = ms1;							// Creates a Multiset and uses the copy constructor to copy the values from ms1

	// Loops through m2 and adds the item into copy
	for (int i = 0; i < ms2.uniqueSize(); i++){
		ItemType item;
		int repeats = ms2.get(i, item); 
		for (int j = 0; j < repeats; j++){
			copy.insert(item);
		}
	}

	result = copy;									// Uses the assignment operator to set result to copy (prevents aliasing)
}

/*
	Takes in three Multisets in the parameter
	Subtracts the numItems of ms2 from ms1
	Example: if ms1 had a Node with value 5 and numItems 7
			 and ms2 had a Ndoe with value 5 and numItems 3
			 result should have a Node with value 5 and numItems (7-3)
*/
void subtract(const Multiset& ms1, const Multiset& ms2, Multiset& result){
	Multiset copy = ms1;							// Creates a Multiset and uses the copy constructor to copy the values from ms1

	// Loops through m2 and adds the item into copy
	for (int i = 0; i < ms2.uniqueSize(); i++){
		ItemType item;
		int repeats = ms2.get(i, item);
		for (int j = 0; j < repeats; j++){
			copy.erase(item);
		}
	}
	result = copy;									// Uses the assignment operator to set result to copy (prevents aliasing)
}
