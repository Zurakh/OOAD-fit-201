#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <misc/vectorOps.h>

#include <Lab5/UObject.h>

#include <Lab5/Movable/CommandMove.h>
#include <Lab5/Movable/CommandStartMove.h>
#include <Lab5/Movable/CommandEndMove.h>

#include "mocks/MockMovable.h"
#include "stubs/GameQueueRealization.h"

#include <Lab5/Movable/MacroCommand.h>
#include <Lab5/Movable/CommandRepeateByKey.h>
#include <Lab5/Movable/CommandInjectable.h>
#include <Lab5/Movable/IInjectable.h>


TEST(Tanks_MovableComponent, BaseMoveCommand)
{
	std::vector<int> position{ 10, 20, 30 };
	const std::vector<int> velocity{ 45, 25, 55 };

	::testing::NiceMock < MockMovable<int>> mcmv;

	mcmv.setPosition(position);
	mcmv.setVelocity(velocity);

	CommandMove<int> CommandMove(mcmv);
	CommandMove.execute();

	EXPECT_EQ(mcmv.getPosition(), position + velocity);
}

TEST (MacroCommand, ItWorks)
{
	GameQueueRealization gameQueue;

	std::vector<int> position{ 10, 20, 30 };
	const std::vector<int> velocity{ 45, 25, 55 };

	::testing::NiceMock < MockMovable<int>> mcmv;


	mcmv.setPosition(position);
	mcmv.setVelocity(velocity);

	CommandMove<int> CommandMove1(mcmv);
	CommandMove<int> CommandMove2(mcmv);
	CommandMove<int> CommandMove3(mcmv);
	CommandMove<int> CommandMove4(mcmv);

	MacroCommand *macro = new MacroCommand(std::vector<ICommand*>{&CommandMove1, &CommandMove2, &CommandMove3, &CommandMove4});
	gameQueue.push(static_cast<ICommand*>(macro));

	gameQueue.front()->execute();
	gameQueue.pop();


	EXPECT_EQ(mcmv.getPosition(), position + velocity + velocity + velocity + velocity );

}

TEST (RepeateByKeyCommand, itCanRepeate)
{
	GameQueueRealization gameQueue;
	UObject obj;

	std::vector<int> position{ 10, 20, 30 };
	const std::vector<int> velocity{ 45, 25, 55 };

	::testing::NiceMock < MockMovable<int>> mcmv;

	mcmv.setPosition(position);
	mcmv.setVelocity(velocity);


	CommandMove<int> commandMove(mcmv);
	CommandRepeateByKey<ICommand*> repeateCommand("moveCommand", obj, gameQueue);
	MacroCommand macro(std::vector<ICommand*>{&commandMove, &repeateCommand});
	obj.setProperty("moveCommand", static_cast<ICommand*>(&macro));
	
	gameQueue.push(static_cast<ICommand*>(&macro));
	gameQueue.front()->execute();
	gameQueue.pop();

	EXPECT_EQ(mcmv.getPosition(), position + velocity);

	gameQueue.front()->execute();
	gameQueue.pop();

	EXPECT_EQ(mcmv.getPosition(), position + velocity * 2);
}

TEST (Injectable, ItCanInject)
{
	GameQueueRealization gameQueue;
	UObject obj;

	std::vector<int> position{ 10, 20, 30 };
	const std::vector<int> velocity{ 45, 25, 55 };

	::testing::NiceMock < MockMovable<int>> mcmv;

	mcmv.setPosition(position);
	mcmv.setVelocity(velocity);


	CommandMove<int> commandMove(mcmv);
	CommandRepeateByKey<ICommand*> repeateCommand("moveCommand", obj, gameQueue);
	MacroCommand macro(std::vector<ICommand*>{&commandMove, &repeateCommand});
	CommandInjectable injCommand;
	injCommand.execute();
	injCommand.inject(static_cast<ICommand*>(&macro));
	obj.setProperty("moveCommand", static_cast<ICommand*>(&injCommand));
	
	gameQueue.push(static_cast<ICommand*>(&injCommand));

	gameQueue.front()->execute();
	gameQueue.pop();

	EXPECT_EQ(gameQueue.size(), 1);
	EXPECT_EQ(mcmv.getPosition(), position + velocity);

}



TEST (Injectable, ItCanStop)
{
	GameQueueRealization gameQueue;
	UObject obj;

	std::vector<int> position{ 10, 20, 30 };
	const std::vector<int> velocity{ 45, 25, 55 };

	::testing::NiceMock < MockMovable<int>> mcmv;

	mcmv.setPosition(position);
	mcmv.setVelocity(velocity);


	CommandMove<int> commandMove(mcmv);
	CommandRepeateByKey<ICommand*> repeateCommand("moveCommand", obj, gameQueue);
	MacroCommand macro(std::vector<ICommand*>{&commandMove, &repeateCommand});
	CommandInjectable injCommand;

	injCommand.inject(static_cast<ICommand*>(&macro));
	obj.setProperty("moveCommand", static_cast<ICommand*>(&injCommand));
	
	gameQueue.push(static_cast<ICommand*>(&injCommand));
	gameQueue.front()->execute();
	gameQueue.pop();
	
	EXPECT_EQ(mcmv.getPosition(), position + velocity);

	gameQueue.front()->execute();
	gameQueue.pop();

	EXPECT_EQ(mcmv.getPosition(), position + velocity * 2);
	injCommand.inject(new EmptyCommand());

	gameQueue.front()->execute();
	gameQueue.pop();

	EXPECT_EQ(mcmv.getPosition(), position + velocity * 2);
	EXPECT_EQ(gameQueue.size(), 0);
}





