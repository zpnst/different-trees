
# include <vector>
# include <cstdint>
# include <iostream>
# include <splay-tree/tree.hpp>
# include <binary-tree/tree.hpp>
# include <two_three_tree/tree.hpp>
# include <red-black-tree/tree.hpp>
# include <avl-binary-tree/tree.hpp>


int main(int argc, char **argv) {
    
    binary_tree<std::int64_t, std::string> bin_tree;
    avl_binary_tree<std::int64_t, std::string> avl_bin_tree;

    std::vector<std::int64_t> vector = {100, 50, 150, 25, 55, 175, 125, 300, 1000};

    for (const auto& object : vector) {
        bin_tree.push_pair(object, std::to_string(object));
        avl_bin_tree.push_pair(object, std::to_string(object));
    }

    std::cout << "\nWe have (1, 2, 3), where\n1 - node value\n2 - node height\n3 - node balance\n\n" << std::endl;
    
    std::cout << "Binary Tree:" << std::endl;
    std::cout << bin_tree << "\n" << std::endl;

    std::cout << "AVL Binary Tree:" << std::endl;
    std::cout << avl_bin_tree << std::endl;
    return 0;
}