#include "user_locks.hpp"

// [x] Bonus task: assuming TSO memory model, add fences for synchronization

user_lock_dekker::user_lock_dekker()
    : user_lock() {
    m_flag[0] = m_flag[1] = false;
    m_turn = 0;
}

void user_lock_dekker::lock(int thread_id) {
    // TODO: Implement the lock acquire part of the Dekker algorithm here
    m_flag[thread_id].store(true); // the thread wants to acquire the lock
    // [x] FENCE: we want that this store will be visible to the other thread before the load
    while (m_flag[(thread_id + 1) % sizeof(m_flag)].load()) // check if the other thread has the lock
    {
        // the other thread did not have the lock
        if(m_turn.load() != thread_id) // check if it's not my turn
        {
            // it's not my turn
            m_flag[thread_id].store(false); // reset my flag
            // [x] FENCE
            while (m_turn.load() != thread_id) // wait for my turn
            {
            }
            m_flag[thread_id].store(true); // raise the flag to signal the other thread that now I have the lock
            // [x] FENCE
        }
    }
}

void user_lock_dekker::unlock(int thread_id) {
    // TODO: Implement the lock release part of the Dekker algorithm here
    m_turn.store((thread_id + 1) % sizeof(m_flag)); // set the turn to the other thread
    m_flag[thread_id].store(false); // reset my flag (unlock the other from the first while)
    // [x] FENCE: this 2 store will be loaded in the Store Buffer, we want to flush them into memory
}
