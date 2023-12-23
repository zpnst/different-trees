# include <cmath>
# include <memory>
# include <cstdint>
# include <iostream>


template<typename key_type, typename value_type>
requires std::is_copy_constructible_v<key_type> and (std::is_integral_v<key_type> or std::is_floating_point_v<key_type>)
class avl_binary_tree final {

    struct tree_node {
        key_type key;
        value_type value; 
        std::int64_t height;
        std::int64_t balance;
        std::shared_ptr<tree_node> left = nullptr;
        std::shared_ptr<tree_node> right = nullptr;
    };

    std::size_t tree_size = 0;
    std::shared_ptr<tree_node> tree_root = nullptr;

    std::shared_ptr<tree_node> create_tree_node(key_type &key, value_type &value) noexcept {
        std::shared_ptr<tree_node> new_tree_node = std::make_shared<tree_node>();
        new_tree_node->key = key;
        new_tree_node->value = value;
        new_tree_node->height = 0;
        new_tree_node->balance = 0;
        return new_tree_node;
    }

    inline std::int64_t get_node_height(std::shared_ptr<tree_node> &current_node) noexcept {
        if (current_node == nullptr) return -1;
        return current_node->height;
    }

    inline std::int64_t get_node_balance(std::shared_ptr<tree_node> &current_node) noexcept {
        if (current_node == nullptr) return 0;
        return (current_node->right ? current_node->right->height : -1) - (current_node->left ? current_node->left->height : -1);
    }

    void update_node_height(std::shared_ptr<tree_node> &current_node) noexcept {
        current_node->height = std::max(get_node_height(current_node->right), get_node_height(current_node->left)) + 1;
    }

    void update_node_balance(std::shared_ptr<tree_node> &current_node) noexcept {
        current_node->balance = get_node_balance(current_node);
    }

    [[nodiscard]] std::shared_ptr<tree_node> rec_get_max_pair(std::shared_ptr<tree_node> &current_root) noexcept {
        if (current_root == nullptr) [[unlikely]] return current_root;
        if (current_root->right == nullptr) return current_root;
        return rec_get_max_pair(current_root->right);
    }

    [[nodiscard]] std::shared_ptr<tree_node> rec_get_min_pair(std::shared_ptr<tree_node> &current_root) noexcept {
        if (current_root == nullptr) [[unlikely]] return current_root;
        if (current_root->left == nullptr) return current_root;
        return rec_get_max_pair(current_root->left);
    }

    [[nodiscard]] std::shared_ptr<tree_node>& rec_search_pair_by_key(std::shared_ptr<tree_node> &current_node, key_type &key) noexcept {
        if (current_node == nullptr) [[unlikely]] return current_node;
        if (key == current_node->key) return current_node;
        if (key < current_node->key) return rec_search_pair_by_key(current_node->left, key);
        else if (key > current_node->key) return rec_search_pair_by_key(current_node->right, key);
        return current_node;
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
        current_node->right->left = current_node->right->right;
        current_node->right->right = temporary_node;
        update_node_height(current_node->right);
        update_node_height(current_node);
        update_node_balance(current_node->right);
        update_node_balance(current_node);
    }

    void left_rotation(std::shared_ptr<tree_node> &current_node) noexcept {
        swap_nodes_data(current_node, current_node->right);
        std::shared_ptr<tree_node> temporary_node = current_node->left;
        current_node->left = current_node->right;
        current_node->right = current_node->right->right;
        current_node->left->right = current_node->left->left;
        current_node->left->left = temporary_node;
        update_node_height(current_node->left);
        update_node_height(current_node);
        update_node_balance(current_node->left);
        update_node_balance(current_node);
    }

    void balance_tree_node(std::shared_ptr<tree_node> &current_node) noexcept {
        if (get_node_balance(current_node) == -2) {
            if (get_node_balance(current_node->left) == 1) left_rotation(current_node->left);
            right_rotation(current_node);
        }
        else if (get_node_balance(current_node) == 2) {
            if (get_node_balance(current_node->right) == -1) {
                right_rotation(current_node->right);
            }
            left_rotation(current_node);
        }
    }

