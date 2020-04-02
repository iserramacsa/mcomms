#include "gtest/gtest.h"
#include "jet/jetcontroller.h"

using namespace Macsa;
using namespace Macsa::MComms;

#define PRINTER_ID		"JetPrinter"
#define PRINTER_ADDR	"127.0.0.1"

class JetControllerUT: public ::testing::Test {
	public:
		JetControllerUT( ) {
			// initialization code here
		}

		void SetUp( ) {
			// code here will execute just before the test ensues
			_controller = new JetController(PRINTER_ID, PRINTER_ADDR);
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

		~JetControllerUT( )  {
			// cleanup any pending stuff, but no exceptions allowed
		}
		// put in any custom data members that you need
	protected:
		JetController* _controller;
};
///
/// \brief Simple setup teardown test to detect memory leaks on test class
///
TEST_F(JetControllerUT, setupTeardown)
{}

