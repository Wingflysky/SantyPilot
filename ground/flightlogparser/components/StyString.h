/**
 * @file ISString.cpp
 * string utils
 * @author: zhangxin
 * @date: 2024-1-29
 */
#ifndef _ISSTRING_H
#define _ISSTRING_H
#include <string>
#include <cwchar> // w_char
#include <cstdlib> // mbstowcs_s
#include "ISUtils.h"
#include <vector>

namespace ISUtils {
	EXPORT_ISUTILS_ABI const std::string join_string(const std::vector<std::string>& list, char split = ' ');
	EXPORT_ISUTILS_ABI bool string_2_wchar(const std::string& str, wchar_t* dst, const size_t& dst_len);
	EXPORT_ISUTILS_ABI const std::vector<std::string> split_string(const std::string& raw, char split);
	EXPORT_ISUTILS_ABI const std::string trim_spaces(const std::string& raw);
}

#endif // _ISSTRING_H
