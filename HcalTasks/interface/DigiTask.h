#ifndef DigiTask_h
#define DigiTask_h

/**
 *	file:			DigiTask.h
 *	Author:			VK
 *	Description:
 *		HCAL DIGI Data Tier Processing.
 *
 *	Online:
 *		
 *	Offline:
 *		- HF Q2/(Q1+Q2) is not included.
 */

#include "DQM/HcalCommon/interface/DQTask.h"
#include "DQM/HcalCommon/interface/Utilities.h"
#include "DQM/HcalCommon/interface/HashFilter.h"
#include "DQM/HcalCommon/interface/ElectronicsMap.h"
#include "DQM/HcalCommon/interface/Container1D.h"
#include "DQM/HcalCommon/interface/Container2D.h"
#include "DQM/HcalCommon/interface/ContainerProf1D.h"
#include "DQM/HcalCommon/interface/ContainerProf2D.h"
#include "DQM/HcalCommon/interface/ContainerSingle1D.h"
#include "DQM/HcalCommon/interface/ContainerSingle2D.h"
#include "DQM/HcalCommon/interface/ContainerSingleProf2D.h"
#include "DQM/HcalCommon/interface/ContainerXXX.h"

using namespace hcaldqm;
using namespace hcaldqm::filter;
class DigiTask : public DQTask
{
	public:
		DigiTask(edm::ParameterSet const&);
		virtual ~DigiTask() {}

		virtual void bookHistograms(DQMStore::IBooker&,
			edm::Run const&, edm::EventSetup const&);
		virtual void beginLuminosityBlock(edm::LuminosityBlock const&,
			edm::EventSetup const&);
		virtual void endLuminosityBlock(edm::LuminosityBlock const&,
			edm::EventSetup const&);

		enum DigiFlag
		{
			//	UniSlot - for HF FEDs use OccupancyCut, for others use 
			//	just Occupancy
			fUniSlot = 0,
			//	missing for 1LS
			fMsn1LS = 1,
			//	caps non rotating
			fCapIdRot = 2,
			//	digi size issues - typically is a consequence
			fDigiSize = 3,
			nDigiFlag = 4
		};

	protected:
		virtual void _process(edm::Event const&, edm::EventSetup const&);
		virtual void _resetMonitors(UpdateFreq);

		edm::InputTag		_tagHBHE;
		edm::InputTag		_tagHO;
		edm::InputTag		_tagHF;
		edm::EDGetTokenT<HBHEDigiCollection> _tokHBHE;
		edm::EDGetTokenT<HODigiCollection>	 _tokHO;
		edm::EDGetTokenT<HFDigiCollection>	_tokHF;

		double _cutSumQ_HBHE, _cutSumQ_HO, _cutSumQ_HF;

		//	hashes/FED vectors
		std::vector<uint32_t> _vhashFEDs;

		//	emap
		HcalElectronicsMap const* _emap;
		electronicsmap::ElectronicsMap _ehashmapuTCA;
		electronicsmap::ElectronicsMap _ehashmapVME;

		//	Filters
		HashFilter _filter_VME;
		HashFilter _filter_uTCA;
		HashFilter _filter_FEDHF;

		/* Containers */
		//	ADC, fC - Charge - just filling - no summary!
		Container1D _cADC_SubdetPM;
		Container1D _cfC_SubdetPM;
		Container1D _cSumQ_SubdetPM;
		ContainerProf2D	_cSumQ_depth;
		ContainerProf1D _cSumQvsLS_SubdetPM;
		ContainerProf1D _cSumQvsBX_SubdetPM;	// online only!

		//	Shape - just filling - not summary!
		Container1D _cShapeCut_FED;

		//	Timing
		//	just filling - no summary!
		Container1D		_cTimingCut_SubdetPM;
		ContainerProf2D _cTimingCut_FEDVME;
		ContainerProf2D	_cTimingCut_FEDuTCA;
		ContainerProf2D _cTimingCut_ElectronicsVME;
		ContainerProf2D _cTimingCut_ElectronicsuTCA;
		ContainerProf1D _cTimingCutvsLS_FED;
		ContainerProf2D _cTimingCut_depth;
		ContainerProf1D _cTimingCutvsiphi_SubdetPM;	// online only!
		ContainerProf1D _cTimingCutvsieta_Subdet;	// online only!

		//	Only for Online mode! just filling - no summary!
		ContainerProf1D _cQ2Q12CutvsLS_FEDHF;	//	online only!

		//	Occupancy w/o a Cut - whatever is sitting in the Digi Collection
		//	used to determine Missing Digis => used for Summary!
		Container2D _cOccupancy_FEDVME;
		Container2D _cOccupancy_FEDuTCA;
		Container2D _cOccupancy_ElectronicsVME;
		Container2D _cOccupancy_ElectronicsuTCA;
		Container2D _cOccupancy_depth;
		Container2D _cOccupancyNR_FEDVME;
		Container2D _cOccupancyNR_FEDuTCA;
		Container1D _cOccupancyvsiphi_SubdetPM; // online only
		Container1D _cOccupnacyvsieta_Subdet;	// online only

		//	Occupancy w/ a Cut
		//	used to determine if occupancy is symmetric or not. =>
		//	used for Summary
		Container2D _cOccupancyCut_FEDVME;
		Container2D _cOccupancyCut_FEDuTCA;
		Container2D _cOccupancyCut_ElectronicsVME;
		Container2D _cOccupancyCut_ElectronicsuTCA;
		Container2D _cOccupancyCut_depth;
		Container2D _cOccupancyCutNR_FEDVME;
		Container2D _cOccupancyCutNR_FEDuTCA;
		Container1D _cOccupancyCutvsiphi_SubdetPM; // online only
		Container1D _cOccupnacyCutvsieta_Subdet;	// online only

		//	Occupancy w/o and w/ a Cut vs BX and vs LS
		ContainerProf1D _cOccupancyvsLS_Subdet;
		ContainerProf1D _cOccupancyCutvsLS_Subdet;	// online only
		ContainerProf1D _cOccupancyCutvsBX_Subdet;	// online only

		//	#Time Samples for a digi. Used for Summary generation
		Container1D _cDigiSize_FEDVME;
		Container1D _cDigiSize_FEDuTCA;
		ContainerProf1D _cDigiSizevsLS_Subdet;	// online only

		//	Summary Histogram
		ContainerSingle2D _cSummary;
};

#endif
