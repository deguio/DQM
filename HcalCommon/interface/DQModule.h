#ifndef DQModule_h
#define DQModule_h

/*
 *	file:			DQModule.h
 *	Author:			Viktor Khristenko
 *	date:			13.10.2015
 */

#include "DQM/HcalCommon/interface/HcalCommonHeaders.h"
#include "DQM/HcalCommon/interface/Logger.h"

#include <string>
#include <vector>
#include <iostream>

namespace hcaldqm
{
	enum ModuleType
	{
		fTask = 0,
		fClient = 1,
		nModuleType = 2
	};

	enum ProcessingType
	{
		fOnline = 0,
		fOffline = 1,
		fLocal = 2,
		nProcessingType = 3
	};

	std::string const pTypeNames[nProcessingType] = {
		"Online", "Offline", "Local"
	};

	class DQModule
	{
		public:
			DQModule(edm::ParameterSet const&);
			virtual ~DQModule() {}

		protected:
			//	Member variables	
			std::string				_name;
			ModuleType				_mtype;
			ProcessingType			_ptype;
			int						_debug;

			int						_runkeyVal;
			std::string				_runkeyName;
			std::string				_subsystem;

			int						_evsTotal;
			int						_evsPerLS;
			int						_currentLS;
			Logger					_logger;
	};
}

#endif










