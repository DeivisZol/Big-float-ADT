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
        int getFirstPartLength();
        int getSecondPartLength();
        int getLengthOfValue();
        int getValueAt(int index);
        vector<char> sum(string stringValue, string bfStringValue, int positionOfDot);
        vector<char> sub(string stringValue, string bfStringValue, int positionOfDot);
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
    private:
        BigFloat(string input, int overload);
        bool isLess(const BigFloat& bf);
        bool isMore(const BigFloat& bf);
        bool isNegative = false;
        vector<char> *value;
        size_t lengthToDot;
};

#endif // BIGFLOAT_HPP
