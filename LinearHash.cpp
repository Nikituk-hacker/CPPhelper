struct ModInt {
  long long value;
  
  ModInt(): value(0) {}
  
  ModInt(long long x): value(x % kMOD) {}
  
  ModInt operator + (ModInt m) {
    ModInt ans;
    ans.value = value + m.value;
    if(ans.value >= kMOD) ans.value -= kMOD;
    return ans;
  }
  
  ModInt operator += (ModInt m) {
    return * this = * this + m;
  }
  
  ModInt operator - (ModInt m) {
    ModInt ans;
    ans.value = value - m.value;
    if(ans.value < 0) ans.value += kMOD;
    return ans;
  }
  
  ModInt operator -= (ModInt m) {
    return * this = * this - m;
  }
  
  ModInt operator * (ModInt m) {
    ModInt ans;
    ans.value = value * m.value;
    if(ans.value >= kMOD) ans.value %= kMOD;
    return ans;
  }
  
  ModInt operator *= (ModInt m) {
    return * this = * this * m;
  }
  
  bool operator == (ModInt m) const {
    return value == m.value;
  }
  
  bool operator < (ModInt m) const {
    return value < m.value;
  }
  
  explicit operator long long() {
    return value;
  }
  
  friend istream & operator >> (istream & is, ModInt & m) {
    long long x;
    is >> x;
    m = x;
    return is;
  }
  
  friend ostream & operator << (ostream & os, ModInt m) {
    return os << m.value;
  }
};

struct ModHash {
  vector < ModInt > h, pw;
  
  ModHash() {}
  
  ModHash(const string & s) {
    const long long n = (long long) s.size();
    h.resize(n + 1);
    h[0] = 0;
    pw.resize(n + 1);
    pw[0] = 1;
    for(long long i = 0; i < n; ++i) {
      h[i + 1] = h[i] * kP + (s[i] - 'a' + 1);
      pw[i + 1] = pw[i] * kP;
    }
  }
  
  ModInt get(long long l, long long r) {
    return h[r] - h[l] * pw[r - l];
  }
};

struct Hash64 {
  vector < unsigned long long > h, pw;
  
  Hash64() {}
  
  Hash64(const string & s) {
    const long long n = (long long) s.size();
    h.resize(n + 1);
    h[0] = 0;
    pw.resize(n + 1);
    pw[0] = 1;
    for(long long i = 0; i < n; ++i) {
      h[i + 1] = h[i] * kP + (s[i] - 'a' + 1);
      pw[i + 1] = pw[i] * kP;
    }
  }
  
  unsigned long long get(long long l, long long r) {
    return h[r] - h[l] * pw[r - l];
  }
};

using DHash = pair < unsigned long long, ModInt > ;

DHash operator * (DHash d, long long x) {
  return {
    d.first * x,
    d.second * x
  };
}

DHash operator + (DHash d, long long x) {
  return {
    d.first + x,
    d.second + x
  };
}

DHash operator + (DHash d1, DHash d2) {
  return {
    d1.first + d2.first,
    d1.second + d2.second
  };
}

DHash operator - (DHash d, long long x) {
  return {
    d.first - x,
    d.second - x
  };
}

struct DoubleHash {
  ModHash mh;
  Hash64 h64;
  DoubleHash() {}
  DoubleHash(const string & s): mh(s), h64(s) {}
  DHash get(long long l, long long r) {
    return {
      h64.get(l, r),
      mh.get(l, r)
    };
  }
};

struct HashHash {
  long long operator()(DHash d) const {
    return (d.first ^ d.second.value) + (d.first & d.second.value);
  }
};
