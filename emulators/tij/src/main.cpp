#include <iostream>
#include <getopt.h>

#include "clientmanager.h"

using namespace std;

#define PORT_OPTION	'p'
#define OPTIONS "p:"

#define DEFAULT_TIJ_MPORT 9991

static void printHelp()
{

}

int main(int argc, char* argv[])
{

	printHelp();

	uint16_t port = DEFAULT_TIJ_MPORT;
	int index;
	int c;

	opterr = 0;

	while ((c = getopt (argc, argv, OPTIONS)) != -1) {
		switch (c)
		{
			case PORT_OPTION:
				port = optarg ? static_cast<uint16_t>(atoi(optarg)) : DEFAULT_TIJ_MPORT;
				break;
			case '?':
			  if (optopt == PORT_OPTION)
				  cerr << "Option -" << static_cast<char>(optopt) << " requires an argument." << endl;
			  else if (isprint (optopt))
				  cerr << "Unknown option -" << static_cast<char>(optopt) << "." << endl;
			  else
				  cerr << "Unknown option character \\x" << hex << optopt << "." << endl;
			  return 1;
			default:
			  abort ();
		}
	}
	if (optind < argc) {
		for (index = optind; index < argc; index++)
			cout << "Non-option argument " << argv[index] << endl;
		return 1;
	}
	if (port == 0){
		cout << "Invalid port" << endl;
		return 1;
	}

	cout << "#################################" << endl;
	cout << "    TIJEmulator version " << EMULATOR_VERSION_STR << endl;
	cout << "#################################" << endl << endl;
	cout << "Emulator configured at port: " << port << endl;

	ClientManager manager;
	if (manager.initServer(port)) {
		manager.run(false);
	}
	else {
		cout << "Unable tot init server" << endl;
	}
	return 0;
}
