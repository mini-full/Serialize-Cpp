#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <typeinfo>
#include <cstdarg>
#include <set>
#include <map>
#include "base64.h"

#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

namespace XML{
    class xmlSerialBase{
        private:
        XMLDocument doc;
        XMLElement* root;
        void reset(){
            doc.Clear();
            XMLDeclaration* dec = doc.NewDeclaration("xml version \"1.0\" encoding = \"UTF-8\"");
            doc.InsertFirstChild(dec);
            // insert the root 
            root = doc.NewElement("serialization");
            doc.InsertEndChild(root);
            return;
        }

        void save(string fileName){
            doc.SaveFile(fileName.c_str());
            return;
        }

        public:
        xmlSerialBase(){
            reset();
        }

        void serialize_xml(const bool& object, string fileName){
            reset();
            serialize(object, root);
            save(fileName);
        }

        void serialize_xml(const char& object, string fileName){
            reset();
            serialize(object, root);
            save(fileName);
        }

        void serialize_xml(const int& object, string fileName){
            reset();
            serialize(object, root);
            save(fileName);
        }

        void serialize_xml(const double& object, string fileName){
            reset();
            serialize(object, root);
            save(fileName);
        }

        void serialize_xml(const string& object, string fileName){
            reset();
            serialize(object, root);
            save(fileName);
        }

        template <typename T>
        void serialize_xml_base64(const T& object, string fileName){
            reset();
            serialize(object, root);
            tinyxml2::XMLPrinter printer;
            doc.Accept(&printer);
            std::string str = printer.CStr();
            std::string base64_str = base64_encode(str.c_str(), str.length());
            std::ofstream ofs(fileName, std::ios::binary);
            if (!ofs.is_open()){
                std::cout << "open file " << fileName << " failed" << std::endl;
                return;
            }
            ofs << base64_str;
            ofs.close();
        }

        template <typename T>
        void deserialize_xml_base64(T& object, string fileName){
            std::ifstream fin(fileName, std::ios::binary);
            if (!fin.is_open()){
                std::cout << "open file " << fileName << " failed" << std::endl;
                return;
            }
            std::string str;
            fin >> str;
            fin.close();
            std::string base64_str = base64_decode(str);


            XMLError ret = doc.Parse(base64_str.c_str());
            if (ret != 0){
                throw std::runtime_error("fail to parse the xml file");
            }
            root = doc.FirstChildElement("serialization");
            if (root == nullptr){
                throw std::runtime_error("can't find the root element");
            }
            XMLElement* element = root->FirstChildElement();
            if (element == nullptr){
                throw std::runtime_error("can't find the expected type in file");
            }
            bool valid = deserialize(object, element);
        }

        bool deserialize_xml(bool& object, string fileName){
            XMLError ret = doc.LoadFile(fileName.c_str());
            if (ret != 0){
                throw std::runtime_error("fail to load the xml file");
            }
            root = doc.FirstChildElement("serialization");

            bool valid = deserialize(object, root->FirstChildElement("std_bool"));
            if (!valid){
                throw std::runtime_error("can't find the expected type in file");
            }
            return true;
        }

        bool deserialize_xml(char& object, string fileName){
            XMLError ret = doc.LoadFile(fileName.c_str());
            if (ret == 0){
                throw std::runtime_error("fail to load the xml file");
            }
            root = doc.FirstChildElement("serialization");

            bool valid = deserialize(object, root->FirstChildElement("std_char"));
            if (!valid){
                throw std::runtime_error("can't find the expected type in file");
            }
            return true;
        }

        bool deserialize_xml(int& object, string fileName){
            XMLError ret = doc.LoadFile(fileName.c_str());
            if (ret != 0){
                throw std::runtime_error("fail to load the xml file");
            }
            root = doc.FirstChildElement("serialization");

            bool valid = deserialize(object, root->FirstChildElement("std_int"));
            if (!valid){
                throw std::runtime_error("can't find the expected type in file");
            }
            return true;
        }

