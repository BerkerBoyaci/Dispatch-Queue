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
            wrappedObject{ std::make_unique<Model < T>>(std::forward<T>(obj)) }
    {
    }

    struct Concept {
        virtual void operator()() = 0;
        virtual ~Concept() = default;
    };

    template <typename T>
    struct Model : public Concept {
        Model(T&& t) noexcept :
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

    std::unique_ptr<Concept> wrappedObject;
};


#endif //end of _TYPEERASURE_H
