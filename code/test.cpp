#include <iostream>
#include "DataStream.h"

using namespace std;
using namespace Binary::serialize;

int main(){
    DataStream ds;
    map<int,double> v;
    v[12]=123;
    v[23] = 234.5;
    ds << v;

    map<int,double> v2;
    ds >> v2;
    
    //traverse v2
    for(map<int,double>::iterator it = v2.begin(); it != v2.end(); ++it){
        cout << it->first << ": " << it->second << endl;
    }

} 