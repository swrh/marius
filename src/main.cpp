#include <err.h>
#include <stdlib.h>

#include <iostream>

#include <boost/program_options.hpp>

using std::cout;
using std::endl;
using std::exception;

namespace po = boost::program_options;

static void
run()
{
}

int
main(int argc, char *argv[])
{
	// Declare the supported options.
	po::options_description desc("Allowed options");
	desc.add_options()
		("help", "produce help message")
	;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.count("help")) {
		cout << desc << endl;
		return EXIT_SUCCESS;
	}

	try {
		run();
	} catch (exception &e) {
		warnx("unhandled exception: %s", e.what());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
