#ifndef Axis_h
#define Axis_h

/*
 *	file:			Axis.h
 *	Author			Viktor Khristenko
 *
 *	Description:
 *		Base Axis Class
 */

#include "DQM/HcalCommon/interface/HcalCommonHeaders.h"
#include "DQM/HcalCommon/interface/Constants.h"

#include <string>
#include <vector>

namespace hcaldqm
{
	using namespace hcaldqm::constants;
	class Container;
	class Container1D;
	class Container2D;
	class ContainerProf1D;
	class ContainerProf2D;
	class ContainerSingle2D;
	class ContainerSingle1D;
	namespace axis
	{
		enum AxisType
		{
			fXaxis = 0,
			fYaxis = 1,
			fZaxis = 2,
			nAxisType = 3
		};
		enum AxisQType
		{
			fValue = 0,
			fCoordinate = 1,
			fFlag = 2,
			nAxisQType = 3
		};

		/*
		 *	Base Class for Axis
		 */
		class Axis
		{
			public:
				friend class hcaldqm::Container;
				friend class hcaldqm::Container1D;
				friend class hcaldqm::Container2D;
				friend class hcaldqm::ContainerProf1D;
				friend class hcaldqm::ContainerProf2D;
				friend class hcaldqm::ContainerSingle2D;
				friend class hcaldqm::ContainerSingle1D;

			public:
				Axis();
				Axis(std::string title,AxisType type, AxisQType qtype, 
					int n, double min, double max, bool log=false);
				virtual ~Axis() {}

				virtual int get(HcalDetId const&) {return 0;}
				virtual int get(HcalElectronicsId const&) {return 0;}
				virtual int get(HcalTrigTowerDetId const&) {return 0;}
				virtual int get(int) {return 0;}
				
			public:
				AxisQType getType() {return _qtype;}
				void setLog(TObject* o)
				{
					if (_log)
						o->SetBit(BIT(FIRST_BIT_TO_USE+_type));
				}
			protected:

				//	some member variables should be public
				int _nbins;
				double _min;
				double _max;
				std::string _title;
				std::vector<std::string> _labels;

				AxisType	_type;
				AxisQType	_qtype;
				bool		_log;
		};
	}
}

#endif