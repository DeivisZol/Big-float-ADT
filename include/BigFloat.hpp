#ifndef BIGFLOAT_HPP
#define BIGFLOAT_HPP
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

class BigFloat {
    public:
        BigFloat(string input);
        virtual ~BigFloat();
        string getValue() const;
        size_t getLengthToDot() const;
        string getFirstPart() const;
        string getSecondPart() const;
        int getDifference() const;
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
        size_t lengthToDot;
};

#endif // BIGFLOAT_HPP
