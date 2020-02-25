#include "gtest/gtest.h"
#include "tijprintercontroller.h"

using namespace Macsa;

#define PRINTER_ID		"tijPrinter"
#define PRINTER_ADDR	"127.0.0.1"

class TijControllerUT: public ::testing::Test {
	public:
		TijControllerUT( ) {
			// initialization code here
		}

		void SetUp( ) {
			// code here will execute just before the test ensues
			_controller = new TijController(PRINTER_ID, PRINTER_ADDR);
		}

		void TearDown( ) {
			// code here will be called just after the test completes
			// ok to through exceptions from here if need be
			try {
				delete _controller;
			} catch (std::exception e) {
				std::cout << __PRETTY_FUNCTION__ << " exception: " << e.what() << std::endl;
			}
		}

		~TijControllerUT( )  {
			// cleanup any pending stuff, but no exceptions allowed
		}
		// put in any custom data members that you need
	protected:
		TijController* _controller;
};
///
/// \brief Simple setup teardown test to detect memory leaks on test class
///
TEST_F(TijControllerUT, setupTeardown)
{}

