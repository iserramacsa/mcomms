#ifndef PRINTER_CONFIG_H
#define PRINTER_CONFIG_H

#include <string>
#include <map>
#include <vector>
#include <stdint.h>

#include "printerTypes.h"
#include "datecodes.h"
#include "shotmode.h"
#include "bcdtable.h"
#include "inputs.h"
#include "outputs.h"

// Nozzles columns definition
#define NOZZLES_COL_A       "COL_A"
#define NOZZLES_COL_B       "COL_B"
#define NOZZLES_COL_BOTH    "BOTH"

namespace Macsa {
	namespace Printers {
		class Configuration
		{
			public:
				Configuration();
				virtual ~Configuration();

				virtual bool autostart() const;
				virtual void setAutostart(bool autostart);

				virtual bool enabled() const;
				virtual void setEnabled(bool enabled);

				virtual bool blocked() const;
				virtual void setBlocked(bool blocked);

				virtual std::string currentMessage() const;
				virtual void setCurrentMessage(const std::string &currentMessage);

				virtual uint8_t bcdMode() const;
				virtual std::string bcdModeStr() const;
				virtual void setBcdMode(const std::string &bcdMode);
				virtual void setBcdMode(const BcdTable::BCDMode_n &bcdMode);
				virtual std::string bcdMessage(uint8_t code) const;
				virtual void setBcdMessage(const uint8_t &code, const std::string& message);

				virtual PrinterDir_n printerDirection() const;
				virtual std::string printerDirectionStr() const;
				virtual void setPrinterDirection(const PrinterDir_n &printerDirection);
				virtual void setPrinterDirection(const std::string &printerDirection);

				virtual bool printRotated() const;
				virtual void setPrintRotated(bool printRotated);

				virtual NozzlesCol_n nozzlesCol() const;
				virtual std::string nozzlesColStr() const;
				virtual void setNozzlesCol(const NozzlesCol_n &nozzlesCol);
				virtual void setNozzlesCol(const std::string &nozzlesCol);

				virtual ShotMode::ShotMode_n shotMode() const;
//				virtual void setShotMode(ShotMode::ShotMode_n mode);		//TODO
				virtual uint16_t shotNumPrints();
				virtual std::vector<unsigned int> shotDelays() const;

				virtual EncoderMode_n encoderMode() const;
				virtual double encoderFixedSpeed() const;
				virtual double encoderResolution() const;
				virtual double encoderWheelDiameter() const;
				virtual void setEncoderMode(EncoderMode_n mode);
				virtual void setEncoderFixedSpeed(double speed);
				virtual void setEncoderResolution(double resolution);
				virtual void setEncoderWheelDiameter(double diameter);

				virtual Photocell_n photocell() const;
				virtual void setPhotocell(const Photocell_n &photocell);

				//Operators
				bool operator == (const Configuration& other){return equal(other);}
				bool operator == (const Configuration* other){return (other != nullptr && equal(*other));}
				bool operator != (const Configuration& other){return !equal(other);}
				bool operator != (const Configuration* other){return (other != nullptr && !equal(*other));}



			protected:
				bool            _autostart;
				bool            _enabled;
				bool            _blocked;
				std::string     _currentMessage;
				BcdTable        _bcd;
				PrinterDir_n	_printerDirection;
				bool            _printRotated;      //Inverted
				NozzlesCol_n    _nozzlesCol;
				ShotMode        _shotMode;
				DateCodes		_dateCodes;
				Encoder_t		_encoder;
				Photocell_n		_photocell;
				std::vector<Inputs> _inputs;
				std::vector<Outputs> _outputs;
				std::map<std::string, std::string> _properties;

				bool equal(const Configuration& other);
		};
	}
}

#endif
