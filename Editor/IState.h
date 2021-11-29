#pragma once
struct IState
{
	virtual void PollEvent() = 0;
};

