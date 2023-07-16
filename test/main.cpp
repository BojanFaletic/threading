#include <iostream>
#include <gtest/gtest.h>

#include "queue.hpp"


TEST(QueueTest, PushPop) {
    Queue<int> q(3);
    q.push(1);
    q.push(2);
    q.push(3);

    EXPECT_EQ(q.pop(), 1);
    EXPECT_EQ(q.pop(), 2);
    EXPECT_EQ(q.pop(), 3);
}

TEST(QueueTest, PushPopThreaded) {
    Queue<int> q(3);

    std::thread t1([&q](){
        q.push(1);
        q.push(2);
        q.push(3);
    });

    std::thread t2([&q](){
        EXPECT_EQ(q.pop(), 1);
        EXPECT_EQ(q.pop(), 2);
        EXPECT_EQ(q.pop(), 3);
    });

    t1.join();
    t2.join();
}

TEST(QueueTest, PushPopThreaded2) {
    Queue<int> q(3);

    std::thread t1([&q](){
        q.push(1);
        q.push(2);
        q.push(3);
    });

    std::thread t2([&q](){
        EXPECT_EQ(q.pop(), 1);
        EXPECT_EQ(q.pop(), 2);
        EXPECT_EQ(q.pop(), 3);
    });

    t2.join();
    t1.join();
}

int main(int argc, char **argv) {
    std::cout << "Running main() from test\\main.cpp\n";

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
