# include <memory>
# include <cstdint>
# include <iostream>

template<typename key_type, typename value_type>
requires std::is_copy_constructible_v<key_type> and (std::is_integral_v<key_type> or std::is_floating_point_v<key_type>) 
class splay_tree final {

    public:
        splay_tree(void) = default;
        ~splay_tree(void) = default;
};