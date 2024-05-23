#include <iostream>
#include <vector>

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* removeMultiplesOf10(ListNode* head) {
    ListNode* dummy = new ListNode(0);
    dummy->next = head;
    ListNode* prev = dummy;
    ListNode* current = head;

    while (current != nullptr) {
        int product = 1;
        ListNode* temp = current;
        
        // 计算当前节点开始的连续节点的乘积
        while (temp != nullptr) {
            product *= temp->val;
            if (product == 10) {
                break;
            }
            temp = temp->next;
        }

        if (product == 10) {
            // 删除连续节点
            prev->next = temp->next;
            current = temp->next;
            delete temp;
        } else {
            prev = current;
            current = current->next;
        }
    }

    ListNode* newHead = dummy->next;
    delete dummy;
    return newHead;
}

void printList(ListNode* head) {
    while (head != nullptr) {
        std::cout << head->val << " ";
        head = head->next;
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> values = {-2, 5, -1, -10, 1, -1, 10, 2, 2, 2, 5, 5};

    // 构造链表
    ListNode* head = nullptr;
    ListNode* prev = nullptr;
    for (int val : values) {
        ListNode* newNode = new ListNode(val);
        if (head == nullptr) {
            head = newNode;
        } else {
            prev->next = newNode;
        }
        prev = newNode;
    }

    std::cout << "Original List: ";
    printList(head);

    // 删除总乘积值为 10 的连续节点组成的序列
    head = removeMultiplesOf10(head);

    std::cout << "Modified List: ";
    printList(head);

    // 释放内存
    while (head != nullptr) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}