#pragma once

#include <iostream>
#include <vector>
#include <Lab5/ICommand.h>


class MacroCommand: public ICommand
{

private:
    std::vector<ICommand*> _cmnds;

public:
	MacroCommand(std::vector<ICommand*>& cmnds):
		_cmnds(cmnds){}

	void execute()
	{
        for (int i = 0; i < _cmnds.size(); ++i)
        {
            (*_cmnds[i]).execute();
        }
	}
};