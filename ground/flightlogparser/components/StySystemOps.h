#ifndef _IS_SYSTEM_OPS_H
#define _IS_SYSTEM_OPS_H

#include <string>
#include <direct.h> // ::_mkdir ::_rmdir
#include <io.h>  // ::_access
#include <cstdio>
#include <iostream>  
#include <fstream>
#include "ISUtils.h"

namespace ISUtils {
class EXPORT_ISUTILS_ABI ISSystemOps {
public:
	static void create_dir(const std::string& dir) {
		::_mkdir(dir.c_str());
	}
	static void delete_dir(const std::string& dir) {
		::_rmdir(dir.c_str());
	}
	static bool file_exist(const std::string& path) {
		return (::_access(path.c_str(), 0) != -1);
	}
	static bool create_file(const std::string& path) {
		std::fstream fs(path.c_str(), std::ios::out); // a more graceful way?
		return true;
	}
	static bool remove_file(const std::string& path) { // true for success to remove
		return ::remove(path.c_str()) == 0;
	}
};
} // ISUtils 

#endif // _IS_SYSTEM_OPS_H
