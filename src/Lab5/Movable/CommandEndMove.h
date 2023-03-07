#pragma once

#include <vector>
#include <Lab5/ICommand.h>
#include <Lab5/IUObject.h>
#include <Lab5/EmptyCommand.h>
#include <Lab5/Movable/IInjectable.h>

template <typename T>
class CommandEndMove: public ICommand
{
private:
	IUObject& _obj;
	EmptyCommand _emptyCommand;
	IMovable<T>& _moveAdapt;
	std::vector<T> _zeros;

public:
	CommandEndMove(IUObject& obj, IMovable<T>& moveAdapt): _obj(obj), _moveAdapt(moveAdapt)
	{}

	void execute()
	{		
		_zeros = std::vector<T>(_moveAdapt.getVelocity().size(), 0);
		_moveAdapt.setVelocity(_zeros);
		std::any_cast<IInjectable*>(_obj.getProperty("moveCommand"))->inject(static_cast<ICommand*>(&_emptyCommand));
	}
};