#pragma once

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

namespace Binary{
    namespace serialize{

        class DataStream;

        class Serializable{
            public:
            virtual void serialize(DataStream& ds) const = 0;
            virtual void deserialize(DataStream& ds) = 0;
        };
    }
}
