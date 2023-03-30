#include <vector>
#include <ranges>
#include <iostream>
#include <cstddef>
#include <cstring>
#include <cassert>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "base64.h"
#include "byte2Json.h"

using namespace rapidjson;

// Pack 8 byte hex nummbers into the struct Content
void byte2Struct(struct Content& c, auto& bytes)
{
    c.co2 = ((bytes[6] << 8) & 0xFF00) | bytes[7];
    c.errCode = bytes[5] & 0x3F;
    c.errType = (bytes[5] >> 6) & 0x01;
    c.error = (bytes[5] >> 7) & 0x01;
    c.reserved = bytes[4];
    c.id = ((bytes[1] & 0xF) << 16) | (bytes[2] << 8) | bytes[3];
    c.segment = (bytes[1] >> 4) & 0xF;
    c.reserved2 = bytes[0]; 
}

std::string getLevelStr(int level)
{
    std::string levelStr {""};
    for (int i {0}; i<level; i++) {
        levelStr += "    ";
    }
    return levelStr;
}

// Format the json string for human readable
std::string formatJson(const std::string& json)
{
    std::string res {""};
    int level {0};
    for (std::string::size_type index {0}; index<json.size(); index++) {
        char c {json[index]};
        if (level>0 && '\n'==json[json.size()-1]) {
            res += getLevelStr(level);
        }
        switch(c) {
        case '{':
        case '[':
            res = res + c + "\n";
            level++;
            res += getLevelStr(level);
            break;
        case ',':
            res = res + c + "\n";
            res += getLevelStr(level);
            break;
        case '}':
        case ']':
            res += "\n";
            level--;
            res += getLevelStr(level);
            res += c;
            break;
        default:
            res += c;
            break;
        }
    }
    return res;
}

// Packs the values of the struct members into a JSON object, using the provided struct
// member names as keys
// Outputs the JSON so that it is both human-readable (indentation) and machine-readable
// (correct JSON syntax)
std::string struct2Json(const Content& c)
{
    StringBuffer s;
    Writer<StringBuffer> writer(s);

    writer.StartObject();

    writer.Key("co2");
    writer.Uint(c.co2);

    writer.Key("errCode");
    writer.Uint(c.errCode);

    writer.Key("errType");
    writer.Uint(c.errType);

    writer.Key("error");
    // writer.Uint(c.error);
    writer.Bool(c.error);

    writer.Key("reserved");
    writer.Uint(c.reserved);

    writer.Key("id");
    writer.Uint(c.id);

    writer.Key("segment");
    writer.Uint(c.segment);

    writer.Key("reserved2");
    writer.Uint(c.reserved2);

    writer.EndObject();
    std::string strJson { formatJson(s.GetString()) };
    return strJson;
}

int main(int argc, char* argv[])
{
    std::vector<uint8_t> bytes {0x87, 0x30, 0x00, 0x08, 0x37, 0x00, 0x02, 0x58};
    struct Content cStruct;
    byte2Struct(cStruct, bytes);
    assert((cStruct.co2 == 600) && "Pack correctly.");
    std::string str1 { struct2Json(cStruct) };
    std::cout << "Conver bytes array \"";
    for (uint8_t ch : bytes) {
        std::cout << ch;
    }
    std::cout << "\" to Json: " << std::endl;
    std::cout << str1.c_str() << std::endl;

    bytes.clear();
    std::string b64Str {"E0ABAkmCAwQ="};
    bytes = {base64_decode(b64Str)};
    byte2Struct(cStruct, bytes);
    assert((cStruct.co2 == 772) && (cStruct.error == true) && "Pack correctly.");
    std::string str2 { struct2Json(cStruct) };
    std::cout << "Convert base64 \"" << b64Str << "\" to Json: " << std::endl;
    std::cout << str2.c_str() << std::endl;

    return 0;
}