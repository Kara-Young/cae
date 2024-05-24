#include <iostream>
#include <vector>

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* removeSublists(ListNode* head)
{
    ListNode* zeroNodePtr = new ListNode(0);
    zeroNodePtr->next = head;
    ListNode* prevPtr = zeroNodePtr;
    ListNode* curPtr = head;

    while (curPtr != nullptr)
    {
        int product = 1;
        ListNode* temp = curPtr;
        
        // 计算当前节点开始的连续节点的乘积
        while (temp != nullptr)
        {
            product *= temp->val;
            if (product == 10) 
            {
                break;
            }
            temp = temp->next;
        }

        if (product == 10)
        {
            // 删除连续节点并更新list
            ListNode* haltNodePtr = temp->next;
            std::string delNumStr = "";
            while (curPtr != haltNodePtr)
            {
                ListNode* delNodePtr = curPtr;
                curPtr = curPtr->next;
                if (delNumStr.length() <= 0)
                {
                    delNumStr = std::to_string(delNodePtr->val);
                }
                else
                {
                    delNumStr = delNumStr + "," + std::to_string(delNodePtr->val);
                }
                delete delNodePtr;
            }
            std::cout << "remove node val(s):" << delNumStr << std::endl;
            // 将当前指针指向头部,重新遍历
            prevPtr->next = curPtr;
            prevPtr = zeroNodePtr;
            curPtr = prevPtr->next;
        } 
        else
        {
            prevPtr = curPtr;
            curPtr = curPtr->next;
        }
    }

    ListNode* newHeadPtr = zeroNodePtr->next;
    delete zeroNodePtr;
    return newHeadPtr;
}

void printList(ListNode* head)
{
    while (head != nullptr)
    {
        std::cout << head->val << " ";
        head = head->next;
    }
    std::cout << std::endl;
}

int main()
{
    std::vector<int> values = {-2, 5, -1, -10, 1, -1, 10, 2, 2, 2, 5, 5};

    // 生成链表
    ListNode* headNodePtr = nullptr;
    ListNode* prevNodePtr = nullptr;
    for (int val : values)
    {
        ListNode* newNode = new ListNode(val);
        if (headNodePtr == nullptr)
        {
            headNodePtr = newNode;
        }
        else
        {
            // prenode的next指针指向当前node
            prevNodePtr->next = newNode;
        }
        // 更新pre指向
        prevNodePtr = newNode;
    }

    std::cout << "Original List: ";
    printList(headNodePtr);

    // 删除总乘积值为 10 的连续节点组成的序列
    headNodePtr = removeSublists(headNodePtr);

    std::cout << "Modified List: ";
    printList(headNodePtr);

    // 释放内存
    while (headNodePtr != nullptr)
    {
        ListNode* temp = headNodePtr;
        headNodePtr = headNodePtr->next;
        delete temp;
    }

    return 0;
}