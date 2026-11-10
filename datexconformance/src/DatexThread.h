#pragma once
#include <dz1_thread.h>
#include <functional>
#include <memory>
#include <stdexcept>

namespace datex {
/* The SDK's Dz1Thread_init/clean pair owns a process-default thread, not TLS.
   SDK users must be created through its managed-thread API. */
class ManagedThread {
    u32_t id_ = static_cast<u32_t>(-1);
    static Dz1Error entry(void *ptr) {
        std::unique_ptr<std::function<void()>> work(static_cast<std::function<void()> *>(ptr));
        Dz1Error error = {};
        try {
            (*work)();
        } catch (...) {
            Dz1Error_set(&error, EFAULT);
        }
        return error;
    }

  public:
    ManagedThread() = default;
    explicit ManagedThread(std::function<void()> work) {
        start(std::move(work));
    }
    ManagedThread(const ManagedThread &) = delete;
    ManagedThread &operator=(const ManagedThread &) = delete;
    ~ManagedThread() {
        join();
    }
    void start(std::function<void()> work) {
        if (joinable())
            throw std::runtime_error("Worker already running");
        auto ptr = new std::function<void()>(std::move(work));
        auto error = _Dz1Thread_create(&id_, "DatexConformanceWorker", entry, ptr, 0);
        if (error.code) {
            delete ptr;
            id_ = static_cast<u32_t>(-1);
            throw std::runtime_error("Worker creation failed");
        }
    }
    bool joinable() const {
        return id_ != static_cast<u32_t>(-1);
    }
    void join() {
        if (joinable()) {
            Dz1Error result = {};
            Dz1Thread_wait(id_, &result);
            id_ = static_cast<u32_t>(-1);
        }
    }
};
} // namespace datex
