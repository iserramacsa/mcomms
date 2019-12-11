#include "nisx/counter.h"

using namespace Macsa::Nisx;

Counter::Counter(int leadingZeros, int min, int max, int step, bool repeat)
{
	_leadingZeros = leadingZeros;
	_min = min;
	_max = max;
	_step = step;
	_repeat = repeat;
}

Counter::~Counter()
{}

int Counter::leadingZeros() const
{
	return _leadingZeros;
}

void Counter::setLeadingZeros(int leadingZeros)
{
	_leadingZeros = leadingZeros;
}

std::string Counter::format() const
{
	std::string format = "";
	for (int i = 0; i < _leadingZeros; i++) {
		format += "0";
	}
	return format;
}

void Counter::setformat(const std::string &format)
{
	int lz = 0;
	for (unsigned int i = 0; i < format.length(); i++) {
		 if (format.at(i) != '0') {
			 if (i > 0 || format.at(i) != '-'  || format.at(i) != '+' ){
				 break;
			 }
		 }
		 lz++;
	}
	_leadingZeros = lz;
}

int Counter::min() const
{
	return _min;
}

void Counter::setMin(int min)
{
	_min = min;
}

int Counter::max() const
{
	return _max;
}

void Counter::setMax(int max)
{
	_max = max;
}

int Counter::step() const
{
	return _step;
}

void Counter::setStep(int step)
{
	_step = step;
}

bool Counter::repeat() const
{
	return _repeat;
}

void Counter::setRepeat(bool repeat)
{
	_repeat = repeat;
}

void Counter::copy(const Counter &other)
{
	_min    = other._min;
	_max    = other._max;
	_step   = other._step;
	_repeat = other._repeat;
	_leadingZeros = other._leadingZeros;
}

bool Counter::compare(const Counter &other)
{
	bool equal = false;

	equal =  _min == other._min;
	equal &= _max == other._max;
	equal &= _step == other._step;
	equal &= _repeat == other._repeat;
	equal &= _leadingZeros == other._leadingZeros;

	return equal;
}

