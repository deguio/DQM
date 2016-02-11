import FWCore.ParameterSet.Config as cms

# prep a FED skip list

rawTask = cms.EDAnalyzer(
	"RawTask",
	
	#	standard parameters
	name = cms.untracked.string("RawTask"),
	debug = cms.untracked.int32(0),
	runkeyVal = cms.untracked.int32(0),
	runkeyName = cms.untracked.string("pp_run"),
	ptype = cms.untracked.int32(0),
	mtype = cms.untracked.bool(True),
	subsystem = cms.untracked.string("Hcal"),

	#	tags
	tagFEDs = cms.untracked.InputTag("rawDataCollector"),

)











