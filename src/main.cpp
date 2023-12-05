#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "cGraph.h"
#include "cxy.h"

raven::graph::cGraph g;
std::vector<cxy> vloc;
std::vector<int> path;


void generate()
{
    g.add("1", "3");
    g.add("2", "3");
    g.add("3", "6");
    g.add("4", "6");
    g.add("5", "6");
    vloc.resize(g.vertexCount());
    vloc[g.find("1")] = cxy(0, 10);
    vloc[g.find("2")] = cxy(10, 10);
    vloc[g.find("3")] = cxy(5, 7);
    vloc[g.find("4")] = cxy(0, 0);
    vloc[g.find("5")] = cxy(10, 0);
    vloc[g.find("6")] = cxy(5, 3);

}

void walkaround(int start )
{
    if( g.adjacentOut(start).size() > 1 )
        throw std::runtime_error("walkaround must start at a leaf");

    path.push_back(start);
    int u = start;

    while (true)
    {
        auto vout = g.adjacentOut(u);
        if (vout.size() == 1)
        {
            // u is a leaf, so we must backtrack
            u = vout[0];
        }
        else
        {
            int prev = path[path.size() - 2];

            int next = -1;

            // select next edge with minimum clockwise angle from entering edge
            double amin = DBL_MAX;
            for (int v : vout)
            {
                double a = -cxy::angle(
                    vloc[u], vloc[prev],
                    vloc[u], vloc[v]);
                if (a < amin)
                {
                    amin = a;
                    next = v;
                }
            }
            u = next;
        }
        path.push_back(u);
        if (u == start)
            return;
    }
}

main()
{

    generate();
    walkaround(0);

    for (int vp : path)
        std::cout << g.userName(vp) << " ";
    std::cout << "\n";

    return 0;
}
