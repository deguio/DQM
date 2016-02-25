#-------------------------------------
#	Hcal DQM Application using New DQM Sources/Clients
#	Description: For Local Use(a la DetDiag)
#-------------------------------------

#-------------------------------------
#	Standard Python Imports
#-------------------------------------
import os, sys, socket, string

#-------------------------------------
#	Input Options
#-------------------------------------
import FWCore.ParameterSet.VarParsing as VarParsing
options = VarParsing.VarParsing()

options.register(
	'inputFiles',
	"root://eoscms.cern.ch//eos/cms/store/group/dpg_hcal/comm_hcal/LS1/USC_248441.root", #default
	VarParsing.VarParsing.multiplicity.list,
	VarParsing.VarParsing.varType.string,
	"Input Files"
)

options.register(
	'processEvents',
	-1,
	VarParsing.VarParsing.multiplicity.singleton,
	VarParsing.VarParsing.varType.int,
	"Number of Events to process"
)

options.register(
	'runType',
	'UNKNOWN',
	VarParsing.VarParsing.multiplicity.singleton,
	VarParsing.VarParsing.varType.string,
	"Local Run Type: pedestal, led, laser, raddam"
)

options.parseArguments()

#-------------------------------------
#	Standard CMSSW Imports/Definitions
#-------------------------------------
import FWCore.ParameterSet.Config as cms
process			= cms.Process('HCALDQM')
subsystem		= 'Hcal'
cmssw			= os.getenv("CMSSW_VERSION").split("_")
debugstr		= "### HcalDQM::cfg::DEBUG: "
warnstr			= "### HcalDQM::cfg::WARN: "
errorstr		= "### HcalDQM::cfg::ERROR:"
local			= True
useMap			= True
dbMap			= False
cmsnet			= True

print debugstr, "Input Files= ", options.inputFiles
print debugstr, "Run over #events=", options.processEvents


#-------------------------------------
#	Central DQM Stuff imports
#-------------------------------------
if local:
	process.source = cms.Source("HcalTBSource",
		fileNames = cms.untracked.vstring(options.inputFiles)
	)
	process.maxEvents = cms.untracked.PSet(
			input = cms.untracked.int32(options.processEvents)
	)
else:
	print errorstr + "There is an error with the Source. Exiting..."
	sys.exit(1)
process.load('DQMServices.Components.DQMEnvironment_cfi')
process.load('DQMServices.Core.DQMStore_cfi')

#-------------------------------------
#	DQM Customization
#-------------------------------------
process.DQM = cms.Service(
	"DQM",
	debug = cms.untracked.bool(False),
	publishFrequency = cms.untracked.double(1.0),
	collectorPort = cms.untracked.int32(9999),
	collectorHost = cms.untracked.string('hcaldqm03.cms'),
	filter = cms.untracked.string('')
)
process.dqmSaver.convention = 'Online'
process.dqmSaver.referenceHandling = 'all'
process.dqmSaver.dirName = '.'
process.dqmSaver.producer = 'DQM'
process.dqmSaver.saveByLumiSection = 10
process.dqmSaver.saveByRun = 1
process.dqmSaver.saveAtJobEnd = False
process.DQMStore.verbose = 0
process.dqmEnv.subSystemFolder = subsystem

#-------------------------------------
#	CMSSW/Hcal non-DQM Related Module import
#-------------------------------------
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('FWCore.MessageLogger.MessageLogger_cfi')
process.load("EventFilter.HcalRawToDigi.HcalRawToDigi_cfi")
process.load("CondCore.CondDB.CondDB_cfi")
from Configuration.AlCa.autoCond import autoCond

#-------------------------------------
#	CMSSW/Hcal non-DQM Related Module Settings
#	-> GlobalTag
#	-> Generic Input tag for the Raw Collection
#	-> cmssw version
#	-> Turn off default blocking of dead channels from rechit collection
#	-> Drop Channel Status Bits (had benn 'HcalCellOff', "HcalCellDead")
#	-> For Trigger Primitives
#	-> L1 GT setting
#	-> Rename the hbheprereco to hbhereco
#-------------------------------------
process.GlobalTag.globaltag = autoCond['run2_data']
#process.GlobalTag.globaltag = '75X_dataRun2_HLTHI_v4'
if cmsnet:
	process.GlobalTag.connect = 'frontier://(serverurl=http://frontier1.cms:8000/FrontierOnProd)(serverurl=http://frontier2.cms:8000/FrontierOnProd)(retrieve-ziplevel=0)/CMS_CONDITIONS'
