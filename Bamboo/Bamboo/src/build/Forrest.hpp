#pragma once

#ifndef FORREST_HPP
#define FORREST_HPP

namespace Fst
{
	extern void Setup(void);
	extern void Frame(unsigned int frameBuffer, unsigned long long deltaTime);
	extern void Close(void);
}

#endif // !FORREST_HPP
