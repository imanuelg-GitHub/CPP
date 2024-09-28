#include <iostream>
#include "Datastructures.h"

int main()
{
    std::cout << "EnqueueDynamic : \n";
    ds::EnqueueDynamic imanuelEnqueueDynamic(4);  // can use any size

    std::cout << "\n\nEnqueue:\n";
    imanuelEnqueueDynamic.enqueue(3);
    imanuelEnqueueDynamic.enqueue(5);
    imanuelEnqueueDynamic.enqueue(7);
    imanuelEnqueueDynamic.enqueue(9);

    std::cout << "Capacity = [" << imanuelEnqueueDynamic.getCapacity() << "]\n";

    for (int i = 0; i < imanuelEnqueueDynamic.getCapacity(); i++)
    {
        std::cout << "item = [" << i << "]     Val = [" << imanuelEnqueueDynamic.printItem(i) << "]\n";
    }

    std::cout << "\n\nDequeue:\n";
    for (int i = 0; i < imanuelEnqueueDynamic.getCapacity(); i++)
    {
        int dequeueVal = imanuelEnqueueDynamic.dequeue();
        if (dequeueVal != -1)
        {
            std::cout << "item = [" << i << "]     Val = [" << dequeueVal << "]\n";
        }
    }



}

