# include <queue>
# include <memory>
# include <cstdint>
# include <iostream>

# define red_color 1
# define black_color 0

template<typename key_type, typename value_type>
requires std::is_copy_constructible_v<key_type> and (std::is_floating_point_v<key_type> or std::is_integral_v<key_type>)
class red_black_tree final {

    struct tree_node {
        bool color;
        key_type key;
        value_type value;
        std::shared_ptr<tree_node> left;
        std::shared_ptr<tree_node> right;
        std::shared_ptr<tree_node> parent;

        tree_node(key_type key, value_type value, bool color) {
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

    void recursion_print_tree(std::shared_ptr<tree_node> &current_node) noexcept {
        if (!current_node) return;
        recursion_print_tree(current_node->left);
        if (current_node->value == recursion_get_max_pair(tree_root)->value) std::cout << "(" << current_node->value << ", " << current_node->color << ")";
        else std::cout << "(" << current_node->value << ", " << current_node->color << ")" << " --> ";
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

    void right_rotation(std::shared_ptr<tree_node> &current_node) noexcept {
        swap_nodes_data(current_node, current_node->left);
        std::shared_ptr<tree_node> temporary_node = current_node->right;
        current_node->right = current_node->left;
        current_node->left = current_node->left->left;
        if (current_node->left) current_node->left->parent = current_node;
        current_node->right->left = current_node->right->right;
        current_node->right->right = temporary_node;
        if (current_node->right->right) current_node->right->right->parent = current_node->right;
    }

    void left_rotation(std::shared_ptr<tree_node> &current_node) noexcept {
        swap_nodes_data(current_node, current_node->right);
        std::shared_ptr<tree_node> temporary_node = current_node->left;
        current_node->left = current_node->right;
        current_node->right = current_node->right->right;
        if (current_node->right) current_node->right->parent = current_node;
        current_node->left->right = current_node->left->left;
        current_node->left->left = temporary_node;
        if (current_node->left->left) current_node->left->left->parent = current_node->left;
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
            
            /* uncle is black or uncle does not exist */
            if (current_uncle == nullptr || current_uncle->color == black_color) {
                /* left rotation */
                if (current_node->parent->right == current_node and current_node->parent->parent->right == current_node->parent) {
                    left_rotation(current_node->parent->parent);
                }
                /* right rotation */
                else if (current_node->parent->left == current_node and current_node->parent->parent->left == current_node->parent) {
                    right_rotation(current_node->parent->parent);
                }
                /* right rotation and after that left rotation */
                else if (current_node->parent->left == current_node and current_node->parent->parent->right == current_node->parent) {
                    right_rotation(current_node->parent);
                    left_rotation(current_node->parent->parent);
                    
                }
                /* left rotation and after that right rotation */
                else {
                    left_rotation(current_node->parent);
                    right_rotation(current_node->parent->parent);

                }
            }
            /* uncle is red */
            else {

            }
            
            //else if () {}
                    
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

        red_black_tree& level_oreder_print(void) noexcept {

            std::queue<std::shared_ptr<tree_node>> node_queue;
            if (tree_root) node_queue.push(tree_root);

            while (!node_queue.empty()) {
                std::shared_ptr<tree_node> temporary_node = node_queue.front();
                node_queue.pop();

                if (temporary_node->left) node_queue.push(temporary_node->left);
                if (temporary_node->right) node_queue.push(temporary_node->right);

                std::cout << "(" << temporary_node->value << ", " << temporary_node->color << ")" << (!node_queue.empty() ? " --> " : "\n");
            }
            return *this;
        }      
};