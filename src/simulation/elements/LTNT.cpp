#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);

void Element::Element_LTNT()
{
	Identifier = "DEFAULT_PT_LTNT";
	Name = "LTNT";
	Colour = 0xC05050_rgb;
	MenuVisible = 1;
	MenuSection = SC_EXPLOSIVE;
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

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 20;

	Weight = 30;

	DefaultProperties.temp = R_TEMP - 2.0f + 273.15f;
	HeatConduct = 88;
	LatentHeat = 7500;
	Description = "Liquid TNT, normal tnt, but liquid form!";

	Properties = TYPE_LIQUID | PROP_NEUTPENETRATE;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &update;
}

static int update(UPDATE_FUNC_ARGS)
{
	if(parts[i].tmp==0)
	{
		if(parts[i].temp>=673.0f)
			parts[i].tmp = 1;
		else
		{
			for (auto rx = -1; rx <= 1; rx++)
			{
				for (auto ry = -1; ry <= 1; ry++)
				{
					if (rx || ry)
					{
						auto r = pmap[y+ry][x+rx];
						if (!r)
							continue;
						if (TYP(r)==PT_FIRE || TYP(r)==PT_PLSM || TYP(r)==PT_SPRK || TYP(r)==PT_LIGH)
						{
							parts[i].tmp = 1;
						}
					}
				}
			}
		}
	}
	else if(parts[i].tmp==1)
	{
		if (pmap[y][x] && ID(pmap[y][x]) == i)
		{
			sim->flood_prop(x, y, Particle::GetProperties()[FIELD_TMP], 2);
		}
		parts[i].tmp = 2;
	}
	else if(parts[i].tmp==2)
	{
		parts[i].tmp = 3;
	}
	else
	{
		float otemp = parts[i].temp-273.15f;
		//Explode!!
		sim->pv[y/CELL][x/CELL] += 0.5f;
		parts[i].tmp = 0;
		if (sim->rng.chance(1, 3))
		{
			if (sim->rng.chance(1, 2))
			{
				sim->create_part(i, x, y, PT_FIRE);
			}
			else
			{
				sim->create_part(i, x, y, PT_SMKE);
				parts[i].life = sim->rng.between(500, 549);
			}
			parts[i].temp = restrict_flt((MAX_TEMP/4)+otemp, MIN_TEMP, MAX_TEMP);
		}
		else
		{
			if (sim->rng.chance(1, 15))
			{
				sim->create_part(i, x, y, PT_EMBR);
				parts[i].tmp = 0;
				parts[i].life = 50;
				parts[i].temp = restrict_flt((MAX_TEMP/3)+otemp, MIN_TEMP, MAX_TEMP);
				parts[i].vx = float(sim->rng.between(-10, 10));
				parts[i].vy = float(sim->rng.between(-10, 10));
			}
			else
			{
				sim->kill_part(i);
			}
		}
		return 1;
	}
	return 0;
}
