#include <map>
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
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
		if(DEBUG_STATEMENTS){
			for(auto el : page_tr){
				cout << el.first << " " << el.second << endl;
			}
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
		vector<vector<double>> mtx = vector<vector<double>>(num_pages);
		for(int i = 0; i < num_pages; i++){
			mtx[i] = vector<double>(num_pages);
			for(int j = 0; j < num_pages; j++){
				mtx[i].assign(num_pages, 0);
			}
			/*
			0 => 1 2 
			1 => 2 
			2 => 3 
			3 => 4 
			4 => 0 1
			*/
			//created the empty matrix
			for(const auto &el : list){	//for every el in the list
				for(auto item : el.second){
					if(DEBUG_STATEMENTS){
						cout << item << " " << el.first << endl;
					}
					if(item == i){
						mtx[i][el.first] = 1.0/page_outdegree(el.first);
					}
				}
			}
		}
		//printing to check it
		if(DEBUG_STATEMENTS){
			for(int i = 0; i < num_pages; i++){
				for(int j = 0; j < num_pages; j++){
					printf("%5.2lf", mtx[i][j]);
				}
				cout << endl;
			}
		}

		vector<double> r = vector<double>(num_pages);
		r.assign(num_pages, 1.0/((double)num_pages));

		if(DEBUG_STATEMENTS){
			for(auto el : page_tr){
				cout << el.first << " " << r[el.second] << endl;
			}
		}
			
		for(int k = 0; k < p - 1; k++){
			vector<double> rn = vector<double>(num_pages);
			rn.assign(num_pages, 0);
			
			for(int i = 0; i < num_pages; i++){
				double sum = 0;
				for(int j = 0; j < num_pages; j++){
					if(DEBUG_STATEMENTS){
						cout << mtx[i][j] << " * " << r[j] << " = " << (mtx[i][j] * r[j]) << endl;
					}
					sum += (mtx[i][j] * r[j]);
				}
				if(DEBUG_STATEMENTS){
					cout << "Final sum: " << sum << endl;
				}
				rn[i] = sum;
			}
			for(int i = 0; i < num_pages; i++){
				r[i] = rn[i];
			}
			if(DEBUG_STATEMENTS)
				cout << "Power iteration " << k + 1 << " complete!" << endl;
		}
		//final print with the site names in alph order
		
		for(auto el : page_tr){
			cout << fixed << showpoint;
			cout << setprecision(2);
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
