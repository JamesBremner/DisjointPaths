
class cPair
{
public:
    cPair(cGrid2D &grid, int c1, int r1, int c2, int r2)
    {
        myCells = std::make_pair(
            grid.index(c1, r1),
            grid.index(c2, r2));
        manhattenDistance = abs(c1 - c2) + abs(r1 - r2);
    }

    int getManDist() const
    {
        return manhattenDistance;
    }

    std::pair<int, int> getCells() const
    {
        return myCells;
    }

private:
    std::pair<int, int> myCells;
    int manhattenDistance;
};

class cDisjointPaths
{
public:
    void setDim(int colCount, int rowCount)
    {
        grid.setDim(colCount, rowCount);
    }

    void add(int c1, int r1, int c2, int r2)
    {
        vPair.emplace_back(grid, c1, r1, c2, r2);
    }

    void Route()
    {
        grid.addOrthoEdges();
        grid.addEdges2Graph(gd.g);
        gd.edgeWeight.resize(2 * gd.g.edgeCount(), 1);

        sortPairs();

        for (auto &p : vPair)
        {
            enablepair(p);
            auto pc = p.getCells();
            gd.startName = grid.name(pc.first);
            gd.endName = grid.name(pc.second);
            auto ret = path(gd);
            paths.push_back(ret.first);
            if (ret.second > ret.first.size())
                std::cout << "path crossed\n";

            disablepath(ret.first);
        }
    }
    void Display()
    {
        for (auto &p : paths)
        {
            auto spa = gd.g.userName(p);
            for (auto &s : spa)
                std::cout << s << " ";
            std::cout << "\n";
        }

        auto viz = pathViz(
            gd.g,
            paths[0],
            true);
        RunDOT(
            gd.g,
            viz);
    }

private:
    cGrid2D grid;
    raven::graph::sGraphData gd;
    std::vector<cPair> vPair;
    std::vector<std::vector<int>> paths;

    void sortPairs()
    {
        std::sort(vPair.begin(), vPair.end(),
                  [](const cPair &l, const cPair &r) -> bool
                  {
                      return l.getManDist() < r.getManDist();
                  });
    }
    void disablepath(
        std::vector<int> &path)
    {
        int prev = -1;
        for (auto v : path)
        {
            if (prev < 0)
            {
                prev = v;
                continue;
            }
            gd.edgeWeight[gd.g.find(prev, v)] = INT_MAX;
            prev = v;
        }
    }

    void enablepair(const cPair &p)
    {
        auto pc = p.getCells();
        for (int v : gd.g.adjacentIn(pc.first))
        {
            gd.edgeWeight[gd.g.find(v, pc.first)] = 1;
        }
        for (int v : gd.g.adjacentIn(pc.second))
        {
            gd.edgeWeight[gd.g.find(v, pc.second)] = 1;
        }
    }
};

