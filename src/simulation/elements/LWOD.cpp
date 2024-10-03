#include "simulation/ElementCommon.h"
#include <algorithm>

static int update(UPDATE_FUNC_ARGS);
static int graphics(GRAPHICS_FUNC_ARGS);

void Element::Element_LWOD()
{
	Identifier = "DEFAULT_PT_LWOD";
	Name = "LWOD";
	Colour = 0xC0A040_rgb;
	MenuVisible = 1;
	MenuSection = SC_LIQUID;
	Enabled = 1;

	Advection = 0.6f;
	AirDrag = 0.01f * CFDS;
	AirLoss = 0.98f;
	Loss = 0.95f;
	Collision = 0.0f;
	Gravity = 0.1f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 2;

	Flammable = 20;
	Explosive = 0;
	Meltable = 0;
	Hardness = 15;

	Weight = 100;

	HeatConduct = 164;
	Description = "Liquid Wood, wood but liquid. Turns solid when frozen.";

	Properties = TYPE_LIQUID | PROP_NEUTPENETRATE;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = 241.15f;
	LowTemperatureTransition = PT_WOOD;
	HighTemperature = 873.0f;
	HighTemperatureTransition = PT_FIRE;

	Update = &update;
	Graphics = &graphics;
}

static int update(UPDATE_FUNC_ARGS)
{
	if (parts[i].temp > 450 && parts[i].temp > parts[i].tmp)
		parts[i].tmp = (int)parts[i].temp;

	if (parts[i].temp > 773.0f && sim->pv[y/CELL][x/CELL] <= -10.0f)
	{
		float temp = parts[i].temp;
		sim->create_part(i, x, y, PT_BCOL);
		parts[i].temp = temp;
	}

	return 0;
}

static int graphics(GRAPHICS_FUNC_ARGS)
{
	float maxtemp = std::max((float)cpart->tmp, cpart->temp);
	if (maxtemp > 400)
	{
		*colr -= (int)restrict_flt((maxtemp-400)/3,0,172);
		*colg -= (int)restrict_flt((maxtemp-400)/4,0,140);
		*colb -= (int)restrict_flt((maxtemp-400)/20,0,44);
	}
	if (maxtemp < 273)
	{
		*colr -= (int)restrict_flt((273-maxtemp)/5,0,40);
		*colg += (int)restrict_flt((273-maxtemp)/4,0,40);
		*colb += (int)restrict_flt((273-maxtemp)/1.5,0,150);
	}
	return 0;
}
