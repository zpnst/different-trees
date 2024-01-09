# include <queue>
# include <memory>
# include <cstdint>
# include <iostream>


template<typename key_type, typename value_type>
requires std::is_copy_constructible_v<key_type> and (std::is_integral_v<key_type> or std::is_floating_point_v<key_type>)
class binary_tree final {

    struct tree_node {
        key_type key;
        value_type value; 
        std::int64_t height;
        std::shared_ptr<tree_node> left = nullptr;
        std::shared_ptr<tree_node> right = nullptr;
    };

    std::size_t tree_size = 0;
    std::shared_ptr<tree_node> tree_root = nullptr;

    std::shared_ptr<tree_node> create_tree_node(key_type key, value_type value) noexcept {
        std::shared_ptr<tree_node> new_tree_node = std::make_shared<tree_node>();
        new_tree_node->key = key;
        new_tree_node->value = value;
        new_tree_node->height = 0;
        return new_tree_node;
    }

    inline void update_node_height(std::shared_ptr<tree_node> &current_node) noexcept {
        current_node->height = std::max(current_node->right == nullptr ? -1 : current_node->right->height, current_node->left == nullptr ? -1 : current_node->left->height) + 1;
    }

    inline std::int64_t get_node_balance(std::shared_ptr<tree_node> &current_node) noexcept {
        if (current_node == nullptr) return 0;
        return (current_node->right ? current_node->right->height : -1) - (current_node->left ? current_node->left->height : -1);
    }

    std::shared_ptr<tree_node> rec_get_max_pair(std::shared_ptr<tree_node> current_root) noexcept {
        if (current_root == nullptr) [[unlikely]] return current_root;
        if (current_root->right == nullptr) return current_root;
        return rec_get_max_pair(current_root->right);
    }

    std::shared_ptr<tree_node> rec_get_min_pair(std::shared_ptr<tree_node> current_root) noexcept {
        if (current_root == nullptr) [[unlikely]] return current_root;
        if (current_root->left == nullptr) return current_root;
        return rec_get_max_pair(current_root->left);
    }

    std::shared_ptr<tree_node>& rec_search_pair_by_key(std::shared_ptr<tree_node>& current_node, key_type key) noexcept {
        if (current_node == nullptr) [[unlikely]] return current_node;
        if (key == current_node->key) return current_node;
        if (key < current_node->key) return rec_search_pair_by_key(current_node->left, key);
        else if (key > current_node->key) return rec_search_pair_by_key(current_node->right, key);
        return current_node;
    }

    void rec_push_pair(std::shared_ptr<tree_node> current_node, key_type key, value_type value) noexcept {
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
        }
    }

    void rec_delete_pair_by_key(std::shared_ptr<tree_node>& current_node, key_type key) noexcept {
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
        }
    }

    void recursion_print_tree(std::shared_ptr<tree_node> &current_root) noexcept {
        if (current_root->left != nullptr) recursion_print_tree(current_root->left);
        if (current_root->value == rec_get_max_pair(tree_root)->value) std::cout << "(" << current_root->value << ", " << current_root->height << ", " << get_node_balance(current_root) << ")";
        else std::cout << "(" << current_root->value << ", " << current_root->height << ", " << get_node_balance(current_root) << ")" << " --> ";
        if (current_root->right != nullptr) recursion_print_tree(current_root->right);
    }
    
    public:

        binary_tree(void) = default;
        ~binary_tree(void) = default;

        binary_tree& push_pair(key_type key, value_type value) noexcept {
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

        binary_tree& order_print() noexcept {
            if (tree_root == nullptr) {
                std::cout << "nullptr";
                return *this;
            }
            recursion_print_tree(tree_root);
            return *this;
        }

        binary_tree& level_oreder_print() noexcept {

            std::queue<std::shared_ptr<tree_node>> node_queue;
            if (tree_root) node_queue.push(tree_root);

            while (!node_queue.empty()) {
                std::shared_ptr<tree_node> temporary_node = node_queue.front();
                node_queue.pop();

                if (temporary_node->left) node_queue.push(temporary_node->left);
                if (temporary_node->right) node_queue.push(temporary_node->right);

                std::cout << "(" << temporary_node->value << ", " << temporary_node->height << ", " << get_node_balance(temporary_node) << ")" << (!node_queue.empty() ? " --> " : "\n");
            }
            return *this;
        }

        binary_tree& erase(key_type key) noexcept {
            rec_delete_pair_by_key(tree_root, key);
            tree_size--;
            return *this;
        }

        friend std::ostream& operator<<(std::ostream& stream, binary_tree& tree_object) noexcept {
            if (tree_object.tree_root == nullptr) {
                std::cout << "nullptr";
                return stream;
            }
            tree_object.order_print();
            return stream;
        }

        inline value_type& operator[](key_type key) noexcept {
            return serach_by_key(key);
        }

        inline std::size_t get_size() noexcept {
            return tree_size;
        }
};