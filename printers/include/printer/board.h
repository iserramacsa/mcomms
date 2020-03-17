#ifndef MACSA_PRINTERS_BOARD_H
#define MACSA_PRINTERS_BOARD_H

#include <string>
#include <map>
#include <vector>
#include <stdint.h>

#include "../tij/datatypes.h"
#include "datecodes.h"
#include "shotmode.h"
#include "inputs.h"
#include "outputs.h"
#include "encoder.h"
#include "cartridge.h"
#include "errors.h"
#include "tij/messagemanager.h"
#include <mutex>
namespace Macsa {
	namespace Printers {
		class TijPrinter;
		class Board {
			public:
#if __cplusplus >= 201103L
				using propertyMap = std::map<std::string, std::string>;
				using propertyPair = std::pair<std::string, std::string>;
				using countersMap = std::map<std::string, int>;
#else
				typedef std::map<std::string, std::string> propertyMap;
				typedef std::pair<std::string, std::string> propertyPair;
				typedef std::map<std::string, int> countersMap;
#endif
			public:
				Board(const int id, TijPrinter* parent);
				Board(const Board& other, TijPrinter* parent = nullptr);
				virtual ~Board();

				int id() const;
				void setParent(TijPrinter* parent);

				virtual std::string type() const;
				virtual void setType(const std::string &type);

				virtual bool autoStart() const;
				virtual void setAutoStart(bool autoStart);

				virtual bool lowLevelOutput() const;
				virtual void setLowLevelOutput(bool lowLevelOutput);

				virtual bool printing() const;
				virtual void setPrinting(bool printing);

				virtual bool enabled() const;
				virtual void setEnabled(bool enabled);

				virtual bool blocked() const;
				virtual void setBlocked(bool blocked);

				virtual std::string currentMessage() const;
				virtual std::string userMessage() const;
				virtual void setUserMessage(const std::string &currentMessage);

				virtual const BCDTable& bcdTable() const;
				virtual BCDMode bcdMode() const;
				virtual uint8_t currentBcdCode() const;
				virtual void setBcdTable(const BCDTable& bcdTable);
				virtual void setBcdMode(const BCDMode &mode);
				virtual void setBcdMode(const nBCDMode &mode);
				virtual void setBcdMode(const std::string &mode);
				virtual void setBcdCurrent(uint8_t current);

				virtual PrinterDir printDirection() const;
				virtual void setPrinterDirection(const PrinterDir &printDirection);
				virtual void setPrinterDirection(const nPrinterDir &printDirection);
				virtual void setPrinterDirection(const std::string &printDirection);

				virtual bool printRotated() const;
				virtual void setPrintRotated(bool printRotated);

				virtual NozzlesCol nozzlesCol() const;
				virtual void setNozzlesCol(const NozzlesCol &nozzlesCol);
				virtual void setNozzlesCol(const nNozzlesCol &nozzlesCol);
				virtual void setNozzlesCol(const std::string &nozzlesCol);

				virtual ShotMode shotMode() const;
				virtual void setShotMode(const ShotMode& shotMode);

				virtual Encoder encoder() const;
				virtual void setEncoder(const Encoder &encoder);

				virtual Photocell photocell() const;
				virtual void setPhotocell(const Photocell& photocell);
				virtual void setPhotocell(const nPhotocell& photocell);
				virtual void setPhotocell(const std::string & photocell);

				virtual countersMap counters() const;
				virtual int counter(const std::string& name) const;
				virtual void setCounters(const countersMap& counters);
				virtual void setCounter(const std::string& name, int value);

				virtual propertyMap statusProperties() const;
				virtual std::string statusProperty(const std::string& name) const;
				virtual void setStatusProperties(const propertyMap& properties);
				virtual void setStatusProperty(const std::string& name, const std::string& value);

				virtual propertyMap configurationProperties() const;
				virtual std::string configurationProperty(const std::string& name) const;
				virtual void setConfigurationProperties(const propertyMap& properties);
				virtual void setConfigurationProperty(const std::string& name, const std::string& value);

				virtual Cartridge cartridge() const;
				virtual void setCartridge(const Cartridge &cartridge);

				virtual std::vector<Input> inputs() const;
				virtual void setInputs(const std::vector<Input>& inputs);
				virtual Input input(unsigned int idx) const;
				virtual void setInput(unsigned int idx, const Input& input);

				virtual std::vector<Output> outputs() const;
				virtual void setOutputs(const std::vector<Output>& outputs);
				virtual Output output(unsigned int idx) const;
				virtual void setOutput(unsigned int idx, const Output& output);

				virtual std::vector<Error> errors() const;
				virtual void setErrors(const std::vector<Error>& errors);
				virtual Error error(unsigned int idx) const;
				virtual void setError(unsigned int idx, const Error& error);

				virtual TijPrinter* printer();
				virtual const TijPrinter* printer() const;

				virtual void clear();

				//Operators
				virtual bool operator == (const Board& other) const {return equal(other);}
				virtual bool operator != (const Board& other) const {return !equal(other);}
				virtual void operator = (const Board& other) { return copy(other);}

			private:
                const int   _id;
				TijPrinter*	_parent;
				std::mutex* _mutex;

				bool			_autostart;
				bool			_lowLvlOutput;
				bool			_printing;
				bool			_enabled;
				bool			_blocked;
				bool			_printRotated;      //Inverted
				std::string		_type;
				MessageManager	_messageManager;
				PrinterDir		_printerDirection;
				NozzlesCol		_nozzlesCol;
				ShotMode		_shotMode;
				Encoder			_encoder;
				Photocell		_photocell;
				Cartridge		_cartridge;
				countersMap		_counters;
				propertyMap		_configProperties;
				propertyMap		_statusProperties;

				std::vector<Input>	_inputs;
				std::vector<Output>	_outputs;
				std::vector<Error>	_errors;
#if __cplusplus >= 201103L
				using itProp = propertyMap::const_iterator;
#else
				typedef propertyMap::const_iterator itProp;
#endif
				bool equal(const Board& other) const;
				void copy(const Board& other);
				void setProperty(std::map<std::string, std::string>&map, const std::string& key, const std::string& value) const;
		};
	}
}

#endif //MACSA_PRINTERS_BOARD_H
