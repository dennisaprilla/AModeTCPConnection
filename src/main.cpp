// core cpp library
#include <iostream>

// dependencies
#include <tclap/CmdLine.h>

// the main class that we will use for streaming
#include "AModeUSConnection.h"

// function for parsing arguments
void commandLineOptions(const int& argc, char** argv,
						std::string& ip, std::string& port, std::string& outputdir,
						int& amodemode, int& amodesamples, int& amodeprobes) {

	// see TCLAP (Templatized C++ Command Line Parser Manual) documentation
	// can be found in: http://tclap.sourceforge.net/manual.html
	try {
		// Define the command line object, and insert a message
		// that describes the program. The "Command description message" 
		// is printed last in the help text. The second argument is the 
		// delimiter (usually space) and the last one is the version number. 
		// The CmdLine object parses the argv array based on the Arg objects
		// that it contains. 
		TCLAP::CmdLine cmd("Command description message", ' ', "1.0");

		// Define a value argument and add it to the command line.
		// A value arg defines a flag and a type of value that it expects,
		// such as "-n Bishop".
		TCLAP::ValueArg<std::string> nameargIP("", "ip", "IP address of A-mode Ultrasound System PC", true, "192.168.0.2", "string");
		TCLAP::ValueArg<std::string> nameargPort("", "port", "Port of A-mode Ultrasound System PC", true, "6340", "string");
		TCLAP::ValueArg<std::string> nameargOutputdir("o", "outputdir", "Output directory to store A-mode data", false, "D:\\amodestream\\log", "string");
		TCLAP::ValueArg<int> nameargAModeMode("m", "mode", "A-Mode data mode. You can choose between raw data or depth data streaming, depends on the configuration you choose from A-mode Ultrasound PC. Specify 0 for raw, 1 for depth.", false, 0, "int");
		TCLAP::ValueArg<int> nameargAModeSamples("n", "samples", "Number of samples of A-Mode Signal. If you want to see deep inside the soft tissue, put bigger value. However, if you put too big, it can affect to streaming speed performance.", false, 1500, "int");
		TCLAP::ValueArg<int> nameargAModeProbes("p", "probes", "Number of probes of A-Mode Signal, depends on the physical setup you have from A-mode Ultrasound machine. Our current setup is 30 probes.", false, 30, "int");

		// Add the argument nameArg to the CmdLine object. The CmdLine object
		// uses this Arg to parse the command line.
		cmd.add(nameargIP);
		cmd.add(nameargPort);
		cmd.add(nameargOutputdir);
		cmd.add(nameargAModeMode);
		cmd.add(nameargAModeSamples);
		cmd.add(nameargAModeProbes);

		// Parse the argv array.
		cmd.parse(argc, argv);

		// Get the value parsed by each arg. 
		ip = nameargIP.getValue();
		port = nameargPort.getValue();
		outputdir = nameargOutputdir.getValue();
		amodemode = nameargAModeMode.getValue();
		amodesamples = nameargAModeSamples.getValue();
		amodeprobes = nameargAModeProbes.getValue();

	}
	catch (TCLAP::ArgException& e)  // catch exceptions
	{
		std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
	}

}

int main(int argc, char** argv)
{
	std::cout << "A-Mode Ultrasound Data Streams" << std::endl;

	// initialize value 
	// (i think i don't need to initialize the value too, because TCLAP also gives
	// default value if the user not specified the arguments.. but just in case)
	std::string ip = "192.168.0.2";
	std::string port = "6340";
	std::string outputdir = "D:\\amodestream\\log";
	int amodemode = 0;
	int amodesamples = 1500;
	int amodeprobes = 30;

	// parse the arguments from command line and store it to our variables
	commandLineOptions(argc, argv, ip, port, outputdir, amodemode, amodesamples, amodeprobes);
	/* uncomment this if you want to see whether the parsings are good or not
	std::cout << "IP address: " << ip << std::endl;
	std::cout << "Port: " << port << std::endl;
	std::cout << "Output Directory: " << outputdir << std::endl;
	std::cout << "AMode Mode: " << amodemode << std::endl;
	std::cout << "AMode Samples: " << amodesamples << std::endl;
	std::cout << "AMode Probes: " << amodeprobes << std::endl;
	*/

	// A-mode Ultrasound
	AModeUSConnection amodeUSConnection(ip, port, amodemode);
	amodeUSConnection.setRecord(true);
	amodeUSConnection.useDataIndex(true);
	amodeUSConnection.setDirectory("D:\\amodestream\\log");

	// The A-mode class supports thread, so that later in the future we can expand this code if we
	// want to combine it with other device
	std::thread threadAMode(std::ref(amodeUSConnection));

	// join "all" threads
	threadAMode.join();


	return 0;
}

