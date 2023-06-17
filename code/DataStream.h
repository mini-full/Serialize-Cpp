#ifndef __DATASTREAM_H__
#define __DATASTREAM_H__

#pragma once
#include <vector>
#include <map>
#include <set>
#include <list>
#include <string>
#include <cstring>
#include "Serializable.h"

/* DEBUG */
#include <iostream>

namespace Binary{
    namespace serialize{

        class DataStream{
            public:
            enum DataType{
                DT_CHAR,
                DT_INT32,
                DT_INT64,
                DT_FLOAT,
                DT_DOUBLE,
                DT_STRING,
                DT_VECTOR,
                DT_MAP,
                DT_SET,
                DT_LIST,
                DT_BOOL,
                DT_NULL,
                DT_CUSTOM
            };
            DataStream(){};
            ~DataStream(){};

            /**
             * @brief Print the data for debugging
             *
             */
            void print_from_bin() const;

            void write(const char* data, int len);

            // Overloaded write functions
            void write(bool value);
            void write(char value);
            void write(__int32 value);
            void write(__int64 value);
            void write(float value);
            void write(double value);
            void write(const char* value);
            void write(const std::string& value);
            void write(const Serializable& value);

            template <typename T>
            void write(const std::vector<T>& value);

            template <typename T>
            void write(const std::list<T>& value);

            template <typename T>
            void write(const std::set<T>& value);

            template <typename K, typename V>
            void write(const std::map<K, V>& value);

            // varible argument template
            template <typename T, typename... Args>
            void write_args(const T& value, const Args&... args);
            void write_args();

            void read(char* data, int len);

            // Read functions
            void read(bool& value);
            void read(char& value);
            void read(__int32& value);
            void read(__int64& value);
            void read(float& value);
            void read(double& value);
            void read(std::string& value);
            void read(Serializable& value);

            template <typename T>
            void read(std::vector<T>& value);

            template <typename T>
            void read(std::list<T>& value);

            template <typename T>
            void read(std::set<T>& value);

            template <typename K, typename V>
            void read(std::map<K, V>& value);

            template <typename T, typename... Args>
            void read_args(T& value, Args&... args);
            void read_args();


            // << operator overloading
            DataStream& operator<<(bool value){
                write(value);
                return *this;
            }
            DataStream& operator<<(char value){
                write(value);
                return *this;
            }
            DataStream& operator<<(__int32 value){
                write(value);
                return *this;
            }
            DataStream& operator<<(__int64 value){
                write(value);
                return *this;
            }
            DataStream& operator<<(float value){
                write(value);
                return *this;
            }
            DataStream& operator<<(double value){
                write(value);
                return *this;
            }
            DataStream& operator<<(const char* value){
                write(value);
                return *this;
            }
            DataStream& operator<<(const std::string& value){
                write(value);
                return *this;
            }

            template <typename T>
            DataStream& operator<<(const std::vector<T>& value){
                write(value);
                return *this;
            }
            template <typename T>
            DataStream& operator<<(const std::set<T>& value){
                write(value);
                return *this;
            }
            template <typename T>
            DataStream& operator<<(const std::list<T>& value){
                write(value);
                return *this;
            }
            template <typename K, typename V>
            DataStream& operator<<(const std::map<K, V>& value){
                write(value);
                return *this;
            }

            DataStream& operator<<(const Serializable& value){
                write(value);
                return *this;
            }


            // >> operator overloading
            DataStream& operator>>(bool& value){
                read(value);
                return *this;
            }
            DataStream& operator>>(char& value){
                read(value);
                return *this;
            }
            DataStream& operator>>(__int32& value){
                read(value);
                return *this;
            }
            DataStream& operator>>(__int64& value){
                read(value);
                return *this;
            }
            DataStream& operator>>(float& value){
                read(value);
                return *this;
            }
            DataStream& operator>>(double& value){
                read(value);
                return *this;
            }
            DataStream& operator>>(std::string& value){
                read(value);
                return *this;
            }

            template <typename T>
            DataStream& operator>>(std::vector<T>& value){
                read(value);
                return *this;
            }
            template <typename T>
            DataStream& operator>>(std::set<T>& value){
                read(value);
                return *this;
            }
            template <typename T>
            DataStream& operator>>(std::list<T>& value){
                read(value);
                return *this;
            }
            template <typename K, typename V>
            DataStream& operator>>(std::map<K, V>& value){
                read(value);
                return *this;
            }

            DataStream& operator>>(Serializable& value){
                read(value);
                return *this;
            }

