#pragma once

#include <vector>

template <typename T>
class IMovable
{
public:
	virtual std::vector<T> getPosition() = 0;
	virtual void setPosition(std::vector<T> value) = 0;
	virtual std::vector<T> getVelocity() = 0;
	virtual void setVelocity(std::vector<T> value) = 0;
	virtual ~IMovable() = default;
};