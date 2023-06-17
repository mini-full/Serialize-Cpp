#include <iostream>
#include "DataStream.h"

using namespace std;
using namespace foo::serialize;

int main(){
    DataStream ds;
    // ds.write("Hello World!");
    ds.write(123);
    ds.print_bin();
} 