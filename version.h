#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "26";
	static const char MONTH[] = "01";
	static const char YEAR[] = "2010";
	static const double UBUNTU_VERSION_STYLE = 10.01;
	
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long MAJOR = 0;
	static const long MINOR = 1;
	static const long BUILD = 5;
	static const long REVISION = 26;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 21;
	#define RC_FILEVERSION 0,1,5,26
	#define RC_FILEVERSION_STRING "0, 1, 5, 26\0"
	static const char FULLVERSION_STRING[] = "0.1.5.26";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 3;
	

}
#endif //VERSION_h
