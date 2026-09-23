#ifndef PREPROCCESSER_H
#define PREPROCCESSER_H
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
std::string resolve_path(const std::string& current_file, const std::string& include_path);
struct PreprocessResult {
    std::string clean_source;
    std::vector<std::string> dependency_paths;
    std::unordered_map<std::string, std::vector<std::string>> namespace_depends;
    std::unordered_map<std::string, std::vector<std::string>> included_namespaces;
    std::unordered_set<std::string> accessible_namespaces;
};

PreprocessResult preprocess_includes(std::string& source, const std::string& current_file);
struct MatchResult {
    size_t else_pos;
    size_t endif_pos;
};
static MatchResult findMatch(const std::string& src, size_t searchStart) {
    int depth = 0;
    size_t elsePos = std::string::npos;
    size_t pos = searchStart;
    while (pos < src.size()) {
        size_t nextIf = src.find("#if", pos);
        size_t nextElse = src.find("#else", pos);
        size_t nextEndif = src.find("#endif", pos);
        size_t next = std::min({nextIf, nextElse, nextEndif});
        if (next == std::string::npos) break;
        if (next == nextIf) {
            depth++;
            pos = next + 3;
        } else if (next == nextElse) {
            if (depth == 0) { elsePos = next; }
            pos = next + 5;
        } else { // nextEndif
            if (depth == 0) { return {elsePos, next}; }
            depth--;
            pos = next + 6;
        }
    }
    return {std::string::npos, std::string::npos};
}
#endif
