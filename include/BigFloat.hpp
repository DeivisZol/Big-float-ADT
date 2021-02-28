#ifndef BIGFLOAT_HPP
#define BIGFLOAT_HPP
#include <string>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

class BigFloat {
    public:
        BigFloat(string input);
        virtual ~BigFloat();
        string getValue() const;
        friend ostream& operator<<(ostream& os, const BigFloat& bf);
        BigFloat operator+(const BigFloat& bf);
        BigFloat operator-(const BigFloat& bf);
        BigFloat operator*(const BigFloat& bf);
        BigFloat operator/(const BigFloat& bf);
        BigFloat operator%(const BigFloat& bf);
        bool operator==(const BigFloat& bf);
        bool operator!=(const BigFloat& bf);
        bool operator>(const BigFloat& bf);
        bool operator<(const BigFloat& bf);
        bool operator>=(const BigFloat& bf);
        bool operator<=(const BigFloat& bf);

    protected:

    private:
        bool isLess(const BigFloat& bf);
        bool isMore(const BigFloat& bf);
        vector<char> *value;
};

#endif // BIGFLOAT_HPP
