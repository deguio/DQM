
#include "DQM/HcalTasks/interface/TPTask.h"

using namespace hcaldqm;
TPTask::TPTask(edm::ParameterSet const& ps):
	DQTask(ps),

	//	Et
	_cEtData_SubDet(_name+"/Et/Data_SubDet", "Et",
		mapper::fTPSubDet,
		new axis::ValueAxis(axis::fXaxis, axis::fEt_256),
		new axis::ValueAxis(axis::fYaxis, axis::fEntries, true)),
	_cEtEmul_SubDet(_name+"/Et/Emul_SubDet", "Et",
		mapper::fTPSubDet,
		new axis::ValueAxis(axis::fXaxis, axis::fEt_256),
		new axis::ValueAxis(axis::fYaxis, axis::fEntries, true)),
	_cEtCorr_SubDet(_name+"/Et/Correlation_SubDet", "Et_DataVSEmul",
		mapper::fTPSubDet,
		new axis::ValueAxis(axis::fXaxis, axis::fEt_128),
		new axis::ValueAxis(axis::fYaxis, axis::fEt_128)),
	_cEtCorrRatiovsLS_TPSubDet(_name+"/Et/CorrRatiovsLS_TPSubDet",
		"CorrelationRatio", mapper::fTPSubDet,
		new axis::ValueAxis(axis::fXaxis, axis::fLS),
		new axis::ValueAxis(axis::fYaxis, axis::fRatio)),
	_cEtCorrRatio_TPSubDet(_name+"/Et/CorrRatio_TPSubDet",
		"CorrelationRatio", mapper::fTPSubDet,
		new axis::ValueAxis(axis::fXaxis, axis::fRatio),
		new axis::ValueAxis(axis::fYaxis, axis::fEntries, true)),
	_cEtCorrRatiovsiphi_TPSubDetPM(_name+"/Et/CorrRatiovsiphi_TPSubDetPM",
		"CorrelationRatio", mapper::fTPSubDetPM,
		new axis::CoordinateAxis(axis::fXaxis, axis::fiphi),
		new axis::ValueAxis(axis::fXaxis, axis::fRatio)),
	_cEtMsm(_name+"/Et/MisMatched", "Et_MisMatched",
		new axis::CoordinateAxis(axis::fXaxis, axis::fTPieta),
		new axis::CoordinateAxis(axis::fYaxis, axis::fiphi),
		new axis::ValueAxis(axis::fZaxis, axis::fEntries)),
	_cNumEtMsmvsLS_TPSubDet(_name+"/Et/MismatchedvsLS_TPSubDet",
		"Et_Mismatched", mapper::fTPSubDet,
		new axis::ValueAxis(axis::fXaxis, axis::fLS),
		new axis::ValueAxis(axis::fYaxis, axis::fEntries100)),
	_cNumEtMsm_TPSubDet(_name+"/Et/Mismatched_TPSubDet",
		"Et_Mismatched", mapper::fTPSubDet,
		new axis::ValueAxis(axis::fXaxis, axis::fEntries100),
		new axis::ValueAxis(axis::fYaxis, axis::fEntries, true)),
	_cNumEtMsmvsiphi_TPSubDetPM(_name+"/Et/Mismatchedvsiphi_TPSubDetPM",
		"Et_Mismatched", mapper::fTPSubDetPM,
		new axis::CoordinateAxis(axis::fXaxis, axis::fiphi),
		new axis::ValueAxis(axis::fYaxis, axis::fEntries)),
	_cdEtRatiovsLS_TPSubDet(_name+"/dEtRatio/vsLS_TPSubDet",
		"dEtRatio", mapper::fTPSubDet,
		new axis::ValueAxis(axis::fXaxis, axis::fLS),
		new axis::ValueAxis(axis::fYaxis, axis::fdEtRatio)),
	_cdEtRatio_TPSubDet(_name+"/dEtRatio/TPSubDet",
		"dEtRatio", mapper::fTPSubDet,
		new axis::ValueAxis(axis::fXaxis, axis::fdEtRatio),
		new axis::ValueAxis(axis::fYaxis, axis::fEntries, true)),
	_cSumdEtvsLS_TPSubDet(_name+"/SumdEt/vsLS_TPSubDet",
		"SumdEt", mapper::fTPSubDet,
		new axis::ValueAxis(axis::fXaxis, axis::fLS),
		new axis::ValueAxis(axis::fYaxis, axis::fSumdEt)),
	_cSumdEt_TPSubDet(_name+"/SumdEt/TPSubDet",
		"SumdEt", mapper::fTPSubDet,
		new axis::ValueAxis(axis::fXaxis, axis::fSumdEt),
		new axis::ValueAxis(axis::fYaxis, axis::fEntries, true)),
	_cEtData_SubDetPM_iphi(_name+"/Et/Data_SubDetPM_iphi", "EtData",
		mapper::fTPSubDetPM_iphi,
		new axis::ValueAxis(axis::fXaxis, axis::fEt_256),
		new axis::ValueAxis(axis::fYaxis, axis::fEntries, true)),
	_cEtData_SubDet_ieta(_name+"/Et/Data_SubDet_ieta", "EtData",
		mapper::fTPSubDet_ieta,
		new axis::ValueAxis(axis::fXaxis, axis::fEt_256),
		new axis::ValueAxis(axis::fYaxis, axis::fEntries, true)),
	_cEtCorr_SubDetPM_iphi(_name+"/Et/Correlation_SubDetPM_iphi", 
		"Et_DataVSEmul",
		mapper::fTPSubDetPM_iphi,
		new axis::ValueAxis(axis::fXaxis, axis::fEt_128),
		new axis::ValueAxis(axis::fYaxis, axis::fEt_128)),

	//	FG
	_cFGCorr_SubDet(_name+"/FG/Correlation_SubDet", "FG_DataVSEmul",
		mapper::fTPSubDet,
		new axis::ValueAxis(axis::fXaxis, axis::fFG),
		new axis::ValueAxis(axis::fYaxis, axis::fFG)),
	_cFGMsm(_name+"/FG/MisMatched", "FG_MisMatched",
		new axis::CoordinateAxis(axis::fXaxis, axis::fTPieta),
		new axis::CoordinateAxis(axis::fYaxis, axis::fiphi),
		new axis::ValueAxis(axis::fZaxis, axis::fEntries)),

	//	Occupancy
	_cOccupancyData(_name+"/Occupancy", "Occupancy_Data",
		new axis::CoordinateAxis(axis::fXaxis, axis::fTPieta),
		new axis::CoordinateAxis(axis::fYaxis, axis::fiphi),
		new axis::ValueAxis(axis::fZaxis, axis::fEntries)),
	_cOccupancyEmul(_name+"/Occupancy", "Occupancy_Emul",
		new axis::CoordinateAxis(axis::fXaxis, axis::fTPieta),
		new axis::CoordinateAxis(axis::fYaxis, axis::fiphi),
		new axis::ValueAxis(axis::fZaxis, axis::fEntries)),
	_cOccupancyDatavsiphi_TPSubDetPM(_name+"/Occupancy/Datavsiphi_TPSubDetPM",
		"Occupancy_Data", mapper::fTPSubDetPM,
		new axis::CoordinateAxis(axis::fXaxis, axis::fiphi)),
	_cOccupancyEmulvsiphi_TPSubDetPM(_name+"/Occupancy/Emulvsiphi_TPSubDetPM",
		"Occupancy_Emul", mapper::fTPSubDetPM,
		new axis::CoordinateAxis(axis::fXaxis, axis::fiphi)),
	_cOccupancyDatavsLS_TPSubDet(_name+"/Occupancy/DatavsLS_TPSubDet",
		"Occupancy_Data", mapper::fTPSubDet,
		new axis::ValueAxis(axis::fXaxis, axis::fLS),
		new axis::ValueAxis(axis::fYaxis, axis::fEntries)),
	_cOccupancyEmulvsLS_TPSubDet(_name+"/Occupancy/EmulvsLS_TPSubDet",
		"Occupancy_Emul", mapper::fTPSubDet,
		new axis::ValueAxis(axis::fXaxis, axis::fLS),
		new axis::ValueAxis(axis::fYaxis, axis::fEntries)),
	_cMsData(_name+"/Missing", "Missing_Data",
		new axis::CoordinateAxis(axis::fXaxis, axis::fTPieta),
		new axis::CoordinateAxis(axis::fYaxis, axis::fiphi),
		new axis::ValueAxis(axis::fZaxis, axis::fEntries)),
	_cMsDatavsiphi_TPSubDetPM(_name+"/Missing/Datavsiphi_TPSubDetPM",
		"Missing_Data", mapper::fTPSubDetPM,
		new axis::CoordinateAxis(axis::fXaxis, axis::fiphi),
		new axis::ValueAxis(axis::fYaxis, axis::fEntries)),
	_cMsEmul(_name+"/Missing", "Missing_Emul",
		new axis::CoordinateAxis(axis::fXaxis, axis::fTPieta),
		new axis::CoordinateAxis(axis::fYaxis, axis::fiphi),
		new axis::ValueAxis(axis::fZaxis, axis::fEntries)),

	//	Digi Sizes
	_cDigiSizeData_TPSubDet(_name+"/DigiSize/DatavsLS_TPSubDet",
		"DigiSize_Data", mapper::fTPSubDet,
		new axis::ValueAxis(axis::fXaxis, axis::fLS),
		new axis::ValueAxis(axis::fYaxis, axis::fDigiSize)),
	_cDigiSizeEmul_TPSubDet(_name+"/DigiSize/EmulvsLS_TPSubDet",
		"DigiSize_Emul", mapper::fTPSubDet,
		new axis::ValueAxis(axis::fXaxis, axis::fLS),
		new axis::ValueAxis(axis::fYaxis, axis::fDigiSize)),

	//	Summary
	_cSummary(_name+"/Summary", "Summary",
		new axis::CoordinateAxis(axis::fXaxis, axis::fSubDet),
		new axis::FlagAxis(axis::fYaxis, "Flag", int(nTPFlag))),
	_cSummaryvsLS_TPSubDet(_name+"/Summary/vsLS_TPSubDet", "Summary"
		mapper::fTPSubDet,
		new axis::ValueAxis(axis::fXaxis, axis::fLS),
		new axis::FlagAxis(axis::fYaxis, "Flag", int(nTPFlag)))
{
	//	tags
	_tagData = ps.getUntrackedParameter<edm::InputTag>("tagData",
		edm::InputTag("hcalDigis"));
	_tagEmul = ps.getUntrackedParameter<edm::InputTag>("tagEmul",
		edm::InputTag("emulDigis"));

	//	Special
	_skip1x1 = ps.getUntrackedParameter<bool>("skip1x1", true);

	//	flags
	_fNames.push_back("Occ. iphi Uniform. D");
	_fNames.push_back("Occ. iphi Uniform. E");
	_fNames.push_back("Low Occupancy E");
	_fNames.push_back("Corr. Ratio");
	_fNames.push_back("Corr. Ratio iphi Uniform");
	_fNames.push_back("Msm. Et iphi Uniform. ");
	_fNames.push_back("Msm. Et Number");
	_fNames.push_back("Missing iphi Uniform. D");
	_fNames.push_back("Missing iphi Uniform. E");
	_cSummary.loadLabels(_fNames);
	_cSummaryvsLS_TPSubDet.loadLabels(_fNames);
}