TEST(Casting, castInjectableToCommand_1)
{
	GameQueueRealization gameQueue;
	UObject obj;

	std::vector<int> position { 10, 20, 30 };
	const std::vector<int> velocity { 45, 25, 55 };

	::testing::NiceMock < MockMovable<int>> mcmv;

	mcmv.setPosition(position);
	mcmv.setVelocity(velocity);


	CommandMove<int> commandMove(mcmv);
	CommandRepeateByKey<ICommand*>repeateCommand("moveCommand", obj, gameQueue);
	MacroCommand macro(std::vector<ICommand*>{&commandMove, & repeateCommand});
	CommandInjectable injCommand;

	injCommand.inject(static_cast<ICommand*>(&macro));
	obj.setProperty("moveCommand", static_cast<ICommand*>(&injCommand));

	gameQueue.push(std::any_cast<ICommand*>(obj.getProperty("moveCommand")));

	gameQueue.front()->execute();
	gameQueue.pop();

	EXPECT_EQ(mcmv.getPosition(), position + velocity);

	gameQueue.front()->execute();
	gameQueue.pop();

	gameQueue.front()->execute();
	gameQueue.pop();

	gameQueue.front()->execute();
	gameQueue.pop();

	EXPECT_EQ(mcmv.getPosition(), position + velocity * 4);
	injCommand.inject(new EmptyCommand());

	gameQueue.front()->execute();
	gameQueue.pop();

	EXPECT_EQ(mcmv.getPosition(), position + velocity * 4);
	EXPECT_EQ(gameQueue.size(), 0);
}


TEST(Casting, castInjectableToCommand_2)
{
	GameQueueRealization gameQueue;
	UObject obj;

	std::vector<int> position { 10, 20, 30 };
	const std::vector<int> velocity { 45, 25, 55 };

	::testing::NiceMock < MockMovable<int>> mcmv;

	mcmv.setPosition(position);
	mcmv.setVelocity(velocity);


	CommandMove<int> *commandMove = new CommandMove<int>(mcmv);
	CommandRepeateByKey<ICommand*>* repeateCommand = new CommandRepeateByKey<ICommand*>("moveCommand", obj, gameQueue);
	MacroCommand* macro = new MacroCommand(std::vector<ICommand*>{commandMove, repeateCommand});
	CommandInjectable* injCommand = new CommandInjectable;

	injCommand->inject(dynamic_cast<ICommand*>(macro));
	obj.setProperty("moveCommand", dynamic_cast<ICommand*>(injCommand));

	gameQueue.push(std::any_cast<ICommand*>(obj.getProperty("moveCommand")));

	gameQueue.front()->execute();
	gameQueue.pop();

	EXPECT_EQ(mcmv.getPosition(), position + velocity);

	gameQueue.front()->execute();
	gameQueue.pop();

	gameQueue.front()->execute();
	gameQueue.pop();

	gameQueue.front()->execute();
	gameQueue.pop();

	EXPECT_EQ(mcmv.getPosition(), position + velocity * 4);
	injCommand->inject(new EmptyCommand());

	gameQueue.front()->execute();
	gameQueue.pop();

	EXPECT_EQ(mcmv.getPosition(), position + velocity * 4);
	EXPECT_EQ(gameQueue.size(), 0);
}





TEST(Tanks_MovableComponent, UseFullMoveCommandSequence_1)
{
	UObject obj;
	std::vector<int> position = { 10, 20, 30 };
	std::vector<int> velocity = { 45, 25, 55 };

	GameQueueRealization gameQueue;

	::testing::NiceMock < MockMovable<int>> mcmv;

	mcmv.setPosition(position);

	CommandStartMove<int> commandStart(obj, gameQueue, mcmv, velocity);
	CommandEndMove<int> commandEnd(obj, mcmv);
	
	gameQueue.push(static_cast<ICommand*>(&commandStart));
	
	
	gameQueue.front()->execute(); //startCommand
	gameQueue.pop();

	EXPECT_EQ(mcmv.getPosition(), position);

	gameQueue.push(static_cast<ICommand*>(&commandEnd));


	gameQueue.front()->execute(); //MoveCommand
	gameQueue.pop();

	EXPECT_EQ(mcmv.getPosition(), position + velocity);

	gameQueue.front()->execute(); //EndMove
	gameQueue.pop();

	EXPECT_EQ(mcmv.getPosition(), position + velocity);

	gameQueue.front()->execute(); // Empty
	gameQueue.pop();

	EXPECT_EQ(mcmv.getPosition(), position + velocity);

	EXPECT_EQ(gameQueue.size(), 0);

} 