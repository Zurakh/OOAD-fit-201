#pragma once

#include <iostream>
#include <vector>
#include <Lab5/ICommand.h>
#include "CommandMove.h"
#include <Lab5/IUObject.h>
#include <Lab5/IGameQueue.h>
#include "IMovable.h"
#include <string>
#include "IInjectable.h"
#include "CommandInjectable.h"
#include <any>
#include <concepts>


template <typename T>
class CommandRepeateByKey: public ICommand
{
private:
    std::string _key;
    IUObject& _object;
    IGameQueue& _gameQueue;
public:
    CommandRepeateByKey(const std::string key, IUObject& object, IGameQueue& gameQueue):
    _key(key), _object(object), _gameQueue(gameQueue){}
    void execute()
	{
        _gameQueue.push(std::any_cast<T>(_object.getProperty(_key)));
    }
};