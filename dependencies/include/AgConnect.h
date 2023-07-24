/******************************************************************************/
/*****         Copyright 1997-2003, Analytical Graphics, Inc.             *****/
/******************************************************************************/

#if defined( CHECK_AGI_CONFIG )
#if !defined( AGI_UTIL_LEVEL )
#define
#endif
#endif

#ifndef AGCONNECT_H
#define AGCONNECT_H 1

#include "AgUtMsgCommon.h"

#if defined(__cplusplus)
extern "C" {
#endif

/******************************************************************************
 * Grouping: AgConnect
 *
 * GroupDescription: Functions related to the Connect operational interface
 *
 * Synopsis: #include "AgConnect.h"
 *
 * Introduction: provides a set of functions that allow external applications
 *               to easily open and manage socket connections to STK.
 ******************************************************************************/

/******************************************************************************
 * Constants:   Socket Type Constants
 *
 * Description: Used to describe the socket type being used.
 *
 * NOTE: These are no longer used and are left in for backwards compatibility.
 *       The function AgConOpenSTK() no longer uses the second argument which
 *       was typically one of these constants. Unix sockets are no longer
 *       supported and the function AgConOpenSTK_TCPIP() should be used instead.
 *
 * Private:
 ******************************************************************************/

#define AgCUnixType _T("UNIXSOCKET")
#define AgCTcpType  _T("TCPSOCKET")

/******************************************************************************
 * Constants:   Connect Constants
 *
 * Description: Generic constants
 *
 * Private:
 ******************************************************************************/

#define AgCMsgVerboseEnvVariable _T("CON_VERBOSE")

#if !defined (AgCRMHAHdrTypeLen)
#define AgCRMHAHdrTypeLen 15
#endif

#if !defined (AgCRMHAHdrIdLen)
#define AgCRMHAHdrIdLen 6
#endif

/******************************************************************************
 * Constants:   Connect Error Codes
 *
 * Description: Generic error codes
 *
 * Private:
 ******************************************************************************/

#if !defined (AgCError)

#define AgCError   -1
#define AgCNoError  0

#endif

#if !defined (AgCIONoData)

#define AgCIONoData             -2
#define AgCIOConnectionGone     -3
#define AgCIOWouldveWaited      -4
#define AgCIOChannelInUse       -5
#define AgCIOMessageTooLong     -6
#define AgCIOVersionMismatch    -7

/******************************************************************************
 * Constants:   IO Default Constants
 *
 * Description: These constants are used as defaults for socket connections
 *              and reads to control the timeout behavior.
 *
 * Private:
 ******************************************************************************/

#define AgCIOWait               -2
#define AgCIONoWait             -1
#define AgCIOUseDefault         0

#endif

#define AgCNackReturned    (AgCError - 1)
#define AgCPendingReturned (AgCNoError + 1)

/******************************************************************************
 * Constants:   Connect Properties Masks
 *
 * Description: Bit masks for setting Connect properties
 *
 * Private:
 ******************************************************************************/

#define AgCConVerboseOn     0x0001
#define AgCConAckOn         0x0002
#define AgCConErrorOn       0x0004
#define AgCConAsyncOn       0x0008

/******************************************************************************
 * Structure: AgTConReturnInfo
 *
 * Description: used to store data returned by Connect commands.  The 'hdrType'
 *              and 'transId' fields are only returned in asyncronous mode.
 *              'numEntries' is the number of pieces of data
 *              returned by STK, and 'returnList' is an array of strings that
 *              contains the returned data.
 ******************************************************************************/

typedef struct AgTConReturnInfo
{
    AgTChar   hdrType[AgCRMHAHdrTypeLen+1];
    AgTChar   transId[AgCRMHAHdrIdLen+1];
    int    numEntries;
    AgTChar **returnList;

}  AgTConReturnInfo;

/******************************************************************************
 * Function: AgConInit
 *
 * Description: opens the Connect configuration file and reads and processes
 *              the information within. The parameter 'initFileName' is the
 *              name of the file to be used.  If none is supplied a default
 *              set of values will be used.  The file can also be specified
 *              via the AGCONNECTINIT environment variable.
 *
 * Diagnostics: returns AgCNoError on success and AgCError on failure.
 ******************************************************************************/

int
AgConInit(
    const AgTChar *pczInitFileName
);

/******************************************************************************
 * Function: AgConOpenSTK
 *
 * Description: opens a TCP/IP connection to an STK application and sends the
 *              initial IPC Control setup. 'connectName' is the name of the
 *              socket. char *notUsed is left in for backwards compatibility but
 *              is not used.
 *
 * Diagnostics: returns AgCNoError on success and AgCError on failure.
 ******************************************************************************/

int
AgConOpenSTK(
    AgTChar **context,
    AgTChar  *notUsed,
    const AgTChar  *pczConnectName
);

/******************************************************************************
 * Function: AgConOpenSTK_TCPIP
 *
 * Description: opens a TCP/IP connection to an STK application and sends the
 *              initial IPC Control setup. 'connectName' is the name of the
 *              socket.
 *
 * Diagnostics: returns AgCNoError on success and AgCError on failure.
 ******************************************************************************/

int
AgConOpenSTK_TCPIP(
    AgTChar **context,
    const AgTChar  *pczConnectName
);

/******************************************************************************
 * Function: AgConCloseSTK
 *
 * Description: closes the socket connection specified by the _T('context')
 *              parameter.
 *
 * Diagnostics: returns AgCNoError on success and AgCError on failure.
 ******************************************************************************/

int
AgConCloseSTK(
    AgTChar **context
);

/******************************************************************************
 * Function: AgConProcessSTKCmd
 *
 * Description: sends an IPC command to the STK application.  Any return data
 *              is stored in 'returnInfo.'  The 'cmdString' is the IPC command
 *              name (such as ALLACCESS).
 *
 * Memory:      Inside of pReturnInfo is an array of strings.  Depending on the
 *              number of messages returned for a given command, that number
 *              of array elements is allocated.  Each array element is then
 *              allocated enough space to hold the returned message.
 *              The AgConCleanupReturnInfo function *must* be used to
 *              free the memory associated with pReturnInfo.
 *
 * Diagnostics: returns AgCNoError on success, AgCError on failure,
 *              and AgCNackReturned in the event the command was
 *              sent successfully but was rejected by STK.
 ******************************************************************************/

int
AgConProcessSTKCmd(
    AgTChar             *context,
    const AgTChar       *pczCmdString,
    AgTConReturnInfo *pReturnInfo
);

/******************************************************************************
 * Function: AgConGetAsync
 *
 * Description: meant to be called when asynchronous data is expected from STK.
 *              This function will listen to STK and return the first
 *              batch of asynchronous data received.  The type and identifier
 *              of the command the data corresponds to can be found in the
 *              returnInfo structure, along with the actual data.  A typical
 *              usage of this function would be to send the AsyncLatLonPick
 *              command with the Once flag to STK, and then call this function
 *              which will wait for the returned pick. As with other socket
 *              reads, the function will wait the timeout period for data
 *              to be returned.
 *
 * Memory: The returnList portion of the pReturnInfo must be deallocated as
 *         with AgConProcessSTKCmd().
 *
 * Diagnostics: returns AgCNoError on success and AgCError on failure.
 ******************************************************************************/

int
AgConGetAsync(
    AgTChar             *context,
    AgTConReturnInfo *pReturnInfo
);

/******************************************************************************
 * Function: AgConSetTimeout
 *
 * Description: sets the timeout value, in milliseconds, that will be used
 *              for a given connection when Connect is waiting for responses
 *              from STK.  For instance, a higher timeout value would be useful
 *              if you plan to send commands to STK that will take a long time
 *              to process.  The constants AgCIOWait, AgCIONoWait and
 *				AgCIOUseDefault may also be specified instead of a value
 *				in milliseconds.
 ******************************************************************************/

void
AgConSetTimeout(
    AgTChar *context,
    int   timeout
);

/******************************************************************************
 * Function: AgConSetProperties
 *
 * Description: sets the Connect properties verbose, acknowledge, async, and
 *              error.  Just OR together the bitmasks defined above and
 *              pass the result to this function.
 ******************************************************************************/

void
AgConSetProperties(
    AgTChar     *context,
    unsigned  props
);

/******************************************************************************
 * Function: AgConShutdownConnect
 *
 * Description: frees all the memory associated with Connect in
 *              preparation for application shutdown.  All connections
 *              should be closed prior to calling this function.  If
 *              you wish to resume Connect operations after calling
 *              this function you must first call AgConInit() before
 *              opening any socket connections.
 ******************************************************************************/

void
AgConShutdownConnect();

/******************************************************************************
 * Function: AgConCleanupReturnInfo
 *
 * Description: frees all memory associated with the AgTConReturnInfo referenced
 *              in the calling parameter list. This function is preferred over
 *              the AgConFreeListEntry/AgConFreeList because AgTConReturnInfo
 *              may have other information that will processed in the future.
 *
 * Memory:      This function *must* be used to free any memory that was allocated
 *              to the AgTConReturnInfo.
 *
 ******************************************************************************/

void
AgConCleanupReturnInfo(
    AgTConReturnInfo *pReturnInfo
);

/******************************************************************************
 * Function: AgConFreeListEntry
 *
 * Description: frees the memory in the return list entry.
 *
 * Notes:       This function is supported for backwards compatability.
 *              New connect applications should utilize the AgConCleanupReturnInfo
 *              function.
 ******************************************************************************/

int
AgConFreeListEntry(
    AgTChar *mem_pointer
);

/******************************************************************************
 * Function: AgConFreeList
 *
 * Description: frees the memory in the return list.
 *
 * Notes:       This function is supported for backwards compatability.
 *              New connect applications should utilize the AgConCleanupReturnInfo
 *              function.
 ******************************************************************************/

int
AgConFreeList(
    AgTChar **mem_pointer
);

/******************************************************************************
 * Function: AgConIsLocalHost
 *
 * Description: given a connection string <host:port> returns AgCTrue of the host
 *              is a local machine.
 ******************************************************************************/
AgTBool 
AgConIsLocalHost(
	const AgTChar *connectName);

#if defined(__cplusplus)
}
#endif

#endif

/******************************************************************************/
/*****         Copyright 1997-2003, Analytical Graphics, Inc.             *****/
/******************************************************************************/
