#include <iostream>
#include <exception>
#include <string>
using namespace std;


string AskTimeServer(){

}


class TimeServer {
public:

    string get_last_fetches_time(){
        return last_fetched_time;
    }
    
    string GetCurrentTime(){
        try{
            last_fetched_time = AskTimeServer();
            return get_last_fetches_time();
        } catch(const system_error& ex){
            return last_fetched_time;
        } catch(exception& ex){
            throw;
        }

    };
private:
    string last_fetched_time = "00:00:00";

};


int main(){

    return 0;
}