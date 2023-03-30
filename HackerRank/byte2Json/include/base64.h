#ifndef __BASE64_H__
#define __BASE64_H__

#include <string>
#include <vector>

std::vector<uint8_t> base64_decode(const std::string& encoded_string);

#endif // __BASE64_H__