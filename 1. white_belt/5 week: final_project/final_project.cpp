#include <iostream>
#include <exception>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <sstream> 
#include <iomanip>
using namespace std;

class Date {
public:

    Date(){};

    Date(int new_year, int new_month, int new_day){
        if(new_month > 12 || new_month < 1){
            throw invalid_argument("Month value is invalid: " + to_string(new_month));
        } else if (new_day > 31 || new_day < 1){
            throw invalid_argument("Day value is invalid: " + to_string(new_day));
        }
        year = new_year;
        month = new_month;
        day = new_day;
    }
    

    int GetYear() const{
        return year;
    };
    int GetMonth() const{
        return month;
    };
    int GetDay() const{
        return day;
    };
private:
    int year;
    int month;
    int day;
};


bool operator<(const Date& lhs, const Date& rhs){
    if(lhs.GetYear() != rhs.GetYear()){
        return (lhs.GetYear() - rhs.GetYear()) < 0;
    } else if(lhs.GetMonth() != rhs.GetMonth()){
        return (lhs.GetMonth() - rhs.GetMonth()) < 0;
    } else {
        return (lhs.GetDay() - rhs.GetDay()) < 0;
    }
};


bool operator>(const Date& lhs, const Date& rhs){
    if(lhs.GetYear() != rhs.GetYear()){
        return (lhs.GetYear() - rhs.GetYear()) > 0;
    } else if(lhs.GetMonth() != rhs.GetMonth()){
        return (lhs.GetMonth() - rhs.GetMonth()) > 0;
    } else {
        return (lhs.GetDay() - rhs.GetDay()) > 0;
    }
};


bool operator==(const Date& lhs, const Date& rhs){
    if(lhs.GetYear() == rhs.GetYear() && lhs.GetMonth() == rhs.GetMonth() && lhs.GetDay() == rhs.GetDay()){
        return true;}
    return false;
};

ostream& operator<<(ostream& stream, const Date& date){
    stream << setw(4) << setfill('0') << date.GetYear() << '-' << setw(2) << setfill('0') << date.GetMonth() << '-' << setw(2) << setfill('0') << date.GetDay();
    return stream;
}

istream& operator>>(istream& in, Date& d) { 
    string input;
    in >> input;

    stringstream stream(input);

    int year,month,day;
    char c1,c2;

	stream >> year >> c1 >> month >> c2 >> day;

	if (stream && c1 == '-' && c2 == '-' && stream.peek() == EOF){
        d = Date(year,month,day);
        return in;
    } else{ 
        throw runtime_error("Wrong date format: " + input);
    }	
}





class Database{

public:
    Database(){
    };

    void AddEvent(const Date& date,const string& event){
        data_base[date].insert(event);
    };

    bool DeleteEvent(const Date& date ,const string& event ){

        if(data_base.count(date) == 1){

            if(data_base.at(date).count(event) == 1){
                data_base[date].erase(event);
                
                if(data_base.at(date).size() == 0){
                    data_base.erase(date);
                }
                return true;

            } else {
                return false;
            } 
        
        } else{
            return false;
        }
    };



    int DeleteDate(const Date& date){
        if(data_base.count(date) == 1){
            const int length_event = data_base.at(date).size();
            data_base.erase(date);
            return length_event;
        } else{
            return 0;
        }
    };

    void Find(const Date& date) const{
        if(data_base.count(date) == 1){
            for(const auto& elem: data_base.at(date)){
                cout << elem << endl; 
            }
        }
    };

    void Print() const {
        for(const auto& elem:data_base){
            for(const auto& event:elem.second){
                cout << elem.first << " " << event << endl;
            }
        }
    };


private:
    map<Date,set<string>> data_base;
};


vector<string> split(string const &str, const char delim)
{
    vector<string> out;
    istringstream ss(str);
    string s;
    while (getline(ss, s, delim)) {
        out.push_back(s);
    }
    return out;
}

void command_check(const string& com,const set<string> check_set){
    if(check_set.count(com) == 0){
        throw runtime_error("Unknown command: " + com);
    }
}

int main() {
    Database db;
    string command;
    set<string> allowed_command = {"Add","Del","Find","Print"};
    
    while (getline(cin, command)) {
        if(command.empty()) {
            continue;
        }
        vector<string> arguments = split(command,' ');
        
            Date date;
            
            try{
                command_check(arguments[0],allowed_command);
            } catch(exception& ex){
                cout << ex.what();
                exit(EXIT_FAILURE);
            }
            
            if(arguments.size() > 1){
                istringstream ss(arguments[1]);
                try{
                    ss >> date;
                } catch(exception& ex){
                    cout << ex.what();
                    exit(EXIT_FAILURE);
                }
            }
        
            if(arguments[0] == "Add"){
                db.AddEvent(date,arguments[2]);

            } else if(arguments[0] == "Del"){
                if(arguments.size() == 3){
                    const bool success = db.DeleteEvent(date,arguments[2]);
                    if(success == true){
                        cout << "Deleted successfully" << endl;
                    } else{
                        cout << "Event not found" << endl;
                    }
                } else{
                    const int num_events = db.DeleteDate(date);
                    cout << "Deleted " << num_events << " events" << endl;
                }

            } else if(arguments[0] == "Find"){
                db.Find(date);
            } else if(arguments[0] == "Print"){
                db.Print();
            }
         
        }
        return 0;
    }



