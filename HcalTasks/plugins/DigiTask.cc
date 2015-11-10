
#include "DQM/HcalTasks/interface/DigiTask.h"

using namespace hcaldqm;
DigiTask::DigiTask(edm::ParameterSet const& ps):
	DQTask(ps),

	//	Signal, ADC, fC, SumQ
	_cfCperTS_SubDetPM(_name+"/Signal/fC_SubDetPM", "fCperTS",
		mapper::fSubDetPM,
		new axis::ValueAxis(axis::fXaxis, axis::fNomFC),
		new axis::ValueAxis(axis::fYaxis, axis::fEntries, true)),
	_cADCperTS_SubDetPM(_name+"/Signal/ADC_SubDetPM", "ADCperTS",
		mapper::fSubDetPM,
		new axis::ValueAxis(axis::fXaxis, axis::fADC),
		new axis::ValueAxis(axis::fYaxis, axis::fEntries, true)),
	_cSumQ_SubDet_iphi(_name+"/Signal/SubDet_iphi", "SumQ",
		mapper::fSubDet_iphi,
		new axis::ValueAxis(axis::fXaxis, axis::fNomFC),
		new axis::ValueAxis(axis::fYaxis, axis::fEntries, true)),
	_cSumQ_depth(_name+"/Signal/depth", "SumQ",
		mapper::fdepth,
		new axis::CoordinateAxis(axis::fXaxis, axis::fieta),
		new axis::CoordinateAxis(axis::fYaxis, axis::fiphi),
		new axis::ValueAxis(axis::fZaxis, axis::fNomFC)),
	_cSumQvsLS_SubDet_iphi(_name+"/Signal/SumQvsLS_SubDet_iphi", "SumQvsLS",
		mapper::fSubDet_iphi,
		new axis::ValueAxis(axis::fXaxis, axis::fLS),
		new axis::ValueAxis(axis::fYaxis, axis::fNomFC)),

	//	Shape
	_cShape_SubDetPM_iphi(_name+"/Shape/SubDetPM_iphi", "Shape",
		mapper::fSubDetPM_iphi,
		new axis::ValueAxis(axis::fXaxis, axis::fTimeTS),
		new axis::ValueAxis(axis::fYaxis, axis::fNomFC)),
	_cShapeCut_SubDetPM_iphi(_name+"/Shape/SubDetPM_iphi", "Shape",
		mapper::fSubDetPM_iphi,
		new axis::ValueAxis(axis::fXaxis, axis::fTimeTS),
		new axis::ValueAxis(axis::fYaxis, axis::fNomFC)),

	//	Timing
	_cTimingCut_SubDet_iphi(_name+"/Timing/SubDet_iphi", 
		"Timing", mapper::fSubDet_iphi,
		new axis::ValueAxis(axis::fXaxis, axis::fTimeTS_200)),
	_cTimingCutvsieta_SubDet_iphi(_name+"/Timing/vsieta_SubDet_iphi",
		"Timingvsieta", mapper::fSubDet_iphi,
		new axis::CoordinateAxis(axis::fXaxis, axis::fieta),
		new axis::ValueAxis(axis::fYaxis, axis::fTimeTS)),
	_cTimingCutvsiphi_SubDet_ieta(_name+"/Timing/vsiphi_SubDet_ieta",
		"Timingvsiphi", mapper::fSubDet_ieta,
		new axis::CoordinateAxis(axis::fXaxis, axis::fiphi),
		new axis::ValueAxis(axis::fYaxis, axis::fTimeTS)),
	_cTimingCut_depth(_name+"/Timing/depth", "Timing",
		mapper::fdepth,
		new axis::CoordinateAxis(axis::fXaxis, axis::fieta),
		new axis::CoordinateAxis(axis::fYaxis, axis::fiphi),
		new axis::ValueAxis(axis::fZaxis, axis::fTimeTS)),

	//	Occupancy
	_cOccupancyvsiphi_SubDet(_name+"/Occupancy/vsiphi_SubDet", "Occupancyvsiphi",
		mapper::fSubDet,
		new axis::CoordinateAxis(fXaxis, axis::fiphi)),
	_cOccupancyCutvsiphi_SubDet(_name+"/Occupancy/vsiphi_SubDet", 
		"Occupancyvsiphi",
		mapper::fSubDet,
		new axis::CoordinateAxis(fXaxis, axis::fiphi)),
	_cOccupancy_depth(_name+"/Occupancy/depth", "Occupancy",
		mapper::fdepth, 
		new axis::CoordinateAxis(axis::fXaxis, axis::fieta), 
		new axis::CoordinateAxis(axis::fYaxis, axis::fiphi)),
	_cOccupancyCut_depth(_name+"/Occupancy/depth", "Occupancy",
		mapper::fdepth, 
		new axis::CoordinateAxis(axis::fXaxis, axis::fieta), 
		new axis::CoordinateAxis(axis::fYaxis, axis::fiphi)),
	_cOccupancyCutiphivsLS_SubDet(_name+"/Occupancy/iphivsLS_SubDet", 
		"OccupancyiphivsLS",
		mapper::fSubDet,
		new axis::ValueAxis(axis::fXaxis, axis::fLS),
		new axis::CoordinateAxis(axis::fYaxis, axis::fiphi),
		new axis::ValueAxis(axis::fZaxis, axis::fEntries))
{
	//	tags
	_tagHBHE = ps.getUntrackedParameter<edm::InputTag>("tagHBHE",
		edm::InputTag("hcalDigis"));
	_tagHO = ps.getUntrackedParameter<edm::InputTag>("tagHO",
		edm::InputTag("hcalDigis"));
	_tagHF = ps.getUntrackedParameter<edm::InputTag>("tagHF",
		edm::InputTag("hcalDigis"));

	// cuts
	_cutSumQ_HBHE = ps.getUntrackedParameter<double>("cutSumQ_HBHE", 20);
	_cutSumQ_HO = ps.getUntrackedParameter<double>("cutSumQ_HO", 20);
	_cutSumQ_HF = ps.getUntrackedParameter<double>("cutSumQ_HF", 20);
	
}

