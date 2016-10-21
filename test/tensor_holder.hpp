#ifndef GUARD_TENSOR_HOLDER_HPP
#define GUARD_TENSOR_HOLDER_HPP

#include <mlopen/tensor.hpp>
#include "ford.hpp"

template<class T>
struct tensor
{
    mlopen::TensorDescriptor desc;
    std::vector<T> data;

    tensor(int n, int c, int h, int w)
    : desc(mlopenFloat, {n,c,h,w}), data(n*c*h*w)
    {}

    tensor(mlopen::TensorDescriptor rhs)
    : desc(std::move(rhs))
    {
        data.resize(desc.GetElementSize());
    }

    template<class G>
    tensor& generate(G g) &
    {
        this->generate_impl(g);
        return *this;
    }

    template<class G>
    tensor&& generate(G g) &&
    {
        this->generate_impl(g);
        return std::move(*this);
    }

    template<class G>
    void generate_impl(G g)
    {
        auto iterator = data.begin();
        this->for_each([&](int i, int j, int k, int m)
        {
            assert(iterator < data.end());
            *iterator = g(i, j, k, m);
            ++iterator;
        });
    }

    template<class F>
    void for_each(F f) const
    {
        int n, c, h, w;
        std::tie(n, c, h, w) = mlopen::tie4(desc.GetLengths());
        ford(n, c, h, w)(std::move(f));
    }

    template<class F>
    void par_for_each(F f) const
    {
        int n, c, h, w;
        std::tie(n, c, h, w) = mlopen::tie4(desc.GetLengths());
        par_ford(n, c, h, w)(std::move(f));
    }

    T& operator()(int n, int c, int h, int w)
    {
        assert(this->desc.GetIndex(n, c, h, w) < data.size());
        return this->data[this->desc.GetIndex(n, c, h, w)];
    }

    const T& operator()(int n, int c, int h, int w) const
    {
        assert(this->desc.GetIndex(n, c, h, w) < data.size());
        return this->data[this->desc.GetIndex(n, c, h, w)];
    }

    typename std::vector<T>::iterator begin()
    {
        return data.begin();
    }

    typename std::vector<T>::iterator end()
    {
        return data.end();
    }

    typename std::vector<T>::const_iterator begin() const
    {
        return data.begin();
    }

    typename std::vector<T>::const_iterator end() const
    {
        return data.end();
    }
};

template<class T, class G>
tensor<T> make_tensor(std::initializer_list<int> dims, G g)
{
    // TODO: Compute float
    return tensor<T>{mlopen::TensorDescriptor{mlopenFloat, dims}}.generate(g);
}

template<class T, class X>
tensor<T> make_tensor(const std::vector<X>& dims)
{
    // TODO: Compute float
    return tensor<T>{mlopen::TensorDescriptor{mlopenFloat, dims.data(), static_cast<int>(dims.size())}};
}

template<class T, class X, class G>
tensor<T> make_tensor(const std::vector<X>& dims, G g)
{
    return make_tensor<T>(dims).generate(g);
}

struct tensor_generate
{
    template<class Tensor, class G>
    Tensor&& operator()(Tensor&& t, G g) const
    {
        return std::forward<Tensor>(t.generate(g));
    }
};

template<class F>
struct protect_fn
{
    F f;
    protect_fn(F x) : f(std::move(x)) 
    {}

    template<class... Ts>
    auto operator()(Ts&&... xs) const MLOPEN_RETURNS
    (f(std::forward<Ts>(xs)...));
};

template<class F>
protect_fn<F> protect(F f)
{
    return {std::move(f)};
}

struct cross_args_apply
{
    template<class F, class T, class... Ts>
    void operator()(F f, T&& x, Ts&&... xs) const
    {
        mlopen::each_args(std::bind(f, std::forward<T>(x), std::placeholders::_1), std::forward<Ts>(xs)...);
    }
};

template<class F, class... Ts>
void cross_args(F f, Ts&&... xs)
{
    mlopen::each_args(
        std::bind(cross_args_apply{}, protect(std::move(f)), std::placeholders::_1, std::forward<Ts>(xs)...),
    std::forward<Ts>(xs)...);
}

template<class T, class Visitor>
struct generate_both_visitation
{
    template<class F, class G1, class G2>
    void operator()(F f, G1 g1, G2 g2) const
    {
        Visitor{}([&](std::initializer_list<int> input, std::initializer_list<int> weights)
        {
            f(make_tensor<T>(input, g1), make_tensor<T>(weights, g2));
        });
    }
};

template<class T, class Visitor, class F, class... Gs>
void generate_all(F f, Gs... gs)
{
    cross_args(
        std::bind(generate_both_visitation<T, Visitor>{}, protect(f), std::placeholders::_1, std::placeholders::_2), 
        gs...);
}


template<class T, class F, class G>
void generate_one(F f, std::vector<int> input, std::vector<int> weights, G g)
{
    f(make_tensor<T>(input, g), make_tensor<T>(weights, g));
}

#endif
