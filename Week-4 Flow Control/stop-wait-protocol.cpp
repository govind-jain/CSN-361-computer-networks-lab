#include <iostream>
#include <time.h>
#include <cstdlib>
#include <vector>

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
int ack = 0;

void sender(vector<int> &frames, int frameId){

    cout<<"Sender: Sending the frame : "<<frameId<<endl;

    t.start();
}

bool reciever(vector<int> &frames, int frameId){

    cout<<"Reciever: ";

    if(ack == frameId){
        // Message recieved successfully
        cout<<"Successfully recieved the frame "<<frameId<<endl;

        ack++;
        return true;
    }
    else{
        cout<<"I am expecting the frame "<<ack<<endl;
    }

    return false;
}

int main(){

    vector<int> frames = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    int frameId = 0;
    int n = frames.size();

    unsigned long seconds = 5;
    srand(time(NULL));
    
    do{
        bool timeout = false;

        sender(frames, frameId);

        randomProcessing();

        bool messageReached = rand() % 2;

        bool ackSentByReciever = false;

        if(messageReached){
            ackSentByReciever = reciever(frames, frameId);
        }

        randomProcessing();

        bool ackRecieved = rand() % 2;
        
        if (!messageReached || !ackRecieved || t.elapsedTime() > seconds){
            timeout = true;
            cout<<"Sender: Timeout occured for frame "<<frameId<<endl;
        }
        else{
            // Sender recieved the acknowledgement before timeout

            if(ackSentByReciever){
                // Message was recieved successfully
                // Send next message
                frameId++;
            }
            else{
                cout<<"Sender: Frame "<<frameId<<" was already recieved by the reciever."<<endl;
                frameId++;
            }
        }

    } while (frameId != n);
    
    return 0;
}