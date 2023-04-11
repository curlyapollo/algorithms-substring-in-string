#include "algorithms.h"
#include <vector>
#include <unordered_map>

int naive_implementation(const std::string& text, const std::string& sample) {
    int ans = -1;
    for (int i = 0; i <= text.size() - sample.size(); ++i) {
        int j = 0;
        while (j < sample.size() && text[i + j] == sample[j]) {
            j++;
        }
        if (j == sample.size()) {
            ans = i;
        }
    }
    return ans;
}

int naive_implementation_regex(const std::string& text, const std::string& sample,
                       const std::vector<int>& inds, const std::vector<std::string>& ss) {
    std::vector<int> split(text.size());
    int pos;
    for (size_t i = 0; i < ss.size(); ++i) {
        pos = naive_implementation(text,ss[i]);
        if (pos - inds[i] >= 0) {
            split[pos - inds[i]]++;
        }
    }
    int ans = -1;
    for (size_t i = 0; i < text.size(); ++i) {
        if (split[i] == ss.size()) {
            ans = i;
        }
    }
    return ans;
}

int kmp_with_opt(const std::string& text, const std::string& sample) {
    int j = 0;
    std::vector<int> br(sample.length());
    std::vector<int> brs(sample.length());
    for (size_t i = 1; i < sample.length(); ++i) {
        while (j > 0 && sample[i] != sample[j]) {
            j = br[j - 1];
        }
        if (sample[i] == sample[j]) {
            j++;
        }
        br[i] = j;
    }
    for (size_t i = 1; i < sample.length(); ++i) {
        if (sample[br[i - 1]] != sample[i]) {
            brs[i - 1] = br[i - 1];
        } else {
            brs[i - 1] = brs[br[i - 1]];
        }
    }
    size_t k = 0;
    int ans = -1;
    for (size_t i = 0; i < text.length(); ++i) {
        while (k > 0 && sample[k] != text[i]) {
            k = brs[k - 1];
        }
        if (sample[k] == text[i]) {
            k++;
        }
        if (k == sample.length()) {
            ans = i - k + 1;
            k = br[sample.length() - 1];
        }
    }
    return ans;
}

int kmp_with_opt_regex(const std::string& text, const std::string& sample,
                       const std::vector<int>& inds, const std::vector<std::string>& ss) {
    std::vector<int> split(text.size());
    int pos;
    for (size_t i = 0; i < ss.size(); ++i) {
        pos = kmp_with_opt(text,ss[i]);
        if (pos - inds[i] >= 0) {
            split[pos - inds[i]]++;
        }
    }
    int ans = -1;
    for (size_t i = 0; i < text.size(); ++i) {
        if (split[i] == ss.size()) {
            ans = i;
        }
    }
    return ans;
}


int kmp_without_opt(const std::string& text, const std::string& sample) {
    int j = 0;
    std::vector<int> br(sample.length());
    std::vector<int> brs(sample.length());
    for (size_t i = 1; i < sample.length(); ++i) {
        while (j > 0 && sample[i] != sample[j]) {
            j = br[j - 1];
        }
        if (sample[i] == sample[j]) {
            j++;
        }
        br[i] = j;
    }
    size_t k = 0;
    int ans = -1;
    for (size_t i = 0; i < text.length(); ++i) {
        while (k > 0 && sample[k] != text[i]) {
            k = br[k - 1];
        }
        if (sample[k] == text[i]) {
            k++;
        }
        if (k == sample.length()) {
            ans = i - k + 1;
            k = br[sample.length() - 1];
        }
    }
    return ans;
}

int kmp_without_opt_regex(const std::string& text, const std::string& sample,
                          const std::vector<int>& inds, const std::vector<std::string>& ss) {
    std::vector<int> split(text.size());
    int pos;
    for (size_t i = 0; i < ss.size(); ++i) {
        pos = kmp_without_opt(text,ss[i]);
        if (pos - inds[i] >= 0) {
            split[pos - inds[i]]++;
        }
    }
    int ans = -1;
    for (size_t i = 0; i < text.size(); ++i) {
        if (split[i] == ss.size()) {
            ans = i;
        }
    }
    return ans;
}

int boyer_moore(const std::string& text, const std::string& sample) {
    std::unordered_map<char, int> table;
    for (int i = 0; i < 256; ++i) {
        table[(char) i] = sample.size();
    }
    for (int i = 0; i < sample.size() - 1; ++i) {
        table[sample[i]] = sample.size() - 1 - i;
    }
    int i = sample.size() - 1, j, k;
    while (i < text.size()) {
        j = i;
        k = i;
        while (j >= 0 && i <= text.size() - 1) {
            j = sample.size() - 1;
            k = i;
            while (j >= 0 && text[k] == sample[j]) {
                k--;
                j--;
            }
            i += table[text[i]];
        }
    }
    if (k >= text.size() - sample.size()) {
        return -1;
    } else {
        return k + 1;
    }
}

int boyer_moore_regex(const std::string& text, const std::string& sample,
                      const std::vector<int>& inds, const std::vector<std::string>& ss) {
    std::vector<int> split(text.size());
    int pos;
    for (size_t i = 0; i < ss.size(); ++i) {
        pos = boyer_moore(text, ss[i]);
        if (pos - inds[i] >= 0) {
            split[pos - inds[i]]++;
        }
    }
    int ans = -1;
    for (size_t i = 0; i < text.size(); ++i) {
        if (split[i] == ss.size()) {
            ans = i;
        }
    }
    return ans;
}

std::pair<std::vector<int>, std::vector<std::string>> for_regex(const std::string& text, const std::string& sample) {
    int ind1 = 0, ind2 = 0;
    std::vector<std::string> ss;
    std::vector<int> inds;
    while (ind2 < sample.size()) {
        if (sample[ind2] == '?') {
            if (sample[ind1] != '?') {
                inds.push_back(ind1);
                ss.push_back(sample.substr(ind1, ind2 - ind1));
                ind2++;
                ind1 = ind2;
            } else {
                ind1++;
                ind2++;
            }
        } else {
            ind2++;
        }
    }
    ind2--;
    if (sample[ind2] != '?') {
        inds.push_back(ind1);
        ss.push_back(sample.substr(ind1, ind2 - ind1 + 1));
    }
    return std::make_pair(inds, ss);
}
