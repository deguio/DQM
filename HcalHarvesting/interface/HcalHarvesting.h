#ifndef HcalHarvesting_h
#define HcalHarvesting_h

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

class HcalHarvesting : public DQHarvester
{
	public:
		HcalHarvesting(edm::ParameterSet const&);
		virtual ~HcalHarvesting(){}

	protected:
		virtual void _dqmEndLuminosityBlock(DQMStore::IBooker&,
			DQMStore::IGetter&, edm::LuminosityBlock const&,
			edm::EventSetup const&);
		virtual void _dqmEndJob(DQMStore::IBooker&,
			DQMStore::IGetter&);

		//	electronicsmap hash
		electronicsmap::ElectronicsMap _emaphash;
};

#endif