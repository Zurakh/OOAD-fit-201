#pragma once

#include "ICommand.h"

class EmptyCommand: public ICommand
{
public:
	void execute()
	{}
};
