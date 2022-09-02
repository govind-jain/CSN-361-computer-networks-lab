#include <iostream>
#include <list>

using namespace std;

class Node{
    public:
        int id;
        list<Node*> adj;

        Node(int i){
            id = i;
        }
};

class ringNetwork{
    private:
        list<Node*> graph;
        int size;
    
    public:
        ringNetwork(int n){

            if(n == 0){
                return;
            }

            Node* first = new Node(1);
            graph.push_back(first);

            Node* prev = first;
            
            for(int i=2; i<=n; i++){
                Node* newNode = new Node(i);
                graph.push_back(newNode);

                (prev->adj).push_back(newNode);
                (newNode->adj).push_back(prev);

                prev = newNode;
            }
            
            (prev->adj).push_back(first);
            (first->adj).push_back(prev);

            size = n;
        }

        void printNetwork(){

            for(auto it=graph.begin(); it != graph.end(); it++){

                Node* thisNode = *it;
                list<Node*> &thisAdjList = thisNode -> adj;

                cout<<(thisNode -> id)<<": ";

                for(auto it2=thisAdjList.begin(); it2!=thisAdjList.end(); it2++){
                    cout<<((*it2) -> id)<<" ";
                }
                
                cout<<endl;
            }
        }
};

int main(){

    ringNetwork rn = ringNetwork(10);
    rn.printNetwork();

    return 0;
}