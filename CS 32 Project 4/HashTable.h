#ifndef HASHTABLE_INCLUDED
#define HASHTABLE_INCLUDED

// TODO: Ask about computeHash

template <typename KeyType, typename ValueType>
class HashTable{
public:
	
	HashTable(unsigned int buckets, unsigned int capacity){
		m_hashTable = new Node*[buckets];
		m_head = nullptr;
		m_tail = nullptr;
		for (int i = 0; i < buckets; i++){
			m_hashTable[i] = nullptr;
		}
		m_numItems = 0;
		m_capacity = capacity;
		m_buckets = buckets;
	}

	~HashTable(){
		for (int i = 0; i < m_buckets; i++){
			Node* curLinkedList = m_hashTable[i];
			for (; curLinkedList != nullptr;){
				Node* temp = curLinkedList;
				curLinkedList = curLinkedList->next;
				delete temp;
			}
			delete curLinkedList;
		}
		while (m_head != nullptr){
			Node* temp = m_head;
			m_head = m_head->next;
			delete temp;
		}
	}

	bool isFull() const{
		return m_numItems == m_capacity;
	}

	// TODO: Change the function so it checks only for the key and modifies value according to the value in the hashTable
	bool get(const KeyType& key, ValueType& value) const{
		// Faster Alternative: Call hash function on key and value to figure out the bucket
		// Then iterate through the bucket to see if any of the Nodes have the same KeyType and ValueType
		unsigned int computeHash(KeyType);
		unsigned int bucketNum = computeHash(key) % m_buckets;
		Node* current = m_hashTable[bucketNum];
		while (current != nullptr){
			if (current->key == key){
				value = current->value;
				return true;
			}
			current = current->next;
		}
		return false;
	}

	bool set(const KeyType&	key, const ValueType& value, bool permanent = false){
		ValueType toCheck;
		if (!get(key, toCheck)){
			if (isFull()){
				return false;
			}
			else{
				addNode(key, value, permanent);
				m_numItems++;
				return true;
			}
		}
		else{
			if (toCheck != value){
				return false;
			}
			unsigned int computeHash(KeyType);
			unsigned int bucketNum = computeHash(key) % m_buckets;
			bool perma;
			Node* temp = m_hashTable[bucketNum];
			while (temp != nullptr){
				if (temp->value == value){
					perma = temp->permanent;
					break;
				}
				temp = temp->next;
			}
			// TODO: update the priority
			if (perma){
				return false;
			}
			Node* traverser = m_head;
			while (traverser != nullptr){
				if (traverser->value == value && traverser->key == key){
					if (traverser->prev != nullptr){
						traverser->prev->next = traverser->next;
					}
					if (traverser->next != nullptr){
						traverser->next->prev = traverser->prev;
					}
					if (traverser == m_tail){
						m_tail = traverser->prev;
					}
					if (traverser == m_head){
						m_head = traverser->next;
					}
					delete traverser;
					break;
				}
			}
			addToList(key, value, perma);
			return true;
		}
	}

	// TODO: Get touch to have a run speed of O(B/C) where B is # of buckets and C is it's capacity
	bool touch(const KeyType& key){
		Node* traverser = m_head;
		while (traverser != nullptr){
			if (traverser->key == key){
				if (traverser->permanent){
					return false;
				}
				if (traverser->prev != nullptr){
					traverser->prev->next = traverser->next;
				}
				if (traverser->next != nullptr){
					traverser->next->prev = traverser->prev;
				}
				if (traverser == m_tail){
					m_tail = traverser->prev;
				}
				if (traverser == m_head){
					m_head = traverser->next;
				}
				addToList(traverser->key, traverser->value, traverser->permanent);
				delete traverser;
				return true;
			}
			traverser = traverser->next;
		}
		return false;
	}

	bool discard(KeyType& key, ValueType& value){
		if (m_head == nullptr || m_tail == nullptr){
			return false;
		}
		Node* temp = m_tail;
		m_tail = m_tail->prev;
		key = temp->key;
		value = temp->value;
		if (temp == m_head){
			m_head = nullptr;
			m_tail = nullptr;
		}
		delete temp;
		unsigned int computeHash(KeyType);
		unsigned int bucketNum = computeHash(key) % m_buckets;
		Node* current = m_hashTable[bucketNum];
		while (current != nullptr){
			if (current->value == value && current->key == key){
				if (current->next != nullptr){
					current->next->prev = current->prev;
				}
				if (current->prev != nullptr){
					current->prev->next = current->next;
				}
				if (current == m_hashTable[bucketNum]){
					m_hashTable[bucketNum] = current->next;
				}
				delete current;
				m_numItems--;
				return true;
			}
			current = current->next;
		}
		return false;
	}
private:
	// Definition of a Node
	struct Node{
		KeyType key;
		ValueType value;
		bool permanent;
		Node* next;
		Node* prev;
	};
	// We prevent a HashTable from being copied or assigned by declaring the
	// copy constructor and assignment operator private and not implementing them.
	HashTable(const HashTable&);
	HashTable& operator=(const HashTable&);

	void addNode(const KeyType&	key, const ValueType& value, bool permanent = false){
		unsigned int computeHash(KeyType);
		unsigned int bucketNum = computeHash(key) % m_buckets;
		Node* forHash = new Node();
		forHash->key = key;
		forHash->value = value;
		forHash->permanent = permanent;
		if (m_hashTable[bucketNum] != nullptr){
			m_hashTable[bucketNum]->prev = forHash;
			forHash->next = m_hashTable[bucketNum];
			forHash->prev = nullptr;
		}
		else{
			forHash->next = nullptr;
			forHash->prev = nullptr;
		}
		m_hashTable[bucketNum] = forHash;

		if (!permanent){
			addToList(key, value, permanent);
		}
	}
	void addToList(const KeyType& key, const ValueType& value, bool permanent){
		Node* forList = new Node();
		forList->key = key;
		forList->value = value;
		forList->permanent = permanent;
		forList->next = nullptr;
		forList->prev = nullptr;
		if (m_head == nullptr && m_tail == nullptr){
			m_head = forList;
			m_tail = forList;
		}
		else{
			forList->next = m_head;
			m_head->prev = forList;
			m_head = forList;
		}
	}
	// Member variables
	Node* m_head;				// Represents a LinkedList in order to keep track of priority and non-permanent Nodes
	Node* m_tail;
	Node** m_hashTable;
	unsigned int m_capacity;
	unsigned int m_numItems;
	unsigned int m_buckets;
};

#endif