        bool deserialize_xml(double& object, string fileName){
            XMLError ret = doc.LoadFile(fileName.c_str());
            if (ret != 0){
                throw std::runtime_error("fail to load the xml file");
            }
            root = doc.FirstChildElement("serialization");

            bool valid = deserialize(object, root->FirstChildElement("std_double"));
            if (!valid){
                throw std::runtime_error("can't find the expected type in file");
            }
            return true;
        }

        bool deserialize_xml(string& object, string fileName){
            XMLError ret = doc.LoadFile(fileName.c_str());
            if (ret != 0){
                throw std::runtime_error("fail to load the xml file");
            }
            root = doc.FirstChildElement("serialization");

            bool valid = deserialize(object, root->FirstChildElement("std_string"));
            if (!valid){
                throw std::runtime_error("can't find the expected type in file");
            }
            return true;
        }

        template<class... Args>
        void custom_serialize_xml(string fileName, Args... rest){
            reset();
            useDefined_serialize(fileName, rest...);
        }

        template<class T>
        void serialize_xml(const vector<T>& vec, string fileName);
        template<class T>
        bool deserialize_xml(vector<T>& vec, string fileName);
        template<class T>
        void serialize_xml(const list<T>& l, string fileName);
        template<class T>
        bool deserialize_xml(list<T>& l, string fileName);
        template<class first, class second>
        void serialize_xml(const pair<first, second>& p, string fileName);
        template<class first, class second>
        bool deserialize_xml(pair<first, second>& p, string fileName);
        template<class T>
        void serialize_xml(const set<T>& s, string fileName);
        template<class T>
        bool deserialize_xml(set<T>& s, string fileName);
        template<class K, class V>
        void serialize_xml(const map<K, V>& m, string fileName);
        template<class K, class V>
        bool deserialize_xml(map<K, V>& m, string fileName);

        private:
        void serialize(const bool& object, XMLElement* node){
            XMLElement* item = doc.NewElement("std_bool");
            item->SetAttribute("value", to_string(object).c_str());
            node->InsertEndChild(item);
        }

        void serialize(const char& object, XMLElement* node){
            XMLElement* item = doc.NewElement("std_char");
            item->SetAttribute("value", to_string(object).c_str());
            node->InsertEndChild(item);
        }

        void serialize(const int& object, XMLElement* node){
            XMLElement* item = doc.NewElement("std_int");
            item->SetAttribute("value", to_string(object).c_str());
            node->InsertEndChild(item);
        }

        void serialize(const double& object, XMLElement* node){
            XMLElement* item = doc.NewElement("std_double");
            item->SetAttribute("value", to_string(object).c_str());
            node->InsertEndChild(item);
        }

        void serialize(const string& object, XMLElement* node){
            XMLElement* item = doc.NewElement("std_string");
            item->SetAttribute("value", object.c_str());
            node->InsertEndChild(item);
        }

        template<class H, class... Args>
        void useDefined_serialize(string fileName, H head, Args... rest){
            serialize(head, root);
            useDefined_serialize(fileName, rest...);
        }

        void useDefined_serialize(string fileName){
            save(fileName);
        }

        bool deserialize(bool& object, XMLElement* node){
            if (node == nullptr){
                return false;
            }
            string value = node->Attribute("value");
            object = stoi(value);
            return true;
        }

        bool deserialize(char& object, XMLElement* node){
            if (node == nullptr){
                return false;
            }
            string value = node->Attribute("value");
            object = stoi(value);
            return true;
        }

        bool deserialize(int& object, XMLElement* node){
            if (node == nullptr){
                return false;
            }
            string value = node->Attribute("value");
            object = stoi(value);
            return true;
        }

        bool deserialize(double& object, XMLElement* node){
            if (node == nullptr){
                return false;
            }
            string value = node->Attribute("value");
            object = stod(value);
            return true;
        }

        bool deserialize(string& object, XMLElement* node){
            if (node == nullptr){
                return false;
            }
            string value = node->Attribute("value");
            object = value;
            return true;
        }

