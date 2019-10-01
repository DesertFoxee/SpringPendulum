
#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <unordered_map>
#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>
#include "Helper.h"

template <typename TypeName  , typename T>
class ResourceManager {

private:
	std::unordered_map<std::string, std::string > paths;
	/*
		unsigned int : using count amount object is using resouce
	*/
	std::unordered_map<std::string, std::pair<T*, unsigned int >> resources;
	
	std::pair<T*, unsigned int>* findResource(const std::string &id);
	
	bool unload(const std::string& id);
	void loadPaths(const std::string & path_file);
public:

	virtual T* loadResource(const std::string& path) = 0;
	T* getResource(const std::string & id);
	std::string  getPath(const std::string &id);
	bool uploadResource(const std::string &id);
	bool releaseResource(const std::string &id);

	void removeResouce();
	void show();

	ResourceManager(const std::string& file_config);
	virtual ~ResourceManager() { this->removeResouce(); };
};


template<typename TypeName, typename T>
std::pair<T*, unsigned int>* ResourceManager<TypeName, T>::findResource(const std::string& id) {
	auto found = resources.find(id);
	return (found != resources.end()) ? &found->second : nullptr;
}

template<typename TypeName, typename T>
T* ResourceManager<TypeName, T>::getResource(const std::string & id) {
	auto found = findResource(id);
	return (found) ? found->first : nullptr;
}

// get fullpath resouce with id
template<typename TypeName, typename T>
std::string ResourceManager<TypeName, T>::getPath(const std::string & id) {
	auto found = paths.find(id);
	return (found != paths.end()) ? found->second : std::string();
}

template<typename TypeName, typename T>
bool ResourceManager<TypeName, T>::uploadResource(const std::string & id) {
	auto found = findResource(id);
	if(found) {
		found->second++;
		return true;
	}

	auto path_id = this->getPath(id);
	if(!path_id.empty()) {
		T* resource = this->loadResource(path_id);
		resources.emplace(id, std::make_pair(resource, 1));
		return true;
	}
	return false;
}


// delete resource for new or reload 
template<typename TypeName, typename T>
bool ResourceManager<TypeName, T>::releaseResource(const std::string & id) {
	auto found = findResource(id);
	if(found ) {
		--found->second;
		if(!found->second) {
			this->unload(id);
		}
		return true;
	}
	return false;
}


template<typename TypeName, typename T>
bool ResourceManager<TypeName, T>::unload(const std::string & id) {
	auto found = resources.find(id);
	if(found == resources.end()) {
		return false;
	}
	delete found->first;
	resources.erase(id);
	return true;
}

template<typename TypeName, typename T>
void ResourceManager<TypeName, T>::removeResouce() {
	while(resources.begin() != resources.end()) {
		delete resources.begin()->second.first;
		resources.erase(resources.begin());
	}
}

template<typename TypeName, typename T>
void ResourceManager<TypeName, T>::loadPaths(const std::string & path_file) {
	std::ifstream paths;
	std::string path_dir = Utils::getPathWorkingDirectory();

	paths.open(path_dir + path_file);

	if(paths.is_open()) {
		std::string line;
		while(std::getline(paths, line)) {
			std::stringstream keystream(line);
			std::string name;
			std::string path;
			keystream >> path;
			keystream >> name;
			this->paths.emplace(name.substr(0 , name.find_last_of('.')) , path_dir+ path +name);  //(name , fullpath)
		}
		paths.close();
		return;
	}
	std::cout << "[x] Loading faided : Path not exist or die [" << path_file <<"]" << std::endl;
}

template<typename TypeName, typename T>
void ResourceManager<TypeName, T>::show() {
	for(auto const &i : paths) {
		std::cout << i.first << " : " << i.second << std::endl;
	}
	for(auto const &i : resources) {
		std::cout << i.first << std::endl;
	}
}


template <typename TypeName, typename T>
ResourceManager<TypeName, T>::ResourceManager(const std::string& file_config) {
	this->paths.clear();
	this->resources.clear();
	this->loadPaths(file_config);
	
}

#endif // !RESOURCEMANAGER_H


