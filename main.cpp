/// АиСД-2, 2023, компьютерное домашнее задание №2
/// Карлинский Леонид Вадимович
/// CLion
/// Проведена работа со временем, сделаны замеры, построены графики, также сделаны csv.

#include "algorithms.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>
#include <set>

std::string binary_alphabet = "ab";
std::string quarternary_alphabet = "abcd";

/// Генерация текста заданного размера с заданным алфавитом.
std::string generation(int size, const std::string& alphabet) {
    srand(time(nullptr));
    std::string str(" ", size);
    for (int i = 0; i < size; ++i) {
        str[i] = alphabet[rand() % alphabet.size()];
    }
    return str;
}

/// Прогон и замер времени наивного алгоритма. Замеров 10.
double measurement_naive(const std::string& text, const std::string& sample, int wildcards) {
    long long time = 0;
    for (int i = 0; i < 10; ++i) {
        auto pr = for_regex(text, sample);
        auto start = std::chrono::high_resolution_clock::now();
        if (wildcards) {
            naive_implementation_regex(text, sample, pr.first, pr.second);
        } else {
            naive_implementation(text, sample);
        }
        time += std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count();
    }
    return time / 10.0;
}

/// Прогон и замер времени алгоритма КМП с утончёнными гранями. Замеров 10.
double measurement_kmp_with_opt(const std::string& text, const std::string& sample, int wildcards) {
    long long time = 0;
    for (int i = 0; i < 10; ++i) {
        auto pr = for_regex(text, sample);
        auto start = std::chrono::high_resolution_clock::now();
        if (wildcards) {
            kmp_with_opt_regex(text, sample, pr.first, pr.second);
        } else {
            kmp_with_opt(text, sample);
        }
        time += std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count();
    }
    return time / 10.0;
}

/// Прогон и замер времени алгоритма КМП со стандартными гранями. Замеров 10.
double measurement_kmp_without_opt(const std::string& text, const std::string& sample, int wildcards) {
    long long time = 0;
    for (int i = 0; i < 10; ++i) {
        auto pr = for_regex(text, sample);
        auto start = std::chrono::high_resolution_clock::now();
        if (wildcards) {
            kmp_without_opt_regex(text, sample, pr.first, pr.second);
        } else {
            kmp_without_opt(text, sample);
        }
        time += std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count();
    }
    return time / 10.0;
}

/// Прогон и замер времени алгоритма Бойера-Мура. Замеров 10.
double measurement_boyer_moore(const std::string& text, const std::string& sample, int wildcards) {
    long long time = 0;
    for (int i = 0; i < 10; ++i) {
        auto pr = for_regex(text, sample);
        auto start = std::chrono::high_resolution_clock::now();
        if (wildcards) {
            boyer_moore_regex(text, sample, pr.first, pr.second);
        } else {
            boyer_moore(text, sample);
        }
        time += std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count();
    }
    return time / 10.0;
}

/// Создание таблицы с разными алгоритмами по размерам шаблона.
void make_CSV(const std::string& text, const std::string& name, int wildcards) {
    std::ofstream fout;
    fout.open("../csv/" + name + ".csv", std::ofstream::out | std::ofstream::trunc);
    fout << "Sample size;Naive algorithm;KMP without opt;KMP with opt;Boyer-Moore\n";
    for (int i = 100; i < 3001; i += 100) {
        std::string sample = text.substr(rand() % (text.size() - i), i);
        std::set<int> indexes;
        for (int j = 0; j < wildcards; ++j) {
            int ind = rand() % i;
            while (indexes.find(ind) != indexes.end()) {
                ind = rand() % i;
            }
            indexes.insert(ind);
            sample[ind] = '?';
        }
        fout << i << ";" << measurement_naive(text, sample, wildcards) << ";" << measurement_kmp_without_opt(text, sample, wildcards) <<
                ";" << measurement_kmp_with_opt(text, sample, wildcards) << ";"
                << measurement_boyer_moore(text, sample, wildcards) << "\n";
    }
}

int main() {
    std::string text1 = generation(10000, binary_alphabet);
    make_CSV(text1, "10000symb_bin_zeroWildcard", 0);
    make_CSV(text1, "10000symb_bin_oneWildcard", 1);
    make_CSV(text1, "10000symb_bin_twoWildcard", 2);
    make_CSV(text1, "10000symb_bin_threeWildcard", 3);
    make_CSV(text1, "10000symb_bin_fourWildcard", 4);
    std::string text2 = generation(10000, quarternary_alphabet);
    make_CSV(text2, "10000symb_quart_zeroWildcard", 0);
    make_CSV(text2, "10000symb_quart_oneWildcard", 1);
    make_CSV(text2, "10000symb_quart_twoWildcard", 2);
    make_CSV(text2, "10000symb_quart_threeWildcard", 3);
    make_CSV(text2, "10000symb_quart_fourWildcard", 4);
    std::string text3 = generation(100000, binary_alphabet);
    make_CSV(text3, "100000symb_bin_zeroWildcard", 0);
    make_CSV(text3, "100000symb_bin_oneWildcard", 1);
    make_CSV(text3, "100000symb_bin_twoWildcard", 2);
    make_CSV(text3, "100000symb_bin_threeWildcard", 3);
    make_CSV(text3, "100000symb_bin_fourWildcard", 4);
    std::string text4 = generation(100000, quarternary_alphabet);
    make_CSV(text4, "100000symb_quart_zeroWildcard", 0);
    make_CSV(text4, "100000symb_quart_oneWildcard", 1);
    make_CSV(text4, "100000symb_quart_twoWildcard", 2);
    make_CSV(text4, "100000symb_quart_threeWildcard", 3);
    make_CSV(text4, "100000symb_quart_fourWildcard", 4);
}
