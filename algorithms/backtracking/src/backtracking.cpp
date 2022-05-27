#include "backtracking.h"

short bktg::isSquare (matrix &table, coordinate begin, coordinate end) {
    int tableSize = table.size();
    if (begin.first < 0 || begin.first >= tableSize || begin.second < 0 || begin.second >= tableSize ||
    	end.first < 0 || end.first >= tableSize || end.second < 0 || end.second >= tableSize || tableSize == 0)
		return -1;

	bool flag = table[begin.second][begin.first];
    for (int i = begin.second; i <= end.second; i++)
        for (int j = begin.first; j <= end.first; j++)
            if (table[i][j] != flag)
                return -1;
    return flag ? 1 : 0;
}

bool bktg::addSquare (square &s, matrix &table) {
	int tableSize = table.size();
	int x = s.first.first, y = s.first.second;
	int size = s.second;

	if (x < 0 || x + size > tableSize || y < 0 || y + size > tableSize || tableSize == 0)
		return false;
	if (isSquare(table, {x, y}, {x + size - 1, y + size - 1}) != 0)
		return false;

    for (int i = y; i < size + y; i++)
        for (int j = x; j < size + x; j++)
	            table[i][j] = true;
    return true;
}

bool bktg::removeSquare (square &s, matrix &table) {
	int tableSize = table.size();
	int x = s.first.first, y = s.first.second;
	int size = s.second;

	if (x < 0 || x + size > tableSize || y < 0 || y + size > tableSize || size == 0 || tableSize == 0)
		return false;
	if (isSquare(table, {x, y}, {x + size - 1, y + size - 1}) != 1)
		return false;

    for (int i = y; i < y + size; i++)
        for (int j = x; j < x + size; j++)
            table[i][j] = false;
    return true;
}

int bktg::getMaximumAllowableSize (int x, int y, matrix &table) {
	int tableSize = table.size();
    for (int i = 1; i < (x < y ? tableSize - y : tableSize - x); i++) {
        for (int j = 0; j <= i; j++) {
            if (table[y + i][x + j])
                return i;
            if (table[y + j][x + i])
                return i;
        }
    }
    return 0;
}

bool bktg::isAvailableSpace (matrix &table) {
    bool flag = false;
    int tableSize = table.size();
    for (int i = 0; i <= tableSize / 2; i++)
        for (int j = 0; j <= tableSize / 2; j++)
            if (!table[i][j]) {
                flag = true;
                break;
            }
    return flag;
}

square bktg::reduceTopSquareSize (std::vector<square> &squares, matrix &table) {
    auto curSquare = squares.back();
    squares.pop_back();
    if (curSquare.second != 0 && !removeSquare(curSquare, table))
    	throw "Error: could not remove square";
    curSquare = std::make_pair(std::make_pair(curSquare.first.first, curSquare.first.second), --curSquare.second);
    if (curSquare.second != 0 && !addSquare(curSquare, table))
    	throw "Error: could not add square";
    squares.push_back(curSquare);
    return curSquare;
}

int bktg::backtrackingSearch (std::vector<square> &minSquares, int tableSize, matrix &table) {
    std::vector<square> squares;
    int counter = 0, min = tableSize * tableSize;
    int maxSquareSize = getMaximumAllowableSize(0, 0, table);
    auto square = std::make_pair(std::make_pair(0, 0), maxSquareSize);
    if (!addSquare(square, table))
    	throw "Error: could not add square";
    int operationCounter = 1;
    squares.push_back(square);
    int x = maxSquareSize, y = 0;
    int center = tableSize / 2;
    while (true) {
        bool isSpace = isAvailableSpace(table);
        if (!isSpace || squares.back().second == 0 || counter == min) {
            if (!isSpace && counter < min) {
                minSquares = squares;
                min = counter;
            }
            if (squares.back().second != 0 && !removeSquare(squares.back(), table))
            	throw "Error: could not remove square";
            operationCounter++;
            squares.pop_back();
            counter--;
            if (squares.empty()) {
                break;
            } else {
                square = reduceTopSquareSize(squares, table);
                operationCounter += 2;
            }
            x = square.first.first;
            y = square.first.second;
        } else {
            while (table[y][x] && (x <= center || y <= center)) {
                if (x <= center) {
                    x++;
                } else {
                    x = 0;
                    y++;
                }
            }
            maxSquareSize = getMaximumAllowableSize(x, y, table);
            square = std::make_pair(std::make_pair(x, y), maxSquareSize);
            if (!addSquare(square, table))
            	throw "Error: could not add square";
            operationCounter++;
            squares.push_back(square);
            counter++;
        }
    }
    return operationCounter;
}

std::vector<square> bktg::getMinSquares (int size, int &operationCounter) {
    if (size == 0 || size == 1)
    	return {};
    std::vector<square> res;
    if (!(size % 2)) {
        res.emplace_back(std::make_pair(std::make_pair(1, 1), size / 2));
        res.emplace_back(std::make_pair(std::make_pair(1, size / 2 + 1), size / 2));
        res.emplace_back(std::make_pair(std::make_pair(size / 2 + 1, 1), size / 2));
        res.emplace_back(std::make_pair(size / 2 + 1, size / 2 + 1), size / 2);
    } else {
        int minDivider = 0;
        for (int num = 3; num <= sqrt(size); num++) {
            if (size % num == 0) {
                minDivider = num;
                break;
            }
        }
        int factor = minDivider ? size / minDivider : 1;
        size = minDivider ? minDivider : size;

        std::vector<bool> arr;
        arr.resize(size, false);
        matrix table;
        for (int i = 0; i < size; i++)
            table.push_back(arr);
        int center = size / 2;

        std::vector<square> firstSquares = {
        	std::make_pair(std::make_pair(center, center), center + 1),
        	std::make_pair(std::make_pair(center + 1, 0), center),
        	std::make_pair(std::make_pair(0, center + 1), center)
        };
        for (auto &obj : firstSquares) {
        	if (!addSquare(obj, table)) {
        		std::cerr << "Error: could not add square\n";
        		return {};
        	}
        	res.push_back(obj);
        }

        std::vector<square> min;
        try	{
        	operationCounter = backtrackingSearch(min, size, table);
        } catch (const char *str) {
        	std::cerr << str << '\n';
        	return {};
        }
        for (auto &obj : min) 
            res.push_back(obj);
        for (auto &obj : res) {
            obj.first.first = obj.first.first * factor + 1;
            obj.first.second = obj.first.second * factor + 1;
            obj.second = obj.second * factor;
        }
    }
    return res;
}
