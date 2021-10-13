#include <err.h>
#include <stdlib.h>

#include <iostream>

#include <boost/program_options.hpp>

#include "marius/game.hpp"
#include "marius/exceptions.hpp"
#include "marius/log.hpp"

using std::cout;
using std::endl;
using std::exception;
using std::ostringstream;

namespace po = boost::program_options;

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
		LINFO() << "Initializing game...";
		marius::game game;

		LINFO() << "Running...";
		game.run();

		LINFO() << "Game stopped.";
	} catch (exception &e) {
		ostringstream os;
		os << e.what();
		const boost::stacktrace::stacktrace* st = boost::get_error_info<marius::traced>(e);
		if (st) {
			os << '\n' << *st;
		}
		errx(EXIT_FAILURE, "Unhandled exception: %s", os.str().c_str());
	}

	return EXIT_SUCCESS;
}
