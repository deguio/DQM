#ifndef ValueQuantity_h
#define ValueQuantity_h

#include "DQM/HcalCommon/interface/Quantity.h"

namespace hcaldqm
{
	namespace quantity
	{
		enum ValueQuantityType
		{
			fN = 0,
			fEvents = 1,
			fEnergy = 2,
			fTiming_ns = 3,
			fADC_128 = 4,
			fADC_5 = 5,
			fADC_15 = 6,
			ffC_10000 = 7,
			ffC_1000 = 8,
			ffC_3000 = 9,
			fTiming_TS = 10,
			fTiming_TS200 = 11,
			fLS = 12,
			fEt_256 = 13,
			fEt_128 = 14,
			fFG = 15,
			fRatio = 16,
			fDigiSize = 17,
			fAroundZero = 18,
			fRatio2 = 19,
			fdEtRatio = 20,
			fSumdEt = 21,
			fTiming_20TS = 22,

			fQIE10ADC_256 = 23,
			fQIE10TDC_64 = 24,
			fQIE10TDC_16 = 25,
			fDiffAbs = 26,
			nValueQuantityType = 27
		};
		std::string const name_value[nValueQuantityType] = {
			"N", "Events", "Energy", "Timing", "ADC", "ADC", "ADC",
			"fC", "fC", "fC", "Timing", "Timing", "LS", "Et", "Et",
			"FG", "Ratio", "DigiSize", "Q", "Ratio",
			"dEtRatio", "SumdEt", "Timing", "ADC", "TDC", "TDC",
			"Q"
		};
		double const min_value[nValueQuantityType] = {
			0, 0, 0, -50, -0.5, -0.5, -0.5, 0, 0, 0, -0.5, 0, .5, 0,
			0, 0, 0, -0.5, -1, 0, 0, 0, -0.5, -0.5, -0.5, -0.5,
			0, 
		};
		double const max_value[nValueQuantityType] = {
			1000, 1000, 200, 50, 127.5, 5, 15, 10000, 1000, 3000,
			9.5, 9.5, 4000.5, 255.5, 255.5, 2, 1, 20.5, 1, 1, 
			1, 1000, 9.5, 255.5, 63.5, 15.5, 1
		};
		int const nbins_value[nValueQuantityType] = {
			200, 200, 100, 200, 128, 100, 300, 1000, 200, 600, 
			10, 200, 4000, 256, 128, 2, 100, 20, 100, 100, 100, 100, 10,
			256, 64, 16, 200
		};

		class ValueQuantity : public Quantity
		{
			public:
				ValueQuantity() {}
				ValueQuantity(ValueQuantityType type, bool isLog=false) :
					Quantity(name_value[type], isLog), _type(type)
				{}
				virtual ~ValueQuantity() {}

				//	get Value to be overriden
				virtual int getValue(int x)
				{return x;}
				virtual double getValue(double x)
				{return x;}

				//	standard properties
				virtual QuantityType type() {return fValueQuantity;}
				virtual int nbins() {return nbins_value[_type];}
				virtual double min() {return min_value[_type];}
				virtual double max() {return max_value[_type];}

				virtual void setBits(TObject* o)
				{Quantity::setBits(o);setLS(o);}
				virtual void setLS(TObject* o)
				{
					if (_type==fLS)
						o->SetBit(BIT(BIT_OFFSET+BIT_AXIS_LS));
				}

			protected:
				ValueQuantityType _type;
		};

		class EventNumber : public ValueQuantity
		{
			public:
				EventNumber() {}
				EventNumber(int nevents) :
					ValueQuantity(fN), _nevents(nevents)
				{}
				virtual ~EventNumber() {}

				virtual int nbins() {return _nevents;}
				virtual double min() {return 0.5;}
				virtual double max() {return _nevents+0.5;}

			protected:
				int _nevents;
		};
	}
}

#endif
