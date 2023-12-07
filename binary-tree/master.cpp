# include <memory>
# include <cstdint>
# include <iostream>

template<typename pointer_type>
using SP = std::shared_ptr<pointer_type>;

/* A class describing the simplest binary tree */
template<typename key_type, typename value_type>
requires std::is_copy_constructible_v<key_type> and (std::is_integral_v<key_type> or std::is_floating_point_v<key_type>)
class BinaryTree final {

    /* The structure of a single node */
    struct TreeNode {
        key_type key;
        value_type value;
        SP<TreeNode> left = nullptr;
        SP<TreeNode> right = nullptr;
    };

    std::size_t tree_size = 0;
    SP<TreeNode> root = nullptr;

    /* Creating a separate tree node */
    SP<TreeNode> make_node(key_type key, value_type value) noexcept {
        SP<TreeNode> new_node = std::make_shared<TreeNode>();
        new_node->key = key;
        new_node->value = value;
        return new_node;
    }

    /* A recursive function for adding tree nodes to the desired location */
    void recursion_push(SP<TreeNode> current_node, key_type key, value_type value) noexcept {
        if (key < current_node->key) {
            if (current_node->left == nullptr) {
                SP<TreeNode> new_node = make_node(key, value);
                current_node->left = new_node;
            }
            else recursion_push(current_node->left, key, value);
        }
        else if (key >= current_node->key) {
            if (current_node->right == nullptr) {
                SP<TreeNode> new_node = make_node(key, value);
                current_node->right = new_node;
            }
            else recursion_push(current_node->right, key, value);
        }
    }

    /* Recursive minimum search */
    SP<TreeNode> recursion_min(SP<TreeNode> current_node) noexcept {
        if (current_node == nullptr) [[unlikely]] return nullptr;
        if (current_node->left == nullptr) return current_node;
        return recursion_max(current_node->left);
    }

    /* Recursive maximum search */
    SP<TreeNode> recursion_max(SP<TreeNode> current_node) noexcept {
        if (current_node == nullptr) [[unlikely]] return current_node;
        if (current_node->right == nullptr) return current_node;
        return recursion_max(current_node->right);
    }

    /* Search for a specific node of the tree by key */
    SP<TreeNode>& recursion_search(SP<TreeNode>& current_node, key_type key) noexcept {
        if (current_node == nullptr) [[unlikely]] return current_node;
        if (current_node->key == key) return current_node;
        return (key < current_node->key) ? recursion_search(current_node->left, key) : recursion_search(current_node->right, key);
    }

    /* Recursive removal of a tree node */
    void recursion_delete(SP<TreeNode>& current_node, key_type key) {
        if (current_node == nullptr) [[unlikely]] throw std::runtime_error("ATTENTION -> There is no such key in the binary tree!");
        else if (key < current_node->key) recursion_delete(current_node->left, key);
        else if (key > current_node->key) recursion_delete(current_node->right, key);
        else {
            if (current_node->left == nullptr || current_node->right == nullptr) { /* only one child or no children */
                (current_node->left == nullptr) ? current_node = current_node->right : current_node = current_node->left;
            }
            else { /* two children */
                SP<TreeNode> max_left = recursion_max(current_node->left);
                current_node->value = max_left->value;
                current_node->key = max_left->key;
                recursion_delete(current_node->left, max_left->key);
            }
        }
    }

    /* Full recursive tree traversal */
    void print_tree(SP<TreeNode>& current_node) noexcept {
        if (current_node == nullptr) return;    
        print_tree(current_node->left);
        std::cout << current_node->value << " ";
        print_tree(current_node->right);
    }

    public:

        BinaryTree(void) = default;
        ~BinaryTree(void) = default;

        BinaryTree& push(key_type key, value_type value) noexcept {
            if (root == nullptr) [[unlikely]] {
                SP<TreeNode> new_node = make_node(key, value);
                root = new_node;
                tree_size++;
                return *this;
            } 
            recursion_push(root, key, value);
            tree_size++;
            return *this;
        }

        value_type& min() noexcept {
            SP<TreeNode> correct_node = recursion_min(root);
            return correct_node->value;
        }

        value_type& max() {
            SP<TreeNode> correct_node = recursion_max(root);
            if (correct_node == nullptr) [[unlikely]] throw std::runtime_error("ATTENTION -> There are no pairs in the tree!");
            return correct_node->value;
        }

        BinaryTree& erase(key_type key) noexcept {
            SP<TreeNode>& correct_node = recursion_search(root, key);
            recursion_delete(correct_node, key);
            tree_size--;
            return *this;
        }

        /* operator  [] overloading */
        value_type& operator[](key_type key) {
            SP<TreeNode> correct_node = recursion_search(root, key);
            if (correct_node == nullptr) throw std::runtime_error("ATTENTION -> There is no such key in the binary tree!");
            return correct_node->value;
        }

        /* Overloading the standard output stream */
        friend std::ostream& operator<<(std::ostream& stream, BinaryTree& object) noexcept {
            if (object.tree_size == 0) std::cout << "nullptr";
            object.print_tree(object.root);
            return stream;
        }
};


int main(int argc, char** argv) {

    BinaryTree<int, std::string> my_tree;

    /* Adding pairs to the tree */
    my_tree.push(70, "70").push(50, "50").push(45, "45").push(61, "61").push(80, "80").push(79, "79").push(92, "92");

    /* Output of the maximum and minimum among the values */
    std::cout << "min: " << my_tree.min() << std::endl;
    std::cout << "max: " << my_tree.max() << std::endl;

    /* Removing the maximum node */
    my_tree.erase(92);

    std::cout << "max after erase: " << my_tree.max() << std::endl;

    /* Accessing the node value by key using the [] operator */
    std::cout<< my_tree[45] << std::endl;

    /* Ordered tree output */
    std::cout << my_tree << std::endl;

    return 0;
}