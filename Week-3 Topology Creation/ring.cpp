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
            size = 0;

            for(int i=1; i<=n; i++){
                addNode(i);
            }
        }

        void addNode(int el){

            auto itr = graph.begin();

            for(; itr != graph.end(); itr++){
                if((*itr)->id == el){
                    break;
                }
            }

            if(itr != graph.end()){
                cout<<"Element is already present"<<endl;
                return;
            }

            Node* toBeAdded = new Node(el);
            Node* first = NULL;
            Node* last = NULL;

            if(size > 0){
                first = *(graph.begin());

                (first->adj).push_back(toBeAdded);
                (toBeAdded->adj).push_front(first);
            }

            if(size > 1){
                last = *(graph.rbegin());

                (last->adj).push_back(toBeAdded);
                (toBeAdded->adj).push_front(last);
            }

            if(size > 2){
                (first->adj).remove(last);
                (last->adj).remove(first);
            }

            graph.push_back(toBeAdded);
            size++;
        }

        void deleteNode(int el){

            if(size == 0){
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

                (prev->adj).remove(toBeDeleted);
                (next->adj).remove(toBeDeleted);
            }

            if(prev != next){
                (prev->adj).push_back(next);
                (next->adj).push_front(prev);
            }

            (toBeDeleted->adj).clear();
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

    int n;

    cout<<"Please input the size of the network"<<endl;
    cin>>n;

    ringNetwork rn = ringNetwork(n);
    
    while(1){
        int op;

        cout<<"\n";
        cout<<"Press 1 and Enter for adding a node\n";
        cout<<"Press 2 and Enter for deleting a node\n";
        cout<<"Press 3 and Enter for printing the network\n";
        cout<<endl;

        cin>>op;

        switch (op){
            case 1:
                int nodeToBeAdded;
                cout<<"Enter ther node id"<<endl;
                cin >> nodeToBeAdded;
                rn.addNode(nodeToBeAdded);
                break;
            
            case 2:
                int nodeToBeDeleted;
                cout<<"Enter ther node id"<<endl;
                cin >> nodeToBeDeleted;
                rn.deleteNode(nodeToBeDeleted);
                break;

            case 3:
                rn.printNetwork();
                break;
        }
        
    }

    return 0;
}