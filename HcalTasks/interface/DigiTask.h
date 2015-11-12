#ifndef DigiTask_h
#define DigiTask_h

/*
 *	file:			DigiTask.h
 *	Author:			Viktor Khristenko
 *	Date:			16.10.2015
 */

#include "DQM/HcalCommon/interface/DQTask.h"
#include "DQM/HcalCommon/interface/Utilities.h"
#include "DQM/HcalCommon/interface/Container1D.h"
#include "DQM/HcalCommon/interface/Container2D.h"
#include "DQM/HcalCommon/interface/ContainerProf1D.h"
#include "DQM/HcalCommon/interface/ContainerProf2D.h"

using namespace hcaldqm;
class DigiTask : public DQTask
{
	public:
		DigiTask(edm::ParameterSet const&);
		virtual ~DigiTask()
		{}

		virtual void bookHistograms(DQMStore::IBooker&,
			edm::Run const&, edm::EventSetup const&);
/*
		enum DigiFlag_Event
		{
			fOcp_lt1728 = 0,
			fOcp_lt1718 = 1,
			fOcp_lt1680 = 2,
			fOcp_gt1728 = 3,

			nDigiFlag = 4
		};
*/
	protected:
		//	funcs
		virtual void _process(edm::Event const&, edm::EventSetup const&);
		virtual void _resetMonitors(int);

		//	Tags
		edm::InputTag	_tagHBHE;
		edm::InputTag	_tagHO;
		edm::InputTag	_tagHF;

		//	Flags
		//	There are 2 types of flags, based on how often we check 
//		bool			_flags_Event[nDigiFlag];

		//	Counters
		int				_numDigis[constants::SUBDET_NUM];
		int				_numDigisCut[constants::SUBDET_NUM];

		//	Cuts
		double _cutSumQ_HBHE, _cutSumQ_HO, _cutSumQ_HF;

		// Containers by quantities

		//	Signal, ADC, fC, SumQ
		Container1D		_cfCperTS_SubDet;
		Container1D		_cADCperTS_SubDet;
		Container1D		_cSumQ_SubDetPM_iphi;
		ContainerProf2D	_cSumQ_depth;
		ContainerProf1D	_cSumQvsLS_SubDetPM_iphi;

		//	Shape
		Container1D		_cShape_SubDetPM_iphi;
		Container1D		_cShapeCut_SubDetPM_iphi;

		//	Timing
		Container1D		_cTimingCut_SubDetPM_iphi;
		ContainerProf1D	_cTimingCutvsieta_SubDet_iphi;
		ContainerProf1D _cTimingCutvsiphi_SubDet_ieta;
		ContainerProf1D _cTimingCutvsLS_SubDetPM_iphi;
		ContainerProf2D	_cTimingCut_depth;

		//	Specific
		ContainerProf1D _cQ2Q12CutvsLS_HFPM_iphi;

		//	Occupancy
		Container1D		_cOccupancyvsiphi_SubDet;
		Container1D		_cOccupancyCutvsiphi_SubDet;
		ContainerProf1D _cOccupancyvsLS_SubDet;
		ContainerProf1D	_cOccupancyCutvsLS_SubDet;
		Container2D		_cOccupancy_depth;
		Container2D		_cOccupancyCut_depth;
		ContainerProf2D	_cOccupancyCutiphivsLS_SubDet;
};

#endif







