#include <vector>
#include <unordered_set>

struct Nlist {
    using nlist_type = typename std::vector<std::unordered_set<std::size_t>>;
    std::size_t getSize() {
	return size_;
    }
    Nlist() = default;
    Nlist(std::size_t const& npt) {
	doi.resize(npt);
	size_ = npt;
    }
    ~Nlist() = default;
    nlist_type doi;
    std::size_t size_;
   
};
