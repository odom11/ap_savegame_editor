
#include <fstream>
#include <filesystem>

#include <QDebug>

#include "SavefileRepository.h"

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

	auto found = data.begin();
	do {
		found = std::find(found, data.end(), *searchItem.begin());
		auto mismatchPair = std::mismatch(searchItem.begin(), searchItem.end(), found);
		if (mismatchPair.first == searchItem.end()) {
			break;
		}
		++found;
	} while (found != data.end());
	if (found == data.end()) {
		qDebug() << "Error: found no item";
		return std::byte(-1);
	}
	found += key.size() + offset;
	commonRequests[key] = found - data.begin();
	return *found;
}

int SavefileRepository::lookForIntValue(const std::string& key, unsigned int offset) {
	lookForValue(key, offset);
	auto storedOffset = commonRequests[key];
	std::byte toCopy[4];
	auto startCopy = data.begin() + storedOffset;
	std::copy(startCopy, startCopy + 4, std::begin(toCopy));
	int returnValue;
	std::byte* ptr = reinterpret_cast<std::byte*>(&returnValue);
	ptr[0] = toCopy[3];
	ptr[1] = toCopy[2];
	ptr[2] = toCopy[1];
	ptr[3] = toCopy[0];
	//int returnvalue = (static_cast<char>(toCopy[3] << 24) | (toCopy[2] << 16) | (toCopy[1] << 8) | (toCopy[0]);
	return returnValue;
}

bool SavefileRepository::alterValue(const std::string& key, std::byte newValue) {
	if (!commonRequests.contains(key)) {
		return false;
	}
	auto position = commonRequests[key];
	data[position] = newValue;
}

bool SavefileRepository::alterIntValue(const std::string& key, int newValue) {
	if (!commonRequests.contains(key)) {
		return false;
	}
	std::byte toCopy[4];
	std::byte* ptr = reinterpret_cast<std::byte*>(&newValue);
	toCopy[0] = ptr[3];
	toCopy[1] = ptr[2];
	toCopy[2] = ptr[1];
	toCopy[3] = ptr[0];
	unsigned int offset = commonRequests[key];
	auto targetIt = data.begin() + offset;
	std::copy(std::begin(toCopy), std::end(toCopy), targetIt);
}