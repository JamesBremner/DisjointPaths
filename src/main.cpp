#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>

#include "GraphTheory.h"
#include "cGrid2D.h"
#include "cDisjointPaths.h"



void ConstructTest1(cDisjointPaths& thePaths)
{
    thePaths.setDim(7, 10);
    thePaths.add(0, 0, 1, 7);
    thePaths.add(0, 1, 5, 6);
    thePaths.add(2, 0, 0, 9);
}

main()
{
    cDisjointPaths thePaths;

    ConstructTest1(thePaths);

    thePaths.Route();
    thePaths.Display();

    return 0;
}
