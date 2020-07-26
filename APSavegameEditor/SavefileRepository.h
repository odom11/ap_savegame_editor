#pragma once
#include <tuple>
#include <string>
#include <vector>
class SavefileRepository
{
public:
	void readData(const std::string& filename);
	void commit();
	std::vector<std::tuple<std::string, unsigned int>> getItems() const;
	void setItemcount(const std::string& item, const unsigned int count);
private:
	std::string currentFile;
};

