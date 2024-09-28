#pragma once
namespace ds
{
    class EnqueueDynamic
    {
    private:
        int capacity;
        int* arr;
        int head;
        int tail;
    public:
        EnqueueDynamic(int size) : capacity(size), head(0), tail(0)
        {
            arr = new int[capacity];
        }

        ~EnqueueDynamic()
        {
            delete[]arr;  // so it's not really removal, is it ? it's skipping items to be printed because we're still having to release memory in the dtor
        }


        int getCapacity()
        {
            return capacity;
        }
      

        void enqueue(int val)
        {
            if (tail < capacity)
            {
                arr[tail] = val;    // Can increase array on fly, i.e. arr = new int ?  Getting confused with linked list ?
                tail++;
            }
        }

        int dequeue()
        {
            head++;
            if (head < capacity)
            {
                return arr[head];
            }
            else
            {
                return -1;  
            }
        }

        int printItem(int item)
        {
            return arr[item];
        }
    };
};




