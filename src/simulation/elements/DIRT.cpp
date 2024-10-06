#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);

void Element::Element_DIRT()
{
	Identifier = "DEFAULT_PT_DIRT";
	Name = "DIRT";
	Colour = 0x6E522C_rgb;
	MenuVisible = 1;
	MenuSection = SC_POWDERS;
	Enabled = 1;

	Advection = 0.4f;
	AirDrag = 0.02f * CFDS;
	AirLoss = 0.70f;
	Loss = 0.85f;
	Collision = -0.1f;
	Gravity = 0.2f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 1;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 0;

	Weight = 50;

	Description = "Dirt, freezes into ice. Turns into mud on contact with water.";

	Properties = TYPE_PART;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = 273.15f;
	LowTemperatureTransition = PT_ICEI;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &update;
}

static int update(UPDATE_FUNC_ARGS)
{
	for (auto rx = -1; rx <= 1; rx++)
	{
		for (auto ry = -1; ry <= 1; ry++)
		{
			if (rx || ry)
			{
				auto r = pmap[y + ry][x + rx];
				if (!r)
					continue;
				if (TYP(r) == PT_WATR && sim->rng.chance(1, 25))
				{
					sim->part_change_type(i, x, y, PT_MUD);
					sim->part_change_type(ID(r), x + rx, y + ry, PT_MUD);
				}
				else if (TYP(r) == PT_MUD && sim->rng.chance(1, 200)) 
				{
				//Very unlikely for mud to spread into dirt, bc of density or smth idk, real.
					sim->part_change_type(i, x, y, PT_MUD);
					sim->part_change_type(ID(r), x + rx, y + ry, PT_MUD);
				}
			}
		}
	}
	return 0;
}