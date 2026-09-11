#include <iostream>
#include <thread>

using namespace std;


void worker(string name)
{
    for(int i=0;i<10;i++)
    {
        cout << name << " : " << i << endl;

        this_thread::sleep_for(chrono::milliseconds(200));
    }
}
void taskA()
{
    int i = 0;

    while(true)
    {
        cout << "A : " << i++ << endl;
    }
}

void taskB()
{
    int i = 0;

    while(true)
    {
        cout << "B : " << i++ << endl;
    }
}

void work()
{
    for(int i=0;i<5;i++)
    {
        cout << this_thread::get_id()
             << " -> "
             << i
             << endl;
    }
}

int main()
{
    thread t1(worker, "A");
    thread t2(worker, "B");

    t1.join();
    t2.join();
}