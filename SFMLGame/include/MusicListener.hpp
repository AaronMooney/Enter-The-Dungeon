#ifndef MusicListener_hpp
#define MusicListener_hpp

#include "GameObject.hpp"

class MusicListener : public GameObject
{
public:

	MusicListener();

	void Update(float timeDelta);

private:
};
#endif