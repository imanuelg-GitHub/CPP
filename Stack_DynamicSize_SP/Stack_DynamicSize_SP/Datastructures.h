#pragma once
namespace ds
{
    class StackDynamicSizeSP
	{
    const int defaultSize = 3;
	private:
		int capacity;
        int top;
        std::unique_ptr<int[]> arr;
	public:
        StackDynamicSizeSP() : capacity(defaultSize), top(0), arr(std::make_unique<int[]>(capacity))
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
        int getSize()
        {
            return top;
        }


        void push(int val)
        {
           if (top < capacity)
           {
               arr[top] = val;  // add element to array/stack
               top++;  // point to one above newly inserted element
           }
           else
           {
               capacity *= 2;
               std::unique_ptr<int[]> newarr = std::make_unique<int[]>(capacity);  // define new arr with double capacity
               for (int i = 0; i < top; i++)   // copy elements from original arr to newarr
               {
                   newarr[i] = arr[i];
               }
               
               newarr[top] = val;  // insert new element to newarr
               top++;
               
               arr = std::make_unique<int[]>(capacity);  // redefine original arr with the new capacity
               for (int i = 0; i < top; i++)
               {
                   arr[i] = newarr[i];  // copy elements from newarr to original arr
               }
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


        int printItem(int element)
        {
            return arr[element];
        }
	};
};




