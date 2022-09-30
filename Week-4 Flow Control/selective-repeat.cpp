#include <iostream>
#include <time.h>
#include <cstdlib>
#include <vector>
#include <set>
// #include <bits/stdc++.h>

using namespace std;

class timer{
    private:
        unsigned long begTime;

    public:
        void start(){
            begTime = clock();
        }
        unsigned long elapsedTime(){
            return ((unsigned long)clock() - begTime) /CLOCKS_PER_SEC;
        }
        bool isTimeout(unsigned long seconds){
            return seconds >= elapsedTime();
        }
};

void randomProcessing(){
    int to = 2460 + rand() % (6400 - 2460) + 1;

    for (int i = 0; i < 6400; i++){
        for (int j = 0; j < to; j++){
        }
    }  
}

timer t;
set<int> recieved;
set<int> frames;

int reciever(int frameId){

    cout<<"Reciever: ";

    if(recieved.find(frameId) != recieved.end()){
        cout<<"Already recieved the frame "<<frameId<<endl;
        return 2;
    }
    
    cout<<"Successfully recieved the frame "<<frameId<<endl;
    recieved.insert(frameId);
    return 1;
}

void sender(int w){

    int lim = min(w, int(frames.size()));
    int count = 0;

    for(auto it = frames.begin(); it!=frames.end() && count<lim; it++){
        cout<<"Sender: Sending the frame : "<<(*it)<<endl;
        count++;
    }

    t.start();
}

void fillSet(set<int> &frames, int s){

    for(int i=0; i<s; i++){
        frames.insert(i);
    }
}

void deleteFromFrames(vector<int> &toBeDeleted){

    for(auto &el: toBeDeleted){
        frames.erase(el);
    }

}

int main(){

    fillSet(frames, 8);

    int n = (int)frames.size();
    int w = n/2;

    unsigned long seconds = 5;
    srand(time(NULL));
    
    do{
        bool timeout = false;

        sender(w);

        randomProcessing();

        int lim = min(w, int(frames.size()));
        int count = 0;

        vector<int> toBeErased;

        for(auto it = frames.begin(); it!=frames.end() && count<lim; it++){
            
            bool messageReached = rand() % 2;

            if(messageReached){
                int token = reciever(*it);

                bool ackRecieved = rand() % 2;

                if(ackRecieved){
                    if(token == 1){
                        toBeErased.push_back(*it);
                    }
                    else if(token == 2){
                        cout<<"Sender: Frame "<<(*it)<<" was already recieved by the reciever."<<endl;
                        toBeErased.push_back(*it);
                    }
                }
            }

            count++;
        }

        deleteFromFrames(toBeErased);

        randomProcessing();
        
        // if (t.elapsedTime() > seconds){
        //     cout<<"Sender: Timeout occured. Send next set "<<endl;
        // }

    } while (!frames.empty());
    
    return 0;
}