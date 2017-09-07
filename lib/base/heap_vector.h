#include <vector>
#include "make_heap.h"

namespace terra
{
    template <class T, class Alloc = std::allocator<T>,
              class Comp = std::less<typename std::vector<T>::value_type>>
    class HeapVector
    {
    private:
        using ValueType = typename typename std::vector<T>::value_type;
        using SizeType = typename std::vector<T>::size_type;
        using ConstReference = typename std::vector<T>::const_reference;
        std::vector<T> vec_;
        Comp comp_;

    public:
        HeapVector() = default;
        explicit HeapVector(const Comp& comp) : comp_(comp) {}
        explicit HeapVector(const std::vector<T>& vec, const Comp& comp = std::less<ValueType>())
            : vec_(vec), comp_(comp)
        {  // construct from initializer_list, optional allocator
            MakeHeap(vec_.begin(), vec_.end(), comp_);
        }

        void Reserve(SizeType capacity) { vec_.reserve(capacity); }

        void Push(ValueType&& val)
        {  // insert element at beginning
            vec_.push_back(std::move(val));
            PushHeap(vec_.begin(), vec_.end(), comp_);
        }

        void Push(const ValueType& val)
        {
            vec_.push_back(val);
            PushHeap(vec_.begin(), vec_.end(), comp_);
        }

        template <class... Args>
        void Emplace(Args&&... args)
        {  // insert element at beginning
            vec_.emplace_back(std::forward<Args>(args)...);
            PushHeap(vec_.begin(), vec_.end(), comp_);
        }

        bool Empty() const
        {  // test if queue is empty
            return (vec_.empty());
        }

        SizeType Size() const
        {  // return length of queue
            return (vec_.size());
        }

        ConstReference Top() const
        {  // return highest-priority element
            return (vec_.front());
        }

        void Pop()
        {  // erase highest-priority element
            PopHeap(vec_.begin(), vec_.end(), comp);
            vec_.pop_back();
        }

        void Swap(T& rhs)
        {  // exchange contents with _Right
            std::swap(vec_, rhs.vec_);
            std::swap(comp, rhs.comp);
        }

        const ValueType& At(const SizeType pos) const
        {  // subscript nonmutable sequence with checking
            return vec_.at(pos);
        }

        void RemoveAt(const SizeType pos)
        {
            PopHeapHoleByIndex(vec_.begin(), pos, vec_.size(), vec_.back(), comp_);
            vec_.pop_back();
        }
    };
}