# include <queue>
# include <memory>
# include <vector>
# include <cstdint>
# include <iostream>


template<typename key_type, typename value_type>
requires std::is_copy_constructible_v<key_type> and (std::is_floating_point_v<key_type> or std::is_integral_v<key_type>)
class red_black_tree final {

    enum tree_colors {black_color, red_color};

    struct tree_node {
        key_type key;
        value_type value;
        tree_colors color;
        std::shared_ptr<tree_node> left;
        std::shared_ptr<tree_node> right;
        std::shared_ptr<tree_node> parent;

        tree_node(key_type key, value_type value, tree_colors color) {
            this->color = color;
            this->key = key; this->value = value;
            this->left = nullptr; this->right = nullptr; this->parent = nullptr;
        }
        ~tree_node(void) = default;
    };

    std::size_t tree_size = 0;
    std::shared_ptr<tree_node> tree_root = nullptr;

    std::shared_ptr<tree_node> recursion_get_max_pair(std::shared_ptr<tree_node> &current_root) noexcept {
        if (current_root == nullptr) [[unlikely]] return current_root;
        if (current_root->right == nullptr) return current_root;
        return recursion_get_max_pair(current_root->right);
    }

    std::shared_ptr<tree_node> recursion_get_min_pair(std::shared_ptr<tree_node> &current_root) noexcept {
        if (current_root == nullptr) [[unlikely]] return current_root;
        if (current_root->left == nullptr) return current_root;
        return recursion_get_min_pair(current_root->left);
    }

    std::shared_ptr<tree_node>& rec_search_pair_by_key(std::shared_ptr<tree_node>& current_node, key_type key) noexcept {
        if (current_node == nullptr) [[unlikely]] return current_node;
        if (key == current_node->key) return current_node;
        if (key < current_node->key) return rec_search_pair_by_key(current_node->left, key);
        else if (key > current_node->key) return rec_search_pair_by_key(current_node->right, key);
        return current_node;
    }

    std::string print_color_helper(tree_colors current_color) noexcept {
        if (current_color == 0) return "\033[1;30mblack\033[0m";
        return "\033[1;31mred\033[0m";
    }

    void recursion_print_tree(std::shared_ptr<tree_node> &current_node) noexcept {
        if (!current_node) return;
        recursion_print_tree(current_node->left);
        if (current_node->value == recursion_get_max_pair(tree_root)->value) std::cout << "(" << current_node->value << ", " << print_color_helper(current_node->color) << ")";
        else std::cout << "(" << current_node->value << ", " << print_color_helper(current_node->color) << ")" << " --> ";
        recursion_print_tree(current_node->right);
    }

    void delete_shared_inks(std::shared_ptr<tree_node> current_node) noexcept {
        if (!current_node) return;
        delete_shared_inks(current_node->left);
        current_node->parent.~shared_ptr();
        delete_shared_inks(current_node->right);
    }

    void swap_nodes_data(std::shared_ptr<tree_node> &first_node, std::shared_ptr<tree_node> &second_node) noexcept {
        key_type temporary_key = first_node->key;
        value_type temporary_value = first_node->value;
        first_node->key = second_node->key;
        first_node->value = second_node->value;
        second_node->key = temporary_key;
        second_node->value = temporary_value;  
    }

    void right_rotation(std::shared_ptr<tree_node> current_node) {
        if (current_node == nullptr || current_node->left == nullptr) return;
        std::shared_ptr<tree_node> current_left = current_node->left;
        current_node->left = current_left->right;
        if (current_left->right != nullptr) current_left->right->parent = current_node;
        current_node->parent = current_node->parent;
        if (current_node->parent == nullptr) tree_root = current_left;
        else if (current_node == current_node->parent->left) current_node->parent->left = current_left;
        else current_node->parent->right = current_left;
        current_left->right = current_node;
        current_node->parent = current_left;
    }

    void left_rotation(std::shared_ptr<tree_node> current_node) {
        if (current_node == nullptr || current_node->right == nullptr) return;
        std::shared_ptr<tree_node> current_right = current_node->right;    
        current_node->right = current_right->left;
        if (current_right->left != nullptr) current_right->left->parent = current_node;
        current_right->parent = current_node->parent;
        if (current_node->parent == nullptr) tree_root = current_right;
        else if (current_node == current_node->parent->left) current_node->parent->left = current_right;
        else current_node->parent->right = current_right;
        current_right->left = current_node;
        current_node->parent = current_right;
    }

