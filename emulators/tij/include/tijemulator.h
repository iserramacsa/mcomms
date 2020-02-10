#ifndef TIJ_EMULATOR_H
#define TIJ_EMULATOR_H

#include "tij/tijprinter.h"

namespace Macsa
{
	namespace Printers
	{
		class TIJEmulator : public TIJPrinter
		{
			public:
				TIJEmulator();
				virtual ~TIJEmulator();

			private:
				void init();
		};
	}
}

#endif //TIJ_EMULATOR_H
