// Implement DFS & BFS. Use undirected graph and develop recursive algorithm 

// BFS: breadth first search
// Shortest path in unweighted graphs
// Example:
// Google Maps (minimum number of roads)
// Finding minimum number of moves in a game (chess, puzzles)
// BFS => Because BFS checks all adjacent nodes first, so the first time you reach a place → it’s the shortest path.


// DFS: depth first search
// Cycle detection
// Example:
// Deadlock detection in OS
// Checking circular dependencies
// Detecting infinite loops in graphs
// DFS => DFS naturally tracks the recursion stack → easy to detect cycles.


#include <bits/stdc++.h>
using namespace std;

class Node{
	string name;
	Node *next;
	Node *down;
public:
	Node(string n):name(n),next(nullptr),down(nullptr){}
	friend class Graph;
};

class Graph{
	Node *head;
	void insert(string a,string b){
		if(!head){
			Node *nodeA = new Node(a);
			Node *nodeB = new Node(b);
			head = nodeA;
			nodeA->next = nodeB;
		}else{
			Node *nptr = head;
			Node *parent = nullptr;
			while(nptr){
				if(nptr->name == a){
					while(nptr->next){
						nptr = nptr->next;
					}
					Node *nodeB = new Node(b);
					nptr->next = nodeB;
					return;
				}
				parent = nptr;
				nptr = nptr->down;
			}
			Node *nodeA = new Node(a);
			Node *nodeB = new Node(b);
			nodeA->next = nodeB;
			if(parent)
				parent->down = nodeA;
			else
				head->down = nodeA;
		}
	}
	bool isConnected(){
		if(head){
			string name = head->name;
			stack<string> s;
			vector<string> visited;
			s.push(name);
			visited.push_back(name);
			while(!s.empty()){
				name = s.top();
				s.pop();

				Node *nptr = head;
				while(nptr){
					if(nptr->name == name){
						Node *curr = nptr->next;
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
			Node *nptr = head;
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

	void insertEdge(string cityA,string cityB){
		insert(cityA,cityB);
		insert(cityB,cityA);
	}

	void display(){
		if(!head){
			cout<<"Empty graph"<<endl;
			return;
		}else{
			Node *nptr = head;
			while(nptr){
				Node *curr = nptr->next;
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
	// void displayBFS(string name){
	// 	if(!isConnected()){
	// 		cout<<"Graph is not connected"<<endl;
	// 		return;
	// 	}
	// 	if(!head){
	// 		cout<<"Empty graph"<<endl;
	// 		return;
	// 	}else{
	// 		cout<<"BFS : \t";
	// 		queue<string> q;
	// 		vector<string> visited;
	// 		q.push(name);
	// 		visited.push_back(name);
	// 		while(!q.empty()){
	// 			name = q.front();
	// 			q.pop();
	// 			cout<<name<<",  ";
	// 			bool found = false;
	// 			Node *nptr = head;
	// 			while(nptr){
	// 				if(nptr->name == name){
	// 					found = true;
	// 					Node *curr = nptr->next;
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
	void displayBFS(queue<string> &q,vector<string> &visited){
		if(q.empty())return;
		string name = q.front();
			q.pop();
			cout<<name<<",  ";
			// bool found = false;
			Node *nptr = head;
			while(nptr){
				if(nptr->name == name){
					// found = true;
					Node *curr = nptr->next;
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
	void displayBFS(string name){
		if(!isConnected()){
			cout<<"Graph is not connected"<<endl;
			return;
		}
		if(!head){
			cout<<"Empty graph"<<endl;
			return;
		}
		cout<<"BFS : \t";
		queue<string> q;
		vector<string> visited;
		q.push(name);
		visited.push_back(name);
		
		displayBFS(q,visited);

		cout<<endl;
		
	}

	// Non recursive 
	// void displayDFS(string name){
	// 	if(!isConnected()){
	// 		cout<<"Graph is not connected"<<endl;
	// 		return;
	// 	}
	// 	if(!head){
	// 		cout<<"Empty graph"<<endl;
	// 		return;
	// 	}else{
	// 		cout<<"DFS : \t";
	// 		stack<string> s;
	// 		vector<string> visited;
	// 		s.push(name);
	// 		visited.push_back(name);
	// 		while(!s.empty()){
	// 			name = s.top();
	// 			s.pop();
	// 			cout<<name<<",  ";
	// 			bool found = false;
	// 			Node *nptr = head;
	// 			while(nptr){
	// 				if(nptr->name == name){
	// 					found = true;
	// 					Node *curr = nptr->next;
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
	void displayDFS(stack<string> &s,vector<string> &visited){
		if(s.empty())return;
		string name = s.top();
		s.pop();
		cout<<name<<",  ";
		bool found = false;
		Node *nptr = head;
		while(nptr){
			if(nptr->name == name){
				found = true;
				Node *curr = nptr->next;
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
	void displayDFS(string name){
		if(!isConnected()){
			cout<<"Graph is not connected"<<endl;
			return;
		}
		if(!head){
			cout<<"Empty graph"<<endl;
			return;
		}else{
			cout<<"DFS : \t";
			stack<string> s;
			vector<string> visited;
			s.push(name);
			visited.push_back(name);
					
			displayDFS(s,visited);

			cout<<endl;
		}
	}


};

int main() {
	Graph g;

	string menu = "1. Insert road. \n2. Display. \n3. Display BFS. \n4. Display DFS. \n5. Exit.";
	cout<<menu<<endl;


	while(true){
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




	// g.insertEdge("A","B");
	// g.insertEdge("C","B");
	// g.insertEdge("C","A");
	// g.insertEdge("A","D");
	// g.insertEdge("F","D");
	// g.insertEdge("F","G");
	// g.insertEdge("D","G");
	// g.insertEdge("A","B");
	// g.display();
	// g.displayBFS("A");
	// g.displayBFS("B");
	// g.displayDFS("A");
	// g.displayDFS("B");

	// g.insertEdge( "Katraj" , "PICT" ) ;
	// g.insertEdge( "Bharti" , "Katraj" ) ;
	// g.insertEdge( "Bharti" , "PICT" ) ;
	// g.insertEdge( "Katraj" , "SKNCOE" ) ;
	// g.insertEdge( "PICT" , "SKNCOE" ) ;
	// g.insertEdge( "SKNCOE" , "Temple" ) ;
	// g.insertEdge( "Temple" , "Katraj" ) ;
	// g.insertEdge( "Temple" , "Kondhwa" ) ;
	// g.display();
	// g.displayBFS("PICT");
	// g.displayDFS("PICT");

	cout << "Hello World" << endl;
	return 0;
}
