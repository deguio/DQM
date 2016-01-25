#ifndef Container1D_h
#define Container1D_h

/*
 *	file:		Container1D.h
 *	Author:		Viktor Khristenko
 *
 *	Description:
 *		1D Container
 */

#include "DQM/HcalCommon/interface/DetectorQuantity.h"
#include "DQM/HcalCommon/interface/Container.h"
#include "DQM/HcalCommon/interface/HashMapper.h"
#include "DQM/HcalCommon/interface/Utilities.h"

#include <vector>
//#include <unordered_map>
#include "boost/ptr_container/ptr_map.hpp"
#include <string>

namespace hcaldqm
{

	using namespace quantity;
	using namespace mapper;
	class Container1D : public Container
	{
		public:
			Container1D();
			//	Initialize Container
			//	@folder - folder name where to start saving - root.
			//	By default it will be the Task's name.
			//
			Container1D(std::string const& folder,
				hashfunctions::HashType, 
				Quantity*,
				Quantity *qy = DetectorQuantity(quantity::fiphi));
			virtual ~Container1D() {}

			//	Initialize Container
			//	@folder - folder name where to save. Should already include the
			//	Tasks's name
			//	@nametitle - namebase of the name and of the title
			//
			virtual void initialize(std::string const& folder, 
				hashfunctions::HashType,  Quantity*
				Quantity *qy = new DetectorQuantity(quantity::fiphi), 
				int debug=0);

			//	using DetId as mapper
			virtual void fill(HcalDetId const&);
			virtual void fill(HcalDetId const&, int);
			virtual void fill(HcalDetId const&, double);
			virtual void fill(HcalDetId const&, int, double);
			virtual void fill(HcalDetId const&, int, int);
			virtual void fill(HcalDetId const&, double, double);

			//	booking
			//	@aux - typically a cut or anything else
			//	@subsystem - subsystem under which to save
			//
			virtual void book(DQMStore::IBooker&, HcalElectronicsMap const&,
				std::string subsystem="Hcal",
				std::string aux="");
			virtual void reset();

		protected:
			typedef boost::unordered_map<uint32_t, MonitorElement*> MEMap;
			MEMap									_mes;
			mapper::HashMapper						_hashmap;
			Quantity								*_qx;
			Quantity								*_qy;
	};
}

#endif








