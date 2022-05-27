#include <iostream>
#include <vector>
#include <cmath>

using coordinate = std::pair<int, int>;
using square = std::pair<coordinate, int>;
using matrix = std::vector<std::vector<bool>>;

namespace bktg {
    short isSquare (matrix &, coordinate, coordinate);

    bool addSquare (square &, matrix &);

    bool removeSquare (square &, matrix &);

    int getMaximumAllowableSize (int, int, matrix &);

    bool isAvailableSpace (matrix &);

    square reduceTopSquareSize (std::vector<square> &, matrix &);

    int backtrackingSearch (std::vector<square> &, int, matrix &);

    std::vector<square> getMinSquares (int, int &);
}
