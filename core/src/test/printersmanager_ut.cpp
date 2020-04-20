#include "gtest/gtest.h"
#include "printersmanager.h"

using namespace Macsa;
using namespace Macsa::MComms;
//using ::testing::Return; // include gmock


class PrintersManagerUT: public ::testing::Test {
	public:
		PrintersManagerUT( ) {
			// initialization code here
		}

		void SetUp( ) {
			// code here will execute just before the test ensues
			_manager = new PrintersManager();
		}

		void TearDown( ) {
			// code here will be called just after the test completes
			// ok to through exceptions from here if need be
			try {
				delete _manager;
			} catch (std::exception e) {
				std::cout << __PRETTY_FUNCTION__ << " exception: " << e.what() << std::endl;
			}
		}

		~PrintersManagerUT( )  {
			// cleanup any pending stuff, but no exceptions allowed
		}
		// put in any custom data members that you need
	protected:
		PrintersManager* _manager;
};
///
/// \brief Simple setup teardown test to detect memory leaks on test class
///
TEST_F(PrintersManagerUT, setupTeardown)
{}

