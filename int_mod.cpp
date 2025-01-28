class int_mod {
	ll value;
	const ll mod;

 public:
	int_mod() : value(0), mod(1e9 + 7) {}

	int_mod(ll a) : mod(1e9 + 7) {
		if (a >= mod) a %= mod;
		value = a;
	}

	int_mod operator+(int_mod other) {
		ll res = this->value + other.value;
		if (res >= mod) res -= mod;
		return res;
	}

	int_mod operator-(int_mod other) {
		ll res = this->value - other.value;
		if (res < 0) res += mod;
		return res;
	}

	int_mod operator*(int_mod other) {
		long long res = 1LL * this->value * other.value;
		if (res >= mod) {
			res %= mod;
		}
		return res;
	}

	int_mod operator+(ll other) { return *this + int_mod(other); }

	int_mod operator-(ll other) { return *this - int_mod(other); }

	int_mod operator*(ll other) { return *this * int_mod(other); }

	int_mod operator=(int_mod other) { return value = other.value; }

	int_mod operator=(ll other) { return *this = int_mod(other); }

	int_mod operator+=(int_mod other) { return *this = *this + other; }

	int_mod operator-=(int_mod other) { return *this = *this - other; }

	int_mod operator*=(int_mod other) { return *this = *this * other; }

	explicit operator ll() { return value; }
};

std::istream& operator>>(std::istream& is, int_mod &imod) {
	ll x;
    is >> x;
    imod = x;
    return is;
}

std::ostream& operator<<(std::ostream& os, int_mod imod) {
	return os << (ll)imod;
}
