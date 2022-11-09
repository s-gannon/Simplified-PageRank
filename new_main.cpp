#include <map>
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <initializer_list>

#define MAX 10000

using namespace std;

//to search for an element, do map.find(); if it doesn't exist
//in the list, it will return map.end()

class AdjacencyList{
private:
	int num_pages;
	map<string, int> page_tr; //page translation from str to int
	map<int, set<int>> list;
public:
	AdjacencyList(){
		num_pages = 0;
	}
	~AdjacencyList(){}
	void insert(string page, string link){
		cout << "Link from " << page << " to " << link << endl;
		if(page_tr.find(page) == page_tr.end())
			page_tr[page] = num_pages++;
		if(page_tr.find(link) == page_tr.end())
			page_tr[link] = num_pages++;
		list[page_tr[page]].insert(page_tr[link]);
	}
	// void print(){
	// 	for(const auto& el : list){
	// 		cout << el.first << " => ";
	// 		for(auto j : el.second){
	// 			cout << j << " ";
	// 		}
	// 		cout << endl;
	// 	}
	// }
	double page_outdegree(string page){
		return list[page_tr[page]].size();
	}
	double page_outdegree(int page){
		return list[page].size();
	}
	void PageRank(int p){
		cout << "?";
		vector<vector<double>> mtx;
		cout << "?";
		for(size_t i = 0; i < list.size(); i++){
			for(size_t j = 0; j < list.size(); j++){
				mtx[i].assign(list.size(), 0);
			}
			for(auto j : list[i]){
				int dj = page_outdegree(j);
				if(dj == 0){
					mtx[i][j] = 1;
				}
				else{
					mtx[i][j] = 1.0/page_outdegree(dj);
				}
			}
		}

		for(size_t i = 0; i < list.size(); i++){
			for(size_t j = 0; j < list.size(); j++){
				cout << mtx[i][j] << " ";
			}
			cout << endl;
		}


		for(int i = 0; i < p; p++){

		}
	}
};

int main(){
	AdjacencyList aj;
	string from, to;
	int num_lines, pow_iters;

	cin >> num_lines;
	cin >> pow_iters;

	for(int i = 0; i < num_lines; i++){
		cout << i;
		cin >> from;
		cin >> to;
		aj.insert(from, to);
	}
	cout << "?";
	// aj.print();
	
	aj.PageRank(pow_iters);

	return EXIT_SUCCESS;
}
