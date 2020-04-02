#include "gtest/gtest.h"
#include "tijmonitor.h"

using namespace Macsa;
using namespace Macsa::MComms;
//using ::testing::Return;


class PrinterMonitorUT: public ::testing::Test {
	public:
		PrinterMonitorUT( ) {
			// initialization code here
		}

		void SetUp( ) {
			// code here will execute just before the test ensues
		}

		void TearDown( ) {
			// code here will be called just after the test completes
			// ok to through exceptions from here if need be
			try {
			} catch (std::exception e) {
				std::cout << __PRETTY_FUNCTION__ << " exception: " << e.what() << std::endl;
			}
		}

		~PrinterMonitorUT( )  {
			// cleanup any pending stuff, but no exceptions allowed
		}
		// put in any custom data members that you need
	protected:
		TijMonitor* monitor;
};
///
/// \brief Simple setup teardown test to detect memory leaks on test class
///
TEST_F(PrinterMonitorUT, setupTeardown)
{

}

