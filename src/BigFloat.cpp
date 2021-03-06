#include "BigFloat.hpp"

BigFloat::BigFloat(string input) {
    if(input[0] == '-') {
        isNegative = true;
        input.erase(input.begin()+0);
    }
    input.erase(0, input.find_first_not_of('0'));
    if(input[0] == '.' ) {
        input = "0" + input;
    }
    reverse(input.begin(), input.end());
    input.erase(0, input.find_first_not_of('0'));
    reverse(input.begin(), input.end());
    if(input[input.length() - 1] == '.') {
        input += "0";
    }
    value = new vector<char>(input.begin(), input.end());
}

BigFloat::BigFloat(string input, int overload) {
    bool negative;
    if(input[0] == '-') {
        input.erase(input.begin()+0);
        negative = true;
    }
    input.erase(0, input.find_first_not_of('0'));
    if(input[0] == '.' ) {
        input = "0" + input;
    }
    reverse(input.begin(), input.end());
    input.erase(0, input.find_first_not_of('0'));
    reverse(input.begin(), input.end());
    if(input[input.length() - 1] == '.') {
        input += "0";
    }
    if(input.length() == 3 && input[0] == '0' && input[2] == '0') negative = false;
    if(negative) input.insert(input.begin(), '-');
    value = new vector<char>(input.begin(), input.end());
}

BigFloat::~BigFloat()
{
    //dtor
}

string BigFloat::getFirstPart() const{
    return getValue().substr(0, getLengthToDot());
}

string BigFloat::getSecondPart() const{
    return getValue().substr(getLengthToDot() + 1);
}

string BigFloat::getValue() const {
    return string(value->begin(), value->end());
}

int BigFloat::getValueAt(int index) {
    if(index < 0) {
        index = (index * -1);
        return getSecondPart()[index-1] - '0';
    }
    return getFirstPart()[index-1] - '0';
}

int BigFloat::getLengthOfValue() {
    return getValue().length(); // with dot
}

int BigFloat::getSecondPartLength() {
    return getSecondPart().length(); // everything before dot
}

int BigFloat::getFirstPartLength() {
    return getFirstPart().length(); // everything after dot
}

size_t BigFloat::getLengthToDot() const {
    return getValue().find('.');
}

bool BigFloat::isMore(const BigFloat& bf) {
    bool bothNegative = false;
    if(bf.getValue()[0] == '-' && getValue()[0] == '-') bothNegative = true;
    if((getValue()[0] != '-' && bf.getValue()[0] == '-' ) || getLengthToDot() > bf.getLengthToDot()) {
        return true;
    }
    if((getValue()[0] == '-' && bf.getValue()[0] != '-' ) || getLengthToDot() < bf.getLengthToDot()) {
        return false;
    }
    for(int i = 0; i < getValue().length(); i++) {
        if(getLengthToDot() == i) {
            continue;
        }
        if(getValue()[i] > bf.getValue()[i]) {
            return !bothNegative;
        }
    }
    return bothNegative;
}

bool BigFloat::isLess(const BigFloat& bf) {
    bool bothNegative = false;
    if(bf.getValue()[0] == '-' && getValue()[0] == '-') bothNegative = true;
    if((getValue()[0] != '-' && bf.getValue()[0] == '-' ) || getLengthToDot() > bf.getLengthToDot()) {
        return false;
    }
    if((getValue()[0] == '-' && bf.getValue()[0] != '-' ) || getLengthToDot() < bf.getLengthToDot()) {
        return true;
    }
    for(int i = 0; i < getValue().length(); i++) {
        if(getLengthToDot() == i) {
            continue;
        }
        if(getValue()[i] > bf.getValue()[i]) {
            return bothNegative;
        }
    }
    return !bothNegative;
}

