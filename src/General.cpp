#include <string>
bool startsWith(const std::string &s, const std::string &prefix) {
    if (s.size() < prefix.size()) return false;
    for (unsigned int i = 0; i < prefix.size(); i++) {
        if (prefix[i] != s[i]) return false;
    }
    return true;
}