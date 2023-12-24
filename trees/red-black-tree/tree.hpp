# include <memory>
# include <cstdint>
# include <iostream>


template<typename key_type, typename value_type>
requires std::is_copy_constructible_v<key_type> and (std::is_integral_v<key_type> or std::is_floating_point_v<key_type>)
class red_black_tree final {

    public: 
        red_black_tree(void) = default;
        ~red_black_tree(void) = default;
};