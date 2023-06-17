#include <iostream>
#include "DataStream.h"

using namespace std;
using namespace foo::serialize;

int main(){
    DataStream ds;
    string s = "Hello";
    // ds.write("Hello World!");
    ds.write(s);
    // ds.write(133);
    ds.print_from_bin();
} 