#ifndef __PRINTFUNCNAME_H__
#define __PRINTFUNCNAME_H__
/*
 * __PRETTY_FUNCTION__, GCC的扩展特性:
 * 以字符串的形式返回完整的函数签名，包括返回值、类名、函数名、参数列表、模板参数。
 */
#include<string>


/*
 * 去掉了括号开始后面的所有内容，只保留返回值、类名、函数名。
 */
static std::string _CutParenthesesNTail(std::string&& prettyFuncon)
{
    auto pos = prettyFuncon.find('(');  // 1st position of '('
    if(pos!=std::string::npos)  // Not end of string
        prettyFuncon.erase(prettyFuncon.begin()+pos, prettyFuncon.end());

    return std::move(prettyFuncon);
}

// Function name
#define __STR_FUNCTION__ _CutParenthesesNTail(std::string(__PRETTY_FUNCTION__))
// Function name + parentheses (P = parentheses)
#define __STR_FUNCTIONP__ __STR_FUNCTION__+"()"
// Function name + parentheses + colon (C = colon)
#define __STR_FUNCTIONPC__ __STR_FUNCTION__+"(): "


#endif  // __PRINTFUNCNAME_H__