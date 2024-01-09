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
        std::int8_t height;
        std::shared_ptr<tree_node> left = nullptr;
        std::shared_ptr<tree_node> right = nullptr;
        std::shared_ptr<tree_node> parent = nullptr;
    };
    
    std::size_t tree_size = 0;
    std::shared_ptr<tree_node> tree_root = nullptr;

    [[nodiscard]] inline bool if_node_leaf(std::shared_ptr<tree_node> &current_node) noexcept {
        return (!current_node->right && !current_node->left);
    }

    inline void update_node_height(std::shared_ptr<tree_node> &current_node) noexcept {
        current_node->height = std::max(current_node->right == nullptr ? -1 : current_node->right->height, current_node->left == nullptr ? -1 : current_node->left->height) + 1;
    }

    inline std::int64_t get_node_balance(std::shared_ptr<tree_node> &current_node) noexcept {
        if (current_node == nullptr) return 0;
        return (current_node->right ? current_node->right->height : -1) - (current_node->left ? current_node->left->height : -1);
    }

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

    std::shared_ptr<tree_node> create_tree_node(key_type &key, value_type &value) noexcept {
        std::shared_ptr<tree_node> new_tree_node = std::make_shared<tree_node>();
        new_tree_node->key = key;
        new_tree_node->value = value;
        new_tree_node->height = 0;
        return new_tree_node;
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

        if (current_node == tree_root || !current_node) return;

        /* zig */
        if (current_node->parent == tree_root) {
            if (current_node->parent->left == current_node) {
                tree_root = right_rotation(tree_root);
            }
            else {
                tree_root = left_rotation(tree_root);
            }
        return;
        }

        /* zig zig (right right) */
        else if (current_node->parent->left == current_node && current_node->parent->parent->left == current_node->parent) {
            if (current_node->parent->parent == tree_root) {
                tree_root = right_rotation(tree_root);
                tree_root = right_rotation(tree_root);
                return;
            }
            else {
                current_node->parent = right_rotation(current_node->parent->parent);
                current_node = right_rotation(current_node->parent);
                splay_current_node(current_node);
                return;
            }
        }

        /* zag zag (left left) */
        else if (current_node->parent->right == current_node && current_node->parent->parent->right == current_node->parent) {
            if (current_node->parent->parent == tree_root) {
                tree_root = left_rotation(tree_root);
                tree_root = left_rotation(tree_root);
                return;
            }
            else {
                current_node->parent = left_rotation(current_node->parent->parent);
                current_node = left_rotation(current_node->parent);
                splay_current_node(current_node);
                return;
            }
        }

        /* zig zag (right left) */
        else if (current_node->parent->left == current_node && current_node->parent->parent->right == current_node->parent) {

            current_node = right_rotation(current_node->parent);

            if (current_node->parent == tree_root) {
                tree_root = left_rotation(tree_root);
                return;
            }
            else {
                current_node = left_rotation(current_node->parent);
                splay_current_node(current_node);
                return;
            }
        }

        /* zag zig (left right) */
        else if (current_node->parent->right == current_node && current_node->parent->parent->left == current_node->parent) {

            current_node = left_rotation(current_node->parent);

            if (current_node->parent == tree_root) {
                tree_root = right_rotation(tree_root);
                return;
            }
            else {
                current_node = right_rotation(current_node->parent);
                splay_current_node(current_node);
                return;
            }
        }

    }

    
    void splay_insert(std::shared_ptr<tree_node> &current_node, key_type &key, value_type &value) noexcept {

        if (key < current_node->key) {
            if (!current_node->left) {
                current_node->left = create_tree_node(key, value);
                current_node->left->parent = current_node;
                splay_current_node(current_node->left);
            }
            else splay_insert(current_node->left, key, value);

        }
        else if (key > current_node->key) {
            if (!current_node->right) {
                current_node->right = create_tree_node(key, value);
                current_node->right->parent = current_node;
                splay_current_node(current_node->right);
            }
            else splay_insert(current_node->right, key, value);
        }
        else {
            current_node->value = value;
            splay_current_node(current_node);
        }
        if (current_node) update_node_height(current_node); 
    }

    void delete_lndoe_inks(std::shared_ptr<tree_node> current_node) noexcept {
        if (!current_node) return;
        delete_lndoe_inks(current_node->left);
        current_node->parent.~shared_ptr();
        delete_lndoe_inks(current_node->right);
    }

    public:
        splay_tree(void) = default;
        ~splay_tree(void) noexcept {
            std::shared_ptr<tree_node> current_node = tree_root;
            delete_lndoe_inks(current_node);
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

        splay_tree& level_oreder_print() noexcept {

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
                std::shared_ptr<tree_node> new_tree_node = create_tree_node(key, value);
                tree_root = new_tree_node;
                tree_size++;
                return *this;
            }
            splay_insert(tree_root, key, value);
            tree_size++;
            return *this;
        }

        friend std::ostream& operator<<(std::ostream &stream, splay_tree &tree_object) noexcept {
            if (tree_object.tree_root == nullptr) {
                std::cout << "nullptr";
                return stream;
            }
            tree_object.order_print();
            return stream;
        }
        
        inline std::size_t get_size() noexcept {
            return tree_size;
        }
};