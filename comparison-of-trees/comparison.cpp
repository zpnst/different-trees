
# include <vector>
# include <cstdint>
# include <iostream>
# include <splay-tree/tree.hpp>
# include <binary-tree/tree.hpp>
# include <red-black-tree/tree.hpp>
# include <avl-binary-tree/tree.hpp>


int main(int argc, char **argv) {
    
    binary_tree<std::int64_t, std::string> bin_tree;
    splay_tree<std::int64_t, std::string> splay_bin_tree;
    avl_binary_tree<std::int64_t, std::string> avl_bin_tree;
    red_black_tree<std::int64_t, std::string> red_black_bin_tree;

    std::vector<std::int64_t> vector = {100, 50, 150, 25, 55, 175, 125, 300, 1000};

    for (const auto& object : vector) {
        bin_tree.push_pair(object, std::to_string(object));
        avl_bin_tree.push_pair(object, std::to_string(object));
        splay_bin_tree.push_pair(object, std::to_string(object));
        //red_black_bin_tree.push_pair(object, std::to_string(object));
    }

    std::cout << "\nWe have (1, 2, 3), where\n1 - node value\n2 - node height\n3 - node balance\n\n" << std::endl;
    
    std::cout << "Binary Tree:\n" << std::endl;
    std::cout << "Order print:" << std::endl;
    std::cout << bin_tree << "\n" << std::endl;
    std::cout << "Level order print:" << std::endl;
    bin_tree.level_oreder_print();

    std::cout << "\n\nAVL Binary Tree:\n" << std::endl;
    std::cout << "Order print:" << std::endl;
    std::cout << avl_bin_tree << "\n" << std::endl;
    std::cout << "Level order print:" << std::endl;
    avl_bin_tree.level_oreder_print();

    std::cout << "\n\nSplay Binary Tree:\n" << std::endl;
    std::cout << "Order print:" << std::endl;
    std::cout << splay_bin_tree << "\n" << std::endl;
    std::cout << "Level order print:" << std::endl;
    splay_bin_tree.level_oreder_print();

    std::cout << "\n\nFeatures\n" << std::endl;

    std::cout << "let's insert 72 into the tree\n" << std::endl;
    splay_bin_tree.push_pair(72, "72");

	std::cout << "After inserting 72, the level order printing of keys is: " << std::endl;
	splay_bin_tree.level_oreder_print();

    return 0;
}