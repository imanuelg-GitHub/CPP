#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "Datastructures.h"

int main()
{
    std::cout << "StackDynamicSizeSP :\n\n";
    ds::StackDynamicSizeSP sds;  // can use any size
    
    std::cout << "Capacity1 = [" << sds.getCapacity() << "]\n\n";
    sds.push(91);
    sds.push(92);
    sds.push(93);

    sds.push(94);
    sds.push(95);
    sds.push(96);
    std::cout << "Capacity2 = [" << sds.getCapacity() << "]\n\n";

    std::cout << "Inserted :\n";
    for (int i = 0; i < sds.getSize(); i++)
    {
        std::cout << "item = [" << i << "]     Val = [" << sds.printItem(i) << "]\n";
    }


    std::cout << "\n\nLIFO = [" << sds.peek() << "]\n\n\n";


    std::cout << "Pop :\n";
    for (int i = 0; i < sds.getCapacity(); i++)
    {
        int popVal = sds.pop();
        if (popVal != -1)
        {
            std::cout << "i = [" << i << "]     Val = [" << popVal << "]\n";
        }
    }
}

