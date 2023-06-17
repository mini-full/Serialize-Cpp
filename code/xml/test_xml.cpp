#include "xml.h"


class Foo{
    public:
    int num;
    string name;
    vector<double> vec;
};

void test_xml_string(){
    cout << "test for xml string " << endl;
    XML::xmlSerialBase baseStr;
    string str0 = "Foo";
    string str1 = "";
    baseStr.serialize_xml(str0, "./file/str.xml");
    baseStr.deserialize_xml(str1, "./file/str.xml");
    cout << "str0  is " << str0 << endl;
    cout << "str1  is " << str1 << endl;
    if (str0 == str1){
        cout << "[pass]" << endl;
    }
    cout << endl;
    return;
}

void test_xml_vector_int(){
    cout << "test for xml vector<int> " << endl;
    XML::xmlSerialBase baseVector;
    vector<int> v0 = {1, 2, 3};
    vector<int> v1;
    baseVector.serialize_xml(v0, "./file/vector1.xml");
    baseVector.deserialize_xml(v1, "./file/vector1.xml");
    cout << "v0 is ";
    for (auto& item : v0){
        cout << item << " ";
    }
    cout << endl;
    cout << "v1 is ";
    for (auto& item : v1){
        cout << item << " ";
    }
    cout << endl;
    if (v0 == v1){
        cout << "[pass]" << endl;
    }
    cout << endl;
}

void test_xml_vector_double(){
    cout << "test for xml vector<double> " << endl;
    XML::xmlSerialBase baseVector;
    vector<double> v0 = {1.2, 2.4, 3.6};
    vector<double> v1;
    baseVector.serialize_xml(v0, "./file/vector2.xml");
    baseVector.deserialize_xml(v1, "./file/vector2.xml");
    cout << "v0 is ";
    for (auto& item : v0){
        cout << item << " ";
    }
    cout << endl;
    cout << "v1 is ";
    for (auto& item : v1){
        cout << item << " ";
    }
    cout << endl;
    if (v0 == v1){
        cout << "[pass]" << endl;
    }
    cout << endl;
}

void test_xml_vector_string(){
    cout << "test for xml vector<string> " << endl;
    XML::xmlSerialBase baseVector;
    vector<string> v0 = {"Foo1", "Foo2", "Foo3"};
    vector<string> v1;
    baseVector.serialize_xml(v0, "./file/vector3.xml");
    baseVector.deserialize_xml(v1, "./file/vector3.xml");
    cout << "v0 is ";
    for (auto& item : v0){
        cout << item << " ";
    }
    cout << endl;
    cout << "v1 is ";
    for (auto& item : v1){
        cout << item << " ";
    }
    cout << endl;
    if (v0 == v1){
        cout << "[pass]" << endl;
    }
    cout << endl;
}

void test_xml_list_int(){
    cout << "test for xml list<int> " << endl;
    XML::xmlSerialBase baseList;
    list<int> l0 = {1, 2, 3};
    list<int> l1;
    baseList.serialize_xml(l0, "./file/list1.xml");
    baseList.deserialize_xml(l1, "./file/list1.xml");
    cout << "l0 is ";
    for (auto& item : l1){
        cout << item << " ";
    }
    cout << endl;
    cout << "l1 is ";
    for (auto& item : l1){
        cout << item << " ";
    }
    cout << endl;
    if (l0 == l1){
        cout << "[pass]" << endl;
    }
    cout << endl;
}


void test_xml_list_string(){
    cout << "test for xml list<string>" << endl;
    XML::xmlSerialBase baseList;
    list<string> l0 = {"Foo1", "Foo2", "Foo3"};
    list<string> l1;
    baseList.serialize_xml(l0, "./file/list2.xml");
    baseList.deserialize_xml(l1, "./file/list2.xml");
    cout << "l0 is ";
    for (auto& item : l1){
        cout << item << " ";
    }
    cout << endl;
    cout << "l1 is ";
    for (auto& item : l1){
        cout << item << " ";
    }
    cout << endl;
    if (l0 == l1){
        cout << "[pass]" << endl;
    }
    cout << endl;
}

void test_xml_pair_int_double(){
    cout << "test for xml pair<int, double>" << endl;
    XML::xmlSerialBase basePair;
    pair<int, double> p0 = {1, 1.2};
    pair<int, double> p1;
    basePair.serialize_xml(p0, "./file/pair1.xml");
    basePair.deserialize_xml(p1, "./file/pair1.xml");
    cout << "p0 is " << p0.first << " " << p0.second << endl;
    cout << "p1 is " << p1.first << " " << p1.second << endl;
    if (p0 == p1){
        cout << "[pass]" << endl;
    }
    cout << endl;
}

void test_xml_set_string(){
    cout << "test for xml set<string>" << endl;
    set<string> s0{"Foo1", "Foo2", "Foo3"};
    set<string> s1;
    XML::xmlSerialBase baseSet;
    baseSet.serialize_xml(s0, "./file/set.xml");
    baseSet.deserialize_xml(s1, "./file/set.xml");
    cout << "s0 is ";
    for (auto& item : s0){
        cout << item << " ";
    }
    cout << endl;
    cout << "s1 is ";
    for (auto& item : s1){
        cout << item << " ";
    }
    cout << endl;
    if (s0 == s1){
        cout << "[pass]" << endl;
    }
    cout << endl;
}

void test_xml_map_int2double(){
    cout << "test for xml map<int double>" << endl;
    XML::xmlSerialBase baseMap;
    map<int, double> m0{
        {1, 1.2},
        {2, 2.4},
        {3, 3.6}
    };
    map<int, double> m1;
    baseMap.serialize_xml(m0, "./file/map1.xml");
    baseMap.deserialize_xml(m1, "./file/map1.xml");
    cout << "m0 is " << endl;
    for (auto& item : m0){
        cout << item.first << " " << item.second << endl;
    }
    cout << "m1 is " << endl;
    for (auto& item : m1){
        cout << item.first << " " << item.second << endl;
    }
    if (m0 == m1){
        cout << "[pass]" << endl;
    }
    cout << endl;
}
void test_xml_map_str2str(){
    cout << "test for xml map<string string>" << endl;
    XML::xmlSerialBase baseMap;
    map<string, string> m0{
        {"Foo1", "Hoo1"},
        {"Foo2k", "Hoo2v"},
        {"Foo3k", "Hoo3v"}
    };
    map<string, string> m1;
    baseMap.serialize_xml(m0, "./file/map2.xml");
    baseMap.deserialize_xml(m1, "./file/map2.xml");
    cout << "m0 is " << endl;
    for (auto& item : m0){
        cout << item.first << " " << item.second << endl;
    }
    cout << "m1 is " << endl;
    for (auto& item : m1){
        cout << item.first << " " << item.second << endl;
    }
    if (m0 == m1){
        cout << "[pass]" << endl;
    }
    cout << endl;
}

void test_xml_userType(){
    XML::xmlSerialBase baseUsrType;
    Foo u1 = {1, "Foo", {1.2, 2.4, 3.6}};
    Foo u2;
    baseUsrType.custom_serialize_xml("./file/usr.xml", u1.num, u1.name, u1.vec);
}

int main(){
    test_xml_string();
    test_xml_string();
    test_xml_vector_int();
    test_xml_vector_double();
    test_xml_vector_string();
    test_xml_list_int();
    test_xml_list_string();
    test_xml_pair_int_double();
    test_xml_set_string();
    test_xml_map_int2double();
    test_xml_map_str2str();
    test_xml_userType();
}