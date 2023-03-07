#pragma once

#include <vector>
#include <Lab5/ICommand.h>
#include <Lab5/IUObject.h>
#include <Lab5/EmptyCommand.h>
#include <Lab5/Movable/IInjectable.h>

class CommandInjectable: public IInjectable
{
private:
	ICommand* _command;
public:
	CommandInjectable() : _command(new EmptyCommand()) {}
	CommandInjectable(ICommand* command): _command(command){}

    void inject(ICommand* command) override
    {
        _command = command;
    }

	void execute() override
	{
		_command->execute();
	}

	~CommandInjectable() = default;
};