/* virtual */ void TPTask::bookHistograms(DQMStore::IBooker &ib,
	edm::Run const& r, edm::EventSetup const& es)
{
	DQTask::bookHistograms(ib, r, es);
	_cEtData_SubDet.book(ib);
	_cEtEmul_SubDet.book(ib);
	_cEtCorr_SubDet.book(ib);
	_cEtCorrRatiovsLS_TPSubDet.book(ib);
	_cEtCorrRatio_TPSubDet.book(ib);
	_cEtCorrRatiovsiphi_TPSubDetPM.book(ib);
	_cEtMsm.book(ib);
	_cdEtRatiovsLS_TPSubDet.book(ib);
	_cdEtRatio_TPSubDet.book(ib);
	_cSumdEtvsLS_TPSubDet.book(ib);
	_cSumdEt_TPSubDet.book(ib);
	_cNumEtMsmvsLS_TPSubDet.book(ib);
	_cNumEtMsm_TPSubDet.book(ib);
	_cNumEtMsmvsiphi_TPSubDetPM.book(ib);
	_cEtData_SubDetPM_iphi.book(ib);
	_cEtData_SubDet_ieta.book(ib);
	_cEtCorr_SubDetPM_iphi.book(ib);
	_cFGCorr_SubDet.book(ib);
	_cFGMsm.book(ib);
	_cOccupancyData.book(ib);
	_cOccupancyEmul.book(ib);
	_cOccupancyDatavsiphi_TPSubDetPM.book(ib);
	_cOccupancyEmulvsiphi_TPSubDetPM.book(ib);
	_cOccupancyDatavsLS_TPSubDet.book(ib);
	_cOccupancyEmulvsLS_TPSubDet.book(ib);
	_cMsData.book(ib);
	_cMsEmul.book(ib);
	_cMsDatavsiphi_TPSubDetPM.book(ib);

	_cDigiSizeDatavsLS_TPSubDet.book(ib);
	_cDigiSizeEmulvsLS_TPSubDet.book(ib);

	_cSummary.book(ib);
	_cSummaryvsLS_TPSubDet.book(ib);
}

