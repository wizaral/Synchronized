#pragma once
#include <mutex>

namespace al {

template <class T, class Mutex = std::mutex>
class Synchronized final {
    mutable Mutex m_mutex;
    T m_value;

public:
    explicit Synchronized(T init = T{})
    : m_value(std::move(init)) {}

    class Access final {
        friend class Synchronized;

        std::lock_guard<Mutex> m_lock;
        T &m_ref;

        Access(T &ref, Mutex &m_mutex)
        : m_lock(m_mutex)
        , m_ref(ref) {}

    public:
        Access() = delete;
        Access(const Access &access) = delete;
        Access(Access &&access) = delete;
        Access &operator=(const Access &access) = delete;
        Access &operator=(Access &&access) = delete;

        auto &ref() {
            return m_ref;
        }

        const auto &ref() const {
            return m_ref;
        }
    };

    auto get() {
        return Access{m_value, m_mutex};
    }

    const auto get() const {
        return Access{m_value, m_mutex};
    }
};

} // namespace al
