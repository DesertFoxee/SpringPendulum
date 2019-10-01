#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <type_traits>
#include <Windows.h>
#include <fstream>
#include <string>

namespace Ref
{
	template <typename T>
	using remove_cv_ref = typename std::remove_cv<typename std::remove_reference<T>::type>::type;

	template <typename T>
	using remove_ref = typename std::remove_reference<T>::type;

};


namespace Utils
{
	static std::string getPathWorkingDirectory() {
		char paths[MAX_PATH];

		GetModuleFileName(NULL, paths , MAX_PATH);

		std::string temp(paths);

		std::size_t found = temp.find_last_of("/\\");
		return temp.substr(0, found+1);
	}

	static std::string getWorkingDirectory() {
		char paths[MAX_PATH];

		GetModuleFileName(NULL, paths, MAX_PATH);

		std::string temp(paths);
	}
}

#endif // !HELPER_H

