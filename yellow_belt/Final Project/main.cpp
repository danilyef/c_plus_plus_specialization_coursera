#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"
#include "unit_tests.h"

using namespace std;

void TestAll()
{
    TestRunner tr;
    tr.RunTest(TestEmptyNode, "TestEmptyNode");
    tr.RunTest(TestDateComparisonNode, "TestDateComparisonNode");
    tr.RunTest(TestEventComparisonNode, "TestEventComparisonNode");
    tr.RunTest(TestLogicalOperationNode, "TestLogicalOperationNode");
    tr.RunTest(TestInsertionOrder, "TestInsertionOrder");
    tr.RunTest(TestAdd, "TestAdd");
    tr.RunTest(TestLast, "TestLast");
    tr.RunTest(TestRemove, "TestRemoveIf");
    tr.RunTest(TestFind, "TestFindIf");
    tr.RunTest(TestDatabase, "TestDatabase");
}


std::string ParseEvent(std::istream& is)
{
    std::string event;
    std::getline(is, event);
    return std::string(std::find_if(event.begin(), event.end(), [](const unsigned char& c) noexcept
    {
        return !std::isspace(c);
    }),
    event.end());
}






int main() {
    TestAll();

    Database db;

    for (string line; getline(cin, line); ) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "Add") {
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);

        } else if (command == "Print") {
            db.Print(cout);

        } else if (command == "Del") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date& date, const string& event) {
            return condition->Evaluate(date, event);
            };

            int count = db.RemoveIf(predicate);
            cout << "Removed " << count << " entries" << endl;
        
        } else if (command == "Find") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date& date, const string& event) {
            return condition->Evaluate(date, event);
            };

            const auto entries = db.FindIf(predicate);
            for (const auto& entry : entries) {
                cout << entry << endl;
            }
            cout << "Found " << entries.size() << " entries" << endl;
        } else if (command == "Last") {
             try {
                cout << db.Last(ParseDate(is)) << endl;
            } catch (invalid_argument&) {
                cout << "No entries" << endl;
            }
        } else if (command.empty()) {
        continue;
        } else {
        throw logic_error("Unknown command: " + command);
        }
    }

    return 0;
}