/* virtual */ void TPTask::_process(edm::Event const& e,
	edm::EventSetup const &es)
{
	edm::Handle<HcalTrigPrimDigiCollection> ctpd;
	edm::Handle<HcalTrigPrimDigiCollection> ctpe;

	if (!e.getByLabel(_tagData, ctpd))
		this->_throw("Collection HcalTrigPrimDigiCollection isn't available",
			" " + _tagData.label() + " " + _tagData.instance());
	if (!e.getByLabel(_tagEmul, ctpe))
		this->_throw("Collection HcalTrigPrimDigiCollection isn't available",
			" " + _tagEmul.label() + " " + _tagEmul.instance());

	//	tmp
	bool useD1 = false;
	//	tmp


	//	iterate thru the Data Digis
	double sumdEtRatio[2] = 0;
	double sumdEt[2] = 0;
	int nMatches[2] = 0;
	for (HcalTrigPrimDigiCollection::const_iterator hddigi=ctpd->begin();
		hddigi!=ctpd->end(); ++hddigi)
	{
		//	tmpt
		if (_skip1x1)
			if (hddigi->id().depth()==10) // 10 is the depth for 1x1 TPs
				continue;
		//\tmp

		//	get quantities
		int soiEt_d = hddigi->SOI_compressedEt();
		int soiFG_d = hddigi->SOI_fineGrain() ? 1 : 0;
		HcalTrigTowerDetId tid = hddigi->id();

		//	tmp
		if (hddigi->id().depth()==1)
			useD1 = true;
		//\tmp

		//	fill individual
		_cEtData_SubDet.fill(tid, soiEt_d);
		_cEtData_SubDetPM_iphi.fill(tid, soiEt_d);
		_cEtData_SubDet_ieta.fill(tid, soiEt_d);
		_cOccupancyData.fill(tid);
		_cOccupancyDatavsiphi_TPSubDetPM.fill(tid);
		_nTPs_Data[utilities::getTPSubDet(tid)]++;
		_cDigiSizeDatavsLS_TPSubDet.fill(tid, _currentLS, hddigi->size());

		//	now, find the emulator digi and compare
		HcalTrigPrimDigiCollection::const_iterator hedigi = 
			ctpe->find(HcalTrigTowerDetId(tid.ieta(),
				tid.iphi(), 0));
	
		if (hedigi!=ctpe->end())
		{
			int soiEt_e = hedigi->SOI_compressedEt();
			int soiFG_e = hedigi->SOI_fineGrain() ? 1 : 0;
			double rEt = double(std::min(soiEt_d, soiEt_e))/
				double(std::max(soiEt_e, soiEt_d));
			sumdEt[utilities::getTPSubDet(toi)]+=std::abs(soiEt_e-soiEt_d);
			sumdEtRatio[utilities::getTPSubDet(toi)]+=
				double(std::abs(soiEt_e-soiEt_d))/
				double(std::max(soiEt_e, soiEt_d));
			nMatches[utilities::getTPSubDet(toi)]++;

			//	fill correlations
			_cEtEmul_SubDet.fill(tid, soiEt_e);
			_cEtCorr_SubDet.fill(tid, soiEt_e, soiEt_d);
			_cEtCorr_SubDetPM_iphi.fill(tid, soiEt_e, soiEt_d);
			_cFGCorr_SubDet.fill(tid, soiFG_e, soiFG_d);
			_cOccupancyEmul.fill(tid);
			_cEtCorrRatiovsLS_TPSubDet.fill(tid, _currentLS, rEt);
			_cEtCorrRatio_TPSubDet.fill(tid, rEt);
			_cOccupancyEmulvsiphi_TPSubDetPM.fill(tid);
			_nTPs_Emul[utilities::getTPSubDet(tid)]++;
			_cEtCorrRatiovsiphi_TPSubDetPM.fill(tid, rEt);
			_cDigiSizeEmulvsLS_TPSubDet.fill(tid, _currentLS, hedigi->size());

			//	fill those that mismatched
			if (soiEt_d!=soiEt_e)
			{
				_cEtMsm.fill(tid);
				_nMsmEt[utilities::getTPSubDet(tid)]++;
				_cNumEtMsmvsiphi_TPSubDetPM.fill(tid);
			}
			if (soiFG_d!=soiEt_e)
			{
				_cFGMsm.fill(hddigi->id());
				_nMsmFG[utilities::getTPSubDet(tid)]++;
			}
		}
		else 
		{
			_cMsEmul.fill(hddigi->id());
		}
	}

	//	iterate thru the Emulator Digis
	for (HcalTrigPrimDigiCollection::const_iterator hedigi=ctpe->begin();
		hedigi!=ctpe->end(); ++hedigi)
	{
		//	tmp
		if (_skip1x1)
			if (hedigi->id().depth()==10)	// 10 for 1x1
				continue;
		//	\tmp

		//	now, find the emulator digi and compare
		//	tmp
		HcalTrigPrimDigiCollection::const_iterator hddigi = 
			ctpd->find(HcalTrigTowerDetId(hedigi->id().ieta(),
				hedigi->id().iphi(), useD1 ? 1: 0));
		//	\tmp

		//	we have to only check those that are missing
		if (hddigi==ctpd->end())
		{
			_cMsData.fill(hedigi->id());
			_cOccupancyEmulvsiphi_TPSubDetPM.fill(hedigi->id());
			_nTPs_Emul[utilities::getTPSubDet(hedigi->id())]++;
			_cDigiSizeEmulvsLS_TPSubDet.fill(hedigi->id(), _currentLS,
				hedigi->size());
		}
	}

	//	fill per event quantities
	_cOccupancyDatavsLS_TPSubDet.fill(HcalTrigTowerDetId(5, 5), 
		_currentLS, _nTPs_Data[0]);
	_cOccupancyDatavsLS_TPSubDet.fill(HcalTrigTowerDetId(30, 5), 
		_currentLS, _nTPs_Data[1]);
	_cOccupancyEmulvsLS_TPSubDet.fill(HcalTrigTowerDetId(5, 5), 
		_currentLS, _nTPs_Emul[0]);
	_cOccupancyEmulvsLS_TPSubDet.fill(HcalTrigTowerDetId(30, 5), 
		_currentLS, _nTPs_Emul[1]);
	_cNumEtMsmvsLS_TPSubDet.fill(HcalTrigTowerDetId(5, 5), 
		_currentLS, _nMsmEt[0]);
	_cNumEtMsmvsLS_TPSubDet.fill(HcalTrigTowerDetId(30, 5), 
		_currentLS, _nMsmEt[1]);
	_cNumEtMsm_TPSubDet.fill(HcalTrigTowerDetId(5, 5), _nMsmEt[0]);
	_cNumEtMsm_TPSubDet.fill(HcalTrigTowerDetId(30, 5), _nMsmEt[1]);
	_cdEtRatiovsLS_TPSubDet.fill(HcalTrigTowerDetId(5, 5), _currentLS,
		sumdEtRatio[0]/nMatches[0]);
	_cdEtRatiovsLS_TPSubDet.fill(HcalTrigTowerDetId(30, 5), _currentLS,
		sumdEtRatio[1]/nMatches[1]);
	_cdEtRatio_TPSubDet.fill(HcalTrigTowerDetId(5, 5),
		sumdEtRatio[0]/nMatches[0]);
	_cdEtRatio_TPSubDet.fill(HcalTrigTowerDetId(30, 5),
		sumdEtRatio[1]/nMatches[1]);
}

