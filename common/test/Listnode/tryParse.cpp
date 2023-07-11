/* testing listnode parse */

#include "ListNode.h"
#include <iostream>

int main() {
    try {
        using namespace linkedList;
        ListNode* head;
        int i = 0;
        if(!tryParse("[1,2,3]", i, head)) {
            std::cerr << "could not parse" << std::endl;
            return 1;
        }
        std::cout << toString(head) << std::endl;
        deleteList(head);
    } catch (std::exception& e) {
        std::cout << "exception: " << e.what() << std::endl;
    }
}
