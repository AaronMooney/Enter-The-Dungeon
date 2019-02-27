#ifndef Torch_hpp
#define Torch_hpp

#include "GameObject.hpp"

class Torch : public GameObject
{
public:

	Torch();
	void Update(float timeDelta);
	float GetBrightness();


private:

	float m_brightness;
};
#endif