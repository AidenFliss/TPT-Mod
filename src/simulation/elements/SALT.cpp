#include "simulation/ElementCommon.h"

void Element::Element_SALT()
{
	Identifier = "DEFAULT_PT_SALT";
	Name = "SALT";
	Colour = 0xFFFFFF_rgb;
	MenuVisible = 1;
	MenuSection = SC_POWDERS;
	Enabled = 1;

	Advection = 0.4f;
	AirDrag = 0.04f * CFDS;
	AirLoss = 0.94f;
	Loss = 0.95f;
	Collision = -0.4f;
	Gravity = 0.07f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 1;

	Flammable = 0;
	Explosive = 0;
	Meltable = 5;
	Hardness = 1;

	Weight = 10;

	HeatConduct = 110;
	Description = "Salt, dissolves in water. Very light and super SLIGHTLY bouncy.";

	Properties = TYPE_PART;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 1173.0f;
	HighTemperatureTransition = PT_LAVA;
}
