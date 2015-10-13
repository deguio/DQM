#ifndef Container2D_h
#define Container2D_h

/*
 *	file:		Container2D.h
 *	Author:		Viktor Khristenko
 *
 *	Description:
 *		Container to hold TH2D or like
 *
 */

#include "DQM/HcalCommon/interface/Container1D.h"

#include <vector>
#include <string>

namespace hcaldqm
{
	class Container2D : public Container1D
	{
		public:
			Container2D() {}
			Container2D(std::string const& folder, std::string nametitle,
				mapper::MapperType mt, axis::AxisQType xvt=axis::fEnergy, 
				axis::AxisQType yvt=axis::fTime,
				axis::AxisQType zvt=axis::fEntries):
				Container1D(folder, nametitle, mt, xvt, yvt),
				_zaxis(fZaxis, zvt)
			{}
			virtual ~Container2D() {}

			//	redeclare what to override
			virtual void fill(HcalDetId const&);
			virtual void fill(HcalDetId const&, int);
			virtual void fill(HcalDetId const&, double);
			virtual void fill(HcalDetId const&, int, double);
			virtual void fill(HcalDetId const&, double, double);

			virtual void fill(HcalElectronicsId const&);
			virtual void fill(HcalElectronicsId const&, int);
			virtual void fill(HcalElectronicsId const&, double);
			virtual void fill(HcalElectronicsId const&, int, double);
			virtual void fill(HcalElectronicsId const&, double, double);

			//	booking
			virtual void book(DQMStore::IBooker&);

		protected:
			Axis					_zaxis;
	};
}


#endif