/* virtual */ void TPTask::endLuminosityBlock(edm::LuminosityBlock const&,
	edm::EventSetup const&)
{
	//	statuses
	double status[constants::TPSUBDET_NUM][nTPFlag];
	for (unsigned int i=0; i<constants::TPSUBDET_NUM; i++)
		for (int j=fOccUniphi_Data; j<nTPFlag; j++)
			status[i][j] = constants::NOT_APPLICABLE;

	/*
	 *	Do the checks here
	 *	-> iphi Uniformity of the Data HF Occupancy
	 *	-> iphi Uniformity of the Emul HF Occupancy
	 *	-> Low Occupancy for HF Emulator (Data is ZSs)
	 *	-> Correlation Ratio vs LS check
	 *	-> Correlation Ratio Uniformity 
	 *	-> iphi Uniformity for the number of mismatches
	 *	-> iphi Uniformity for Missing Data
	 *	-> iphi Uniformity for Missing Emul
	 */

	//	Low Occp for HF Emul
	MonitorElement *meocpHF = _cOccupancyEmulvsLS_TPSubDet.at(1);
	double numChs = meocpHF->getBinContent(_currentLS);
	if (constants::TPCHS_NUM[1] - numChs>=4)
		status[1][fLowOcp_Emul] = constants::VERY_LOW;
	else if (constants::TPCHS_NUM[1] - numChs>=1)
		status[1][fLowOcp_Emul] = constants::LOW;
	else if [constants::TPCHS_NUM[1]-numChs<0]
		status[1][fLowOcp_Emul] = constants::LOW;
	else if (constants::TPCHS_NUM[1]==numChs)
		status[1][fLowOcp_Emul] = constants::GOOD;

	//	iphi Occupancy Uniformity for Data/Emul HF
	for (int i=1; i<=69; i+=8)
	{
		int i1= i;
		int i2 = (i+4)%IPHI_NUM;

		double occ1_m_d = _cOccupancyDatavsiphi_TPSubDetPM.getBinContent(2, i1);
		double occ2_m_d = _cOccupancyDatavsiphi_TPSubDetPM.getBinContent(2, i2);
		double ratio_m_d = std::min(occ1_m_d, occ2_m_d)/
			std::max(occ1_m_d, occ2_m_d);
		double occ1_p_d = _cOccupancyDatavsiphi_TPSubDetPM.getBinContent(3, i1);
		double occ2_p_d = _cOccupancyDatavsiphi_TPSubDetPM.getBinContent(3, i2);
		double ratio_p_d = std::min(occ1_p_d, occ2_p_d)/
			std::max(occ1_p_d, occ2_p_d);
		
		double occ1_m_e = _cOccupancyEmulvsiphi_TPSubDetPM.getBinContent(2, i1);
		double occ2_m_e = _cOccupancyEmulvsiphi_TPSubDetPM.getBinContent(2, i2);
		double ratio_m_e = std::min(occ1_m_e, occ2_m_e)/
			std::max(occ1_m_e, occ2_m_e);
		double occ1_p_e = _cOccupancyEmulvsiphi_TPSubDetPM.getBinContent(3, i1);
		double occ2_p_e = _cOccupancyEmulvsiphi_TPSubDetPM.getBinContent(3, i2);
		double ratio_p_e = std::min(occ1_p_e, occ2_p_e)/
			std::max(occ1_p_e, occ2_p_e);

		double msm1_m = _cNumEtMsmvsiphi_TPSubDetPM.getBinContent(2, i1);
		double msm2_m = _cNumEtMsmvsiphi_TPSubDetPM.getBinContent(2, i2);
		double msmratio_m = std::min(msm1_m, msm2_m)/
			std::max(msm1_m, msm2_m);
		double msm1_p = _cNumEtMsmvsiphi_TPSubDetPM.getBinContent(3, i1);
		double msm2_p = _cNumEtMsmvsiphi_TPSubDetPM.getBinContent(3, i2);
		double msmratio_p = std::min(msm1_p, msm2_p)/
			std::max(msm1_p, msm2_p);

		if (ratio_m_d<0.8 || ratio_p_d<0.8)
			status[1][fOccUniphi_Data] = constants::VERY_LOW;
		else
			status[1][fOccUniphi_Data] = constants::GOOD;
		if (ratio_m_e<0.8 || ratio_p_e<0.8)
			status[1][fOccUniphi_Emul] = constants::VERY_LOW;
		else 
			status[1][fOccUniphi_Emul] = constants::GOOD;
		if (msmratio_m<0.8 || msmratio_p<0.8)
			status[1][fMsmEtUniphi] = constants::LOW;
		else 
			status[1][fMsmEtUniphi] = constants::GOOD;
	}

	//	Correlation Ratio
	double ratio_HBHE  = _cEtCorrRatiovsLS_TPSubDet.at(0);
	double ratio_HF  = _cEtCorrRatiovsLS_TPSubDet.at(1);
	if (ratio_HBHE<0.7)
		status[0][fCorrRatio] = constants::LOW;
	else if (ratio_HBHE<0.8)
		status[0][fCorrRatio] = constants::PROBLEMATIC;
	else 
		status[0][fCorrRatio] = constants::GOOD;
	if (ratio_HF<0.8)
		status[1][fCorrRatio] = constants::LOW;
	else if (ratio_HF<0.9)
		status[1][fCorrRatio] = constants::PROBLEMATIC;
	else
		status[1][fCorrRatio] = constants::GOOD;

	//	Number of Mismatches
	double ratio_nmsm_HBHE = _cNumEtMsmvsLS_TPSubDet.at(0)/
		constants::TPCHS_NUM[0];
	double ratio_nmsm_HF = _cNumEtMsmvsLS_TPSubDet.at(1)/
		constants::TPCHS_NUM[1];
	if (ratio_nmsm_HBHE>=0.2)
		status[0][fMsmEtNum] = constants::VERY_LOW;
	else if (ratio_nmsm_HBHE>=0.1)
		status[0][fMsmEtNum] = constants::LOW;
	else if (ratio_nmsm_HBHE>=0.05)
		status[0][fMsmEtNum] = constants::PROBLEMATIC;
	else 
		status[0][fMsmEtNum] = constants::GOOD;

	//	finally set all the statuses
	for (unsigned int i=0; i<constants::TPSUBDET_NUM; i++)
		for (int j=fOccUniphi_Data; j<nTPFlag; j++)
		{
			_cSummary.setBinContent(i, j, status[i][j]);
			_cSummaryvsLS_TPSubDet.setBinContent(i, _currentLS, j,
				status[i][j]);
		}
}

/* virtual */ void TPTask::_resetMonitors(UpdateFreq uf)
{
	switch (uf)
	{
		case fEvent:
			for (unsigned int idet=0; idet<constants::TPSUBDET_NUM; idet++)
			{
				_nMsmEt[idet] = 0;
				_nMsmFG[idet] = 0;
				_nTPs_Data[idet] = 0;
				_nTPs_Emul[idet] = 0;
			}
			break;
		case hcaldqm::fLS:
			break;
		case hcaldqm::f10LS:
			break;
		default:
			break;
	}

	DQTask::_resetMonitors(uf);
}

DEFINE_FWK_MODULE(TPTask);