/* virtual */ void DigiTask::bookHistograms(DQMStore::IBooker &ib,
	edm::Run const& r, edm::EventSetup const& es)
{
	char cutstr[200];
	sprintf(cutstr, "_SumQHBHE%dHO%dHF%d", int(_cutSumQ_HBHE),
		int(_cutSumQ_HO), int(_cutSumQ_HF));

	DQTask::bookHistograms(ib, r, es);
	_cADCperTS_SubDetPM.book(ib);
	_cfCperTS_SubDetPM.book(ib);
	_cSumQ_SubDet_iphi.book(ib);
	_cSumQ_depth.book(ib);
	_cSumQvsLS_SubDet_iphi.book(ib);

	_cShape_SubDetPM_iphi.book(ib);
	_cShapeCut_SubDetPM_iphi.book(ib, _subsystem, std::string(cutstr));

	_cTimingCut_SubDet_iphi.book(ib, _subsystem, std::string(cutstr));
	_cTimingCutvsieta_SubDet_iphi.book(ib, _subsystem, 
		std::string(cutstr));
	_cTimingCutvsiphi_SubDet_ieta.book(ib, _subsystem, std::string(cutstr));
	_cTimingCut_depth.book(ib, _subsystem, std::string(cutstr));

	_cOccupancyvsiphi_SubDet.book(ib);
	_cOccupancyCutvsiphi_SubDet.book(ib, _subsystem, std::string(cutstr));
	_cOccupancy_depth.book(ib);
	_cOccupancyCut_depth.book(ib, _subsystem, std::string(cutstr));
	_cOccupancyCutiphivsLS_SubDet.book(ib, _subsystem, std::string(cutstr));
}

/* virtual */ void DigiTask::_resetMonitors(int pflag)
{
	DQTask::_resetMonitors(pflag);
	if (pflag==0)
	{
		for (unsigned int i=0; i<constants::SUBDET_NUM; i++)
			_numDigis[i]=0;
	}
}