cmssw			= os.getenv("CMSSW_VERSION").split("_")
rawTagStr		= "source"
rawTag			= cms.InputTag(rawTagStr)
process.MessageLogger.cerr.FwkReport.reportEvery = 100

#-------------------------------------
#	Hcal DQM Tasks and Clients import
#-------------------------------------
process.load("DQM.SpecificTasks.QIE10TestTask")

#-------------------------------------
#	To force using uTCA
#	Will not be here for Online DQM
#-------------------------------------
if useMap==True and dbMap==True:
	process.es_pool = cms.ESSource("PoolDBESSource",
			process.CondDBSetup,
			timetype = cms.string('runnumber'),
			toGet = cms.VPSet(
				cms.PSet(
					record = cms.string(
						"HcalElectronicsMapRcd"
					),
					tag = cms.string(
						"HcalElectronicsMap_v7.00_offline"					  )
				)
			),
			connect = cms.string(
				'frontier://FrontierProd/CMS_CONDITIONS'),
			authenticationMethod = cms.untracked.uint32(0)
	)	
	process.es_prefer_es_pool = cms.ESPrefer('PoolDBESSource', 'es_pool')
elif useMap==True and dbMap==False:
	process.es_ascii = cms.ESSource(
		'HcalTextCalibrations',
		input = cms.VPSet(
			cms.PSet(
				object = cms.string('ElectronicsMap'),
				file = cms.FileInPath('version_G_emap_all_ngHF2016_feb24.txt')
#				file = cms.FileInPath('emap_split_PMT_BOX_UXC.txt')
#				file = cms.FileInPath('version_qie10.txt')
#				file = cms.FileInPath('version_G_emap_2015_may_20')
			)
		)
	)
	process.es_prefer = cms.ESPrefer('HcalTextCalibrations', 'es_ascii')

#-------------------------------------
#	To have vme Digis as a separate collection
#-------------------------------------
process.vmeDigis = process.hcalDigis.clone()
process.vmeDigis.InputLabel = rawTag
process.vmeDigis.FEDs = cms.untracked.vint32(719, 720)

process.utcaDigis = process.hcalDigis.clone()
process.utcaDigis.InputLabel = rawTag
process.utcaDigis.FEDs = cms.untracked.vint32(1100, 1102, 1104, 1106,
	1108, 1110, 1112, 1114, 1116)

process.qie10Digis = process.hcalDigis.clone()
process.qie10Digis.InputLabel = rawTag
process.qie10Digis.FEDs = cms.untracked.vint32(1132)

process.tasksSequence = cms.Sequence(process.qie10TestTask)

#-------------------------------------
#	Some Settings for Local(a la DetDiag)
#	All Modules are muted by default
#	isGlobal must be set to False!
#	Get the Local Trigger Information	
#-------------------------------------
process.hcalDigis.InputLabel = rawTag
process.qie10TestTask.tagRaw = cms.untracked.InputTag("source")
process.qie10TestTask.ptype = cms.untracked.int32(2)

#-------------------------------------
#	Execution Sequence Definition
#-------------------------------------
process.p = cms.Path(
					process.qie10Digis
					*process.tasksSequence
                    *process.dqmEnv
                    *process.dqmSaver
)

#-------------------------------------
#	Outputs the event Content for Debugging mostly
#-------------------------------------
#process.Out = cms.OutputModule(
#	"PoolOutputModule",
#	fileName = cms.untracked.string("test.root")
#)
#process.finalize = cms.EndPath(process.Out)

#-------------------------------------
#	Scheduling
#-------------------------------------
process.options = cms.untracked.PSet(
		Rethrow = cms.untracked.vstring(
			"ProductNotFound",
			"TooManyProducts",
			"TooFewProducts"
		)
)
