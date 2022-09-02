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

class meshNetwork{
    private:
        list<Node*> graph;
        int size;
    
    public:
        meshNetwork(int n){
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

            for(auto it=graph.begin(); it != graph.end(); it++){

                Node* thisNode = *it;
                list<Node*> &thisAdjList = thisNode -> adj;

                thisAdjList.push_back(toBeAdded);
                (toBeAdded->adj).push_back(thisNode);
            }

            graph.push_back(toBeAdded);
            size++;
        }

        void deleteNode(int el){

            if(size == 0){
                cout<<"Graph is empty"<<endl;
                return;
            }

            auto itr = graph.begin();

            for(; itr != graph.end(); itr++){
                if((*itr)->id == el){
                    break;
                }
            }

            if(itr == graph.end()){
                cout<<"Element is not present"<<endl;
                return;
            }

            Node* toBeDeleted = *itr;

            graph.erase(itr);
            size--;

            for(auto it=graph.begin(); it != graph.end(); it++){
                list<Node*> &thisAdjList = (*it) -> adj;
                thisAdjList.remove(toBeDeleted);
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

    meshNetwork mn = meshNetwork(n);
    
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
                mn.addNode(nodeToBeAdded);
                break;
            
            case 2:
                int nodeToBeDeleted;
                cout<<"Enter ther node id"<<endl;
                cin >> nodeToBeDeleted;
                mn.deleteNode(nodeToBeDeleted);
                break;

            case 3:
                mn.printNetwork();
                break;
        }
    }

    return 0;
}