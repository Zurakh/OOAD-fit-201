#include <unordered_map>
#include "IUObject.h"
#include <any>
#include <string>

class UObject: public IUObject
{
public:
	std::any getProperty(const std::string& key);
	void setProperty(const std::string& key, const std::any& value);

private:
	std::unordered_map<std::string, std::any> _store;
};
