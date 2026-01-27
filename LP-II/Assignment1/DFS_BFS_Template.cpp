#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct Node{
	T name;
	Node<T> *next;
	Node<T> *down;
public:
	Node(T n):name(n),next(nullptr),down(nullptr){}
};

template<typename T>
class Graph{
	Node<T> *head;
	void insert(T a,T b){
		if(!head){
			Node<T> *nodeA = new Node<T>(a);
			Node<T> *nodeB = new Node<T>(b);
			head = nodeA;
			nodeA->next = nodeB;
		}else{
			Node<T> *nptr = head;
			Node<T> *parent = nullptr;
			while(nptr){
				if(nptr->name == a){
					while(nptr->next){
						nptr = nptr->next;
					}
					Node<T> *nodeB = new Node<T>(b);
					nptr->next = nodeB;
					return;
				}
				parent = nptr;
				nptr = nptr->down;
			}
			Node<T> *nodeA = new Node<T>(a);
			Node<T> *nodeB = new Node<T>(b);
			nodeA->next = nodeB;
			if(parent)
				parent->down = nodeA;
			else
				head->down = nodeA;
		}
	}
	bool isConnected(){
		if(head){
			T name = head->name;
			stack<T> s;
			vector<T> visited;
			s.push(name);
			visited.push_back(name);
			while(!s.empty()){
				name = s.top();
				s.pop();

				Node<T> *nptr = head;
				while(nptr){
					if(nptr->name == name){
						Node<T> *curr = nptr->next;
						while(curr){
							if(find(visited.begin(),visited.end(),curr->name) == visited.end()){
								visited.push_back(curr->name);
								s.push(curr->name);
							}
							curr = curr->next;
						}
						break;
					}
					nptr = nptr->down;
				}
			}
			Node<T> *nptr = head;
			while(nptr){
				if(find(visited.begin(),visited.end(),nptr->name) == visited.end())
					return false;
				nptr = nptr->down;
			}
		}
		return true;
	}

	public:
	Graph(){
		head = nullptr;
	}

	void insertEdge(T cityA,T cityB){
		insert(cityA,cityB);
		insert(cityB,cityA);
	}

	void display(){
		if(!head){
			cout<<"Empty graph"<<endl;
			return;
		}else{
			Node<T> *nptr = head;
			while(nptr){
				Node<T> *curr = nptr->next;
				cout.width(20);
				cout<<nptr->name;
				cout<<" =>\t";
				while(curr){
					cout<<curr->name<<",\t";
					curr = curr->next;
				}
				cout<<endl;
				nptr = nptr->down;
			}
		}
	}


	// Non recursive 
	// void displayBFS(T name){
	// 	if(!isConnected()){
	// 		cout<<"Graph is not connected"<<endl;
	// 		return;
	// 	}
	// 	if(!head){
	// 		cout<<"Empty graph"<<endl;
	// 		return;
	// 	}else{
	// 		cout<<"BFS : \t";
	// 		queue<T> q;
	// 		vector<T> visited;
	// 		q.push(name);
	// 		visited.push_back(name);
	// 		while(!q.empty()){
	// 			name = q.front();
	// 			q.pop();
	// 			cout<<name<<",  ";
	// 			bool found = false;
	// 			Node<T> *nptr = head;
	// 			while(nptr){
	// 				if(nptr->name == name){
	// 					found = true;
	// 					Node<T> *curr = nptr->next;
	// 					while(curr){
	// 						if(find(visited.begin(),visited.end(),curr->name) == visited.end()){
	// 							visited.push_back(curr->name);
	// 							q.push(curr->name);
	// 						}
	// 						curr = curr->next;
	// 					}
	// 					break;
	// 				}
	// 				nptr = nptr->down;
	// 			}
	// 			if(!found){
	// 				cout<<"Node not in graph"<<endl;
	// 				return;
	// 			}
	// 		}
	// 		cout<<endl;
	// 	}
	// }

	// recursive 
	void displayBFS(queue<T> &q,vector<T> &visited){
		if(q.empty())return;
		T name = q.front();
			q.pop();
			cout<<name<<",  ";
			// bool found = false;
			Node<T> *nptr = head;
			while(nptr){
				if(nptr->name == name){
					// found = true;
					Node<T> *curr = nptr->next;
					while(curr){
						if(find(visited.begin(),visited.end(),curr->name) == visited.end()){
							visited.push_back(curr->name);
							q.push(curr->name);
						}
						curr = curr->next;
					}
					break;
				}
				nptr = nptr->down;
			}
			displayBFS(q,visited);
	}
	void displayBFS(T name){
		if(!isConnected()){
			cout<<"Graph is not connected"<<endl;
			return;
		}
		if(!head){
			cout<<"Empty graph"<<endl;
			return;
		}
		cout<<"BFS : \t";
		queue<T> q;
		vector<T> visited;
		q.push(name);
		visited.push_back(name);
		
		displayBFS(q,visited);

		cout<<endl;
		
	}