            private:
            std::vector<char> buf;
            int pos = 0;
            void reserve(int len);
        };

        void DataStream::print_from_bin() const{
            int size = buf.size();
            printf("size: %d\n", size);
            int  i = 0;
            while (i < size){
                switch ((DataType)buf[i]){
                case DT_CHAR:
                    printf("DT_CHAR: %c\n", buf[i + 1]);
                    i += 2;
                    break;
                case DT_INT32:
                    printf("DT_INT32: %d\n", *(int*)&buf[i + 1]);
                    i += 5;
                    break;
                case DT_INT64:
                    printf("DT_INT64: %lld\n", *(long long*)&buf[i + 1]);
                    i += 9;
                    break;
                case DT_FLOAT:
                    printf("DT_FLOAT: %f\n", *(float*)&buf[i + 1]);
                    i += 5;
                    break;
                case DT_DOUBLE:
                    printf("DT_DOUBLE: %lf\n", *(double*)&buf[i + 1]);
                    i += 9;
                    break;
                case DT_STRING:
                    int len;
                    if ((DataType)buf[++i] != DataType::DT_INT32){
                        throw std::logic_error("Erorr: DT_STRING should be followed by DT_INT32");
                    }
                    memcpy(&len, &buf[++i], sizeof(int));
                    i += 4;
                    std::cout << "DT_STRING: " << std::string(&buf[i], len) << std::endl;
                    i += len;
                    break;
                case DT_BOOL:
                    printf("DT_BOOL: %d\n", *(bool*)&buf[i + 1]);
                    // printf((int)buf[i + 1] ? "true\n" : "false\n");
                    i += 2;
                    break;
                default:
                    printf("Unknown type: %d\n", buf[i]);
                    i += 1;
                    break;
                }
            }
        }

        void DataStream::reserve(int len){
            int size = buf.size();
            int cap = buf.capacity();
            // make the buffer big enough
            if (size + len > cap){
                while (size + len > cap){
                    if (cap == 0){
                        cap = 1;
                    }
                    else{
                        cap *= 2;
                    }
                }
                buf.reserve(cap);
            }
        }

        void DataStream::write(const char* data, int len){
            reserve(len);
            // make memcpy able to write to the buffer
            int size = buf.size();
            buf.resize(size + len);
            std::memcpy(&buf[size], data, len);
        }

        void DataStream::write(bool value){

            char type = DataType::DT_BOOL;
            write((char*)&type, sizeof(char));
            write((char*)&value, sizeof(bool)); // TODO
        }

        void DataStream::write(char value){
            char type = DataType::DT_CHAR;
            write((char*)&type, sizeof(char));
            write((char*)&value, sizeof(char));
        }

        void DataStream::write(__int32 value){
            char type = DataType::DT_INT32;
            write((char*)&type, sizeof(char));
            write((char*)&value, sizeof(__int32));
        }

        void DataStream::write(__int64 value){
            char type = DataType::DT_INT64;
            write((char*)&type, sizeof(char));
            write((char*)&value, sizeof(__int64));
        }

        void DataStream::write(float value){
            char type = DataType::DT_FLOAT;
            write((char*)&type, sizeof(char));
            write((char*)&value, sizeof(float));
        }

        void DataStream::write(double value){
            char type = DataType::DT_DOUBLE;
            write((char*)&type, sizeof(char));
            write((char*)&value, sizeof(double));
        }

        void DataStream::write(const char* value){
            char type = DataType::DT_STRING;
            write((char*)&type, sizeof(char));
            int len = strlen(value);
            write(len);
            write(value, len);
        }

        void DataStream::write(const std::string& value){
            char type = DataType::DT_STRING;
            write((char*)&type, sizeof(char));
            int len = value.length();
            write(len);
            write(value.c_str(), len);
        }

        void DataStream::write(const Serializable& value){
            value.serialize(*this);
        }

        template <typename T>
        void DataStream::write(const std::vector<T>& value){
            char type = DataType::DT_VECTOR;
            write((char*)&type, sizeof(char));
            int len = value.size();
            write(len);
            for (int i = 0; i < len; i++){
                write(value[i]);
            }
        }

        template <typename T>
        void DataStream::write(const std::list<T>& value){
            char type = DataType::DT_LIST;
            write((char*)&type, sizeof(char));
            int len = value.size();
            write(len);
            for (auto it = value.begin(); it != value.end(); it++){
                write(*it);
            }
        }

