#include <Lab5/IGameQueue.h>
#include <Lab5/ICommand.h>
#include <queue>

class GameQueueRealization: public IGameQueue
{
private:
	std::queue<ICommand*> _queue;

public:
	GameQueueRealization() = default;

	void push(ICommand* com) override
	{
		_queue.push(com);
	}

	void pop() override
	{
		_queue.pop();
	}

	ICommand* front() override
	{
		return _queue.front();
	}

	int size()
	{
		return _queue.size();
	}

	~GameQueueRealization() = default;
};
