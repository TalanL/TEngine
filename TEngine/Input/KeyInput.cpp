#include "Windows.h"
#include "KeyInput.h"
#include "IKeyMapper.h"

namespace Input {
	KeyInput KeyInput::instace;

	bool KeyInput::initialize(IKeyMapper* keyMapper, int maxActionValue)
	{
		this->keyMapper = keyMapper;
		this->maxActionValue = maxActionValue;
		return true;
	}

	bool KeyInput::shutdown()
	{
		return true;
	}

	void KeyInput::update()
	{
		_actionsThisFrame = 0;
		int possibleAction = 1;
		while(possibleAction != maxActionValue) {
			int key = keyMapper->getKeyfor(possibleAction);
			if(GetAsyncKeyState(key)){
				_actionsThisFrame |= possibleAction;
			}
			possibleAction <<= 1;
		}
	}


	bool KeyInput::actionHot(int actions) const
	{
		return (_actionsThisFrame & actions) != 0;
	}

	KeyInput& KeyInput::getInstance()
	{
		return instace;
	}
}