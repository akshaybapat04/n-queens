#include<iostream>
#include<vector>
#include<stdlib.h>
#include<time.h>
#include<random>
using namespace std;

#define iter 1000;

bool is_solved(vector <int> v){
	for(int i=0;i<v.size();i++){
		for(int j=i+1;j<v.size();j++){
			if(v[i] == v[j]){
				return 0;
			}
			else if(v[i]-v[j] == i-j){
				return 0;
			}
			else if(v[i]-v[j] == j-i){
				return 0;
			}
		}
	}
	return 1;
}

int count_conflicts(vector <int> v){
	int conflicts=0;
	for(int i=0;i<v.size();i++){
		for(int j=i+1;j<v.size();j++){
			if((v[i] == v[j])||(v[i]-v[j] == i-j)||(v[i]-v[j] == j-i)){
				conflicts++;
			}
		}
	}
	return conflicts;	
}

int randval(int x){
	return rand()%x;
}

int findbestval(vector <int> v, int loc){
	int i,n = v.size();
	vector <int> all_conflicts;
	for(i=0;i<n;i++){
		v[loc] = i;
		all_conflicts.push_back(count_conflicts(v));
	}
	int minval = all_conflicts[0];
	for(i=1;i<n;i++){
		if(minval<all_conflicts[i]){
			minval = all_conflicts[i];
		}
	}
	vector <int> choosefromthesevals;
	for(i=0;i<n;i++){
		if(all_conflicts[i]==minval){
			choosefromthesevals.push_back(i);
		}
	}
	return choosefromthesevals[randval(choosefromthesevals.size())];
}

void min_conflicts(vector <int> &v){
	int n = v.size(),num_conf;
	vector <int> conflicts;
	for(int i=0;i<n;i++){
		num_conf = 0;
		for(int j=0;j<n;j++){
			if(i==j){
				continue;
			}
			else{
				if(v[i] == v[j]){
					num_conf++;
					break;
				}
				else if(v[i]-v[j] == i-j){
					num_conf++;
					break;
				}
				else if(v[i]-v[j] == j-i){
					num_conf++;
					break;
				}
			}
		}
		if(num_conf>0){
			conflicts.push_back(i);
		}
		
	}

	// Print all conflicting colums
	for(int i=0;i<conflicts.size();i++){
		cout<<conflicts[i]<<" ";
	}
	cout<<endl;	
	
	int rand_loc = conflicts[randval(conflicts.size())];
	//Pass by ref instead
	v[rand_loc] = findbestval(v,rand_loc);
}

void solve(int n){
	int i,count=iter;
	vector <int> v;
//	for(i=0;i<n;i++){
//		v.push_back(randval(n));
//	}
	
	cout<<"Initial State:";
	for(i=0;i<n;i++){
		cout<<v[i]<<" ";
	}
	cout<<endl;
	cout<<"==============="<<endl;
	
	while(!is_solved(v) && count){
		min_conflicts(v);
		cout<<"For iteration "<<count<<endl;
//		if(count%10==0){
//			cout<<count_conflicts(v)<<" ";
//		}
		count--;
	}
	if(is_solved(v)){
		cout<<"Solved!";
	}
}

int main(){
	int n;
	srand (time(NULL));
	n = 4;
	solve(n);
	return 0;
}	
