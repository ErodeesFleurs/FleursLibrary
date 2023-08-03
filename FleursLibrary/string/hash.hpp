#ifndef FLEURS_HASH_HPP
#define FLEURS_HASH_HPP 1

#include <string>
#include <vector>

namespace fleurs {
    
    template <int M, class B>
    struct HashUnit {
        using ull = unsigned long long;
        int x; B b;
        HashUnit(int x=0) : x(x), b(x) {}
        HashUnit(int x, B b) : x(x), b(b) {}
        explicit operator ull() { 
            return x ^ (ull) b << 21; 
        }
        ull hashVal() { 
            return x ^ (ull) b << 21; 
        }
        HashUnit operator+(HashUnit o) {
            int y = x+o.x; return{y - (y>=M)*M, b+o.b};
        }
        HashUnit operator-(HashUnit o) {
            int y = x-o.x; return{y + (y< 0)*M, b-o.b};
        }
        HashUnit operator*(HashUnit o) { 
            return {(int)(1LL*x*o.x % M), b*o.b}; 
        }
        bool operator==(HashUnit o) const { 
            return (ull)*this == (ull)o; 
        }
        bool operator<(HashUnit o) const { 
            return (ull)*this < (ull)o; 
        }
    };

    using HashPair = HashUnit<1000000007, HashUnit<1000000009, unsigned>>;

    struct HashDouble {
    static const unsigned long long C = 1e11 + 3;
	std::vector<HashPair> ha, pw;
	HashDouble(std::string& str) : ha(str.size()+1), pw(ha) {
		pw[0] = 1;
		for(int i=0;i<str.size();i++)
			ha[i+1] = ha[i] * C + str[i],
			pw[i+1] = pw[i] * C;
	}
	void push_back(char c) {
		ha.push_back(ha.back() * C + c);
		pw.push_back(pw.back() * C);
	}
	void push_back(std::string& str) {
		for(char c : str) push_back(c);
	}
	size_t size() {
		return ha.size()-1;
	}
	// hash [a, b)
	HashPair hashInterval(int a, int b) {
		return ha[b] - ha[a] * pw[b - a];
	}
};

} // namespace fleurs 

#endif // FLEURS_HASH_HPP