vector<char> BigFloat::sum(string stringValue, string bfStringValue, int positionOfDot) {
    vector <char> partFinal;
    bool carry = false;
    for(int i = stringValue.length()-1; i >= 0; i--) {
        int temp = 0;
        if(carry) {
            carry = false;
            temp++;
        }
        temp = temp + bfStringValue[i] - '0' + stringValue[i] - '0';
        if(temp >= 10) {
            carry = true;
            temp = temp - 10;
        }
        partFinal.insert(partFinal.begin(), temp + 48);
    }
    partFinal.insert(partFinal.end() - positionOfDot, '.');
    if(carry)partFinal.insert(partFinal.begin(), '1');
    return partFinal;
}

vector<char> BigFloat::sub(string stringValue, string bfStringValue, int positionOfDot) {
    bool carry = false;
    vector <char> partFinal;
    for(int i = stringValue.length() - 1;i >= 0; i--) {
        int temp = 0;
        if(carry) {
            carry = false;
            temp--;
        }
        if(stringValue[i] < bfStringValue[i]) {
            carry = true;
        }
        temp = temp  + (carry ? (stringValue[i] - '0') + 10 : stringValue[i] - '0') - (bfStringValue[i] - '0');
        partFinal.insert(partFinal.begin(), temp + 48);
    }
    partFinal.insert(partFinal.end() - positionOfDot, '.');
    if(carry)partFinal.insert(partFinal.begin(), '1');
    return partFinal;
}

BigFloat BigFloat::operator+(const BigFloat& bf){
    bool carry = false;
    bool bothNegative;
    int first = getFirstPart().length();
    int bfFirst = bf.getFirstPart().length();
    int second = getSecondPart().length();
    int bfSecond = bf.getSecondPart().length();
    if(isNegative == true && bf.isNegative == true) {
        bothNegative = true;
    }
    vector <char> partFinal;
    string stringValue = getValue().substr(0, getLengthToDot()) + getValue().substr(getLengthToDot() + 1);
    string bfStringValue = bf.getValue().substr(0, bf.getLengthToDot()) + bf.getValue().substr(bf.getLengthToDot() + 1);
    if(first > bfFirst){
        while(first != bfFirst) {
            bfFirst++;
            bfStringValue = '0' + bfStringValue;
        }
    }
    else if(first < bfFirst) {
        while(first != bfFirst) {
            first++;
            stringValue = '0' + stringValue;
        }
    }
    if(second > bfSecond){
        while(second != bfSecond) {
            bfSecond++;
            bfStringValue +=  '0';
        }
    }
    else if(second < bfSecond) {
        while(second != bfSecond) {
            second++;
            stringValue += '0';
        }
    }
    if(isNegative && !bf.isNegative) {
        if(isMore(bf)) {
            partFinal = sub(stringValue, bfStringValue,  second);
            partFinal.insert(partFinal.begin(), '-');
        }
        else {
            partFinal = sub(bfStringValue, stringValue, second);
        }
    }
    else if(!isNegative && bf.isNegative) {
        if(isMore(bf)){
            partFinal = sub(stringValue, bfStringValue, second);
        }
        else {
            partFinal = sub(bfStringValue, stringValue, second);
            partFinal.insert(partFinal.begin(), '-');
        }
    }
    else {
        partFinal = sum(stringValue, bfStringValue, second);
    }
    if(bothNegative) {
        partFinal.insert(partFinal.begin(), '-');
    }
    return BigFloat(string(partFinal.begin(), partFinal.end()), 0);
}

