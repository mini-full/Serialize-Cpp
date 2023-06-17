My machine is little endian.

```cpp
// check the byte order of the machine
// little endian or?
#include <iostream>
using namespace std;
int main(){
  int n = 0x12345678;
  char* p = (char*)&n;
  if(*p == 0x78){
    cout << "little endian" << endl;
  }else{
    cout << "big endian" << endl;
  }
  return 0;
}
```

By default, the program runs in little endian way.
