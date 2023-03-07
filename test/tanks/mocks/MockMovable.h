#include <gmock/gmock.h>
#include <Lab5/Movable/IMovable.h>
#include <vector>

template <typename T>
class MockMovable: public IMovable<T>
{
private:
	std::vector<T> _position;
	std::vector<T> _velocity;
public:

	MOCK_METHOD(std::vector<T>, getPosition, (), (override));
	MOCK_METHOD(void, setPosition, (std::vector<T> value), (override));
	MOCK_METHOD(std::vector<T>, getVelocity, (), (override));
	MOCK_METHOD(void, setVelocity, (std::vector<T> value), (override));

	MockMovable()
	{
		ON_CALL(*this, getPosition).WillByDefault([this]()
		{
			return this->_position;
		});

		ON_CALL(*this, setPosition).WillByDefault([this](std::vector<T> value)
		{
			this->_position = value;
		});

		ON_CALL(*this, getVelocity).WillByDefault([this]()
		{
			return this->_velocity;
		});

		ON_CALL(*this, setVelocity).WillByDefault([this](std::vector<T> value)
		{
			this->_velocity = value;
		});
	}
};