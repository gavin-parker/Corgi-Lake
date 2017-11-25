#pragma once
enum State {
	READY,				//Indicates that the component is ready and will execute on next tick
	EXECUTING,			//Indicates that the component is performing it's function for some number of cycles / waiting for dependency
	DONE,				//Function has been performed and result placed on output
};