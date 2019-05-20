#ifndef EPICS_INTERFACE_H
#define EPICS_INTERFACE_H
#endif
#include "LoggingSystem.h"
// EPICS include
#ifndef __CINT__
#include <cadef.h>
#endif
class EPICSInterface
{
	public:
		EPICSInterface();
		EPICSInterface(bool& shouldStartEpics, bool& shouldStartVirtualMachine);
		EPICSInterface(bool& shouldStartEpics, bool& shouldStartVirtualMachine, LoggingSystem& messaging);

		double get_CA_PEND_IO_TIMEOUT() const;
		void set_CA_PEND_IO_TIMEOUT(double value);
		chid retrieveCHID(std::string &pv);
		chtype retrieveCHTYPE(chid &channelID);
		unsigned long retrieveCOUNT(chid &channelID);

	protected:
		bool shouldStartEpics = true;
		bool shouldStartVirtualMachine = true;
		LoggingSystem messaging;
		unsigned short EPICS_ACTIVATE, EPICS_SEND, EPICS_RESET;
		// some other stuff might be needed here, need to check interface.h from VELA-CLARA Controllers

	#ifndef __CINT__
		ca_client_context *thisCaContext;
		void attachTo_thisCAContext();
		void detachFrom_thisCAContext();
		void addILockChannels(const int numILocks,
			const std::string& pvRoot,
			const std::string& objectName
			// map_ilck_pvstruct& ILockPVStructs,
			);
		template<typename T> T getDBR(const event_handler_args& args)
		{
			T dbr_holder;
			dbr_holder = args.dbr;
			return dbr_holder;
		}
	#endif
};