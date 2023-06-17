#pragma once
#include <vector>
#include <string>
#include <cstring>

/* DEBUG */
#include <iostream>

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

            // Read functions
            void read(bool& value);
            void read(char& value);
            void read(__int32& value);
            void read(__int64& value);
            void read(float& value);
            void read(double& value);
            void read(std::string& value);


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


    }
}