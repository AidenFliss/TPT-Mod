#include "simulation/ElementCommon.h"

void Element::Element_DUST()
{
	Identifier = "DEFAULT_PT_DUST";
	Name = "DUST";
	Colour = 0xFFE0A0_rgb;
	MenuVisible = 1;
	MenuSection = SC_POWDERS;
	Enabled = 1;

	Advection = 0.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.01f;
	Loss = 1.00f;
	Collision = -0.70f;
	Gravity = 0.050f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 1;

	Flammable = 10;
	Explosive = 0;
	Meltable = 0;
	Hardness = 30;
	PhotonReflectWavelengths = 0x3FFFFFC0;

	Weight = 85;

	HeatConduct = 70;
	Description = "Very light dust. Flammable. Slightly bouncy.";

	Properties = TYPE_PART;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Graphics = NULL; // it this needed?
}
