/******************************************************************************************
*
* Copyright 2016 KigKrazy
* 
* NOTE:文件为boost::program_options的使用用DEMO
* 
* 项目地址：https://git.oschina.net/KigKrazy/s_lib.git
*
* 使用注意：
*	1.请先在工程中配置好boost目录
******************************************************************************************/

#include <boost/program_options.hpp>
namespace po = boost::program_options;
#include <iostream>
#include <iterator>
using namespace std;

int main(int ac, char* av[])
{
	try {

		po::options_description desc("Allowed options");
		desc.add_options()
			("help,h", "produce help message")
			("compression", po::value<double>(), "set compression level")
			("include-path,I", po::value<std::string>(), "set path")
			("debugflag,D", po::value<bool>(), "set file")
			;

		po::variables_map vm;        
		po::store(po::parse_command_line(ac, av, desc), vm);
		po::notify(vm);

		if (vm.count("help")) {
			cout << desc << "\n";
			//return 0;
		}

		if (vm.count("compression")) {
			cout << "Compression level was set to " 
				<< vm["compression"].as<double>() << ".\n";
		} else {
			cout << "Compression level was not set.\n";
		}

		if (vm.count("include-path")) {
			cout << "include-path are :  " 
				<< vm["include-path"].as<std::string>() << ".\n";
		} else {
			cout << "include-path  was not set.\n";
		}


		if (vm.count("debugflag")) {
			cout << "debugflag are : " 
				<< vm["debugflag"].as<bool>() << ".\n";
		} else {
			cout << "debugflag was not set.\n";
		}
	}
	catch(exception& e) {
		cerr << "error: " << e.what() << "\n";
		return 1;
	}
	catch(...) {
		cerr << "Exception of unknown type!\n";
	}
	system("pause");
	return 0;
}
