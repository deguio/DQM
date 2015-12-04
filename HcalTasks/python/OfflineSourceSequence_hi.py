import FWCore.ParameterSet.Config as cms

#-----------------
#	HCAL DQM Offline Source Sequence Definition for Heavy Ions
#	To be used for Offline DQM importing
#-----------------

#	import the tasks
from DQM.HcalTasks.DigiTask import digiTask
from DQM.HcalTasks.RawTask import rawTask
from DQM.HcalTasks.TPTask import tpTask
from DQM.HcalTasks.RecHitTask import recHitTask

#	set processing type to Offine
digiTask.ptype = cms.untracked.int32(1)
tpTask.ptype = cms.untracked.int32(1)
recHitTask.ptype = cms.untracked.int32(1)
rawTask.ptype = cms.untracked.int32(1)

#	set the run key(value and name)
digiTask.runkeyVal = cms.untracked.int32(-1),
tpTask.runkeyVal = cms.untracked.int32(-1),
recHitTask.runkeyVal = cms.untracked.int32(-1)
rawTask.runkeyVal = cms.untracked.int32(-1)

digiTask.runkeyName = cms.untracked.string("hi_run")
tpTask.runkeyName = cms.untracked.string("hi_run")
recHitTask.runkeyName = cms.untracked.string("hi_run")
rawTask.runkeyName = cms.untracked.string("hi_run")

hcalOfflineSourceSequence = cms.Sequence(
	digiTask
	+tpTask
	+recHitTask
	+rawTask)

