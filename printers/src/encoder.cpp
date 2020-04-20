#include "printer/encoder.h"

using namespace Macsa::Printers;

Encoder::Encoder()
{
	clear();
}

Encoder::Encoder(double fixedspeed)
{
	_mode = nEncoderMode::INTERNAL_ENCODER;
	_fixedSpeed = fixedspeed;
	_resolution = 0.0;
	_diameter	= 0.0;
	_abcPitch	= 0.0;
}

Encoder::Encoder(double resolution, double diameter, double abcPitch)
{
	_mode = nEncoderMode::INTERNAL_ENCODER;
	_fixedSpeed = 0.0;
	_resolution = resolution;
	_diameter	= diameter;
	_abcPitch = abcPitch;
}

Encoder::~Encoder()
{}

void Encoder::clear()
{
	_mode = nEncoderMode::FIXED_SPEED;
	_fixedSpeed = 0.0;
	_resolution = 0.0;
	_diameter	= 0.0;
	_abcPitch	= 0.0;
}

void Encoder::operator = (const Encoder &other)
{
	_mode		= other._mode;
	_fixedSpeed = other._fixedSpeed;
	_resolution = other._resolution;
	_diameter   = other._diameter;
	_abcPitch   = other._abcPitch;
}

bool Encoder::equal(const Encoder &other) const
{
    bool equal = false;
    equal  = _mode()	 == other._mode();
    equal &= static_cast<int>(_fixedSpeed * 100)  == static_cast<int>(other._fixedSpeed * 100);
	equal &= static_cast<int>(_resolution * 100)  == static_cast<int>(other._resolution * 100);
	equal &= static_cast<int>(_diameter   * 100)  == static_cast<int>(other._diameter   * 100);
	equal &= static_cast<int>(_abcPitch   * 100)  == static_cast<int>(other._abcPitch   * 100);

	return equal;
}
