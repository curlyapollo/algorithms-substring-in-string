#ifndef STRINGS_ALGORITHMS_H
#define STRINGS_ALGORITHMS_H
#include <string>

int naive_implementation(const std::string& text, const std::string& sample);

int naive_implementation_regex(const std::string& text, const std::string& sample,
                               const std::vector<int>& inds, const std::vector<std::string>& ss);

int kmp_with_opt(const std::string& text, const std::string& sample);

int kmp_with_opt_regex(const std::string& text, const std::string& sample,
                       const std::vector<int>& inds, const std::vector<std::string>& ss);

int kmp_without_opt(const std::string& text, const std::string& sample);

int kmp_without_opt_regex(const std::string& text, const std::string& sample,
                          const std::vector<int>& inds, const std::vector<std::string>& ss);

int boyer_moore(const std::string& text, const std::string& sample);

int boyer_moore_regex(const std::string& text, const std::string& sample,
                      const std::vector<int>& inds, const std::vector<std::string>& ss);

std::pair<std::vector<int>, std::vector<std::string>> for_regex(const std::string& text, const std::string& sample);


#endif