        template<class T>
        void serialize(const vector<T>& vec, XMLElement* node);
        template<class T>
        bool deserialize(vector<T>& vec, XMLElement* node);
        template<class T>
        void serialize(const list<T>& l, XMLElement* node);
        template<class T>
        bool deserialize(list<T>& l, XMLElement* node);
        template<class first, class second>
        void serialize(const pair<first, second>& p, XMLElement* node);
        template<class first, class second>
        bool deserialize(pair<first, second>& p, XMLElement* Node);
        template<class T>
        void serialize(const set<T>& s, XMLElement* node);
        template<class T>
        bool deserialize(set<T>& s, XMLElement* node);
        template<class K, class V>
        void serialize(const map<K, V>& m, XMLElement* node);
        template<class K, class V>
        bool deserialize(map<K, V>& m, XMLElement* node);
    };

    template<class T>
    void xmlSerialBase::serialize(const vector<T>& vec, XMLElement* node){
        XMLElement* item = doc.NewElement("std_vector");
        item->SetAttribute("size", to_string(vec.size()).c_str());
        node->InsertEndChild(item);
        for (auto& elem : vec){
            serialize(elem, item);
        }
        return;
    }

    template<class T>
    void xmlSerialBase::serialize_xml(const vector<T>& vec, string fileName){
        reset();
        serialize(vec, root);
        save(fileName);
    }

    template<class T>
    bool xmlSerialBase::deserialize(vector<T>& vec, XMLElement* node){
        if (node == nullptr){
            return false;
        }
        XMLElement* child = node->FirstChild()->ToElement();
        for (int i = 0; i < atoi(node->Attribute("size")); i++){
            T  item;
            deserialize(item, child);
            vec.emplace_back(item);
            if (child->NextSibling()){
                child = child->NextSibling()->ToElement();
            }
        }
        return true;
    }

    template<class T>
    bool xmlSerialBase::deserialize_xml(vector<T>& vec, string fileName){
        XMLError ret = doc.LoadFile(fileName.c_str());
        if (ret != 0){
            cout << "fail to load the xml file" << endl;
            return false;
        }

        root = doc.FirstChildElement("serialization");
        bool valid = deserialize(vec, root->FirstChildElement("std_vector"));
        if (!valid){
            cout << "can't find the expected type in xml file" << endl;
            return false;
        }
        return true;
    }

    template<class T>
    void xmlSerialBase::serialize(const list<T>& l, XMLElement* node){
        XMLElement* item = doc.NewElement("std_list");
        item->SetAttribute("size", to_string(l.size()).c_str());
        node->InsertFirstChild(item);
        for (auto& elem : l){
            serialize(elem, item);
        }

    };

    template<class T>
    void xmlSerialBase::serialize_xml(const list<T>& l, string fileName){
        reset();
        serialize(l, root);
        save(fileName);
        return;
    }

    template<class T>
    bool xmlSerialBase::deserialize(list<T>& l, XMLElement* node){
        if (node == nullptr){
            return false;
        }
        XMLElement* child = node->FirstChild()->ToElement();
        for (int i = 0; i < atoi(node->Attribute("size")); i++){
            T item;
            deserialize(item, child);
            l.push_back(item);
            if (child->NextSibling()){
                child = child->NextSibling()->ToElement();
            }
        }
        return true;
    }

    template<class T>
    bool xmlSerialBase::deserialize_xml(list<T>& l, string fileName){
        XMLError ret = doc.LoadFile(fileName.c_str());
        if (ret != 0){
            cout << "fail to load the xml file" << endl;
            return false;
        }
        root = doc.FirstChildElement("serialization");
        bool valid = deserialize(l, root->FirstChildElement("std_list"));
        if (!valid){
            cout << "can't find the expected type in xml file" << endl;
            return false;
        }
        return true;
    }

    template<class first, class second>
    void xmlSerialBase::serialize(const pair<first, second>& p, XMLElement* node){
        XMLElement* item = doc.NewElement("std_pair");
        XMLElement* p1 = doc.NewElement("first");
        serialize(p.first, p1);
        item->InsertFirstChild(p1);
        XMLElement* p2 = doc.NewElement("second");
        serialize(p.second, p2);
        item->InsertEndChild(p2);
        node->InsertEndChild(item);
        return;
    }

    template<class first, class second>
    void xmlSerialBase::serialize_xml(const pair<first, second>& p, string fileName){
        reset();
        serialize(p, root);
        save(fileName);
        return;
    }

