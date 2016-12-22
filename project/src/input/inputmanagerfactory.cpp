/*
 * inputmanagerfactory.cpp
 *
 *  Created on: 31 de may. de 2016
 *      Author: jorge
 */

#include "input/sdlkeyinputmanager.h"
#include "input/inputmanagerfactory.h"

namespace dc
{

	CKeyInputManager* CInputManagerFactory::CreateKeyInputManager(EInputType type)
	{
		switch (type)
		{
			case EInputType::SDL:
			{
				return new CSDLKeyInputManager();
			}
		}

		return 0;
	}

} /* namespace dc */