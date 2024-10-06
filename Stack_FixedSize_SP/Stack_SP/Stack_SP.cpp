#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "Datastructures.h"

int main()
{
    std::cout << "\n\nStackFixedSizeSP :\n\n";
    ds::StackDynamic o(5);  // can use any size

    std::cout << "Capacity = [" << o.getCapacity() << "]\n\n";
    o.push(11);
    o.push(22);
    o.push(33);
    o.push(44);
    o.push(55);

    std::cout << "Start: Top = [" << o.peek() << "]\n\n";

    for (int i = 0; i < o.getCapacity(); i++)
    {
        int popVal = o.pop();
        if (popVal != -1)
        {
            std::cout << "i = [" << i << "]     Val = [" << popVal << "]\n";
        }
    }

    std::cout << "\nEnd: Top = [" << o.peek() << "]\n";  // after the first element was pop'ed, getting undefined value
}

