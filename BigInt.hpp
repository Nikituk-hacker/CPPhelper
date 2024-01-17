#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::string To_str(auto a) {
    return std::to_string(a);
}

std::string To_str(char c) {
    std::string ans{};
    ans.push_back(c);
    return ans;
}

std::string To_str(const char *a) {
    return std::string(a, sizeof(a));
}

std::string To_str(std::basic_string<char> &s) {
    return s;
}

struct BigInt {
    std::string num;

    BigInt() {
        num = "0";
    }

    BigInt(auto a) {
        num = To_str(a);
    }

    BigInt operator=(auto x) {
        num = To_str(x);
        return num;
    }

    BigInt operator-() {
        if (num[0] == '-') {
            num.erase(num.begin());
        } else {
            num = '-' + num;
        }
        return num;
    }

    int size() {
        return num.size();
    }
};

using bi = BigInt;

std::istream& operator>>(std::istream &is, bi &val) {
    return is >> val.num;
}

std::ostream& operator<<(std::ostream &os, bi val) {
    return os << val.num << ' ';
}

bool operator!=(bi a, bi b) {
    return a.num != b.num;
}

bool operator!=(bi a, auto b) {
    return a.num != To_str(b);
}

bool operator==(bi a, bi b) {
    return a.num == b.num;
}

bool operator==(bi a, auto b) {
    return a.num == To_str(b);
}

bool operator<(bi a, bi b) {
    if (a.num[0] == '-' && b.num[0] == '-') {
        if (a == b) return false;
        return !(a.num < b.num);
    }
    if (a.num[0] == '-') {
        return true;
    } 
    if (b.num[0] == '-') {
        return false;
    }
    if (a.size() != b.size()) {
        return a.size() < b.size() ? 1 : 0;
    }
    return a.num < b.num;
} 

bool operator<(bi a, auto b) {
    return a.num < To_str(b);
}

bool operator>(bi a, bi b) {
    if (a.num[0] == '-' && b.num[0] == '-') {
        if (a == b) return false;
        return !(a.num > b.num);
    }
    if (a.num[0] == '-') {
        return false;
    } 
    if (b.num[0] == '-') {
        return true;
    }
    if (a.size() != b.size()) {
        return a.size() > b.size() ? 1 : 0;
    }
    return a.num > b.num;
} 

bool operator>(bi a, auto b) {
    return a.num > To_str(b);
}

bool operator>=(bi a, bi b) {
    return a.num > b.num || a.num == b.num;
} 

bool operator>=(bi a, auto b) {
    return a.num >= To_str(b);
}

bool operator <=(bi a, bi b) {
    return a.num < b.num || a.num == b.num;
} 

bool operator <=(bi a, auto b) {
    return a.num <= To_str(b);
}

// bi operator-(bi a, bi b) {
//     auto x = a.num;
//     auto y = b.num;

// }

bi operator+(bi a, bi b) {
    auto x = a.num;
    auto y = b.num;
    if (x.size() < y.size()) {
        swap(x, y);
    }
    std::string ans = "";
    // if ((a < 0 && b >= 0) || (a >= 0 && b < 0)) {
    //     return a - b;
    // }

    int sign = (x[0] == '-' ? -1 : 1); //sign of answer

    if (sign == -1) {
        x.erase(x.begin());
        y.erase(y.begin());
    }

    int ptr_on_x = x.size() - 1, ptr_on_y = y.size() - 1;
    short plus = 0;
    while (std::min(ptr_on_x, ptr_on_y) >= 0) {
        short sum = x[ptr_on_x] - '0' + y[ptr_on_y] - '0' + plus;
        --ptr_on_x;
        --ptr_on_y;
        ans.push_back(sum % 10 + '0');
        plus = 0;
        if (sum > 9) {
            plus = 1;
        }
    }
    while (ptr_on_x >= 0) {
        short sum = x[ptr_on_x] - '0' + plus;
        --ptr_on_x;
        ans.push_back(sum % 10 + '0');
        plus = 0;
        if (sum > 9) {
            plus = 1;
        }
    }
    while (ptr_on_y >= 0) {
        short sum = y[ptr_on_y] - '0' + plus;
        --ptr_on_y;
        ans.push_back(sum % 10 + '0');
        plus = 0;
        if (sum > 9) {
            plus = 1;
        }
    }
    if (plus) {
        ans.push_back('1');
    }
    if (sign == -1) {
        ans.push_back('-');
    }
    std::reverse(ans.begin(), ans.end());
    return bi(ans);
}

bi operator-(bi a, bi b) {
    if (a < b) {
        return -(b - a);
    }
    if (b < 0) {
        return a + (-b);
    }
    bi ans;
    ans.num = "";
    if (a.num.size() > b.num.size()) {
        b.num = std::string(a.num.size() - b.num.size(), '0') + b.num;
    }
    for (int i = a.num.size() - 1; i >= 0; --i) {
        if (a.num[i] >= b.num[i]) {
            ans.num.push_back((char)a.num[i] - b.num[i] + '0');
        } else {
            a.num[i - 1] -= 1;
            ans.num.push_back((char)a.num[i] + 10 - b.num[i] + '0');
        }
    }
    std::reverse(ans.num.begin(), ans.num.end());
    while (ans.num.size() > 1 && *ans.num.begin() == '0') {
        ans.num.erase(ans.num.begin());
    }
    return ans;
}

bi operator-(bi a, auto b) {
    return a - bi(b);
}

bi operator+(bi a, auto b) {
    return a + bi(b);
}

bi operator+=(bi &a, auto b) {
    a = a + bi(b);
    return a;
}

bi& operator++(bi &a) {
    a += 1;
    return a;
}

bi operator++(bi &a, int value) {
    bi tmp = a;
    a += 1;
    return tmp;
}

namespace std {
    bi min(bi a, bi b) {
        return a < b ? a : b;
    }
}
