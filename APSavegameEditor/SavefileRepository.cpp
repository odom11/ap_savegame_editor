
#include <fstream>
#include <filesystem>

#include <QDebug>

#include "SavefileRepository.h"

constexpr unsigned int INT_SIZE = 4;

std::unique_ptr<SavefileRepository> SavefileRepository::currentInstance;

SavefileRepository::SavefileRepository() {}

SavefileRepository& SavefileRepository::getInstance() {
	if (!currentInstance) {
		SavefileRepository* repository = new SavefileRepository();
		currentInstance = std::unique_ptr<SavefileRepository>(repository);
	}
	return *currentInstance;
}

bool SavefileRepository::readdata(const std::string& filename) {
	commonRequests.clear();
	missingKeys.clear();
	std::basic_ifstream<std::byte> myfile{ filename, std::ios::binary };
	if (!myfile.good()) {		
		qDebug() << "file " << QString::fromStdString(filename) << " does not exist";
	}
	currentFile = filename;
	std::vector<std::byte> filecontent{ std::istreambuf_iterator<std::byte>(myfile), {} }; 
	data = std::move(filecontent);
	return data.size() != 0;
}

void SavefileRepository::commit() {
	//TODO backup
	std::ofstream outputFile(currentFile, std::ios::binary | std::ios::out);
	outputFile.write(reinterpret_cast<const char*>(data.data()), data.size());
	qDebug() << "wrote data to file";
}
std::byte SavefileRepository::lookForValue(const std::string& key, unsigned int offset) {
	if (commonRequests.contains(key)) {
		std::byte returnvalue = data.at(commonRequests[key]);
		return returnvalue;
	}
	std::vector<std::byte> searchItem;
	searchItem.reserve(key.size());
	std::transform(key.begin(), key.end(), std::back_inserter(searchItem), [](const auto& i) {return static_cast<std::byte>(i); });
	auto match = std::search(data.begin(), data.end(), searchItem.begin(), searchItem.end());
	if (match == data.end()) {
		missingKeys.push_back(key);
		return std::byte(-1);
	}

	match += key.size() + offset;
	commonRequests[key] = match - data.begin();
	return *match;
}

int SavefileRepository::lookForIntValue(const std::string& key, unsigned int offset) {
	lookForValue(key, offset);
	if (!commonRequests.contains(key)) {
		return -11;
	}
	auto storedOffset = commonRequests[key];

	auto startCopy = data.rbegin() + data.size() - storedOffset - INT_SIZE;
	std::byte temp[INT_SIZE];
	std::copy(startCopy, startCopy + INT_SIZE, temp);

	int returnValue = 0;
	std::copy(temp, temp + INT_SIZE, reinterpret_cast<std::byte*>(&returnValue));
	
	return returnValue;
}

bool SavefileRepository::alterValue(const std::string& key, std::byte newValue) {
	if (!commonRequests.contains(key)) {
		return false;
	}
	auto position = commonRequests[key];
	data[position] = newValue;
	return true;
}

bool SavefileRepository::alterIntValue(const std::string& key, int newValue) {
	if (!commonRequests.contains(key)) {
		return false;
	}
	std::byte* ptr = reinterpret_cast<std::byte*>(&newValue);
	std::reverse(ptr, ptr + INT_SIZE);
	unsigned int offset = commonRequests[key];
	auto targetIt = data.begin() + offset;
	std::copy(ptr, ptr + INT_SIZE, targetIt);
	return true;
}

const std::list<std::string>& SavefileRepository::getMissingKeys() const {
	return missingKeys;
}
