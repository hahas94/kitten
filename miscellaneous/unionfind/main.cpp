/**
* main.cpp
 * -------
 * Union Find (https://open.kattis.com/problems/unionfind):
 *  Application of the Union Find data structure.
 *   
 *
 * Solution:
 *  The problem is solved aptly by implementing the unionfind data structure. *   
 *
 **/
 
#include "../../algorithms/unionfind.hpp"
#include <sstream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

  std::ostringstream answers {};
    
    int N, Q;
    int x, y;
    char query;
    bool ans;

    while(std::cin >> N >> Q){
        UnionFind sets {N};
        for(int i = 0; i < Q; i++){
            std::cin >> query >> x >> y;
            
            if(query == '='){sets.join(x, y);}
            else{
                ans = sets.same(x, y); 
                if(ans){answers << "yes\n";}
                else{answers << "no\n";}
            }
        }
    }

    std::cout << answers.str();
    return 0;
}

// ============== END OF FILE ==============

