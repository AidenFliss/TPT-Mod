#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);

void Element::Element_STCK()
{
	Identifier = "DEFAULT_PT_STCK";
	Name = "STCK";
	Colour = PIXPACK(0x2B1717);
	MenuVisible = 1;
	MenuSection = SC_SOLIDS;
	Enabled = 1;

	Advection = 0.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.90f;
	Loss = 0.00f;
	Collision = 0.0f;
	Gravity = 0.0f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 0;

	Flammable = 500;
	Explosive = 0;
	Meltable = 0;
	Hardness = 3;

	Weight = 30;

	HeatConduct = 0;
	Description = "Stick, very flammable and weak.";

	Properties = TYPE_SOLID | PROP_NEUTPENETRATE;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 100.0f;
	HighTemperatureTransition = PT_FIRE;

	Update = &update;
}

static int update(UPDATE_FUNC_ARGS)
{
	if (parts[i].temp > 80 && parts[i].temp > parts[i].tmp)
		parts[i].tmp = (int)parts[i].temp;

	if (parts[i].temp > 320.0f && sim->pv[y/CELL][x/CELL] <= -10.0f)
	{
		float temp = parts[i].temp;
		sim->create_part(i, x, y, PT_BCOL);
		parts[i].temp = temp;
	}

	return 0;
}