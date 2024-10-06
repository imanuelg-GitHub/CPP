#pragma once
namespace ds
{
    class StackDynamic
	{
	private:
		int capacity;
        int top;
        std::unique_ptr<int[]> arr;
	public:
        StackDynamic(int size) : capacity(size), top(0), arr(std::make_unique<int[]>(capacity))
        {
        }

        /*~StackDynamic()  // no 'new' in ctor, so no need for dtor
        {
            //delete []arr;
        }*/


        int getCapacity()
        {
            return capacity;
        }
        void push(int val)
        {
           if (top < capacity)
           {
                arr[top] = val;  // add element to array/stack
                top++;  // point to one above newly inserted element
           }
        }

        int pop()
        {
            if (top > 0)
            {
                top--;
                return arr[top];
            }
            else
            {
                return -1;
            }
        }
        int peek() const
        {
            return arr[top-1];
        }
	};
};




