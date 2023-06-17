#include <iostream>
#include "DataStream.h"

using namespace std;
using namespace foo::serialize;

int main(){
    DataStream ds;
    bool b = true;
    ds << b;
    bool c;
    ds.read(c);
    cout << c << endl;
} 