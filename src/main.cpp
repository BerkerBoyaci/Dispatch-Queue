
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "../include/DispatchQueue.h"
#if __cplusplus >= 201703L
#include <filesystem>
#endif
void foo(void) {
    std::cout << "foo\n";
}

int func(void) {
    std::cout << "ret\n";
    return 12;
}

int mySum(int first, int sec) {
    std::cout << "mySum\n";
    std::cout << "param1 \t: " << first << "\t"
                                           "param2 \t:"<< sec <<"\n";

    return first + sec;
}

double mySum2(double first, double sec) {
    std::cout << "mySum\n";
    std::cout << "param1 \t: " << first << "\t"
                                           "param2 \t:" << sec << "\n";

    return first + sec;
}

//  print the current directory given
void printDir(const std::string& strDir)
{
#if __cplusplus >= 201703L
    namespace fs = std::filesystem;
    fs::path currentDir{ strDir };
    for (const auto& dir : fs::directory_iterator(currentDir)) {
        std::cout << "found: " << dir.path() << "\n";
    }
#endif
}

class DummyClass {
public:
    DummyClass() = default;
    ~DummyClass() = default;

    static void doSomeFunc(int x) {
        std::cout << x << "\n";
    }

    void Foo(double d) const
    {
        std::cout << d << "\n";
    }

    int Assign(int a)
    {
        mx = a;
        std::cout << "mx : " << mx << "\n";
        return mx;
    }

private:
    int mx = 0;
};


int main()
{
    //  Create an instances of DispatchQueue class
    concurrency::DispatchQueue w1, w2;

    std::cout << "number of threads available: " << w1.size() << "\n";

    // push our functions into the worker queue.
    w1.push(foo);
    w1.push(func);
    w1.push([](int a, int c) {
        std::cout << "HELLO WORLD!!!\n"
                  << a << " : " << c << "\n";
    }, 14, 15);

    w1.push([](int a) mutable {
        std::cout << "MUTABLE FUNCTION!!!\n"
                  << a << "\n";
    }, 888);

    w1.push(&mySum, 3, 5);

    w1.push(&mySum2, 5454.1, 78.3);

    w1.push(&DummyClass::doSomeFunc, 23);

    w1.push(&DummyClass::Foo, DummyClass{}, 75);

    w1.push(&DummyClass::Assign, DummyClass{}, 15);

    w1.push(printDir, std::filesystem::current_path().string() );

    return 0;

}