BigFloat BigFloat::operator-(const BigFloat& bf){
    vector <char> partFinal;
    bool carry = false;
    bool bothNegative;
    int first = getFirstPart().length();
    int bfFirst = bf.getFirstPart().length();
    int second = getSecondPart().length();
    int bfSecond = bf.getSecondPart().length();
    if(isNegative == true && bf.isNegative == true) {
        bothNegative = true;
    }
    string stringValue = getValue().substr(0, getLengthToDot()) + getValue().substr(getLengthToDot() + 1);
    string bfStringValue = bf.getValue().substr(0, bf.getLengthToDot()) + bf.getValue().substr(bf.getLengthToDot() + 1);
    if(first > bfFirst){
        while(first != bfFirst) {
            bfFirst++;
            bfStringValue = '0' + bfStringValue;
        }
    }
    else if(first < bfFirst) {
        while(first != bfFirst) {
            first++;
            stringValue = '0' + stringValue;
        }
    }
    if(second > bfSecond){
        while(second != bfSecond) {
            bfSecond++;
            bfStringValue +=  '0';
        }
    }
    else if(second < bfSecond) {
        while(second != bfSecond) {
            second++;
            stringValue += '0';
        }
    }
    partFinal = sub(stringValue, bfStringValue, second);
    if(bothNegative) {
        partFinal.insert(partFinal.begin(), '-');
    }
    return BigFloat(string(partFinal.begin(), partFinal.end()), 0);
}

BigFloat BigFloat::operator*(const BigFloat& bf) {
    vector <char> partFinal;
    if ((getFirstPart()[0] == '0' && getSecondPart()[0] == '0') || (bf.getFirstPart()[0] == '0' && bf.getSecondPart()[0] == '0' )) {
        partFinal.insert(partFinal.begin(), '0');
        partFinal.insert(partFinal.begin(), '.');
        partFinal.insert(partFinal.begin(), '0');
        return BigFloat(string(partFinal.begin(), partFinal.end()));
    }
    string stringValue = getValue().substr(0, getLengthToDot()) + getValue().substr(getLengthToDot() + 1);
    string bfStringValue = bf.getValue().substr(0, bf.getLengthToDot()) + bf.getValue().substr(bf.getLengthToDot() + 1);
    vector<int> temp(stringValue.length() + bfStringValue.length(), 0);
    int index1 = 0;
    int index2 = 0;
    for (int i = stringValue.length() - 1; i >= 0; i--) {
        int carry = 0;
        int value1 = stringValue[i] - 48;
        index2 = 0;
        for (int k = bfStringValue.length() - 1; k >= 0; k--) {
            int value2 = bfStringValue[k] - 48;
            int answ = value1*value2 + temp[index1 + index2] + carry;
            carry = answ / 10;
            temp[index1 + index2] = answ % 10;
            index2++;
        }
        if (carry > 0) {
            temp[index1 + index2] += carry;
        }
        index1++;
    }
    int zero = temp.size() - 1;
    while (zero >= 0 && temp[zero] == 0) {
        zero--;
    }
    while (zero >= 0) {
        partFinal.insert(partFinal.end(), temp[zero--] + 48);
    }
    partFinal.insert((getSecondPart().length() >= bf.getSecondPart().length() ? partFinal.end() - getSecondPart().length() - 1 : partFinal.end() - bf.getSecondPart().length() - 1), '.');
    if((isNegative && !bf.isNegative) || (!isNegative && bf.isNegative)) {
        partFinal.insert(partFinal.begin(), '-');
    }
    return BigFloat(string(partFinal.begin(), partFinal.end()), 1);
}

BigFloat BigFloat::operator/(const BigFloat& bf) {
    //To do
}

BigFloat BigFloat::operator%(const BigFloat& bf){
    //To do
}

bool BigFloat::operator==(const BigFloat& bf) {
    return getValue() == bf.getValue();
}

bool BigFloat::operator!=(const BigFloat& bf) {
    return getValue() != bf.getValue();
}

bool BigFloat::operator>(const BigFloat& bf) {
    return isMore(bf);
}

bool BigFloat::operator<(const BigFloat& bf) {
    return isLess(bf);
}

bool BigFloat::operator>=(const BigFloat& bf) {
    if(getValue() == bf.getValue()) {
        return true;
    }
    return isMore(bf);
}

bool BigFloat::operator<=(const BigFloat& bf) {
    if(getValue() == bf.getValue()) {
        return true;
    }
    return isLess(bf);
}

ostream& operator<<(ostream& os, const BigFloat& bf) {
    os << bf.getValue();
    return os;
}
