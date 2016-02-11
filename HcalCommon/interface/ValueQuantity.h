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

			fRatio_0to2 = 27,
			fN_to3000 = 28,
			nValueQuantityType = 29
		};
		std::string const name_value[nValueQuantityType] = {
			"N", "Events", "Energy", "Timing", "ADC", "ADC", "ADC",
			"fC", "fC", "fC", "Timing", "Timing", "LS", "Et", "Et",
			"FG", "Ratio", "DigiSize", "Q", "Ratio",
			"dEtRatio", "SumdEt", "Timing", "ADC", "TDC", "TDC",
			"Q", "Ratio", "N",
		};
		double const min_value[nValueQuantityType] = {
			0, 0, 0, -50, -0.5, -0.5, -0.5, 0, 0, 0, -0.5, 0, .5, 0,
			0, 0, 0, -0.5, -1, 0.5, 0, 0, -0.5, -0.5, -0.5, -0.5,
			0, 0, 0,
		};
		double const max_value[nValueQuantityType] = {
			1000, 1000, 200, 50, 127.5, 5, 15, 10000, 1000, 3000,
			9.5, 9.5, 4000.5, 255.5, 255.5, 2, 1, 20.5, 1, 1.5, 
			1, 1000, 9.5, 255.5, 63.5, 15.5, 1, 2, 3000
		};
		int const nbins_value[nValueQuantityType] = {
			200, 200, 100, 200, 128, 100, 300, 1000, 200, 600, 
			10, 200, 4000, 256, 128, 2, 100, 20, 100, 100, 100, 100, 10,
			256, 64, 16, 200, 100, 3000
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

		class FlagQuantity : public ValueQuantity
		{
			public:
				FlagQuantity() {}
				FlagQuantity(std::vector<int> const& flags, 
					std::vector<std::string> const& names) :
					_flags(flags), _names(names)
				{}
				virtual ~FlagQuantity() {}

				virtual int nbins() {return _flags.size();}
				virtual double min() {return 0;}
				virtual double max() {return _flags.size();}
				virtual std::vector<std::string> getLabels()
				{return _names;}
				virtual int getValue(int f) {return f;}
				virtual uint32_t getBin(int f) {return this->getValue(f)+1;}

			protected:
				std::vector<int>		 _flags;
				std::vector<std::string> _names;
		};

		class RunNumber : public ValueQuantity
		{
			public:
				RunNumber() {}
				RunNumber(std::vector<int> runs) :
					_runs(runs) 
				{}
				virtual ~RunNumber() {}

				virtual int nbins() {return _runs.size();}
				virtual double min() {return 0;}
				virtual double max() {return _runs.size();}
				virtual std::vector<std::string> getLabels()
				{
					char name[10];
					std::vector<std::string> labels;
					for (uint32_t i=0; i<_runs.size(); i++)
					{
						sprintf(name, "%d", _runs[i]);
						labels.push_back(name);
					}
					return labels;
				}
				virtual int getValue(int run)
				{
					int ir = -1;
					for (uint32_t i=0; i<_runs.size(); i++)
						if (_runs[i]==run)
						{
							ir = (int)i;
							break;
						}

					if (ir==-1)
						throw cms::Exception("HCALDQM")
							<< "run number doens't exist " << run; 

					return ir;
				}

				virtual uint32_t getBin(int run)
				{
					return (this->getValue(run)+1);
				}

			protected:
				std::vector<int> _runs;
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
