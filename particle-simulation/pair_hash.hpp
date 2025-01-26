#include <utility>
#include <functional>

// Custom hash function for std::pair
struct PairHash {
    template <typename T1, typename T2>
    std::size_t operator()(const std::pair<T1, T2>& pair) const {
        std::size_t hash1 = std::hash<T1>()(pair.first);
        std::size_t hash2 = std::hash<T2>()(pair.second);
        return hash1 ^ (hash2 << 1); // Combine hashes
    }
};