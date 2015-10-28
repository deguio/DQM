#ifndef LEDTask_h
#define LEDTask_h

/*
 *	file:			LEDTask.h
 *	Author:			Viktor Khristenko
 *	Date:			16.10.2015
 */

#include "DQM/HcalCommon/interface/DQTask.h"
#include "DQM/HcalCommon/interface/Utilities.h"
#include "DQM/HcalCommon/interface/ContainerCompact.h"
#include "DQM/HcalCommon/interface/Container1D.h"
#include "DQM/HcalCommon/interface/Container2D.h"
#include "DQM/HcalCommon/interface/ContainerProf1D.h"
#include "DQM/HcalCommon/interface/ContainerProf2D.h"

using namespace hcaldqm;
class LEDTask : public DQTask
{
	public:
		LEDTask(edm::ParameterSet const&);
		virtual ~LEDTask()
		{}

		virtual void bookHistograms(DQMStore::IBooker&,
			edm::Run const&, edm::EventSetup const&);
		virtual void endRun(edm::Run const&, edm::EventSetup const&)
		{this->_dump();}

	protected:
		//	funcs
		virtual void _process(edm::Event const&, edm::EventSetup const&);
		virtual void _resetMonitors(int);
		virtual bool _isApplicable(edm::Event const&);
		virtual void _dump();

		//	vars
		edm::InputTag	_tagHBHE;
		edm::InputTag	_tagHO;
		edm::InputTag	_tagHF;
		edm::InputTag	_tagTrigger;

		//	Compact
		ContainerCompact _cSignals;
		ContainerCompact _cTiming;

		//	1D
		Container1D		_cSignalMeans1D_SubDet;
		Container1D		_cSignalRMSs1D_SubDet;
		Container1D		_cTimingMeans1D_SubDet;
		Container1D		_cTimingRMSs1D_SubDet;

		//	Prof1D
		ContainerProf1D	_cShape_SubDet_iphi;

		//	2D
		Container2D		_cSignalMeans2D_depth;
		Container1D		_cSignalRMSs2D_depth;
		Container2D		_cTimingMeans2D_depth;
		Container1D		_cTimingRMSs2D_depth;
};

#endif







