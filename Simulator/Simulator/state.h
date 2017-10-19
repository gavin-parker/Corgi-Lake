#pragma once
enum State {
	READY,				//Indicates that the component is ready and will execute on next tick
	EXECUTING,			//Indicates that the component is performing it's function for some number of cycles / waiting for dependency
	HOLD,				//Indicates that the component is idle and needs to be started by setting to READY
	DONE,				//Function has been performed and result placed on output
	WAIT_FOR_MEM,
	WAIT_FOR_ALU,
	FETCHING_INSTRUCTION,
	STALLED
};