    void insert_red(std::shared_ptr<tree_node> current_node, key_type key, value_type value) noexcept {
        if (tree_root == nullptr) {
            tree_root = std::make_shared<tree_node>(key, value, black_color);
            return;
        }
        if (key < current_node->key) {
            if (current_node->left == nullptr) {
                current_node->left = std::make_shared<tree_node>(key, value, red_color);
                current_node->left->parent = current_node;
                fix_insertation(current_node->left);
            }
            else insert_red(current_node->left, key, value);
        }
        else if (key > current_node->key) {
            if (current_node->right == nullptr) {
                current_node->right = std::make_shared<tree_node>(key, value, red_color);
                current_node->right->parent = current_node;
                fix_insertation(current_node->right);
            } 
            else insert_red(current_node->right, key, value);
        }
        else {
            current_node->value = value;
        }
    }

    
    void fix_insertation(std::shared_ptr<tree_node> current_node) noexcept {
        if (current_node->parent->color == black_color) {
            return;
        }
        else if (current_node->parent->color == red_color) {

            std::shared_ptr<tree_node> current_uncle = nullptr;

            if (current_node->parent->parent->right == current_node->parent) current_uncle = current_node->parent->parent->left; 
            else current_uncle = current_node->parent->parent->right;
            
            if (current_uncle == nullptr || current_uncle->color == black_color) {
                if (current_node->parent->right == current_node and current_node->parent->parent->right == current_node->parent) {
                    left_rotation(current_node->parent->parent);
                    current_node->parent->color = black_color;
                    current_node->parent->left->color = red_color;
                }
                else if (current_node->parent->left == current_node and current_node->parent->parent->left == current_node->parent) {
                    right_rotation(current_node->parent->parent);
                    current_node->parent->color = black_color;
                    current_node->parent->right->color = red_color;
                }
                else if (current_node->parent->left == current_node and current_node->parent->parent->right == current_node->parent) {
                    right_rotation(current_node->parent);
                    left_rotation(current_node->parent->parent);
                    current_node->parent->color = black_color;
                    current_node->parent->left->color = red_color;
                    
                }
                else {
                    left_rotation(current_node->parent);
                    right_rotation(current_node->parent->parent);
                    current_node->parent->color = black_color;
                    current_node->parent->left->color = red_color;

                }
            }
            else {
                current_uncle->color = black_color;
                current_node->parent->color = black_color;
                if (current_node->parent->parent != tree_root) current_node->parent->parent->color = red_color;
            }                 
        }
    }

    void deletion_helper(std::shared_ptr<tree_node> current_node) noexcept {
        while (current_node != tree_root and current_node != nullptr and current_node->color == black_color) {
            if (current_node == current_node->parent->left) {
                std::shared_ptr<tree_node> current_brother = current_node->parent->right;
                if (current_brother->color == red_color) {
                    current_brother->color = black_color;
                    current_node->parent->color = red_color;
                    left_rotation(current_node->parent);
                    current_brother = current_node->parent->right;
                }
                if ((current_brother->left == nullptr or current_brother->left->color == black_color) and (current_brother->right == nullptr || current_brother->right->color == black_color)) {
                    current_brother->color = red_color;
                    current_node = current_node->parent;
                } 
                else {
                    if (current_brother->right == nullptr or current_brother->right->color == black_color) {
                        if (current_brother->left != nullptr) current_brother->left->color = black_color;
                        current_brother->color = red_color;
                        right_rotation(current_brother);
                        current_brother = current_node->parent->right;
                    }
                    current_brother->color = current_node->parent->color;
                    current_node->parent->color = black_color;
                    if (current_brother->right != nullptr) current_brother->right->color = black_color;
                    left_rotation(current_node->parent);
                    current_node = tree_root;
                }
            } 
            else {
                std::shared_ptr<tree_node> current_brother = current_node->parent->left;
                if (current_brother->color == red_color) {
                    current_brother->color = black_color;
                    current_node->parent->color = red_color;
                    right_rotation(current_node->parent);
                    current_brother = current_node->parent->left;
                }
                if ((current_brother->right == nullptr or current_brother->right->color == black_color) and (current_brother->left == nullptr or current_brother->left->color == black_color)) {
                    current_brother->color = red_color;
                    current_node = current_node->parent;
                } 
                else {
                    if (current_brother->left == nullptr or current_brother->left->color == black_color) {
                        if (current_brother->right != nullptr) current_brother->right->color = black_color;
                        current_brother->color = red_color;
                        left_rotation(current_brother);
                        current_brother = current_node->parent->left;
                    }
                    current_brother->color = current_node->parent->color;
                    current_node->parent->color = black_color;
                    if (current_brother->left != nullptr) current_brother->left->color = black_color;
                    right_rotation(current_node->parent);
                    current_node = tree_root;
                }
            }
        }
        if (current_node != nullptr)
            current_node->color = black_color;
    }

