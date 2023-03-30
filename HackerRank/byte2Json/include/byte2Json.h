#ifndef __BYTE2JSON_H__
#define __BYTE2JSON_H__

struct Content {
    uint16_t co2;
    uint8_t errCode : 6;
    uint8_t errType : 1;
    uint8_t error : 1;
    uint8_t reserved;
    uint32_t id : 20;
    uint32_t segment : 4;
    uint8_t reserved2;
};

#endif // __BYTE2JSON_H__