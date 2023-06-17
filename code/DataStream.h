#pragma once
#include <vector>
#include <string>
#include <cstring>

namespace foo{
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

            void print_bin() const;

            void write(const char* data, int len);
            void read(char* data, int len);

            // Overloaded write functions
            void write(bool value);
            void write(char value);
            void write(__int32 value);
            void write(__int64 value);
            void write(float value);
            void write(double value);
            void write(const char* value);
            void write(const std::string& value);

            private:
            std::vector<char> buf;
            void reserve(int len);
        };

        void DataStream::print_bin() const{
            int size = buf.size();
            printf("size: %d\n", size);
            // for (int i = 0; i < buf.size(); i++){
            //     printf("%02x ", buf[i]);
            // }
            // printf("\n");
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
            write((char*)&len, sizeof(int));
            write(value, len);
        }

        void DataStream::write(const std::string& value){
            char type = DataType::DT_STRING;
            write((char*)&type, sizeof(char));
            int len = value.length();
            write((char*)&len, sizeof(int));
            write(value.c_str(), len);
        }
    }
}