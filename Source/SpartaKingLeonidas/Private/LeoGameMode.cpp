#include "LeoGameMode.h"
#include "LeoPawn.h"

ALeoGameMode::ALeoGameMode()
{
	DefaultPawnClass = ALeoPawn::StaticClass();
}