    void delete_node(std::shared_ptr<tree_node> &current_node, key_type key) noexcept {
        if (current_node == nullptr) return;

        if (key < current_node->key) delete_node(current_node->left, key);
        else if (key > current_node->key) delete_node(current_node->right, key);
        else {
            if (current_node->right == nullptr or current_node->left == nullptr) {
                current_node->right == nullptr ? current_node = current_node->left : current_node = current_node->right;
                if (current_node != nullptr) deletion_helper(current_node);
            }
            else {
                std::shared_ptr<tree_node> min_of_maxes = recursion_get_min_pair(current_node->right);
                current_node->key = min_of_maxes->key;
                current_node->value = min_of_maxes->value;
                delete_node(current_node->right, min_of_maxes->key);
            }
        }
    }
    

    public:

        red_black_tree(void) = default;
        ~red_black_tree(void) noexcept {
            std::shared_ptr<tree_node> current_node = tree_root;
            delete_shared_inks(current_node);
        }

        red_black_tree& push_pair(key_type key, value_type value) noexcept {
            insert_red(tree_root, key, value);
            tree_size++;
            return *this;
        }

        red_black_tree& order_print(void) noexcept {
            if (tree_root == nullptr) {
                std::cout << "nullptr";
                return *this;
                tree_size++;
            }
            recursion_print_tree(tree_root);
            tree_size++;
            return *this;
        }

        red_black_tree& delete_pair(key_type key) noexcept(false) {
            std::shared_ptr<tree_node>& correct_node = rec_search_pair_by_key(tree_root, key);
            if (correct_node == nullptr) throw std::runtime_error(std::string("ATTENTION -> There is no key " + std::to_string(key) + " in the tree!"));
            delete_node(tree_root, key);
            tree_size--;
            return *this;
        }

        value_type get_max() noexcept {
            std::shared_ptr<tree_node> max_pair = recursion_get_max_pair(tree_root);
            return max_pair->value;
        }

        value_type get_min() noexcept {
            std::shared_ptr<tree_node> min_pair = recursion_get_min_pair(tree_root);
            return min_pair->value;
        }

        red_black_tree& level_order_print(void) noexcept {

            std::queue<std::shared_ptr<tree_node>> node_queue;
            if (tree_root) node_queue.push(tree_root);

            while (!node_queue.empty()) {
                std::shared_ptr<tree_node> temporary_node = node_queue.front();
                node_queue.pop();

                if (temporary_node->left) node_queue.push(temporary_node->left);
                if (temporary_node->right) node_queue.push(temporary_node->right);

                std::cout << "(" << temporary_node->value << ", " << print_color_helper(temporary_node->color) << ")" << (!node_queue.empty() ? " --> " : "\n");
            }
            return *this;
        }      

        friend std::ostream& operator<<(std::ostream& stream, red_black_tree& tree_object) noexcept {
            if (tree_object.tree_root == nullptr) {
                std::cout << "nullptr";
                return stream;
            }
            tree_object.order_print();
            return stream;
        }

        value_type& operator[](key_type key) noexcept(false) {
            std::shared_ptr<tree_node>& correct_node = rec_search_pair_by_key(tree_root, key);
            if (correct_node == nullptr) throw std::runtime_error(std::string("ATTENTION -> There is no key " + std::to_string(key) + " in the tree!"));
            return rec_search_pair_by_key(key);
        }

        std::size_t get_size() noexcept {
            return tree_size;
        }
};