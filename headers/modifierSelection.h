#ifndef MODIFIER_SELECTION_H
#define MODIFIER_SELECTION_H

#include "selection.h"
#include "modifier.h"

namespace idl {

class ModifierSelection : public Modifier {
protected :
	std::shared_ptr<Selection> selection;

public:
	ModifierSelection(std::shared_ptr<Selection>);
	virtual void apply() = 0;
};
	
}

#endif