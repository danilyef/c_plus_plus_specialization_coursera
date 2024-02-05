#include "test_runner.h"

#include <ostream>
using namespace std;

#define PRINT_VALUES(out, x, y) out << (x) << "\n" << (y) << endl




int main() {
    TestRunner tr;
    tr.RunTest([] {
        ostringstream output;
        PRINT_VALUES(output, 2, "red belt");
        ASSERT_EQUAL(output.str(), "2 red belt\n");
    }, "PRINT_VALUES usage example");
}



