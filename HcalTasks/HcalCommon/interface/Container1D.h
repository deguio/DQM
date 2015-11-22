#ifndef Container1D_h
#define Container1D_h

/*
 *	file:		Container1D.h
 *	Author:		Viktor Khristenko
 *
 *	Description:
 *		1D Container
 */

#include "DQM/HcalCommon/interface/ValueAxis.h"
#include "DQM/HcalCommon/interface/CoordinateAxis.h"
#include "DQM/HcalCommon/interface/Container.h"
#include "DQM/HcalCommon/interface/Mapper.h"
#include "DQM/HcalCommon/interface/Utilities.h"

#include <vector>
#include <string>

namespace hcaldqm
{

	using namespace axis;
	using namespace mapper;
	class Container1D : public Container
	{
		public:
			Container1D() {}
			//	Initialize Container
			//	@folder - folder name where to save. Should already include the
			//	Tasks's name
			//	@nametitle - namebase of the name and of the title
			//
			Container1D(std::string const& folder, std::string const& nametitle,
				mapper::MapperType mt, axis::Axis* xaxis, 
				axis::Axis* yaxis = new ValueAxis(fYaxis, fEntries));
			virtual ~Container1D() {}

			//	just to have here
			virtual void fill(double ) {}
			virtual void fill(int) {}
			//	using int as mapper or double
			virtual void fill(int, int);
			virtual void fill(int, double);
			virtual void fill(int, int, double);
			virtual void fill(int, double, double);

			//	using DetId as mapper
			virtual void fill(HcalDetId const&);
			virtual void fill(HcalDetId const&, int);
			virtual void fill(HcalDetId const&, double);
			virtual void fill(HcalDetId const&, int, double);
			virtual void fill(HcalDetId const&, int, int);
			virtual void fill(HcalDetId const&, double, double);

			//	using ElectronicsId as mapper
			virtual void fill(HcalElectronicsId const&);
			virtual void fill(HcalElectronicsId const&, int);
			virtual void fill(HcalElectronicsId const&, double);
			virtual void fill(HcalElectronicsId const&, int, double);
			virtual void fill(HcalElectronicsId const&, double, double);

			virtual void fill(HcalTrigTowerDetId const&);
			virtual void fill(HcalTrigTowerDetId const&, int);
			virtual void fill(HcalTrigTowerDetId const&, double);
			virtual void fill(HcalTrigTowerDetId const&, int, int);
			virtual void fill(HcalTrigTowerDetId const&, int, double);

			//	booking
			//	@aux - typically a cut or anything else
			//	@subsystem - subsystem under which to save
			//
			virtual void book(DQMStore::IBooker&, std::string subsystem="Hcal",
				std::string aux="");
			virtual void reset();

		protected:
			typedef	std::vector<MonitorElement*>	MEVector;
			MEVector								_mes;
			mapper::Mapper							_mapper;
			axis::Axis								*_xaxis;
			axis::Axis								*_yaxis;

	};
}

#endif







