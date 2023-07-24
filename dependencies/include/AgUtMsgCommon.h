/******************************************************************************/
/*****         Copyright 1997-2001, Analytical Graphics, Inc.             *****/
/******************************************************************************/

#ifndef AGUTMSGCOMMON_H
#define AGUTMSGCOMMON_H 1

#if defined (AGCONNECT) && !defined(AGTYPES_H)
#define AgTUInt unsigned int
#define AgTInt int
#define AgTBool int
#define AgTChar char
#define AgTVoid void
#define _T(x) x
#endif

#include <stdarg.h>

#if defined(__cplusplus)
extern "C" {
#endif

#if !defined (AgCFalse)
#if !defined (FALSE)
#define AgCFalse            0
#else
#define AgCFalse            FALSE
#endif
#endif

#if !defined (AgCTrue)
#if !defined (TRUE)
#define AgCTrue             1
#else
#define AgCTrue             TRUE
#endif
#endif

/******************************************************************************
 * Grouping: AgUtMsgCommon
 * 
 * GroupDescription: Common Utility Message Operations
 * 
 * Synopsis: #include "AgUtMsgCommon.h"
 *
 * Introduction: AgUtMsgCommon provides constants, macros and functions to 
 *               support user configurable message reporting. Valid
 *               message levels include debug, informational, warnings
 *               and alarms. Individual callback functions can be 
 *               registered for each message type. 
 ******************************************************************************/

/******************************************************************************
 * Function_Type: AgTMessageFunc
 *
 * Description: Messaging function type
 *
 ******************************************************************************/

typedef AgTVoid 
(*AgTMessageFunc)( 
    AgTInt                    msgType, 
    AgTBool                   waitFlag, 
    AgTInt                    displayID, 
    AgTInt                    errorCode, 
    const AgTChar            *sourceFile,
    AgTInt                    lineNo, 
    const AgTChar            *message 
 );

/******************************************************************************
 * Constants:   General Messaging Constants
 *
 * Description: This constant represents the maximum message length supported
 *              by the AgUtMsg functions.
 * Private:
 ******************************************************************************/

#define AgCMsgMaxMsgLen        2048

/******************************************************************************
 * Constants:   Message Type Constants
 *
 * Description: These constants define the valid values for the msgType parameter
 *               of the AgUtMsg function. Additionally, the values can be assigned
 *               to the AEAgMsgVerbose External variable to specify which levels of
 *               messages are displayed in the message log.
 * Private:
 ******************************************************************************/

#define    AgCMsgNone            -1
#define    AgCMsgDebug            0
#define    AgCMsgInfo             1
#define    AgCMsgForceInfo        2
#define    AgCMsgWarning          3
#define    AgCMsgAlarm            4

typedef enum
{
    AgEMsgDebug = AgCMsgDebug,
    AgEMsgInfo,
    AgEMsgForceInfo,
    AgEMsgWarning,
    AgEMsgAlarm

}  AgTUtMsgType;

/******************************************************************************
 * Constants:   Message WaitFlag Constants
 *
 * Description: These constants define the valid values for the waitFlag parameter
 *               of the AgUtMsg function. 
 * Private:
 ******************************************************************************/

#define AgCMsgNoWait          AgCFalse
#define AgCMsgWait            AgCTrue

/******************************************************************************
 * Constants:   Message DisplayID Constants
 *
 * Description: These constants define the valid values for the displayID parameter
 *               of the AgUtMsg function. 
 * Private:
 ******************************************************************************/

#define AgCMsgDispAll           -1
#define AgCMsgDispDefault        0
#define AgCMsgDispMsgWin         1
#define AgCMsgDispStatusBar		 2
#define AgCMsgDispStatusBarOnly	 3


/******************************************************************************
 * Constants:   Set Message Option Constants
 *
 * Description: These constants define the value to assign to the setOption
 *              parameter of the AgUtMsgSetMsgFunc() function. 
 *
 * Private:
 ******************************************************************************/

#define AgCMsgReplace        0
#define AgCMsgAdd            1
#define AgCMsgRemove         2

/******************************************************************************
 * Constants:   Message Error Code Constants
 *
 * Description: This constant defines the value to assign to the errorCode parameter
 *               of the AgUtMsg function when no error code is being supplied.
 * Private:
 ******************************************************************************/

#define AgCMsgNoErrorCode        0

/******************************************************************************
 * Constants:   Batched Message Name Constants
 *
 * Description: These constants are used to group messages.
 * Private:
 ******************************************************************************/

#define AgCMsgInterplanetaryBatch   _T("Interplanetary")

/******************************************************************************
 * Constants:   File Constants
 *
 * Description: This constant is defined to insert the file name and source
 *              line number for convenient use with the AgUtMsg
 *              function.
 * Private:
 ******************************************************************************/

#if (defined AGCONNECT) && !(defined _UNICODE)
#define AgCMSourceLine __FILE__,__LINE__
#else
#define AgCMSourceLine __TFILE__,__LINE__
#endif

/******************************************************************************
 * Function:    AgUtMsgSetMsgFunc
 *
 * Description: sets the message function for a display ID. The setOption 
 *              parameter is checked to determine whether to replace, add or
 *              _tremove the message function associated with the displayID. If
 *              add or replace, the message function is set to messageFunc
 *              (function to be called when a message of the specified 
 *              displayID type generated).
 *
 * Diagnostics: If unsuccessful, the function returns, AgCError; otherwise,
 *              AgCNoError is returned.        
 ******************************************************************************/

AgTInt
AgUtMsgSetMsgFunc( 
    AgTInt                    setOption, 
    AgTInt                    displayID, 
    AgTMessageFunc            messageFunc 
);

/******************************************************************************
 * Function:    AgUtMsgReserveBuffer
 *
 * Description: allows the user to specify the largest buffer that could be 
 *              generated from the format statement passed in to AgUtMsg. 
 *              This allows AgUtMsg to process the format without serious
 *              memory over-write errors. The default buffer size is 
 *              AgCMsgMaxMsgLen+1, if more memory is not reserved.
 ******************************************************************************/

AgTVoid
AgUtMsgReserveBuffer( 
	AgTUInt						uiSize 
);

/******************************************************************************
 * Function:    AgUtMsg
 *
 * Description: generates a message, based on the calling parameters.  
 *              Valid settings for msgType are located in the 'Mesage Type 
 *              Constants_T('. See ')Message WaitFlag Constants' for waitFlag settings,
 *              _T('Message DisplayID Constants') for displayID. The errorCode 
 *              parameter can be set to any integer error you wish to have 
 *              displayed, or AgCMsgNoErrorCode if you do not wish to supply 
 *              one.  If registered, the message function associated with the
 *              displayID is called to generate the correct error message.
 *
 * Example:     Here is a sample call containing one argument:
 *
 *              AgUtMsg( AgCMsgAlarm, AgCMsgWait, AgCMsgDispDefault, 
 *                       *rc, AgCMSourceLine, _T("Couldn't open file: %s"), 
 *                       fileName ); 
 *  
 * Notes:       This function accepts a variable argument list to handle the 
 *              creation of the message based on msgFormat.  
 ******************************************************************************/

AgTVoid
AgUtMsg( 
    AgTInt                    msgType, 
    AgTBool                   waitFlag, 
    AgTInt                    displayID, 
    AgTInt                    errorCode, 
    const AgTChar            *sourceFile, 
    AgTInt                    lineNo, 
    const AgTChar            *msgFormat, 
    ... 
);

/******************************************************************************
 * Function:    AgUtMsgNoArg
 *
 * Description: generates a message, based on the calling parameters.  
 *              Valid settings for msgType are located in the 'Mesage Type 
 *              Constants_T('. See ')Message WaitFlag Constants' for waitFlag settings,
 *              _T('Message DisplayID Constants') for displayID. The errorCode 
 *              parameter can be set to any integer error you wish to have 
 *              displayed, or AgCMsgNoErrorCode if you do not wish to supply 
 *              one.  If registered, the message function associated with the
 *              displayID is called to generate the correct error message.
 *
 * Example:     Here is a sample call containing one argument:
 *
 *              AgUtMsg( AgCMsgAlarm, AgCMsgWait, AgCMsgDispDefault, 
 *                       *rc, AgCMSourceLine, _T("This i%s an error")); 
 *  
 ******************************************************************************/

AgTVoid
AgUtMsgNoArg( 
    AgTInt                    msgType, 
    AgTBool                   waitFlag, 
    AgTInt                    displayID, 
    AgTInt                    errorCode, 
    const AgTChar            *sourceFile, 
    AgTInt                    lineNo, 
    const AgTChar            *msg
);


/******************************************************************************
 * Function:    AgUtMsgSetAllowDuplicates
 *
 * Description: allows the user to turn on/off a mode which will not allow duplicate
 *              messages in the message viewer.  returns the previous mode setting.
 ******************************************************************************/
AgTBool AgUtMsgSetAllowDuplicates( AgTBool allowDuplicates );

/******************************************************************************
 * Function:    AgUtMsgCreateMsgBatch
 *
 * Description: Creates group for batched messages by name.
 *
 ******************************************************************************/
AgTVoid
AgUtMsgCreateMsgBatch(
    AgTChar         *pBatchName
);

/******************************************************************************
 * Function:    AgUtMsgAddBatchedMsg
 *
 * Description: Stores a message to a group batch if it exists based
 *              on the calling parameters which will be output when
 *              AgUtMsgOutputBatchedMsgs() is called or outputs the
 *              message if the input name does not have a batched group. 
 *              See _T('Message WaitFlag Constants') for waitFlag settings,
 *              _T('Message DisplayID Constants') for displayID. The errorCode 
 *              parameter can be set to any integer error you wish to have 
 *              displayed, or AgCMsgNoErrorCode if you do not wish to supply 
 *              one.  If registered, the message function associated with the
 *              displayID is called to generate the correct error message.
 *
 ******************************************************************************/
AgTVoid
AgUtMsgAddBatchedMsg(
    const AgTChar         *pBatchName,
    AgTInt           msgType, 
    AgTBool          waitFlag, 
    AgTInt           displayID, 
    AgTInt           errorCode, 
    const AgTChar   *sourceFile, 
    AgTInt           lineNo, 
    const AgTChar   *msg
);

/******************************************************************************
 * Function:    AgUtMsgFreeBatchedMsgs
 *
 * Description: Frees all batched messages.
 *  
 ******************************************************************************/
AgTVoid
AgUtMsgFreeBatchedMsgs();

/******************************************************************************
 * Function:    AgUtMsgOutputBatchedMsgs
 *
 * Description: Outputs all batched messages.
 *              See _T('Message WaitFlag Constants') for waitFlag settings.
 *
 ******************************************************************************/
AgTVoid
AgUtMsgOutputBatchedMsgs( 
    AgTBool waitFlag
);

/******************************************************************************
 * Function:    AgUtMsgOutputBatchedMsgByName
 *
 * Description: Outputs batched messages for input batch name.
 *              See _T('Message WaitFlag Constants') for waitFlag settings.
 *
 ******************************************************************************/
AgTVoid
AgUtMsgOutputBatchedMsgByName(
    AgTChar *pBatchName,
    AgTBool waitFlag
);

/******************************************************************************
 * Function:    AgUtMsgBatchedMsgExistForName
 *
 * Description: Returns true false if messages exist for input batch name.
 *
 ******************************************************************************/
AgTBool
AgUtMsgBatchedMsgExistForName(
    AgTChar *pBatchName
);

/******************************************************************************
 * Private:
 ******************************************************************************/

typedef AgTVoid 
(*AgTLogMessageFunc)( 
    AgTInt                    msgType, 
    const AgTChar            *msgTypeDesc,
    AgTBool                   waitFlag, 
    AgTInt                    displayID, 
    AgTInt                    errorCode, 
    const AgTChar            *sourceFile,
    AgTInt                    lineNo, 
    const AgTChar            *message
 );

AgTVoid AgUtMsgSetLogMsgFunc(
  AgTLogMessageFunc  messageFunc
);

AgTInt AgUtMsgSetLogMsgFuncEx( 
  AgTLogMessageFunc messageFunc 
);

AgTVoid AgUtMsgUnSetLogMsgFuncEx(
  AgTInt cookie
);

#if defined(__cplusplus)
}
#endif

#endif

/******************************************************************************/
/*****         Copyright 1997-2001, Analytical Graphics, Inc.             *****/
/******************************************************************************/
