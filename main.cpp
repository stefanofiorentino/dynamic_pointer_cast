#include <iostream>

#include <vector>
#include <memory>

struct B {
    virtual void x() {
        std::puts(__PRETTY_FUNCTION__);
    }
};

struct D : public B {
    void x() final {
        std::puts(__PRETTY_FUNCTION__);
        B::x();
    }

    virtual void y() final {
        std::puts(__PRETTY_FUNCTION__);
    }
};

namespace details {
    std::vector<std::shared_ptr<B>> base_shared_ptr_vector;
}

int main() {
    std::shared_ptr<B> b = std::make_shared<B>(B{});
    ::details::base_shared_ptr_vector.push_back(b);

    std::shared_ptr<D> d = std::make_shared<D>(D{});
    ::details::base_shared_ptr_vector.push_back(d);

    for (auto const &item : ::details::base_shared_ptr_vector) {
        item->x();

        if (auto pi = std::dynamic_pointer_cast<D>(item)) {
            pi->y();
        }
    }
    return 0;
}
