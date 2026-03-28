#include<concepts>
#include<numeric>


template<typename I> requires std::integral<I>
class rational
{
	I num_;
	I den_;
	
	void semplifica() {
		if (den_ == I{0}) return;
		
		if (num_ == I{0}) {
			den_ = I{1};
			return;
		}
		
		I g = std::gcd(num_,den_);
		num_ /= g;
		den_ /= g;
		
		if (den_ < I{0}) {
			num_= -num_;
			den_=-den_;
		}
	}
	
	bool is_nan() const {
		return num_ == I{0} && den_ == I{0};
	}
	
	bool is_inf() const {
		return den_  == I{0} && num_ != I{0};
	}
	
	
	public:
		rational()
			: num_(I{0}), den_(I{1}) 
		{}
		
		rational(const I& n, const I& d)
			: num_(n), den_(d)
		{
			if (den_ == I{0}) {
				return;
			}
			semplifica();
		}
		
		I num() const { return num_; }
		I den() const { return den_; }
		
		rational& operator+=(const rational& other) {
			if (is_nan() || other.is_nan()) {
				num_= den_ = I{0};
				return *this;
			}
		
			if (is_inf() || other.is_inf()) {
				num_ = I{1};
				den_ = I{0};
				return *this;
			}
		
			num_ = num_*other.den_+other.num_*den_;
			den_= den_ *other.den_;
		
			semplifica();
			return *this;
		}
		
		rational operator+(const rational& other) const {
			rational ret = *this;
			ret += other;
			return ret;
		}
		
		rational& operator -=(const rational& other) {
			if (is_nan() || other.is_nan()) {
				num_= den_ = I{0};
				return *this;
			}
		
			if (is_inf() || other.is_inf()) {
				num_ = I{1};
				den_ = I{0};
				return *this;
			}
			
			num_ = num_*other.den_- other.num_*den_;
			den_ = den_*other.den_;
			
			semplifica();
			return *this;
		}
		
		rational operator-(const rational& other) const {
			rational ret = *this;
			ret -= other;
			return ret;
		}
		
		rational& operator*=(const rational& other) {
			if (is_nan() || other.is_nan()) {
				num_= den_ = I{0};
				return *this;
			}
		
			if (is_inf() || other.is_inf()) {
				num_ = I{1};
				den_ = I{0};
				return *this;
			}
			
			num_ *= other.num_;
			den_ *= other.den_;
			
			semplifica();
			return *this;
		}
		
		rational operator*(const rational& other) const {
			rational ret = *this;
			ret *= other;
			return ret;
		}
		
		rational& operator /=(const rational& other)  {
			if (is_nan() || other.is_nan()) {
				num_= den_ = I{0};
				return *this;
			}
		
			if (is_inf() || other.is_inf()) {
				num_ = I{1};
				den_ = I{0};
				return *this;
			}
			
			num_ *= other.den_;
			den_ *= other.num_;
			
			semplifica();
			return *this;
		}
		
		rational operator/(const rational& other) const {
			rational ret = *this;
			ret /= other;
			return ret;
		}
};

template<typename I>
std::ostream&
operator<<(std::ostream& os, const rational<I>& r)
{
	if (r.num() == I{0} && r.den() == I{0})
		return os << "NaN";
	
	if (r.den() == I{0})
		return os << "Inf";
	
	
	os << r.num() << "/" << r.den();
	return os;
}