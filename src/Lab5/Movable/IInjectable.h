#pragma once

#include <Lab5/ICommand.h>

class IInjectable : virtual public ICommand
{
public:
	virtual void inject(ICommand* command) = 0;
};