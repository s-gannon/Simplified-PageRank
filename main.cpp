#include <iostream>

using namespace std;

template <typename T>
class Node{
private:
	T data;
	Node* next;
public:
	Node(){
		next = nullptr;
	}
	Node(T _data){
		data = _data;
		next = nullptr;
	}
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
	LinkedList(){
		root = nullptr;
	}
	LinkedList(T data){
		root = Node<T>(data);
	}
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
};

template <typename T>
class AdjacencyList{
private:
	LinkedList<T> list;
public:

};

int main(){
	cout << "Hello world!" << endl;
}
