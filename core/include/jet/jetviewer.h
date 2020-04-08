#ifndef MACSA_MCOMMS_JET_VIEWER_H
#define MACSA_MCOMMS_JET_VIEWER_H

#include "jetcontroller.h"
#include "jetobserver.h"
#include "network/nodeobserver.h"
#include "jet/jetprinter.h"

namespace Macsa {
	namespace MComms {
		class JetViewer : public JetObserver, protected Network::NodeObserver
		{
			public:
				enum class JetPrinterStatus ///Todo: change to smart enum
				{
					DISCONNECTED = -1,
					CONNECTING,
					STOPPED,
					ERROR,
					RUNNING,
					PRINTING
				};

				using countersMap = std::map<unsigned int, unsigned int>;

			public:
				JetViewer(JetController& controller);
				virtual ~JetViewer() override;

				//Files access methods
				std::vector<std::string> printerDrives() const;
				std::vector<std::string> printerDirectories(const std::string& drive) const;
				std::vector<std::string> printerSubdirectories(const std::string& drive, const std::string& directory) const;
				std::vector<std::string> printerFiles(const std::string& drive, const std::string& directory) const;

				const Printers::Drive* printerDrive(const std::string& drive) const;
				const Printers::Directory* printerSubdirectory(const std::string& drive, const std::string& directory) const;
				const Printers::File* printerFile(const::std::string path) const;

				//Ethernet connections
				const Printers::JetEthernet * printerEthernetIface(const std::string& iface) const;
				std::vector<std::string> printerEthernetIfaces() const;

				//Printer base getters
				std::time_t dateTime() const;
				std::string printerType() const;
				JetPrinterStatus printerStatus() const;

				//Versions
				std::string printheadVersion(unsigned int numBoard = 0) const;
				std::string signalsBoardVersion(unsigned int numBoard = 0) const;
				std::map<std::string, std::string> installedLibrariesVersions() const;

				//Jet Status parameters
				int id() const;
				Printers::PrintDirection printDirection() const;
				uint64_t sscc() const;
				bool bitmapInverted() const;
				bool isInError() const;
				Printers::JetPrinter::logsList printerLogs(time_t from, time_t to) const;
				Printers::JetPrinter::logsList printerLogs() const;
				bool printStatus() const;
				Printers::JetPrinter::tanksMap inkTanks() const;
				unsigned int tankLevel(unsigned int id) const;

				//messages manager
				std::string currentMessage() const;
				int currentMessageNum() const;
				std::string currentMessageGroup() const;
				std::vector<std::string> messageGroups() const;
//				std::vector<Message> messages(const std::string& group) const;	//Required??
//				Message message(unsigned int num) const;						//Required??
				countersMap messagesCounters() const;

				//configuration
				bool paused() const;


				//Printhead
				Printers::JetPrinthead printerPrinthead(unsigned int id = 0);
				std::vector<Printers::JetIO> printheadInputs(unsigned int id = 0) const;
				std::vector<Printers::JetIO> signalsBoardInputs(unsigned int id = 0) const;
				std::vector<Printers::JetIO> printerInputs() const;
				Printers::JetIO printerInput(const std::string& id) const;
				//outputs
				std::vector<Printers::JetIO> printerOutputs() const;
				Printers::JetIO printerOutput(const std::string& id) const;

				//Jet Observer callbacks
				virtual void statusChanged() override;
				virtual void configChanged() override;
				virtual void filesListChanged() override;
				virtual void fontsChanged() override;
				virtual void errorsLogsChanged() override;

			private:
				//Node Observer callbacks
				virtual void nodeStatusChanged(const Network::NetworkNode::nNodeStatus& status) override;
				virtual void nodeTimeout() override;

			private:
				JetController& _controller;
				inline const Printers::JetPrinter& jetPrinter() const {return dynamic_cast<const Printers::JetPrinter&>(*(_controller.printer()));}
//				inline const Printers::Board& JetBoard() const {return (*tijprinter().board(0));}
//				inline bool validBoard() const { return (tijprinter().board(0) != nullptr);}
		};
	}
}

#endif //MACSA_MCOMMS_JET_VIEWER_H
