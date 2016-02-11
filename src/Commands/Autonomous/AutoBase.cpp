#include <Commands/Autonomous/AutoBase.h>
#include "Commands/CommandGroup.h"

AutoBase::AutoBase() :
		CommandGroup("AutoBase-Blank") {
}
AutoBase::AutoBase(char *style) :
		CommandGroup(style) {
}

AutoBase::~AutoBase() {
}
