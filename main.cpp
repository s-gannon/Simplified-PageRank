#include <map>
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <initializer_list>

#define MAX 10000
#define DEBUG_STATEMENTS 0

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
		if(DEBUG_STATEMENTS)
			cout << "Link from " << page << " to " << link << endl;
		if(page_tr.find(page) == page_tr.end())
			page_tr[page] = num_pages++;
		if(page_tr.find(link) == page_tr.end())
			page_tr[link] = num_pages++;
		list[page_tr[page]].insert(page_tr[link]);
	}
	void print(){
		for(const auto& el : list){
			cout << el.first << " => ";
			for(auto j : el.second){
				cout << j << " ";
			}
			cout << endl;
		}
	}
	double page_outdegree(string page){
		return list[page_tr[page]].size();
	}
	double page_outdegree(int page){
		if(DEBUG_STATEMENTS)
			cout << "Number of elements in page #" << page << " is " <<  list[page].size() << endl;
		return list[page].size();
	}
	void PageRank(int p){
		vector<vector<double>> mtx = vector<vector<double>>(list.size());
		for(size_t i = 0; i < list.size(); i++){
			mtx[i] = vector<double>(list.size());
			for(size_t j = 0; j < list.size(); j++){
				mtx[i].assign(list.size(), 0);
			}
			for(auto j : list[i]){
				double dj = page_outdegree(j);
				if(dj < 1 ){
					mtx[i][j] = 1;
				}
				else{
					mtx[i][j] = 1.0/dj;
				}
			}
		}
		//printing to check it
		if(DEBUG_STATEMENTS){
			for(size_t i = 0; i < list.size(); i++){
				for(size_t j = 0; j < list.size(); j++){
					cout << mtx[i][j] << " ";
				}
				cout << endl;
			}
		}

		vector<double> r = vector<double>(list.size());
		r.assign(list.size(), 1.0/((double)list.size()));

		for(auto el : page_tr){
			cout << el.first << " " << r[el.second] << endl;
		}

		for(int k = 0; k < p; k++){
			vector<double> rn = vector<double>(list.size());
			for(size_t i = 0; i < list.size(); i++){
				double sum = 0;
				for(size_t j = 0; j < list.size(); j++){
					sum += (mtx[i][j] * r[i]);
				}
				rn[i] = sum;
			}
			for(size_t i = 0; i < list.size(); i++){
				r[i] = rn[i];
			}
			if(DEBUG_STATEMENTS)
				cout << "Power iteration " << k + 1 << " complete!" << endl;
		}
		//final print with the site names in alph order
		
		for(auto el : page_tr){
			cout << el.first << " " << r[el.second] << endl;
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
		if(DEBUG_STATEMENTS)
			cout << i << " ";
		cin >> from;
		cin >> to;
		aj.insert(from, to);
	}
	// aj.print();
	
	aj.PageRank(pow_iters);

	return EXIT_SUCCESS;
}
