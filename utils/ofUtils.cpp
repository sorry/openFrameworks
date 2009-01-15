#include "ofUtils.h"
#include "ofImage.h"

static bool enableDataPath = true;

//--------------------------------------------------
// not for the public, just for glutGlue -> ofUtil comm.
static int numFrames = 0;
void setFrameNum(int num){
	numFrames = num;
}

//--------------------------------------
int ofGetFrameNum(){
	return numFrames;
}

//--------------------------------------
int ofGetElapsedTimeMillis(){
	return (int)(glutGet(GLUT_ELAPSED_TIME));
}

//--------------------------------------
float ofGetElapsedTimef(){
	return (float)(glutGet(GLUT_ELAPSED_TIME))/1000.0f;
}

//--------------------------------------------------
int ofGetSeconds(){
	time_t 	curr;
	tm 		local;
	time(&curr);
	local	=*(localtime(&curr));
	return local.tm_sec;
}

//--------------------------------------------------
int ofGetMinutes(){
	time_t 	curr;
	tm 		local;
	time(&curr);
	local	=*(localtime(&curr));
	return local.tm_min;
}

//--------------------------------------------------
int ofGetHours(){
	time_t 	curr;
	tm 		local;
	time(&curr);
	local	=*(localtime(&curr));
	return local.tm_hour;
}

//--------------------------------------------------
int ofGetYear(){
  time_t    curr;
  tm       local;
  time(&curr);
  local   =*(localtime(&curr));
  int year = local.tm_year + 1900;
  return year;
}

//--------------------------------------------------
int ofGetMonth(){
  time_t    curr;
  tm       local;
  time(&curr);
  local   =*(localtime(&curr));
  int month = local.tm_mon + 1;
  return month;
}

//--------------------------------------------------
int ofGetDay(){
  time_t    curr;
  tm       local;
  time(&curr);
  local   =*(localtime(&curr));
  return local.tm_mday;
}

//--------------------------------------------------
int ofGetWeekday(){
  time_t    curr;
  tm       local;
  time(&curr);
  local   =*(localtime(&curr));
  return local.tm_wday;
}

//--------------------------------------------------
void ofEnableDataPath(){
	enableDataPath = true;
}

//--------------------------------------------------
void ofDisableDataPath(){
	enableDataPath = false;
}

//--------------------------------------------------
string ofToDataPath(string path){
	if( enableDataPath ){
		#ifdef TARGET_OSX
			if(path.substr(0,1) != "/" && path.substr(0,14) != "../../../data/") path = "../../../data/"+path;
		#else
			if(path.substr(0,1) != "/" && path.substr(0,5) != "data/") path = "data/"+path;
		#endif
	}
	return path;
}

//--------------------------------------------------
string ofToString(double value, int precision){
	stringstream sstr;
	sstr << fixed << setprecision(precision) << value;
	return sstr.str();
}

//--------------------------------------------------
string ofToString(int value){
	stringstream sstr;
	sstr << value;
	return sstr.str();
}



//--------------------------------------------------
void ofLaunchBrowser(string url){

	// http://support.microsoft.com/kb/224816

	//make sure it is a properly formatted url
	if(url.substr(0,7) != "http://"){
		ofLog(OF_WARNING, "ofLaunchBrowser: url must begin http://\n");
		return;
	}

	//----------------------------
	#ifdef TARGET_WIN32
	//----------------------------

		#if (_MSC_VER)
		// microsoft visual studio yaks about strings, wide chars, unicode, etc
		ShellExecuteA(NULL, "open", url.c_str(),
                NULL, NULL, SW_SHOWNORMAL);
		#else
		ShellExecute(NULL, "open", url.c_str(),
                NULL, NULL, SW_SHOWNORMAL);
		#endif

	//----------------------------
	#endif
	//----------------------------

	//--------------------------------------
	#ifdef TARGET_OSX
	//--------------------------------------
		// ok gotta be a better way then this,
		// this is what I found...
		string commandStr = "open "+url;
		system(commandStr.c_str());
	//----------------------------
	#endif
	//----------------------------

}

//--------------------------------------------------
string ofGetVersionInfo(){
	string version;
	stringstream sstr;
	sstr << "of version: " << OF_VERSION << endl;
	return sstr.str();
}

//---- new to 006
//from the forums http://www.openframeworks.cc/forum/viewtopic.php?t=1413

//--------------------------------------------------
void ofSaveScreen(string filename) { 
   ofImage screen; 
   screen.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR); 
   screen.grabScreen(0, 0, ofGetWidth(), ofGetHeight()); 
   screen.saveImage(filename); 
} 

//--------------------------------------------------
int saveImageCounter = 0; 
void ofSaveFrame(){ 
   string fileName = ofToString(saveImageCounter) + ".png";   
   ofSaveScreen(fileName);
   saveImageCounter++;
} 

//levels are currently:
// see ofConstants.h
// OF_NOTICE
// OF_WARNING
// OF_ERROR
// OF_FATAL_ERROR

//--------------------------------------------------
void ofSetLogLevel(int logLevel){
	currentLogLevel = logLevel;
}

//--------------------------------------------------
void ofLog(int logLevel, string message){
	if(logLevel >= currentLogLevel){
		if(logLevel == OF_NOTICE){
			printf("OF_NOTICE: ");
		}else if(logLevel == OF_WARNING){
			printf("OF_WARNING: ");
		}
		else if(logLevel == OF_ERROR){
			printf("OF_ERROR: ");
		}
		else if(logLevel == OF_FATAL_ERROR){
			printf("OF_FATAL_ERROR: ");
		}
		printf(message.c_str());
	}
}

//--------------------------------------------------
void ofLog(int logLevel, const char* format, ...){
	//thanks stefan!
	//http://www.ozzu.com/cpp-tutorials/tutorial-writing-custom-printf-wrapper-function-t89166.html
	
	if(logLevel >= currentLogLevel){
		va_list args;
		va_start( args, format );
		if(logLevel == OF_NOTICE){
			printf("OF_NOTICE: ");
		}else if(logLevel == OF_WARNING){
			printf("OF_WARNING: ");
		}
		else if(logLevel == OF_ERROR){
			printf("OF_ERROR: ");
		}
		else if(logLevel == OF_FATAL_ERROR){
			printf("OF_FATAL_ERROR: ");
		}
		vprintf( format, args );
		va_end( args );		
	}
}

//for setting console color
//doesn't work in the xcode console - do we need this?
//works fine on the terminal though - not much use

//--------------------------------------------------
void ofSetConsoleColor(int color){
	#ifdef TARGET_WIN32
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	#else
		printf("\033[%im",  color);
	#endif
}

//--------------------------------------------------
void ofRestoreConsoleColor(){
	#ifdef TARGET_WIN32
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), OF_CONSOLE_COLOR_RESTORE);
	#else
		printf("\033[%im",  OF_CONSOLE_COLOR_RESTORE);
	#endif
}






