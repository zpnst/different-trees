# include <memory>
# include <cstdint>
# include <iostream>


template<typename key_type, typename value_type>
requires std::is_copy_constructible_v<key_type> and (std::is_integral_v<key_type> or std::is_floating_point_v<key_type>)
class binary_tree final {

    struct tree_node {
        key_type key;
        value_type value; 
        std::shared_ptr<tree_node> left = nullptr;
        std::shared_ptr<tree_node> right = nullptr;
    };

    std::size_t tree_size = 0;
    std::shared_ptr<tree_node> tree_root = nullptr;

    std::shared_ptr<tree_node> create_tree_node(key_type key, value_type value) noexcept {
        std::shared_ptr<tree_node> new_tree_node = std::make_shared<tree_node>();
        new_tree_node->key = key;
        new_tree_node->value = value;
        return new_tree_node;
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
    }

    void rec_print_tree(std::shared_ptr<tree_node> current_root) noexcept {
        if (current_root->left != nullptr) rec_print_tree(current_root->left);
        if (current_root->value == rec_get_max_pair(tree_root)->value) std::cout << current_root->value;
        else std::cout << current_root->value << " --> ";
        if (current_root->right != nullptr) rec_print_tree(current_root->right);
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

        binary_tree& print_tree() noexcept {
            if (tree_root == nullptr) {
                std::cout << "nullptr";
                return *this;
            }
            rec_print_tree(tree_root);
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
            tree_object.print_tree();
            return stream;
        }

        inline value_type& operator[](key_type key) noexcept {
            return serach_by_key(key);
        }

        inline std::size_t get_size() noexcept {
            return tree_size;
        }
};


int main(int argc, char **argv) {

    binary_tree<std::int64_t, std::string> tree;

    tree.push_pair(10, "a10").push_pair(20, "b20").push_pair(30, "c30").push_pair(5, "d5").push_pair(7, "e7").push_pair(8, "f8").push_pair(6, "g6").push_pair(19, "h19");
    
    std::cout << "max value: " << tree.get_max() << std::endl;
    std::cout << "min value: " << tree.get_min() << std::endl;

    std::cout << "value by key 19: " << tree.serach_by_key(19) << std::endl;
    
    tree.print_tree();
    std::cout << std::endl;

    std::cout << "tree size: " << tree.get_size() << std::endl;

    tree.erase(8);

    tree.print_tree();
    std::cout << std::endl;

    std::cout << "tree[20]: " << tree[20] << std::endl;

    std::cout << tree << std::endl;

    std::cout << "tree size: " << tree.get_size() << std::endl;
    
    return 0;
}