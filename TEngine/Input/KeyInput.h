#ifndef ENGIEN_KEY_INPUT_H
#define ENGIEN_KEY_INPUT_H
#include "ExportHeader.h"
namespace Input {
	class IKeyMapper;
	class ENGINE_SHARED KeyInput
	{
		IKeyMapper* keyMapper;
		int maxActionValue;
		int _actionsThisFrame;
		KeyInput(){};
		KeyInput(const KeyInput&);
		KeyInput& operator=(const KeyInput&);
		static KeyInput instace;
	public:
		bool initialize(IKeyMapper* keyMapper, int maxActionValue);
		bool shutdown();
		void update();
		int actionsThisFrame() const {return _actionsThisFrame;};
		bool actionHot(int actions) const;
		static KeyInput& getInstance();

	};
	#define input Input::KeyInput::getInstance()
}

#endif // !KEY_INPUT_H
