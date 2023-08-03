#ifndef FLEURS_KMP_HPP
#define FLEURS_KMP_HPP 1

#include <vector>
#include <string>

namespace fleurs{
    
    template<class T>
    std::vector<int> kmp(std::vector<T>& text, std::vector<T>& pattern){
        int n = text.size(), m = pattern.size();
        std::vector<int> res;
        std::vector<int> pi(m + 1);
        pi[0] = -1;
        for(int i = 0, j = -1; i < m; ++ i){
            while(j >= 0 && pattern[i] != pattern[j]) j = pi[j];
            pi[i + 1] = ++ j;
        }
        for(int i = 0, j = 0; i < n; ++ i){
            while(j >= 0 && text[i] != pattern[j]) j = pi[j];
            if(++ j == m){
                res.push_back(i - m + 1);
                j = pi[j];
            }
        }
        return res;
    }
    std::vector<int> kmp(std::string& text, std::string& pattern) {
        std::vector<char> text_v = std::vector<char>(text.begin(), text.end());
        std::vector<char> pattern_v = std::vector<char>(pattern.begin(), pattern.end());
        return kmp(text_v, pattern_v);
    }

    template<class T>
    std::vector<int> exkmp(std::vector<T>& s) {
        int n = s.size();
        if (n == 0) return {};
        std::vector<int> z(n);
        z[0] = n;
        for(int i = 1, j = 0; i < n; ++ i){
            while(i + j < n && s[j] == s[i + j]) ++ j;
            z[i] = j;
            if(j == 0) continue;
            int k = 1;
            while(i + k < n && k + z[k] < j) z[i + k] = z[k], ++ k;
            i += k - 1, j -= k;
        }
        return z;
    }
    std::vector<int> exkmp(std::string& s) {
        std::vector<char> s_v = std::vector<char>(s.begin(), s.end());
        return exkmp(s_v);
    }
} // namespace fleurs

#endif // FLEURS_KMP_HPP