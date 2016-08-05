
#include "DQM/HcalTasks/interface/UMNioTask.h"

using namespace hcaldqm;
UMNioTask::UMNioTask(edm::ParameterSet const& ps):
	DQTask(ps)
{
	_tagHBHE = ps.getUntrackedParameter<edm::InputTag>("tagHBHE",
		edm::InputTag("hcalDigis"));
	_tagHO = ps.getUntrackedParameter<edm::InputTag>("tagHO",
		edm::InputTag("hcalDigis"));
	_tagHF = ps.getUntrackedParameter<edm::InputTag>("tagHF",
		edm::InputTag("hcalDigis"));
	_taguMN = ps.getUntrackedParameter<edm::InputTag>("taguMN",
		edm::InputTag("hcalDigis"));

	_tokHBHE = consumes<HBHEDigiCollection>(_tagHBHE);
	_tokHO = consumes<HODigiCollection>(_tagHO);
	_tokHF = consumes<HFDigiCollection>(_tagHF);
	_tokuMN = consumes<HcalUMNioDigi>(_taguMN);

	_lowHBHE = ps.getUntrackedParameter<double>("lowHBHE",
		20);
	_lowHO = ps.getUntrackedParameter<double>("lowHO",
		20);
	_lowHF = ps.getUntrackedParameter<double>("lowHF",
		20);
}
	
/* virtual */ void UMNioTask::bookHistograms(DQMStore::IBooker &ib,
	edm::Run const& r, edm::EventSetup const& es)
{
	if (_ptype==fLocal)
		if (r.runAuxiliary().run()==1)
			return;

	DQTask::bookHistograms(ib, r, es);
	
	edm::ESHandle<HcalDbService> dbService;
	es.get<HcalDbRecord>().get(dbService);
	_emap = dbService->getHcalMapping();

	_cEventType.initialize(_name, "EventType",
		new quantity::LumiSection(_maxLS),
		new quantity::EventType(_eventtypes),
		new quantity::ValueQuantity(quantity::fN));
	_cTotalCharge.initialize(_name, "TotalCharge",
		new quantity::LumiSection(_maxLS),
		new quantity::DetectorQuantity(quantity::fSubdetPM),
		new quantity::ValueQuantity(quantity::ffC_10000, true));
	_cEventType.book(ib, _subsystem);
	_cTotalCharge.book(ib, _subsystem);
}

/* virtual */ void UMNioTask::_process(edm::Event const& e,
	edm::EventSetup const& es)
{
	edm::Handle<HcalUMNioDigi> cumn;
	if (!e.getByToken(_tokuMN, cumn))
		std::cout << "Collection HcalUMNioDigi is not found" << std::endl;

	uint8_t eventType = cumn->eventType();
	uint32_t laserType = cumn->valueUserWord(0);
	_cEventType.fill(_currentLS, eventType==constants::EVENTTYPE_PEDESTAL ?
		(int)eventType : (int)laserType);

	//	Compute the Total Charge in the Detector...
	dm::Handle<HBHEDigiCollection>     chbhe;
	edm::Handle<HODigiCollection>       cho;
	edm::Handle<HFDigiCollection>       chf;

	if (!e.getByToken(_tokHBHE, chbhe))
		_logger.dqmthrow("Collection HBHEDigiCollection isn't available "
			+ _tagHBHE.label() + " " + _tagHBHE.instance());
	if (!e.getByToken(_tokHO, cho))
		_logger.dqmthrow("Collection HODigiCollection isn't available "
			+ _tagHO.label() + " " + _tagHO.instance());
	if (!e.getByToken(_tokHF, chf))
		_logger.dqmthrow("Collection HFDigiCollection isn't available "
			+ _tagHF.label() + " " + _tagHF.instance());

	for (HBHEDigiCollection::const_iterator it=chbhe->begin();
		it!=chbhe->end(); ++it)
	{
		double sumQ = utilities::sumQ<HBHEDataFrame>(*it, 2.5, 0, digi.size()-1);
		_cTotalCharge.fill(it->id(), _currentLS, sumQ);
	}
	for (HODigiCollection::const_iterator it=cho->begin();
		it!=cho->end(); ++it)
	{
		double sumQ = utilities::sumQ<HODataFrame>(*it, 8.5, 0, digi.size()-1);
		_cTotalCharge.fill(it->id(), _currentLS, sumQ);
	}
	for (HFDigiCollection::const_iterator it=chf->begin();
		it!=chf->end(); ++it)
	{
		double sumQ = utilities::sumQ<HFDataFrame>(*it, 2.5, 0, digi.size()-1);
		_cTotalCharge.fill(it->id(), _currentLS, sumQ);
	}
}
/* virtual */ void UMNioTask::endLuminosityBlock(edm::LuminosityBlock const& lb,
	edm::EventSetup const& es)
{
	DQTask::endLuminosityBlock(lb, es);
}

DEFINE_FWK_MODULE(UMNioTask);