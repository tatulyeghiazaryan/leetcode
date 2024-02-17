#include <iostream>
#include <vector>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
 
class Solution {
public:
    ListNode *addNode(ListNode *node, int value) {
        ListNode *new_node = new ListNode(value);
        if (node == nullptr) {
            node = new_node;
            return node;
        }
        node->next = new_node;
        return new_node;
    }
    
    void printList(ListNode *starting_node) {
        ListNode *iterator = starting_node;
        while (iterator != nullptr) {
            std::cout << iterator->val << " ";
            iterator = iterator->next;
        }
        
        std::cout << std::endl;
    }
    
    void fillListsFromVectors(ListNode **list, std::vector<int>v) {
        ListNode *iterator = nullptr;
        for (int i = 0; i < v.size(); ++i) {
            if (i == 0) {
                *list = addNode(*list, v.at(i));
                iterator = *list;
            } else {
                iterator = addNode(iterator, v.at(i));
            }
        }
    }
    
    ListNode *addRemainingListElems(ListNode *srcList, ListNode *destList,
                                    int *carryPtr) {
        ListNode *iterator = destList;
        while (srcList != nullptr) {
            iterator = addNode(destList, (((srcList->val) % 10) +
                               (*carryPtr)) % 10);
            if (srcList->val + (*carryPtr) >= 10) {
                *carryPtr = 1;
            } else {
                *carryPtr = 0;
            }
            srcList = srcList->next;
            iterator = iterator->next;
        }
        return iterator;
    }

    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        ListNode *headNode = nullptr;
        int carry = 0;
        int *carry_ptr = &carry;
        int num_iterations = 0;
        ListNode *iterator = nullptr;
        while (l1 != nullptr && l2 != nullptr) {
            if (headNode == nullptr) {
                headNode = addNode(headNode, ((l1->val + l2->val) % 10));
                iterator = headNode;
            } else {
                iterator->next =
                    addNode(iterator,
                            (((l1->val + l2->val) % 10) + carry) % 10);
            }
            if (l1->val + l2->val + carry >= 10) {
                *carry_ptr = 1;
            } else {
                *carry_ptr = 0;
            }
            l1 = l1->next;
            l2 = l2->next;
        }
        iterator = iterator->next;
        if (l1 != nullptr) {
            iterator = addRemainingListElems(l1, iterator, &carry);
        } else if (l2 != nullptr) {
            iterator = addRemainingListElems(l2, iterator, &carry);
        }
        if (*carry_ptr == 1) {
            iterator = addNode(iterator, 1);
        }
        return headNode;
    }
};

int main() {
    Solution s;
    ListNode *head = nullptr;
    std::vector<int> vec_list_1;
    vec_list_1.push_back(1);
    vec_list_1.push_back(2);
    vec_list_1.push_back(3);

    ListNode *head2 = nullptr;
    std::vector<int> vec_list_2;
    vec_list_2.push_back(3);
    vec_list_2.push_back(4);
    s.fillListsFromVectors(&head, vec_list_1);
    s.fillListsFromVectors(&head2, vec_list_2);
    ListNode *new_list = s.addTwoNumbers(head, head2);
    s.printList(new_list);
}