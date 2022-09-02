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

            if(n == 0){
                return;
            }

            for(int i=1; i<=n; i++){
                Node* newNode = new Node(i);
                graph.push_back(newNode);
            }
            
            for(auto it=graph.begin(); it != graph.end(); it++){
                Node* thisNode = *it;
                list<Node*> &thisAdjList = thisNode -> adj;

                for(auto it2=graph.begin(); it2 != graph.end(); it2++){

                    if(it != it2){
                        ((*it)->adj).push_back(*it2);
                    }
                }
            }

            size = n;
        }

        void deleteNode(int el){

            if(graph.size() == 0){
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

    meshNetwork mn = meshNetwork(10);
    mn.printNetwork();

    return 0;
}