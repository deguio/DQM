import FWCore.ParameterSet.Config as cms

digiTask = cms.EDAnalyzer(
	"DigiTask",
	
	#	standard parameters
	name = cms.untracked.string("DigiTask"),
	debug = cms.untracked.int32(0),
	runkeyVal = cms.untracked.int32(0),
	runkeyName = cms.untracked.string("pp_run"),

	#	tags
	tagHBHE = cms.untracked.InputTag("hcalDigis"),
	tagHO = cms.untracked.InputTag("hcalDigis"),
	tagHF = cms.untracked.InputTag("hcalDigis")
)