	// Non recursive 
	// void displayDFS(T name){
	// 	if(!isConnected()){
	// 		cout<<"Graph is not connected"<<endl;
	// 		return;
	// 	}
	// 	if(!head){
	// 		cout<<"Empty graph"<<endl;
	// 		return;
	// 	}else{
	// 		cout<<"DFS : \t";
	// 		stack<T> s;
	// 		vector<T> visited;
	// 		s.push(name);
	// 		visited.push_back(name);
	// 		while(!s.empty()){
	// 			name = s.top();
	// 			s.pop();
	// 			cout<<name<<",  ";
	// 			bool found = false;
	// 			Node<T> *nptr = head;
	// 			while(nptr){
	// 				if(nptr->name == name){
	// 					found = true;
	// 					Node<T> *curr = nptr->next;
	// 					while(curr){
	// 						if(find(visited.begin(),visited.end(),curr->name) == visited.end()){
	// 							visited.push_back(curr->name);
	// 							s.push(curr->name);
	// 						}
	// 						curr = curr->next;
	// 					}
	// 					break;
	// 				}
	// 				nptr = nptr->down;
	// 			}
	// 			if(!found){
	// 				cout<<"Node not in graph"<<endl;
	// 				return;
	// 			}
	// 		}
	// 		cout<<endl;
	// 	}
	// }

	// recursive 
	void displayDFS(stack<T> &s,vector<T> &visited){
		if(s.empty())return;
		T name = s.top();
		s.pop();
		cout<<name<<",  ";
		bool found = false;
		Node<T> *nptr = head;
		while(nptr){
			if(nptr->name == name){
				found = true;
				Node<T> *curr = nptr->next;
				while(curr){
					if(find(visited.begin(),visited.end(),curr->name) == visited.end()){
						visited.push_back(curr->name);
						s.push(curr->name);
					}
					curr = curr->next;
				}
				break;
			}
			nptr = nptr->down;
		}
		displayDFS(s,visited);
	}
	void displayDFS(T name){
		if(!isConnected()){
			cout<<"Graph is not connected"<<endl;
			return;
		}
		if(!head){
			cout<<"Empty graph"<<endl;
			return;
		}else{
			cout<<"DFS : \t";
			stack<T> s;
			vector<T> visited;
			s.push(name);
			visited.push_back(name);
					
			displayDFS(s,visited);

			cout<<endl;
		}
	}


};

int main() {
	Graph<string> g;
	Graph<int> g1;

	string menu = "1. Insert road. \n2. Display. \n3. Display BFS. \n4. Display DFS. \n5. Exit.";
	cout<<menu<<endl;


	while(!true){
		int choice;
		cout<<endl<<"Enter choice : ";
		cin>>choice;

		if(choice == 1){
			string node1,node2;
			cout<<"Enter node 1 : ";
			cin>>node1;
			cout<<"Enter node 2 : ";
			cin>>node2;
			g.insertEdge(node1,node2);
		}else if(choice == 2){
			g.display();
		}else if(choice == 3){
			string name;
			cout<<"Enter node : ";
			cin>>name;
			g.displayBFS(name);
		}else if(choice == 4){
			string name;
			cout<<"Enter node : ";
			cin>>name;
			g.displayDFS(name);
		}else if(choice == 5){
			cout<<"Thank You !"<<endl;
			break;
		}else{
			cout<<"Invalid choice."<<endl;
		}
	}


	g.insertEdge("A","B");
	g.insertEdge("C","B");
	g.insertEdge("C","A");
	g.insertEdge("A","D");
	g.insertEdge("F","D");
	g.insertEdge("F","G");
	g.insertEdge("D","G");
	g.insertEdge("A","B");
	g.display();
	g.displayBFS("A");
	g.displayBFS("B");
	g.displayDFS("A");
	g.displayDFS("B");


	g1.insertEdge(1,2);
	g1.insertEdge(2,3);
	g1.insertEdge(1,3);
	g1.insertEdge(1,4);
	g1.insertEdge(5,4);
	g1.insertEdge(5,6);
	g1.insertEdge(4,6);
	g1.insertEdge(1,2);
	g1.display();
	g1.displayBFS(1);
	g1.displayBFS(2);
	g1.displayDFS(1);
	g1.displayDFS(2);

    
	cout << "Hello World" << endl;
	return 0;
}
