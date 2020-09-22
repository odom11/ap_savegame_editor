#pragma once
#include <tuple>
#include <string>
#include <vector>
#include <memory>


class SavefileRepository
{
public:
	static SavefileRepository& getInstance();
	bool readdata(const std::string& filename);
	void commit();
	std::byte lookForValue(const std::string& key, unsigned int offset = 4);
	int lookForIntValue(const std::string& key, unsigned int offset = 1);
	bool alterValue(const std::string& key, std::byte newValue);
	bool alterIntValue(const std::string& key, int newValue);
	const std::list<std::string>& getMissingKeys() const;
	//std::vector<std::tuple<std::string, unsigned int>> getitems() const;
	//void setitemcount(const std::string& item, const unsigned int count);
private:
	SavefileRepository();
	static std::unique_ptr<SavefileRepository> currentInstance;
	std::string currentFile;
	std::vector<std::byte> data;
	std::unordered_map<std::string, unsigned int> commonRequests;
	std::list<std::string> missingKeys;
};