#ifndef TIJ_EMULATOR_H
#define TIJ_EMULATOR_H

#include "tij/tijprinter.h"

namespace Macsa
{
	namespace Printers
	{
		class TIJEmulator : public TijPrinter
		{
			public:
				TIJEmulator();
				virtual ~TIJEmulator();

			private:
				void init();
				void initBoard(Printers::Board& board);
		};
	}
}

#endif //TIJ_EMULATOR_H
