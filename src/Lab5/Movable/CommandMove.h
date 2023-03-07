#pragma once

#include <vector>
#include <Lab5/ICommand.h>
#include "IMovable.h"

template <typename T>
class CommandMove: public ICommand
{
private:
	IMovable<T>& _moveAdapt;

public:
	CommandMove(IMovable<T>& moveAdapt): _moveAdapt(moveAdapt){}

	void execute()
	{
        std::vector<T>&& position = _moveAdapt.getPosition();
        const std::vector<T>&& velocity = _moveAdapt.getVelocity();

        const int dim = std::min(position.size(), velocity.size());

        for (int i = 0; i < dim; i++)
        {
            position[i] += velocity[i];
        }

        _moveAdapt.setPosition(position);
	}
};