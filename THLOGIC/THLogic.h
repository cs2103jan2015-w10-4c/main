
#ifndef THLOGIC_H
#define THLOGIC_H

#include "THParser.h"
#include "THCommand.h"
#include "THTask.h"
#include "THExecutor.h"
#include "THDisplay.h"
#include "THUtility.h"
#include "THCommandInterpreter.h"
#include "THLogging.h"


// This class serves to retrieve userinput from UI and analyse
// the input by using THParser and THCommandInterpreter in order 
// to facilitate the execution by THExecutor to fullfill the user command.
// Upon declaration, THLogic will retrieve previous tasks 
// saved through openFile method provided by THExecutor. 
class THLogic {
public:

	THLogic();

	void      runInput  (std::string, THUtility::PageType);
	THDisplay getDisplay();

private:
     
	THParser             _parser;
	THExecutor           _executor;
	THDisplay            _display;
	THCommandInterpreter _commandInterpreter;
	
	void executeCommand(THCommand, THUtility::PageType);
	
	static const int         ERROR_INDEX;
	static const std::string ADD_LOG;         
    static const std::string EDIT_LOG;          
    static const std::string DELETE_LOG;        
    static const std::string DELETEALL_LOG;      
    static const std::string SEARCH_LOG;         
    static const std::string DONE_LOG;           
    static const std::string UNDONE_LOG;         
    static const std::string VIEWALL_LOG;        
    static const std::string VIEWTIMED_LOG;      
    static const std::string VIEWFLOATING_LOG;   
    static const std::string VIEWDONE_LOG;       
    static const std::string VIEWUNDONE_LOG;     
    static const std::string VIEWDEADLINE_LOG;  
    static const std::string VIEWOVERDUE_LOG ;  
    static const std::string VIEWTODAY_LOG; 
    static const std::string UNDO_LOG;      
    static const std::string REDO_LOG;       
    static const std::string REFRESH_LOG;      
    static const std::string EXIT_LOG;

};
#endif