# include <queue>
# include <memory>
# include <cstdint>
# include <iostream>


template<typename key_type, typename value_type>
requires std::is_copy_constructible_v<key_type> and (std::is_floating_point_v<key_type> or std::is_integral_v<key_type>)
class splay_tree final {

    struct tree_node {
        key_type key;
        value_type value;
        std::shared_ptr<tree_node> left = nullptr;
        std::shared_ptr<tree_node> right = nullptr;
        std::shared_ptr<tree_node> parent = nullptr;

        tree_node(key_type key, value_type value) {
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

    void recursion_print_tree(std::shared_ptr<tree_node> &current_node) noexcept {
        if (!current_node) return;
        recursion_print_tree(current_node->left);
        if (current_node->value == recursion_get_max_pair(tree_root)->value) std::cout << current_node->value;
        else std::cout << current_node->value << " --> ";
        recursion_print_tree(current_node->right);
    }


	[[nodiscard]] std::shared_ptr<tree_node> right_rotation(std::shared_ptr<tree_node> &current_node) noexcept {
        std::shared_ptr<tree_node> node = current_node;
        std::shared_ptr<tree_node> node_parent = node->parent;
        std::shared_ptr<tree_node> node_left_child = node->left;
        std::shared_ptr<tree_node> node_left_right_child = node_left_child->right;

        node_left_child->right = node;
        node->parent = node_left_child;

        node->left = node_left_right_child;

        if (node_left_right_child) node_left_right_child->parent = node;
        node_left_child->parent = node_parent;

        if (node_left_child->parent) {
            if (node_left_child->parent->left == node) node_left_child->parent->left = node_left_child;
            else node_left_child->parent->right = node_left_child;
        }
        return node_left_child;
    }

    [[nodiscard]] std::shared_ptr<tree_node> left_rotation(std::shared_ptr<tree_node> &current_node) noexcept {
        std::shared_ptr<tree_node> node = current_node;
        std::shared_ptr<tree_node> node_parent = node->parent;
        std::shared_ptr<tree_node> node_right_child = node->right;
        std::shared_ptr<tree_node> node_right_left_child = node_right_child->left;

        node_right_child->left = node;
        node->parent = node_right_child;

        node->right = node_right_left_child;

        if (node_right_left_child) node_right_left_child->parent = node;
        node_right_child->parent = node_parent;

        if (node_right_child->parent) {
            if (node_right_child->parent->left == node) node_right_child->parent->left = node_right_child;
            else node_right_child->parent->right = node_right_child;
        }
        return node_right_child;
    }


    void splay_current_node(std::shared_ptr<tree_node> current_node) noexcept {

        if (current_node == tree_root or !current_node) return;

        if (current_node->parent == tree_root) {
            if (current_node->parent->left == current_node) {
                tree_root = right_rotation(tree_root);
            }
            else {
                tree_root = left_rotation(tree_root);
            }
            return;
        }
        else if (current_node->parent->left == current_node and current_node->parent->parent->left == current_node->parent) {
            if (current_node->parent->parent == tree_root) {
                tree_root = right_rotation(tree_root);
                tree_root = right_rotation(tree_root);
            }
            else {
                current_node->parent = right_rotation(current_node->parent->parent);
                current_node = right_rotation(current_node->parent);
                splay_current_node(current_node);
            }
        }

        else if (current_node->parent->right == current_node and current_node->parent->parent->right == current_node->parent) {
            if (current_node->parent->parent == tree_root) {
                tree_root = left_rotation(tree_root);
                tree_root = left_rotation(tree_root);
            }
            else {
                current_node->parent = left_rotation(current_node->parent->parent);
                current_node = left_rotation(current_node->parent);
                splay_current_node(current_node);
            }
        }

        else if (current_node->parent->left == current_node and current_node->parent->parent->right == current_node->parent) {

            current_node = right_rotation(current_node->parent);

            if (current_node->parent == tree_root) {
                tree_root = left_rotation(tree_root);
            }
            else {
                current_node = left_rotation(current_node->parent);
                splay_current_node(current_node);
            }
        }

        else if (current_node->parent->right == current_node and current_node->parent->parent->left == current_node->parent) {

            current_node = left_rotation(current_node->parent);

            if (current_node->parent == tree_root) {
                tree_root = right_rotation(tree_root);
            }
            else {
                current_node = right_rotation(current_node->parent);
                splay_current_node(current_node);
            }
        }

    }

    void splay_insert(std::shared_ptr<tree_node> &current_node, key_type &key, value_type &value) noexcept {

        if (key < current_node->key) {
            if (!current_node->left) {
                current_node->left = std::make_shared<tree_node>(key, value);
                current_node->left->parent = current_node;
                splay_current_node(current_node->left);
            }
            else splay_insert(current_node->left, key, value);

        }
        else if (key > current_node->key) {
            if (!current_node->right) {
                current_node->right = std::make_shared<tree_node>(key, value);
                current_node->right->parent = current_node;
                splay_current_node(current_node->right);
            }
            else splay_insert(current_node->right, key, value);
        }
        else {
            current_node->value = value;
            splay_current_node(current_node);
        }
    }

    std::shared_ptr<value_type> search_node_by_value(std::shared_ptr<tree_node> &current_node, key_type &key)  {

        if (current_node->key == key) [[likely]] {
            splay_current_node(current_node);
            std::shared_ptr<value_type> result = std::make_shared<value_type>(tree_root->value);
            return result;
        }
        if ((!current_node->left and key < current_node->key) or (!current_node->right and key > current_node->key)) [[unlikely]] {
            splay_current_node(current_node);
            return nullptr;
        }
        else if (key < current_node->key) return search_node_by_value(current_node->left, key);
        else return search_node_by_value(current_node->right, key);
    }


    void splay_delete(std::shared_ptr<tree_node>& current_node, key_type &key) noexcept {

        if ((!current_node->left and key < current_node->key) or (!current_node->right and key > current_node->key)) {
            splay_current_node(current_node);
        }
        
        else if (key < current_node->key) splay_delete(current_node->left, key);
        else if (key > current_node->key) splay_delete(current_node->right, key);
        else {
            if (!current_node->right and !current_node->left) {
                std::shared_ptr<tree_node> current_parent = current_node->parent;
                current_node = nullptr;
                splay_current_node(current_parent);
            }
            else if (!current_node->right or !current_node->left) {
                if (!current_node->right) {
                    std::shared_ptr<tree_node> current_parent = current_node->parent;
                    current_node = current_node->left;
                    current_node->parent = current_parent;
                    splay_current_node(current_node->parent);
                }
                else {
                    std::shared_ptr<tree_node> current_parent = current_node->parent;
                    current_node = current_node->right;
                    current_node->parent = current_parent;
                    splay_current_node(current_node->parent);
                }
            }
            else {
                std::shared_ptr<tree_node> max_of_mins = recursion_get_max_pair(current_node->left);
                current_node->key = max_of_mins->key;
                current_node->value = max_of_mins->value;
                splay_delete(current_node->left, max_of_mins->key);
            }
        }
    }

    void delete_shared_inks(std::shared_ptr<tree_node> current_node) noexcept {
        if (!current_node) return;
        delete_shared_inks(current_node->left);
        current_node->parent.~shared_ptr();
        delete_shared_inks(current_node->right);
    }

    public:

        splay_tree(void) = default;
        ~splay_tree(void) noexcept {
            std::shared_ptr<tree_node> current_node = tree_root;
            delete_shared_inks(current_node);
        }

        value_type get_max() noexcept {
            std::shared_ptr<tree_node> max_pair = recursion_get_max_pair(tree_root);
            return max_pair->value;
        }

        value_type get_min() noexcept {
            std::shared_ptr<tree_node> min_pair = recursion_get_min_pair(tree_root);
            return min_pair->value;
        }

        splay_tree& order_print() noexcept {
            if (tree_root == nullptr) {
                std::cout << "nullptr";
                return *this;
                tree_size++;
            }
            recursion_print_tree(tree_root);
            tree_size++;
            return *this;
        }

        splay_tree& level_order_print() noexcept {

            std::queue<std::shared_ptr<tree_node>> node_queue;
            if (tree_root) node_queue.push(tree_root);

            while (!node_queue.empty()) {
                std::shared_ptr<tree_node> temporary_node = node_queue.front();
                node_queue.pop();

                if (temporary_node->left) node_queue.push(temporary_node->left);
                if (temporary_node->right) node_queue.push(temporary_node->right);

                std::cout << temporary_node->value << (!node_queue.empty() ? " --> " : "\n");
            }
            return *this;
        }

        splay_tree& push_pair(key_type key, value_type value) noexcept {
            if (!tree_root) [[unlikely]] {
                std::shared_ptr<tree_node> new_tree_node = std::make_shared<tree_node>(key, value);
                tree_root = new_tree_node;
                tree_size++;
                return *this;
            }
            splay_insert(tree_root, key, value);
            tree_size++;
            return *this;
        }

        splay_tree& delete_pair(key_type key) noexcept(false) {
            std::shared_ptr<tree_node>& correct_node = rec_search_pair_by_key(tree_root, key);
            if (correct_node == nullptr) throw std::runtime_error(std::string("ATTENTION -> There is no key " + std::to_string(key) + " in the tree!"));
            splay_delete(tree_root, key);
            tree_size--;
            return *this;
        }
        
        value_type search(key_type key) {
            std::shared_ptr<value_type> result = search_node_by_value(tree_root, key);
            if (!result) {
                std::cout << "ATTENTION --> Key " + std::to_string(key) + " is not in the tree!" << std::endl;
                return value_type();
            }
            return *result;
        }

        friend std::ostream& operator<<(std::ostream &stream, splay_tree &tree_object) noexcept {
            if (tree_object.tree_root == nullptr) {
                std::cout << "nullptr";
                return stream;
            }
            tree_object.order_print();
            return stream;
        }

        value_type operator[](key_type key) noexcept(false) {
            std::shared_ptr<tree_node>& correct_node = rec_search_pair_by_key(tree_root, key);
            if (correct_node == nullptr) throw std::runtime_error(std::string("ATTENTION -> There is no key " + std::to_string(key) + " in the tree!"));
            return search(key);
        }

        [[nodiscard]] std::size_t get_size() noexcept {
            return tree_size;
        }
};