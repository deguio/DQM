#include "DQM/HcalCommon/interface/ContainerSingleProf1D.h"

namespace hcaldqm
{
	ContainerSingleProf1D::ContainerSingleProf1D()
	{
		_qx = NULL;
		_qy = NULL;
	}

	ContainerSingleProf1D::ContainerSingleProf1D(std::string const& folder,
		Quantity *qx, Quantity *qy):
		ContainerSingle1D(folder, qy->name()+"vs"+qx->name(), qx, qy);
	{}
	
	/* virtual */ void ContainerSingleProf1D::initialize(std::string const& 
		folder, std::string const& qname,
		Quantity *qx, Quantity *qy,
		int debug/*=0*/)
	{
		ContainerSingle1D::initialize(folder, qname, qx, qy, debug);
	}

	/* virtual */ void ContainerSingleProf1D::book(DQMStore::IBooker& ib,
		std::string subsystem, std::string aux)
	{
		ib.setCurrentFolder(subsystem+"/"+_folder+"/"+_qname+aux);
		_me = ib.bookProfile(_qname, _qname,
			_qx->nbins(), _qx->min(), _qx->max(),
			_qy->min(), _qy->max());
	}
}



