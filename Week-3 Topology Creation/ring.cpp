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

        void deleteNode(int el){

            if(graph.size() == 0){
                cout<<"Graph is empty"<<endl;
                return;
            }

            Node* prev = NULL;
            auto itr = graph.begin();

            for(; itr != graph.end(); itr++){

                if((*itr)->id == el){
                    break;
                }

                prev = *itr;
            }

            if(itr == graph.end()){
                cout<<"Element is not present"<<endl;
                return;
            }

            Node* toBeDeleted = *itr;

            auto nextItr = itr;
            advance(nextItr, 1);
            Node *next = (nextItr != graph.end())? *nextItr: NULL;

            graph.erase(itr);
            size--;

            if(size > 0){
                if(prev == NULL){
                    prev = *(graph.rbegin());
                }
                else if(next == NULL){
                    next = *(graph.begin());
                }

                if(prev == next){
                    (next->adj).remove(toBeDeleted);
                }
                else{
                    (prev->adj).remove(toBeDeleted);
                    (next->adj).remove(toBeDeleted);

                    (prev->adj).push_back(next);
                    (next->adj).push_front(prev);
                }

                (toBeDeleted->adj).clear();
            }

            delete(toBeDeleted);
            cout<<"Successfully deleted the node: "<<el<<endl;
        }

        void printNetwork(){

            cout<<"--------------"<<endl;

            for(auto it=graph.begin(); it != graph.end(); it++){

                Node* thisNode = *it;
                list<Node*> &thisAdjList = thisNode -> adj;

                cout<<(thisNode -> id)<<": ";

                for(auto it2=thisAdjList.begin(); it2!=thisAdjList.end(); it2++){
                    cout<<((*it2) -> id)<<" ";
                }
                
                cout<<endl;
            }

            cout<<"--------------"<<endl;
        }
};

int main(){

    ringNetwork rn = ringNetwork(10);
    rn.printNetwork();

    rn.deleteNode(1);
    rn.printNetwork();

    rn.deleteNode(10);
    rn.printNetwork();

    rn.deleteNode(7);
    rn.printNetwork();

    return 0;
}