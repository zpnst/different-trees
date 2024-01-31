
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

    std::cout << "\n\033[1;34mLet's insert the values 100, 50, 150, 25, 55, 175, 125, 300, 1000 and then delete the values 150, 50 and 1000\033[0m" << std::endl;

    for (const auto& object : vector) {
        bin_tree.push_pair(object, std::to_string(object));
        avl_bin_tree.push_pair(object, std::to_string(object));
        splay_bin_tree.push_pair(object, std::to_string(object));
        red_black_bin_tree.push_pair(object, std::to_string(object));
    }

    bin_tree.delete_pair(150).delete_pair(50).delete_pair(1000);
    avl_bin_tree.delete_pair(150).delete_pair(50).delete_pair(1000);
    splay_bin_tree.delete_pair(150).delete_pair(50).delete_pair(1000);
    red_black_bin_tree.delete_pair(150).delete_pair(50).delete_pair(1000);

    std::cout << "\n\033[1;36mIn binary and AVL binary tree we have (1, 2, 3), where\033[0m\n\n\033[1;35m1)\033[0m - node value\n\033[1;35m2)\033[0m - node height\n\033[1;35m3)\033[0m - node balance\n\n" << std::endl;
    
    std::cout << "\033[1;36mBinary Tree:\033[0m\n" << std::endl;
    std::cout << "\033[1;35mOrder print:\033[0m" << std::endl;
    std::cout << bin_tree << std::endl;
    std::cout << "\033[1;35mLevel order print:\033[0m" << std::endl;
    bin_tree.level_oreder_print();

    std::cout << "\n\n\033[1;36mAVL Binary Tree:\033[0m\n" << std::endl;
    std::cout << "\033[1;35mOrder print:\033[0m" << std::endl;
    std::cout << avl_bin_tree << std::endl;
    std::cout << "\033[1;35mLevel order print:\033[0m" << std::endl;
    avl_bin_tree.level_oreder_print();

    std::cout << "\n\n\033[1;36mSplay Binary Tree:\033[0m\n" << std::endl;
    std::cout << "\033[1;35mOrder print:\033[0m" << std::endl;
    std::cout << splay_bin_tree << std::endl;
    std::cout << "\033[1;35mLevel order print:\033[0m" << std::endl;
    splay_bin_tree.level_oreder_print();

    std::cout << "\n\n\033[1;31mRed\033[0m \033[1;30mBlack\033[0m \033[1;36mBinary Tree:\033[0m\n" << std::endl;
    std::cout << "\033[1;35mOrder print:\033[0m" << std::endl;
    std::cout << red_black_bin_tree << std::endl;
    std::cout << "\033[1;35mLevel order print:\033[0m" << std::endl;
    red_black_bin_tree.level_oreder_print();

    /*
    std::cout << "\n\nFeatures\n" << std::endl;

    std::cout << "let's insert 72 into the tree\n" << std::endl;
    splay_bin_tree.push_pair(72, "72");

	std::cout << "After inserting 72, the level order printing of keys is: " << std::endl;
	splay_bin_tree.level_oreder_print();
    */

    return 0;
}