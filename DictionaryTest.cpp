/********************************************************************************* 
* Devasha Trivedi, detrived
* 2022 Spring CSE101 PA8
* DictionaryTest.cpp
* Test file for the Dictionary ADT
*********************************************************************************/
#include <stdbool.h>
#include <iostream>
#include "Dictionary.h"

using namespace std;

typedef enum {
    BEGIN,
    END,
    NEXT,
    PREV,
    SET_VALUE,
    REMOVE,
    GET_VALUE,
    CONTAINS,

    TESTS_END
} Tests;

static const char *test_desc[] = {
    [BEGIN] = "Begin",
    [END] = "End",
    [NEXT] = "Next",
    [PREV] = "Prev",
    [SET_VALUE] = "Set Value",
    [REMOVE] = "Remove",
    [GET_VALUE] = "Get Value",
    [CONTAINS] = "Contains",
};

int test(int test) {

    Dictionary A, B;

    int success = 1;

    switch (test) {
    case BEGIN: {
        A.setValue("d", 29);
        A.setValue("a", 1);
        A.setValue("b", 17);
        A.setValue("c", 28);

        A.begin();
        if (A.currentVal() != 1 || A.currentKey() != "a") {
            success = 0;
        }

        A.remove("a");
        A.begin();
        if (A.currentVal() != 17 || A.currentKey() != "b") {
            success = 0;
        }
        break;
    }
    case END: {
        A.setValue("d", 29);
        A.setValue("a", 1);
        A.setValue("b", 17);
        A.setValue("c", 28);

        A.end();
        if (A.currentVal() != 29 || A.currentKey() != "d") {
            success = 0;
        }

        A.remove("d");
        A.end();
        if (A.currentVal() != 28 || A.currentKey() != "c") {
            success = 0;
        }
        break;
    }
    case NEXT: {
        A.setValue("d", 29);
        A.setValue("a", 1);
        A.setValue("b", 17);
        A.setValue("c", 28);

        A.begin();
        A.next();
        if (A.currentVal() != 17 || A.currentKey() != "b") {
            success = 0;
        }

        A.remove("a");
        A.begin();
        A.next();
        if (A.currentVal() != 28 || A.currentKey() != "c") {
            success = 0;
        }
        break;
    }
    case PREV: {
        A.setValue("d", 29);
        A.setValue("a", 1);
        A.setValue("b", 17);
        A.setValue("c", 28);

        A.end();
        A.prev();
        if (A.currentVal() != 28 || A.currentKey() != "c") {
            success = 0;
        }

        A.remove("d");
        A.end();
        A.prev();
        if (A.currentVal() != 17 || A.currentKey() != "b") {
            success = 0;
        }
        break;
    }
    case SET_VALUE: {
        A.setValue("a", 27);
        A.setValue("r", 5);
        A.setValue("c", 2);
        A.setValue("b", 6);
        if (A.size() != 4) {
            success = 0;
        }
        if (A.getValue("a") != 27) {
            success = 0;
        }

        A.setValue("a", 32);
        if (A.size() != 4) {
            success = 0;
        }
        if (A.getValue("a") != 32) {
            success = 0;
        }
        break;
    }
    case REMOVE: {
        A.setValue("a", 27);
        A.setValue("r", 5);
        A.setValue("c", 2);
        A.setValue("b", 6);

        if (A.size() != 4) {
            success = 0;
        }

        A.begin();
        A.remove("a");

        if (A.size() != 3) {
            success = 0;
        }
        if (A.hasCurrent()) {
            success = 0;
        }
        break;
    }
    case GET_VALUE: {
        A.setValue("a", 27);
        A.setValue("r", 5);
        A.setValue("c", 2);
        A.setValue("b", 6);

        if (A.size() != 4) {
            success = 0;
        }

        A.begin();
        if (A.getValue(A.currentKey()) != 27) {
            success = 0;
        }

        A.next();
        if (A.getValue(A.currentKey()) != 6) {
            success = 0;
        }

        A.end();
        if (A.getValue(A.currentKey()) != 5) {
            success = 0;
        }
        break;
    }
    case CONTAINS: {
        A.setValue("a", 27);
        A.setValue("r", 5);
        A.setValue("c", 2);
        A.setValue("b", 6);

        if (A.contains("d")) {
            success = 0;
        }

        A.setValue("d", 34);

        if (!A.contains("d")) {
            success = 0;
        }

        if (!A.contains("a")) {
            success = 0;
        }

        if (!A.hasCurrent()) {
            success = 0;
        }
        break;
    }
    }

    return success;
}

int main(int argc, char const *argv[]) {
    int totalFailed = 0, totalSuccess = 0, totalPending = 0;

    for (int i = BEGIN; i < TESTS_END; i++) {
        int outcome = test(i);
        if (outcome == 0) {
            cout << test_desc[i] << " : Failed" << endl;
            totalFailed++;
        } else if (outcome == 1) {
            totalSuccess++;
        } else if (outcome == -1) {
            totalPending++;
        }
    }

    cout << "Total Tests [" << TESTS_END << "] Failed Tests [" << totalFailed << "] Success Tests ["
         << totalSuccess << "] Pending Tests [" << totalPending << "]" << endl;

    return 0;
}
