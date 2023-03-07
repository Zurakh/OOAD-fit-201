#pragma once

#include <iostream>
#include <vector>
#include <Lab5/ICommand.h>
#include "CommandMove.h"
#include <Lab5/IUObject.h>
#include <Lab5/IGameQueue.h>
#include "IMovable.h"

#include <Lab5/Movable/MacroCommand.h>
#include <Lab5/Movable/CommandRepeateByKey.h>
#include <Lab5/Movable/CommandInjectable.h>
#include <Lab5/Movable/IInjectable.h>
#include <any>

template <typename T>
class CommandStartMove: public ICommand
{

private:
	IUObject& _object;
	IGameQueue& _gameQueue;
	IMovable<T>& _moveAdapt;
	std::vector<T>& _velocity;

public:
	CommandStartMove(IUObject & object, IGameQueue & gameQueue, IMovable<T>&moveAdapt, std::vector<T>&velocity):
			_object(object), _moveAdapt(moveAdapt), _gameQueue(gameQueue), _velocity(velocity)
	{}

	void execute()
	{
		_moveAdapt.setVelocity(_velocity);

		_object.setProperty("moveCommand", static_cast<IInjectable*>(new CommandInjectable));

		std::any_cast<IInjectable*>(_object.getProperty("moveCommand"))->inject(
			new MacroCommand(
				std::vector<ICommand*>{
					new CommandMove<T>(_moveAdapt),
					new CommandRepeateByKey<IInjectable*>("moveCommand", _object, _gameQueue)
				}
			)
		);


		_gameQueue.push(std::any_cast<IInjectable*>(_object.getProperty("moveCommand")));
		
		
	}
};