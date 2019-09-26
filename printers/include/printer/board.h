#ifndef MACSA_PRINTERS_BOARD_H
#define MACSA_PRINTERS_BOARD_H

#include <string>
#include <map>
#include <vector>
#include <stdint.h>

#include "datatypes.h"
#include "datecodes.h"
#include "shotmode.h"
#include "bcdtable.h"
#include "inputs.h"
#include "outputs.h"
#include "encoder.h"
#include "cartridge.h"

namespace Macsa {
	namespace Printers {
		class Board {
			public:
				Board(const int id);
				~Board();

				int id() const;

				virtual std::string type() const;
				virtual void setType(const std::string &type);

				virtual bool autoStart() const;
				virtual void setAutoStart(bool autoStart);

				virtual bool lowLevelOutput() const;
				virtual void setLowLevelOutput(bool lowLevelOutput);

				virtual bool enabled() const;
				virtual void setEnabled(bool enabled);

				virtual bool blocked() const;
				virtual void setBlocked(bool blocked);

				virtual std::string currentMessage() const;
				virtual void setCurrentMessage(const std::string &currentMessage);

				virtual BcdTable bcdTable() const;
				virtual void setBcdTable(const BcdTable& bcdTable);

				virtual PrinterDir printerDirection() const;
				virtual void setPrinterDirection(const PrinterDir &printerDirection);
				virtual void setPrinterDirection(const PrinterDir::N &printerDirection);
				virtual void setPrinterDirection(const std::string &printerDirection);

				virtual bool printRotated() const;
				virtual void setPrintRotated(bool printRotated);

				virtual NozzlesCol nozzlesCol() const;
				virtual void setNozzlesCol(const NozzlesCol &nozzlesCol);
				virtual void setNozzlesCol(const NozzlesCol::N &nozzlesCol);
				virtual void setNozzlesCol(const std::string &nozzlesCol);

				virtual ShotMode shotMode() const;
				virtual void setShotMode(const ShotMode& shotMode);

				virtual Encoder encoder() const;
				virtual void setEncoder(const Encoder &encoder);

				virtual Photocell photocell() const;
				virtual void setPhotocell(const Photocell& photocell);
				virtual void setPhotocell(const Photocell::N& photocell);
				virtual void setPhotocell(const std::string & photocell);

				virtual std::map<std::string, std::string> properties() const;
				virtual std::string property(const std::string& name) const;
				virtual void setProperties(const std::map<std::string, std::string>& properties);
				virtual void setProperty(const std::string& name, const std::string& value);

				virtual Cartridge cartridge() const;
				virtual void setCartridge(const Cartridge &cartridge);

				virtual DateCodes dateCodes() const;
				virtual void setDateCodes(const DateCodes &dateCodes);

				virtual std::vector<Input> inputs() const;
				virtual void setInputs(const std::vector<Input>& inputs);
				virtual Input input(unsigned int idx) const;
				virtual void setInput(unsigned int idx, const Input& input);

				virtual std::vector<Output> outputs() const;
				virtual void setOutputs(const std::vector<Output>& inputs);
				virtual Output output(unsigned int idx) const;
				virtual void setOutput(unsigned int idx, const Output& output);

				//Operators
				bool operator == (const Board& other) const {return equal(other);}
				bool operator != (const Board& other) const {return !equal(other);}

			private:
				const int	_id;
				std::string	_type;
				bool		_autostart;
				bool		_lowLvlOutput;
				bool		_enabled;
				bool		_blocked;
				std::string	_currentMessage;
				PrinterDir	_printerDirection;
				BcdTable	_bcdTable;
				bool        _printRotated;      //Inverted
				NozzlesCol	_nozzlesCol;
				ShotMode	_shotMode;
				Encoder		_encoder;
				Photocell	_photocell;
				std::map<std::string, std::string> _properties;
				Cartridge	_cartridge;
				DateCodes	_dateCodes;

				std::vector<Input> _inputs;
				std::vector<Output> _outputs;

				using itProp = std::map<std::string, std::string>::const_iterator;
				bool equal(const Board& other) const;
				bool checkProperties(const std::map<std::string, std::string> other) const;
				template<class T>
				bool isSameVector(const std::vector<T> a, const std::vector<T> b) const;
		};
	}
}

#endif
