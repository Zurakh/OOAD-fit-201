#include "UObject.h"

std::any UObject::getProperty(const std::string& key){
    return _store[key];
}

void UObject::setProperty(const std::string& key, const std::any& value) {
    _store[key] = value;
}
