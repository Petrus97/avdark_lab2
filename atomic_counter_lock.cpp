#include "atomic_counters.hpp"

atomic_counter_lock::atomic_counter_lock()
    : atomic_counter()
    , m_value(0)
    , m_lock() {
}

int atomic_counter_lock::increment() {
    this->m_lock.lock();
    // TODO: Add locks here
    int prev_value = m_value;
    m_value = m_value + 1;
    this->m_lock.unlock();
    return prev_value;
}

int atomic_counter_lock::decrement() {
    this->m_lock.lock();
    // TODO: Add locks here
    int prev_value = m_value;
    m_value = m_value - 1;
    this->m_lock.unlock();
    return prev_value;
}

void atomic_counter_lock::set(int value) {
    this->m_lock.lock();
    // TODO: Add locks here
    m_value = value;
    this->m_lock.unlock();
}

int atomic_counter_lock::get() {
    // TODO: Add locks here
    int current;
    this->m_lock.lock();
    current = m_value;
    this->m_lock.unlock();
    return current;
}
