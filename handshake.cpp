#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool is_syn_printed = false;
void query(int count) {
    for (int i = 0; i < count; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        while (is_syn_printed) {
            cv.wait(lock);
        }
        // print statement
        std::cout << "[" << i << "] SYN ... ";
        is_syn_printed = true;
        cv.notify_one();
    }
void response(int count) {
    for (int i = 0; i < count; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        while (!is_syn_printed)
            cv.wait(lock);
        
        // Print statement
        std::cout << "ACK" << std::endl;
        is_syn_printed = false;
        cv.notify_one();
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: ./handshake <count>\n");
        exit(1);
    }

    // 1
    int count = std::stoi(argv[1])
    /**
     * Steps to follow:
     * 1. Get the "count" from cmd args
     * 2. Create necessary synchronization primitive(s)
     * 3. Create two threads, one for "SYN" and the other for "ACK"
     * 4. Provide the threads with necessary args
     * 5. Update the "query" and "response" functions to synchronize the output
    */

    // 2 - 4
    std::thread t1(query, count);
    std::thread t2(response, count);

    // 5
    t1.join();
    t2.join();
    
    return 0;
}
