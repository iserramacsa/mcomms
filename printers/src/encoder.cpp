#include "printer/encoder.h"

using namespace Macsa::Printers;

Encoder::Encoder()
{
	clear();
}

Encoder::Encoder(double fixedspeed)
{
	_mode = EncoderMode_n::INTERNAL_ENCODER;
	_fixedSpeed = fixedspeed;
	_resolution = 0.0;
	_diameter	= 0.0;
}

Encoder::Encoder(double resolution, double diameter)
{
	_mode = EncoderMode_n::INTERNAL_ENCODER;
	_fixedSpeed = 0.0;
	_resolution = resolution;
	_diameter	= diameter;
}

Encoder::~Encoder()
{}

EncoderMode Encoder::mode() const
{
	return _mode;
}

void Encoder::setMode(const EncoderMode &value)
{
	_mode = value;
}

//void Encoder::setMode(const std::string &value)
//{
//	_mode = value;
//}

double Encoder::fixedSpeed() const
{
	return _fixedSpeed;
}

void Encoder::setFixedSpeed(double value)
{
	_fixedSpeed = value;
}

double Encoder::resolution() const
{
	return _resolution;
}

void Encoder::setResolution(double value)
{
	_resolution = value;
}

double Encoder::diameter() const
{
	return _diameter;
}

void Encoder::setDiameter(double value)
{
	_diameter = value;
}

void Encoder::clear()
{
	_mode = EncoderMode_n::INTERNAL_ENCODER;
	_fixedSpeed = 0.0;
	_resolution = 0.0;
	_diameter	= 0.0;
}

void Encoder::operator = (const Encoder &other)
{
	_mode		= other._mode;
	_fixedSpeed = other._fixedSpeed;
	_resolution = other._resolution;
	_diameter   = other._diameter;
}

bool Encoder::equal(const Encoder &other) const
{
	bool equal = false;
	equal  = _mode()	 == other._mode();
	equal &= static_cast<int>(_fixedSpeed * 100)  == static_cast<int>(other._fixedSpeed * 100);
	equal &= static_cast<int>(_resolution * 100)  == static_cast<int>(other._resolution * 100);
	equal &= static_cast<int>(_diameter   * 100)  == static_cast<int>(other._diameter   * 100);

	return equal;
}
