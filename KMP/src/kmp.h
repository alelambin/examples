#include <string>
#include <vector>

namespace kmp {
	std::vector<int> prefixFunction (std::string &);

	std::vector<int> kmpSearch (std::string &, std::string &);

	std::string convertVector (std::vector<int> &);
}