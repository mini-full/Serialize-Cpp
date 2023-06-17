#ifndef __SERIALIZABLE_H__
#define __SERIALIZABLE_H__
#pragma once

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
#endif