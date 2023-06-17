# Object Serialization

<center> 3210105636 王开炫

​    

## Project requirements

### Description

In computer science, serialization is the process of translating object state into a format that can be stored/transmitted and reconstructed later.

Binary serialization uses binary encoding to produce a compact result for uses such as storage or socket-based network streams. This mechanism is especially useful if you have to handle big data where the loading/saving time is crucial.
For cases where you want to read/edit the serialized data, e.g., for software configuration, a serialization to text files (XML, JSON, etc.) is a natural choice.

Please refer to [Serialization](https://en.wikipedia.org/wiki/Serialization) for more details.

### Requirements

- Implement a module to support binary serialization/deserialization:

```cpp
int n0 = 256, n1;
// serialize object n0 to a binary file n.data
serialize(n0, "n.data");
// reconstruct object n1 from the content of n.data
deserialize(n1, "n.data");
// now n0 == n1 should be true.
```

- Implement a wrapper module of [tinyxml2](https://github.com/leethomason/tinyxml2) to support **XML** serialization:

```cpp
std::pair<int, double> pair0 = {2, 3.1}, pair1;
// serialize object pair0 to an XML file pair.xml with the name std_pair
serialize_xml(pair0, "std_pair", "pair.xml");
// reconstruct object pair1 from the content of pair.xml
deserialize_xml(pair1, "std_pair", "pair.xml");
// now pair0 == pair1 should be true.
```

The `pair.xml` would be something like:

```xml
<serialization>
<std_pair>
    <first val="2"/>
    <second val="3.1000000000000001"/>
</std_pair>
</serialization>
```

- Every module has its namespace.
- Both modules should at least support the serialization of arithmetic types (see `std::is_arithmetic`), C++ string type (`std::string`), and STL containers (`std::pair`, `std::vector`, `std::list`, `std::set`, and `std::map`).
- Both modules should provide a convenient mechanism (by macro, template, etc.) to support the serialization of user-defined types
- During testing, you should cover all the required types and options.
- **Bonus** Use binary-to-text encoding/decoding ([base64](https://en.wikipedia.org/wiki/Base64)) to implement a binary mode of XML serialization.
- **Bonus** Support the serialization of smart pointers, e.g., `std::unique_ptr`.

## Binary Serialization

In the first part, binary serialization is implemented. It supports:

* Basic types serialization
* Serialization of stl containers, including
  * `set`
  * `map`
  * `vector`
  * `list`
  * Others like `unorder_map` is trivial to implement.
* Serialization of user-defined type, including **nested user-defined** type.
* **Byte order awareness**, i.e., you can serialize in a machine that is litttle-endian and deserialize in a machine that is big-endian, and vise versa.

### Specification

* User-defined class should be inherited from `Serializable` and implement `serialize()` and `deserialize()` to be serializable.
* A macro is offered to make the implementation of the above function easier:

```cpp
#define SERIALIZE(...) \
void serialize(DataStream& ds) const override{ \
    char type = DataStream::DataType::DT_CUSTOM; \
    ds.write((char*)&type, sizeof(char)); \
    ds.write_args(__VA_ARGS__); \
} \
void deserialize(DataStream& ds) override{ \
    char type; \
    ds.read((char*)&type, sizeof(char)); \
    if(type != DataStream::DataType::DT_CUSTOM){ \
        throw runtime_error("Reading invalid data type"); \
    } \
    ds.read_args(__VA_ARGS__); \
}
```

Just write in the `public` area of your class definition: `SERIALIZE(#all member in your class)`, like:

```
SERIALIZE(name, age, weight, a)
```

### Test

To compile the program, run in `code/bin`

```make
make
```

Note that the test is completed in Ubuntu (WSL), it may fail to compile in Windows, due to the incompatibility of type `__int32_t`, change it to `__int32` and same for `__int64_t` may make it able to compile in Windows.

Run the test `test_bin.cpp`, it should print out:

```Name: John
Age: 25
Weight: 50.5
A: 0
1 2 Hello 1 !
```

which proves that my program works correctly.



Note that my machine is little endian, which can be check in the below program.
Every time `DataStream` is constructed, it will check that if the machine is little-endian and if not, a reverse of the lower byte and the upper will be conducted.

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

## XML Serialization

To compile the program, run in `code/xml`

```make
make
```

The `.xml` files will be saved in `xml/file`

Below is one of the file:

```xml
<?xml version "1.0" encoding = "UTF-8"?>
<serialization>
    <std_int value="1"/>
    <std_string value="Foo"/>
    <std_vector size="3">
        <std_double value="1.200000"/>
        <std_double value="2.400000"/>
        <std_double value="3.600000"/>
    </std_vector>
</serialization>
```

It even does not need the user to define functions to serialize his/her class.
