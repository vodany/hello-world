#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <vector>



using namespace std;

int gcd (int a, int b) {
    a = abs(a);
    b = abs(b);
    if (a == 0 || b == 0) {
        return 1;
    }
    int gcd;
    while (a!=0 && b!=0) {
        if (a>b) {
            a=a%b;
        }
        else b=b%a;
    }
    gcd = a+b;
    if (gcd < 0){
        gcd *= -1;
    }
    return gcd;
}


class Rational{
public:
    Rational(){
        numerator = 0;
        denominator = 1;
    };
    Rational (int new_numerator, int new_denominator){
        Rational_normalize(new_numerator, new_denominator);
    };
    int Numerator() const{
        return numerator;
    };
    int Denominator() const{
        return denominator;
    };
    void Rational_normalize(int new_numerator, int new_denominator){
        numerator = new_numerator / gcd(new_numerator,new_denominator);
        denominator = new_denominator / gcd(new_numerator,new_denominator);
        if (numerator == 0 || denominator == 0){
            numerator = 0;
            denominator = 1;
        }
        else if ((numerator > 0 && denominator < 0) || (numerator < 0 && denominator < 0) ){
            numerator *= -1;
            denominator *= -1;
        }
    };
private:
    int numerator;
    int denominator;
};

Rational operator+(const Rational& r_1, const Rational& r_2){
    int numerator = r_1.Numerator()*r_2.Denominator() + r_2.Numerator()*r_1.Denominator();
    int denominator = r_1.Denominator()*r_2.Denominator();
    Rational summ(numerator, denominator);
    return summ;
}
Rational operator-(const Rational& r_1, const Rational& r_2){
    int numerator = r_1.Numerator()*r_2.Denominator() - r_2.Numerator()*r_1.Denominator();
    int denominator = r_1.Denominator()*r_2.Denominator();
    Rational summ(numerator, denominator);
    return summ;
}
Rational operator*(const Rational& r_1, const Rational& r_2){
    int numerator = r_1.Numerator()*r_2.Numerator();
    int denominator = r_1.Denominator()*r_2.Denominator();
    Rational summ(numerator, denominator);
    return summ;
}
Rational operator/(const Rational& r_1, const Rational& r_2){
    int numerator = r_1.Numerator()*r_2.Denominator();
    int denominator = r_1.Denominator()*r_2.Numerator();
    Rational summ(numerator, denominator);
    return summ;
}
bool operator==(const Rational& r_1, const Rational& r_2){
    if (r_1.Numerator()==r_2.Numerator() && r_1.Denominator()==r_2.Denominator()){
        return true;
    } else {
        return false;
    }

}
istream& operator>>(istream& stream, Rational& r){
    int numerator = 0, denominator = 0;
    char slash;
    stream >> numerator >> slash >> denominator;
    if (slash != '/') { return stream; }
    r.Rational_normalize(numerator, denominator);
    return stream;
}
ostream& operator<<(ostream& stream, const Rational& r){
    stream << r.Numerator() << "/" << r.Denominator();
    return stream;
}
bool operator<(const Rational& lhr, const Rational& rhr){
    return (lhr.Numerator()*rhr.Denominator() < rhr.Numerator()*lhr.Denominator());
}
bool operator>(const Rational& lhr, const Rational& rhr){
    return (lhr.Numerator()*rhr.Denominator() > rhr.Numerator()*lhr.Denominator());
}

int main() {
    {
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            cout << x << " ";
            v.push_back(x);
        }
        cout << endl;
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
            for (auto s : v){
                cout << s << " ";
            }
            cout << endl;
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}


