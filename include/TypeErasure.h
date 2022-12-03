//
// Created by berker on 03.12.2022.
//

#ifndef _TYPEERASURE_H
#define _TYPEERASURE_H

#include <functional>
#include <memory>


//	Type erasure idiom to make independented function signature
struct TypeErasure {
    // move only
    TypeErasure(const TypeErasure& rhs) = delete;
    TypeErasure& operator=(const TypeErasure& rhs) = delete;
    TypeErasure(TypeErasure&& rhs) = default;
    TypeErasure& operator=(TypeErasure&& rhs) = default;

    template <typename T>
    TypeErasure(T&& obj) :
            wrappedObject{ std::make_unique<Wrapper<T>>(std::forward<T>(obj)) }
    {
    }

    struct ObjectBase {
        virtual void operator()() = 0;
        virtual ~ObjectBase() = default;
    };

    template <typename T>
    struct Wrapper : public ObjectBase {
        Wrapper(T&& t) noexcept :
                wrappedObject(std::forward<T>(t))
        {
        }

        void operator()() override
        {
            wrappedObject();
        }

        T wrappedObject;
    };

    void operator()()
    {
#if __cplusplus >= 201703L
        std::invoke(*wrappedObject);
#else
        (*wrappedObject)();
#endif
    }

    std::unique_ptr<ObjectBase> wrappedObject;
};


#endif //end of _TYPEERASURE_H
