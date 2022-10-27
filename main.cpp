#include <iostream>

using namespace std;

template <typename T>
class Node{
private:
	T data;
	Node* next;
public:
	T get_data(){return data;}
	Node<T>* get_next(){return next;}

	void set_data(T _data){data = _data;}
	void set_next(Node<T>* _next){next = _next;}
};

template <typename T>
class LinkedList{
private:
	Node<T> root;
public:
	void insert(T data, Node<T>* head){
		if(root == nullptr){
			root.set_data(data);
		}
		else if(head == nullptr){
			head->set_data(data);
		}
		else{
			insert(head->get_next(), data);
		}
	}
	Node<T>* search(T needle, Node<T>* head){
		if(root == nullptr){
			return nullptr;
		}
		else if(head->get_data() != needle && head->get_next() == nullptr){
			return nullptr;
		}
		else if(head->get_data() == needle){
			return head;
		}
		else{
			search(head->get_next(), needle);
		}
	}
	Node<T>* get_root(){return root;}
	//removes the specified data from LL
	//returns false if it failed / didn't exist in the list, true if it worked
	// bool remove_data(Node<T>* head = root; T data){
	// 	if(root == nullptr){
	// 		return false;
	// 	}

	// 	if(head.get_data() != )
	// }
};

int main(){
	cout << "Hello world!" << endl;
}
