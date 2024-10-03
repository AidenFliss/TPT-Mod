#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);

void Element::Element_CGAS()
{
	Identifier = "DEFAULT_PT_CGAS";
	Name = "CGAS";
	Colour = PIXPACK(0x9DA832);
	MenuVisible = 1;
	MenuSection = SC_GAS;
	Enabled = 1;

	Advection = 2.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.99f;
	Loss = 0.30f;
	Collision = -0.1f;
	Gravity = 0.1f;
	Diffusion = 1.50f;
	HotAir = 0.000f * CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 50;
	Meltable = 0;
	Hardness = 0;

	Weight = 1;

	HeatConduct = 70;
	Description = "Clorine Gas, acts like ACID. Heavier than air.";

	Properties = TYPE_GAS | PROP_DEADLY;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	DefaultProperties.life = 1000;

	Update = &update;
}

static int update(UPDATE_FUNC_ARGS)
{
	for (int rx = -2; rx <= 2; rx++)
		for (int ry = -2; ry <= 2; ry++)
			if (BOUNDS_CHECK && (rx || ry))
			{
				int r = pmap[y + ry][x + rx];
				if (!r)
					continue;
				if (TYP(r) == PT_GAS)
				{
					if (sim->pv[(y + ry) / CELL][(x + rx) / CELL] > 3)
					{
						sim->part_change_type(ID(r), x + rx, y + ry, PT_RFRG);
						sim->part_change_type(i, x, y, PT_RFRG);
					}
				}
				else if (TYP(r) != PT_ACID && TYP(r) != PT_CAUS && TYP(r) != PT_RFRG && TYP(r) != PT_RFGL && TYP(r) != PT_CGAS)
				{
					if ((TYP(r) != PT_CLNE && TYP(r) != PT_PCLN && RNG::Ref().chance(sim->elements[TYP(r)].Hardness, 500)))
					{
						// SAND protects stuff from acid
						if (sim->parts_avg(i, ID(r), PT_SAND) != PT_SAND)
						{
							parts[i].life++;
							sim->kill_part(ID(r));
						}
					}
				}
			}
	return 0;
}
