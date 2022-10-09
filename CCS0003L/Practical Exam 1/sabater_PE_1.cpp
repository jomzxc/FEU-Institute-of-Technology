#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#define USD 0.02307822433373
#define EURO 0.01695600990425
#define YUAN 0.14647596668335
#define KORUNA 0.43323896647403
#define KRONE 0.12575340594204
#define SHEQEL 0.08599717199439
#define DINAR 0.00633700346335

int main()
{
    double php = 0;
    cout << "Enter Philippine peso: ";
    cin >> php;

    double usd = php * USD;
    double euro = php * EURO;
    double yuan = php * YUAN;
    double koruna = php * KORUNA;
    double krone = php * KRONE;
    double sheqel = php * SHEQEL;
    double dinar = php * DINAR;

    cout << fixed << setprecision(3);
    cout << "The amount's equivalent to:" << endl;
    cout << "US Dollar is" << string(1, '\t') << ':' << string(1, '\t') << usd << endl;
    cout << defaultfloat << setprecision(7);
    cout << "Euro" << string(2, '\t') << ':' << string(1, '\t') << euro << endl;
    cout << "Yuan" << string(2, '\t') << ':' << string(1, '\t') << yuan << endl;
    cout << "Koruna" << string(2, '\t') << ':' << string(1, '\t') << koruna << endl;
    cout << "Krone" << string(2, '\t') << ':' << string(1, '\t') << krone << endl;
    cout << "Sheqel" << string(2, '\t') << ':' << string(1, '\t') << sheqel << endl;
    cout << "Dinar" << string(2, '\t') << ':' << string(1, '\t') << dinar << endl;

    return 0;
}