    template<class first, class second>
    bool xmlSerialBase::deserialize(pair<first, second>& p, XMLElement* node){
        if (node == nullptr){
            return false;
        }
        XMLElement* p1 = node->FirstChildElement("first");
        deserialize(p.first, p1->FirstChild()->ToElement());
        XMLElement* p2 = node->FirstChildElement("second");
        deserialize(p.second, p2->FirstChild()->ToElement());
        return true;
    }

    template<class first, class second>
    bool xmlSerialBase::deserialize_xml(pair<first, second>& p, string fileName){
        XMLError ret = doc.LoadFile(fileName.c_str());
        if (ret != 0){
            cout << "fail to load the xml file" << endl;
            return false;
        }
        root = doc.FirstChildElement("serialization");
        bool valid = deserialize(p, root->FirstChildElement("std_pair"));
        if (!valid){
            cout << "can't find the expected type in xml file" << endl;
            return false;
        }
        return true;
    }

    template<class T>
    void xmlSerialBase::serialize(const set<T>& s, XMLElement* node){
        XMLElement* item = doc.NewElement("std_set");
        item->SetAttribute("size", to_string(s.size()).c_str());
        node->InsertFirstChild(item);
        for (auto& elem : s){
            serialize(elem, item);
        }
        return;
    }

    template<class T>
    void xmlSerialBase::serialize_xml(const set<T>& s, string fileName){
        reset();
        serialize(s, root);
        save(fileName);
        return;
    }

    template<class T>
    bool xmlSerialBase::deserialize(set<T>& s, XMLElement* node){
        if (node == nullptr){
            return false;
        }
        XMLElement* child = node->FirstChild()->ToElement();
        for (int i = 0; i < atoi(node->Attribute("size")); i++){
            T elem;
            deserialize(elem, child);
            s.insert(elem);
            if (child->NextSibling()){
                child = child->NextSibling()->ToElement();
            }
        }
        return true;
    }

    template<class T>
    bool xmlSerialBase::deserialize_xml(set<T>& s, string fileName){
        XMLError ret = doc.LoadFile(fileName.c_str());
        if (ret != 0){
            cout << "fail to load the xml file" << endl;
            return false;
        }
        root = doc.FirstChildElement("serialization");
        bool valid = deserialize(s, root->FirstChildElement("std_set"));
        if (!valid){
            cout << "can't find the expected type in xml file" << endl;
            return false;
        }
        return true;
    }

    template<class K, class V>
    void xmlSerialBase::serialize(const map<K, V>& m, XMLElement* node){
        XMLElement* item = doc.NewElement("std_map");
        item->SetAttribute("size", to_string(m.size()).c_str());
        node->InsertFirstChild(item);
        for (auto& elem : m){
            serialize(make_pair(elem.first, elem.second), item);
        }
        return;
    }

    template<class K, class V>
    void xmlSerialBase::serialize_xml(const map<K, V>& m, string fileName){
        reset();
        serialize(m, root);
        save(fileName);
        return;
    }

    template<class K, class V>
    bool xmlSerialBase::deserialize(map<K, V>& m, XMLElement* node){
        if (node == nullptr){
            return false;
        }
        XMLElement* child = node->FirstChild()->ToElement();
        for (int i = 0; i < atoi(node->Attribute("size")); i++){
            pair<K, V> p;
            deserialize(p, child);
            m.insert(p);
            if (child->NextSibling()){
                child = child->NextSibling()->ToElement();
            }
        }
        return true;
    }

    // the external interface for deserializing the map xml
    template<class K, class V>
    bool xmlSerialBase::deserialize_xml(map<K, V>& m, string fileName){
        XMLError ret = doc.LoadFile(fileName.c_str());
        if (ret != 0){
            cout << "fail to load the xml file" << endl;
            return false;
        }
        root = doc.FirstChildElement("serialization");
        bool valid = deserialize(m, root->FirstChildElement("std_map"));
        if (!valid){
            cout << "can't find the expected type in xml file" << endl;
            return false;
        }
        return true;
    }
};
