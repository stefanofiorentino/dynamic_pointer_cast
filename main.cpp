#include <iostream>

#include <vector>
#include <memory>


struct B
{
    virtual void x()
    {
        std::puts(__PRETTY_FUNCTION__);
    }
};

struct D : B
{
    void x() final
    {
        std::puts(__PRETTY_FUNCTION__);
    }

    virtual void y() final
    {
        std::puts(__PRETTY_FUNCTION__);
    }
};

std::vector<std::shared_ptr<B>> base_shared_ptr_vector;

int main()
{
    std::shared_ptr<B> b = std::make_shared<B>(B{});
    base_shared_ptr_vector.push_back(b);

    std::shared_ptr<D> d = std::make_shared<D>(D{});
    base_shared_ptr_vector.push_back(d);

    for (auto const &item : base_shared_ptr_vector)
    {
        item->x();

        auto p = dynamic_cast<typename std::shared_ptr<D>::element_type *>(item.get());
        if (p != nullptr)
        {
            std::shared_ptr<D>(item, p)->y();
        }
    }
    return 0;
}
