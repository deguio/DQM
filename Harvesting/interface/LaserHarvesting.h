#ifndef LaserHarvesting_h
#define LaserHarvesting_h

/**
 *	file:		
 *	Author:	
 *	Date:
 */

#include "DQM/HcalCommon/interface/HcalCommonHeaders.h"
#include "DQM/HcalCommon/interface/DQHarvester.h"
#include "DQM/HcalCommon/interface/Container1D.h"
#include "DQM/HcalCommon/interface/Container2D.h"
#include "DQM/HcalCommon/interface/ContainerProf1D.h"
#include "DQM/HcalCommon/interface/ContainerProf2D.h"
#include "DQM/HcalCommon/interface/ContainerSingle1D.h"
#include "DQM/HcalCommon/interface/ContainerSingle2D.h"
#include "DQM/HcalCommon/interface/ContainerSingleProf1D.h"
#include "DQM/HcalCommon/interface/ContainerSingleProf2D.h"
#include "DQM/HcalCommon/interface/ElectronicsMap.h"

using namespace hcaldqm;

class LaserHarvesting : public DQHarvester
{
	public:
		LaserHarvesting(edm::ParameterSet const&);
		virtual ~LaserHarvesting(){}

		virtual void endRun(edm::Run const&, edm::EventSetup const&);

	protected:
		void book(DQMStore*);

		//	electronicsmap
		HcalElectronicsMap const* _emap;
		electronicsmap::ElectronicsMap _emaphash;

		//	ROOT files to be processed
		//	0 is the one with respect to which all ratios are computed
		std::vector<std::string>	_vfiles;
		std::vector<int>			_vruns;

		//	new containers
		Container2D _cTimingMean_SubdetPM;
		Container2D _cSignalRatio_SubdetPM;
		std::vector<Container1D> _vcSignalRatio_SubdetPM;
		std::vector<ContainerProf2D> _vcSignalRatio_depth;

		//	containers to be loaded
		std::vector<ContainerProf2D> _vcTimingMean_depth;
		std::vector<ContainerProf2D> _vcSignalMean_depth;
};

#endif