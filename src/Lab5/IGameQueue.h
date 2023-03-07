#pragma once

#include "ICommand.h"

class IGameQueue
{
public:
	virtual void push(ICommand* com) = 0;
	virtual void pop() = 0;
	virtual ICommand* front() = 0;
	virtual ~IGameQueue() = default;
};
