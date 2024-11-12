/**
* main.cpp
 * -----------------
 * Fenwick (https://open.kattis.com/problems/fenwick):
 *  Implemting the Fenwick tree data structure to answer queries.    
 *
 **/
 
#include "../../algorithms/bit.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t N, Q;
    int delta;
    std::size_t index;
    char op;
    long long int sum {0};

    while(std::cin >> N >> Q){
        BIT tree {N};

        for(std::size_t i {0}; i < Q; i++){
            std::cin >> op >> index;
            if(op == '+'){
                std::cin >> delta;
                tree.add(index, delta);
            }
            else{
                sum = tree.sum(index);
                std::cout << sum << "\n";
            }

            // std::cout << "tree: " << tree << "\n";
        }
    }

    std::cout << std::flush;
    
    return 0;
}

// ============== END OF FILE ==============

