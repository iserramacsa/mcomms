#include "printer/shotmode.h"

using namespace Macsa;
using namespace Macsa::Printers;
using namespace std;

ShotMode::ShotMode()
{
	clear();
}

ShotMode::ShotMode(ShootingMode mode, unsigned int numPrints, const std::vector<Delay> &delays, bool repeat)
{
	initByMode(mode(), numPrints, delays, repeat);
}

ShotMode::ShotMode(nShootingMode mode, unsigned int numPrints, const std::vector<Delay> &delays, bool repeat)
{
	initByMode(mode, numPrints, delays, repeat);
}

ShootingMode ShotMode::mode() const
{
	return _mode;
}

uint16_t ShotMode::numPrints() const
{
	return static_cast<uint16_t>(_numPrints);
}

std::vector<Delay> ShotMode::delays() const
{
	return _delays;
}

bool ShotMode::repeat() const
{
	return _repeat;
}

void ShotMode::operator = (const ShotMode &other)
{
	initByMode(other._mode(), other._numPrints, other._delays, other._repeat);
}

void ShotMode::initByMode(nShootingMode mode, unsigned int numPrints, const std::vector<Delay> &delays, bool repeat)
{
	_mode = mode;
	_delays.clear();
	unsigned int nDelays = static_cast<unsigned int>(delays.size());
	switch (_mode()) {
		case nShootingMode::MULTI_SHOT_REL:
			if(nDelays) {
				_delays.push_back(delays.at(0));
				if (nDelays > 1){
					_delays.push_back(delays.at(1));
				}
				else{
					Delay delay;
					_delays.push_back(delay);
				}
			}
			else{
				Delay delay;
				_delays.push_back(delay);
			}
			_numPrints = numPrints;
			break;
		case nShootingMode::MULTI_SHOT_ABS:
			_numPrints = static_cast<unsigned>(delays.size());
			for (unsigned int i = 0; i < numPrints; i++) {
				_delays.push_back(delays.at(i));
			}
			break;
		case nShootingMode::SINGLE_SHOT:
			if(delays.size()) {
				_delays.push_back(delays.at(0));
			}
			else{
				Delay delay;
				_delays.push_back(delay);
			}
			_numPrints = static_cast<unsigned>(delays.size());
			break;
	}
	_repeat = repeat;
}

bool ShotMode::equal(const ShotMode &other) const
{
    bool equal = false;

	if ((_mode() == other._mode()) && (_numPrints == other._numPrints) && (_repeat == other._repeat)) {
		if (_delays.size() == other._delays.size()) {
			unsigned i = 0;
			for (; i < static_cast<unsigned>(_delays.size()); i++) {
				if (_delays.at(i) != other._delays.at(i)) {
					break;
				}
			}
			equal = (i == _delays.size());
		}
	}

	return equal;
}

void ShotMode::clear()
{
	Delay delay;
	_delays.clear();

	_mode = nShootingMode::SINGLE_SHOT;
	_delays.push_back(delay);
	_numPrints = static_cast<unsigned>(_delays.size());
	_repeat = false;
}

