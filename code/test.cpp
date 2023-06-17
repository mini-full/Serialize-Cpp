#include <iostream>
#include "DataStream.h"

using namespace std;
using namespace foo::serialize;

int main(){
    DataStream ds;
    __int64 i = 32;
    ds << i;
    ds << 23.23;
    ds << "Hello World";
    ds.print_from_bin();
    __int64 o;
    double d;
    string s;
    ds >> o >> d >> s;
    cout << o << endl;
    cout << d << endl;
    cout << s << endl;
}