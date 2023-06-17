#include <iostream>
#include "DataStream.h"
#include "Serializable.h"
using namespace std;
using namespace Binary::serialize;

class A : public Serializable{
    public:
    int a;
    A(){a = 0;}
    SERIALIZE(a)
};

class Foo : public Serializable{
    private:
    string name;
    int age;
    double weight;
    A a;
    public:
    Foo(){}
    Foo(const string& name, int age, double weight, A a) : name(name),age(age), weight(weight), a(a){}
    ~Foo(){}
    SERIALIZE(name, age, weight, a)
    // void serialize(DataStream& ds) const override{
    //     char type = DataStream::DataType::DT_CUSTOM;
    //     ds.write((char*)&type, sizeof(char));
    //     ds.write(name);
    //     ds.write(age);
    // }
    // void deserialize(DataStream& ds) override{
    //     char type;
    //     ds.read((char*)&type, sizeof(char));
    //     if(type != DataStream::DataType::DT_CUSTOM){
    //         throw runtime_error("Reading invalid data type");
    //     }
    //     ds.read(name);
    //     ds.read(age);
    // }

    void show_Foo() const{
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Weight: " << weight << endl;
        cout << "A: " << a.a << endl;
    }
};

int main(){
    DataStream ds;
    Foo foo("John", 25, 50.5, A());
    foo.serialize(ds);
    Foo foo2;
    foo2.deserialize(ds);
    foo2.show_Foo();
}