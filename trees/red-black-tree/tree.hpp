# include <memory>
# include <cstdint>
# include <iostream>

/* the root is always black
   the tree leaves are nullptr
   the black height is always the same
   the red node always has two black children */

enum node_colors {
    red_color, black_color
};

template<typename key_type, typename value_type>
requires std::is_copy_constructible_v<key_type> and (std::is_integral_v<key_type> or std::is_floating_point_v<key_type>)
class red_black_tree final {

    struct tree_node {
        bool color;
        key_type key;
        value_type value;
        std::int64_t height;
        std::int64_t balance;
        std::shared_ptr<tree_node> left = nullptr;
        std::shared_ptr<tree_node> right = nullptr;
        std::shared_ptr<tree_node> parent = nullptr;
    };

    std::size_t tree_size = 0;
    std::shared_ptr<tree_node> tree_root = nullptr;

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

    std::shared_ptr<tree_node> create_tree_node(key_type &key, value_type &value) noexcept {
        std::shared_ptr<tree_node> new_tree_node = std::make_shared<tree_node>();
        new_tree_node->key = key;
        new_tree_node->value = value;
        new_tree_node->height = 0;
        new_tree_node->balance = 0;
        new_tree_node->color = red_color;
        return new_tree_node;
    }

    
    void push_pair(std::shared_ptr<tree_node> &current_node, key_type &key, value_type &value) noexcept {
        
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

    public: 
        red_black_tree(void) = default;
        ~red_black_tree(void) = default;
};  
