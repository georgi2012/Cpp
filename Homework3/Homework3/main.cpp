#include "FileComparer.h"


int main(int argc, char* argv[]) {
	if (argc > 3) {
		std::cerr << "Too many command line arguments.\nPlease, input the 2 file paths directories and quote if whitespaces exist.\n";
		return -1;
	}
	else if (argc < 3) {
		std::cerr << "Too few command line arguments.\nPlease, input the 2 file paths directories and quote if whitespaces exist.\n";
		return -1;
	}
	
	FileComparer fc;
	try {
		fc.analizeFileDataFor(argv[1], argv[2]);
	}
	catch (const std::bad_alloc&) {
		std::cerr << "Error: There was not enough memory to execute the operation." << std::endl;
	}
	catch (const std::runtime_error& e) {
		std::cerr <<"Error: "<< e.what()<<std::endl;
	}
	catch (const std::logic_error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	catch (...) {
		std::cerr << "Error: Unexpected problem occured and operation could not be completed.\n";
	}

}



