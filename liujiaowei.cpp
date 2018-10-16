#include <iostream>
#include <cstdint>

struct node{
    int val;
    node* next= nullptr;
    node(int value):val(value){}
    node(){}
};

class Linked_list{
    node* head;
    uint16_t size;
public:
    Linked_list():head(nullptr), size(0){}
    void creat(uint16_t k){
        if(k > 0) {
            head = new node;
            std::cin >> head->val;
            head->next = nullptr;
            size++;
            if(k > 1){
                node* now_node = head;
                node* next_node;
                for (int i = 1; i < k; ++i) {
                    next_node = new node;
                    std::cin >> next_node->val; // 赋值
                    now_node->next = next_node; // 连接
                    now_node = next_node;
                    size++;
                }
                now_node->next = nullptr;
            }
        }
    }
    void disp(){
        auto p = head;
        while(p != nullptr){
            std::cout << p->val << ' ';
            p = p->next;
        }
        std::cout << std::endl;
    }
    void insert(uint16_t ind, int val){
        if(ind <= size){
            auto new_node = new node(val);
            if(ind == 1){
                new_node->next = head;
                head = new_node;
            } else{
                auto p = head;
                for (int j = 0; j < ind-2; ++j) {
                    p = p->next;
                }
                new_node->next = p->next;
                p->next = new_node;
            }
            size++;
            disp();
        } else
            std::cout << -1 << std::endl;
    }
    void remove(uint16_t ind){
        if(ind <= size){
            auto p = head;
            if(ind == 1){
                head = head->next;
                delete p;
            } else{
                for (int j = 0; j < ind-2; ++j) {
                    p = p->next;
                }
                auto tmp = p->next;
                p->next = p->next->next;
                delete tmp;
            }
            size--;
            disp();
        } else
            std::cout << -1 << std::endl;
    }
    int search(int val){
        auto p = head;
        uint16_t ind = 0;
        while(p != nullptr && p->val != val){
            ind++;
            p = p->next;
        }
        if(p){
            return ind+1;
        } else return -1;
    }
    uint16_t length(){
        return size;
    }
};

int main(){
    Linked_list l;
    uint16_t n, i, j;
    std::cin >> n;
    l.creat(n);

    l.disp();

    std::cin >> i;
    int val;
    std::cin >> val;
    l.insert(i, val);

    std::cin >> j;
    l.remove(j);

    int value;
    std::cin >> value;
    std::cout << l.search(value) << std::endl;

    std::cout << l.length() << std::endl;
}