        template <typename T>
        void DataStream::write(const std::set<T>& value){
            char type = DataType::DT_SET;
            write((char*)&type, sizeof(char));
            int len = value.size();
            write(len);
            for (auto it = value.begin(); it != value.end(); it++){
                write(*it);
            }
        }

        template <typename K, typename V>
        void DataStream::write(const std::map<K, V>& value){
            char type = DataType::DT_MAP;
            write((char*)&type, sizeof(char));
            int len = value.size();
            write(len);
            for (auto it = value.begin(); it != value.end(); it++){
                write(it->first);
                write(it->second);
            }
        }

        template <typename T, typename ...Args>
        void DataStream::write_args(const T& value, const Args&... args){
            write(value);
            write_args(args...);
        }
        void DataStream::write_args(){}

        void DataStream::read(char* data, int len){
            std::memcpy(data, (char*)&buf[pos], len);
            pos += len;
        }

        template <typename T>
        void DataStream::read(std::set<T>& value){
            value.clear();
            pos = 0;
            if (buf[pos] != DataType::DT_SET){
                throw std::logic_error("Error: attempt to read set a type other than set");
            }
            pos++;
            int len;
            read(len);
            for (int i = 0; i < len; i++){
                T t;
                read(t);
                value.insert(t);
            }
        }

        template <typename T>
        void DataStream::read(std::vector<T>& value){
            value.clear();
            pos = 0;
            if (buf[pos] != DataType::DT_VECTOR){
                throw std::logic_error("Error: attempt to read vector a type other than vector");
            }
            pos++;
            int len;
            read(len);
            value.resize(len);
            for (int i = 0; i < len; i++){
                read(value[i]);
            }
        }

        template <typename T>
        void DataStream::read(std::list<T>& value){
            value.clear();
            pos = 0;
            if (buf[pos] != DataType::DT_LIST){
                throw std::logic_error("Error: attempt to read list a type other than list");
            }
            pos++;
            int len;
            read(len);
            for (int i = 0; i < len; i++){
                T tmp;
                read(tmp);
                value.push_back(tmp);
            }
        }

        template <typename K, typename V>
        void DataStream::read(std::map<K, V>& value){
            value.clear();
            pos = 0;
            if (buf[pos] != DataType::DT_MAP){
                throw std::logic_error("Error: attempt to read map a type other than map");
            }
            pos++;
            int len;
            read(len);
            for (int i = 0; i < len; i++){
                K k;
                V v;
                read(k);
                read(v);
                value[k] = v;
            }
        }

        void DataStream::read(bool& value){
            if (buf[pos] != DataType::DT_BOOL){
                throw std::logic_error("Error: attempt to read bool a type other than bool");
            }
            value = *(bool*)&buf[pos + 1];
            pos += 2;
        }

        void DataStream::read(char& value){
            if (buf[pos] != DataType::DT_CHAR){
                throw std::logic_error("Error: attempt to read char a type other than char");
            }
            value = *(char*)&buf[pos + 1];
            pos += 2;
        }

        void DataStream::read(__int32& value){
            if (buf[pos] != DataType::DT_INT32){
                throw std::logic_error("Error: attempt to read int32 a type other than int32");
            }
            value = *(int*)&buf[pos + 1];
            pos += 5;
        }

        void DataStream::read(__int64& value){
            if (buf[pos] != DataType::DT_INT64){
                throw std::logic_error("Error: attempt to read int64 a type other than int64");
            }
            value = *(long long*)&buf[pos + 1];
            pos += 9;
        }

        void DataStream::read(float& value){
            if (buf[pos] != DataType::DT_FLOAT){
                throw std::logic_error("Error: attempt to read float a type other than float");
            }
            value = *(float*)&buf[pos + 1];
            pos += 5;
        }

        void DataStream::read(double& value){
            if (buf[pos] != DataType::DT_DOUBLE){
                throw std::logic_error("Error: attempt to read double a type other than double");
            }
            value = *(double*)&buf[pos + 1];
            pos += 9;
        }

        void DataStream::read(std::string& value){
            if (buf[pos] != DataType::DT_STRING){
                throw std::logic_error("Error: attempt to read string a type other than string");
            }
            pos += 1;
            int len;
            read(len);
            if (len < 0){
                throw std::logic_error("Error: attempt to read string with negative length");
            }
            value.assign((char*)&buf[pos], len);
            pos += len;
        }

        void DataStream::read(Serializable& value){
            value.deserialize(*this);
        }

        template <typename T, typename ...Args>
        void DataStream::read_args(T& value, Args&... args){
            read(value);
            read_args(args...);
        }
        void DataStream::read_args(){}

    }
}

#endif