    void rec_push_pair(std::shared_ptr<tree_node> &current_node, key_type &key, value_type &value) noexcept {
        if (key < current_node->key) {
            if (current_node->left == nullptr) {
                std::shared_ptr<tree_node> new_tree_node = create_tree_node(key, value);
                current_node->left = new_tree_node;
            }
            else rec_push_pair(current_node->left, key, value);
        }
        else if (key >= current_node->key) {
            if (current_node->right == nullptr) {
                std::shared_ptr<tree_node> new_tree_node = create_tree_node(key, value);
                current_node->right = new_tree_node;
            }
            else rec_push_pair(current_node->right, key, value);  
        }
        if (current_node != nullptr) {
            update_node_height(current_node); 
            update_node_balance(current_node);
            balance_tree_node(current_node);
        }
    }

    void rec_delete_pair_by_key(std::shared_ptr<tree_node> &current_node, key_type &key) noexcept {
        if (key < current_node->key) rec_delete_pair_by_key(current_node->left, key);
        else if (key > current_node->key) rec_delete_pair_by_key(current_node->right, key);
        else {
            if (current_node->right == nullptr || current_node->left == nullptr) {
                current_node->right == nullptr ? current_node = current_node->left : current_node = current_node->right;
            }
            else {
                std::shared_ptr<tree_node> max_of_mins = rec_get_min_pair(current_node->left);
                current_node->key = max_of_mins->key;
                current_node->value = max_of_mins->value;
                rec_delete_pair_by_key(current_node->left, max_of_mins->key);
            }
        }
        if (current_node != nullptr) {
            update_node_height(current_node); 
            update_node_balance(current_node);
            balance_tree_node(current_node);
        }
    }

    void rec_print_tree(std::shared_ptr<tree_node> &current_root) noexcept {
        if (current_root->left != nullptr) rec_print_tree(current_root->left);
        if (current_root->value == rec_get_max_pair(tree_root)->value) std::cout << "(" << current_root->value << ", " << current_root->height << ", " << current_root->balance << ")";
        else std::cout << "(" << current_root->value << ", " << current_root->height << ", " << current_root->balance << ")" << " --> ";
        if (current_root->right != nullptr) rec_print_tree(current_root->right);
    }

    public:

        avl_binary_tree(void) = default;
        ~avl_binary_tree(void) = default;

        avl_binary_tree& push_pair(key_type key, value_type value) noexcept {
            if (tree_root == nullptr) [[unlikely]] {
                std::shared_ptr<tree_node> new_tree_node = create_tree_node(key, value);
                tree_root = new_tree_node;
                tree_size++;
                return *this;
            }
            rec_push_pair(tree_root, key, value);
            tree_size++;
            return *this;
        }

        value_type get_max() noexcept {
            std::shared_ptr<tree_node> max_pair = rec_get_max_pair(tree_root);
            return max_pair->value;
        }

        value_type get_min() noexcept {
            std::shared_ptr<tree_node> min_pair = rec_get_min_pair(tree_root);
            return min_pair->value;
        }

        value_type& serach_by_key(key_type key) noexcept {
            std::shared_ptr<tree_node>& correct_node = rec_search_pair_by_key(tree_root, key);
            return correct_node->value;
        }

        avl_binary_tree& print_tree() noexcept {
            if (tree_root == nullptr) {
                std::cout << "nullptr";
                return *this;
            }
            rec_print_tree(tree_root);
            return *this;
        }

        avl_binary_tree& erase(key_type key) {
            std::shared_ptr<tree_node>& correct_node = rec_search_pair_by_key(tree_root, key);
            if (correct_node == nullptr) throw std::runtime_error(std::string("ATTENTION -> There is no key " + std::to_string(key) + " in the tree!"));
            rec_delete_pair_by_key(tree_root, key);
            tree_size--;
            return *this;
        }

        friend std::ostream& operator<<(std::ostream &stream, avl_binary_tree &tree_object) noexcept {
            if (tree_object.tree_root == nullptr) {
                std::cout << "nullptr";
                return stream;
            }
            tree_object.print_tree();
            return stream;
        }

        inline value_type& operator[](key_type key) {
            std::shared_ptr<tree_node>& correct_node = rec_search_pair_by_key(tree_root, key);
            if (correct_node == nullptr) throw std::runtime_error(std::string("ATTENTION -> There is no key " + std::to_string(key) + " in the tree!"));
            return serach_by_key(key);
        }

        inline std::size_t get_size() noexcept {
            return tree_size;
        }
};