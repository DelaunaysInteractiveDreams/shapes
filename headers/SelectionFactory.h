#ifndef SELECTION_FACTORY_H
#define SELECTION_FACTORY_H

#include "selection.h"
#include <memory>
#include "FileManager.h"

namespace idl {
	class SelectionFactory
	{
	public:
		static SelectionFactory& getInstance();
		shared_ptr<Selection> create(json& jSelection);

	private:
		SelectionFactory();
		shared_ptr<Selection> getSelection(vector<string>, json& );
		
		~SelectionFactory();
	};
}

#endif // !SELECTION_FACTORY_H
