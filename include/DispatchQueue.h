//
// Created by berker on 03.12.2022.
//

#ifndef TYPEERASURE_DISPATCHQUEUE_H
#define TYPEERASURE_DISPATCHQUEUE_H


#include <functional>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "TypeErasure.h"


#if __cplusplus >= 201703L
#define NODISCARD   [[nodiscard]]
#else
#define NODISCARD
#endif


namespace concurrency {

    class DispatchQueue {

        using worker_thread = std::thread;

    public:
        DispatchQueue(std::size_t thread_cnt = std::thread::hardware_concurrency());

        // non-copyable class
        DispatchQueue(const DispatchQueue& rhs) = delete;
        DispatchQueue& operator=(const DispatchQueue& rhs) = delete;

        virtual ~DispatchQueue();

        /// <summary>
        /// Push an operation into the main queue.
        /// </summary>
        template <typename Fn, typename... Args>
        void push(Fn&& fn, Args&&... args)
        {
            std::unique_lock<std::mutex> lock(m_lock);
            m_funcQueue.emplace(std::bind(std::forward<Fn>(fn),
                                          std::forward<Args>(args)...));

            lock.unlock();
            m_cv.notify_one();
        }

        /// <summary>
        /// returns the number of threads which are currently alive.
        /// </summary>
        /// <returns>number of threads</returns>
        NODISCARD std::size_t size() const noexcept;
    private:
        bool m_quit{};			   // quit flag to notify the threads waiting
        std::size_t m_thread_size; // max number of threads

        std::mutex m_lock;					   // locking operations
        std::condition_variable m_cv;		   // notify the threads waiting
        std::queue<TypeErasure> m_funcQueue; // main queue to hold operations
        std::vector<worker_thread> m_threads;  // thread container
    };


} //end of namespace concurrency



#endif //TYPEERASURE_DISPATCHQUEUE_H