/* virtual */ void DigiTask::_process(edm::Event const& e,
	edm::EventSetup const& es)
{
	edm::Handle<HBHEDigiCollection>		chbhe;
	edm::Handle<HODigiCollection>		cho;
	edm::Handle<HFDigiCollection>		chf;

	if (!e.getByLabel(_tagHBHE, chbhe))
		this->_throw("Collection HBHEDigiCollection isn't available",
			" " + _tagHBHE.label() + " " + _tagHBHE.instance());
	if (!e.getByLabel(_tagHO, cho))
		this->_throw("Collection HODigiCollection isn't available",
			" " + _tagHO.label() + " " + _tagHO.instance());
	if (!e.getByLabel(_tagHF, chf))
		this->_throw("Collection HFDigiCollection isn't available",
			" " + _tagHF.label() + " " + _tagHF.instance());

	for (HBHEDigiCollection::const_iterator it=chbhe->begin();
		it!=chbhe->end(); ++it)
	{
		const HBHEDataFrame digi = (const HBHEDataFrame)(*it);
		double sumQ = utilities::sumQ<HBHEDataFrame>(digi, 2.5, 0, 
			digi.size()-1);
		double timing = utilities::aveTS<HBHEDataFrame>(digi, 2.5, 0,
			digi.size()-1);
		const HcalDetId did = digi.id();

		//	fill without a cut
		_cOccupancy_depth.fill(did);
		_cOccupancyvsiphi_SubDet.fill(did);
		_cSumQ_SubDet_iphi.fill(did, sumQ);
		_cSumQ_depth.fill(did, sumQ);
		_cSumQvsLS_SubDet_iphi.fill(did, _currentLS, sumQ);

		//	fill with a cut
		if (sumQ>_cutSumQ_HBHE)
		{
			_cTimingCut_SubDet_iphi.fill(did, timing);
			_cTimingCutvsieta_SubDet_iphi.fill(did, timing);
			_cTimingCutvsiphi_SubDet_ieta.fill(did,	timing);
			_cTimingCut_depth.fill(did, timing);
			_cOccupancyCutvsiphi_SubDet.fill(did);
			_cOccupancyCut_depth.fill(did);
//			_cOccupancyCutiphivsLS_SubDet.fill(did, _currentLS);
		}
		
		//	per TS
		for (int i=0; i<digi.size(); i++)
		{
			//	without a cut
			_cADCperTS_SubDetPM.fill(did, digi.sample(i).adc());
			_cfCperTS_SubDetPM.fill(did, digi.sample(i).nominal_fC());
			_cShape_SubDetPM_iphi.fill(did, i, digi.sample(i).nominal_fC()-2.5);

			//	with a cut
			if (sumQ>_cutSumQ_HBHE)
			{
				_cShapeCut_SubDetPM_iphi.fill(did, i,
					digi.sample(i).nominal_fC()-2.5);
			}
		}
	}
	for (HODigiCollection::const_iterator it=cho->begin();
		it!=cho->end(); ++it)
	{
		const HODataFrame digi = (const HODataFrame)(*it);
		double sumQ = utilities::sumQ<HODataFrame>(digi, 8.5, 0, 
			digi.size()-1);
		double timing = utilities::aveTS<HODataFrame>(digi, 8.5, 0,
			digi.size()-1);
		const HcalDetId did = digi.id();

		//	fill without a cut
		_cOccupancy_depth.fill(did);
		_cOccupancyvsiphi_SubDet.fill(did);
		_cSumQ_SubDet_iphi.fill(did, sumQ);
		_cSumQ_depth.fill(did, sumQ);
		_cSumQvsLS_SubDet_iphi.fill(did, _currentLS, sumQ);

		//	fill with a cut
		if (sumQ>_cutSumQ_HO)
		{
			_cTimingCut_SubDet_iphi.fill(did, timing);
			_cTimingCutvsieta_SubDet_iphi.fill(did, timing);
			_cTimingCutvsiphi_SubDet_ieta.fill(did,	timing);
			_cTimingCut_depth.fill(did, timing);
			_cOccupancyCutvsiphi_SubDet.fill(did);
			_cOccupancyCut_depth.fill(did);
//			_cOccupancyCutiphivsLS_SubDet.fill(did, _currentLS);
		}
		
		//	per TS
		for (int i=0; i<digi.size(); i++)
		{
			//	without a cut
			_cADCperTS_SubDetPM.fill(did, digi.sample(i).adc());
			_cfCperTS_SubDetPM.fill(did, digi.sample(i).nominal_fC());
			_cShape_SubDetPM_iphi.fill(did, i, digi.sample(i).nominal_fC()-8.5);

			//	with a cut
			if (sumQ>_cutSumQ_HO)
			{
				_cShapeCut_SubDetPM_iphi.fill(did, i,
					digi.sample(i).nominal_fC()-8.5);
			}
		}
	}
	for (HFDigiCollection::const_iterator it=chf->begin();
		it!=chf->end(); ++it)
	{
		const HFDataFrame digi = (const HFDataFrame)(*it);
		double sumQ = utilities::sumQ<HFDataFrame>(digi, 2.5, 0, 
			digi.size()-1);
		double timing = utilities::aveTS<HFDataFrame>(digi, 2.5, 0,
			digi.size()-1);
		const HcalDetId did = digi.id();

		//	fill without a cut
		_cOccupancy_depth.fill(did);
		_cOccupancyvsiphi_SubDet.fill(did);
		_cSumQ_SubDet_iphi.fill(did, sumQ);
		_cSumQ_depth.fill(did, sumQ);
		_cSumQvsLS_SubDet_iphi.fill(did, _currentLS, sumQ);

		//	fill with a cut
		if (sumQ>_cutSumQ_HF)
		{
			_cTimingCut_SubDet_iphi.fill(did, timing);
			_cTimingCutvsieta_SubDet_iphi.fill(did, timing);
			_cTimingCutvsiphi_SubDet_ieta.fill(did,	timing);
			_cTimingCut_depth.fill(did, timing);
			_cOccupancyCutvsiphi_SubDet.fill(did);
			_cOccupancyCut_depth.fill(did);
//			_cOccupancyCutiphivsLS_SubDet.fill(did, _currentLS);
		}
		
		//	per TS
		for (int i=0; i<digi.size(); i++)
		{
			//	without a cut
			_cADCperTS_SubDetPM.fill(did, digi.sample(i).adc());
			_cfCperTS_SubDetPM.fill(did, digi.sample(i).nominal_fC());
			_cShape_SubDetPM_iphi.fill(did, i, digi.sample(i).nominal_fC()-2.5);

			//	with a cut
			if (sumQ>_cutSumQ_HF)
			{
				_cShapeCut_SubDetPM_iphi.fill(did, i,
					digi.sample(i).nominal_fC()-2.5);
			}
		}
	}
}

DEFINE_FWK_MODULE(DigiTask);


