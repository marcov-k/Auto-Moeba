#pragma once

#include <iostream>
#include <stdexcept>
#include <unordered_map>

using namespace std;

enum class ParticleType
{
	Predator,
	Prey,
	Scavenger,
	Membrane,
	Nucleus,
	Connector,
	Food,
	Waste,
	End
};

struct TypeAttractions
{
	unordered_map<ParticleType, float> _attractions;

	static unordered_map<ParticleType, float> get_attractions(ParticleType type)
	{
		switch (type)
		{
		case ParticleType::Predator:
			return predator();
		case ParticleType::Prey:
			return prey();
		case ParticleType::Scavenger:
			return scavenger();
		case ParticleType::Membrane:
			return membrane();
		case ParticleType::Nucleus:
			return nucleus();
		case ParticleType::Connector:
			return connector();
		case ParticleType::Food:
			return food();
		case ParticleType::Waste:
			return waste();
		case ParticleType::End:
			return empty();
		default:
			throw invalid_argument("Unkown particle type.");
		}
	}

	static unordered_map<ParticleType, float> empty()
	{
		return unordered_map<ParticleType, float>
		{
			{ ParticleType::Predator, 0.0f },
			{ ParticleType::Prey, 0.0f },
			{ ParticleType::Scavenger, 0.0f },
			{ ParticleType::Membrane, 0.0f },
			{ ParticleType::Nucleus, 0.0f },
			{ ParticleType::Connector, 0.0f },
			{ ParticleType::Food, 0.0f },
			{ ParticleType::Waste, 0.0f }
		};
	}

	static unordered_map<ParticleType, float> predator()
	{
		return unordered_map<ParticleType, float>
		{
			{ ParticleType::Predator, -10.0f },
			{ ParticleType::Prey, -40.0f },
			{ ParticleType::Scavenger, 6.0f },
			{ ParticleType::Membrane, -30.0f },
			{ ParticleType::Nucleus, 0.0f },
			{ ParticleType::Connector, 5.0f },
			{ ParticleType::Food, 0.0f },
			{ ParticleType::Waste, 0.0f }
		};
	}

	static unordered_map<ParticleType, float> prey()
	{
		return unordered_map<ParticleType, float>
		{
			{ ParticleType::Predator, 40.0f },
			{ ParticleType::Prey, 1.0f },
			{ ParticleType::Scavenger, 0.0f },
			{ ParticleType::Membrane, 0.0f },
			{ ParticleType::Nucleus, 0.0f },
			{ ParticleType::Connector, 5.0f },
			{ ParticleType::Food, 0.0f },
			{ ParticleType::Waste, 0.0f }
		};
	}

	static unordered_map<ParticleType, float> scavenger()
	{
		return unordered_map<ParticleType, float>
		{
			{ ParticleType::Predator, -1.0f },
			{ ParticleType::Prey, 0.0f },
			{ ParticleType::Scavenger, -5.0f },
			{ ParticleType::Membrane, 0.0f },
			{ ParticleType::Nucleus, 0.0f },
			{ ParticleType::Connector, 5.0f },
			{ ParticleType::Food, 0.0f },
			{ ParticleType::Waste, 0.0f }
		};
	}

	static unordered_map<ParticleType, float> membrane()
	{
		return unordered_map<ParticleType, float>
		{
			{ ParticleType::Predator, 30.0f },
			{ ParticleType::Prey, 0.0f },
			{ ParticleType::Scavenger, 0.0f },
			{ ParticleType::Membrane, 2.0f },
			{ ParticleType::Nucleus, 0.0f },
			{ ParticleType::Connector, 5.0f },
			{ ParticleType::Food, 0.0f },
			{ ParticleType::Waste, 0.0f }
		};
	}

	static unordered_map<ParticleType, float> nucleus()
	{
		return unordered_map<ParticleType, float>
		{
			{ ParticleType::Predator, 10.0f },
			{ ParticleType::Prey, 0.0f },
			{ ParticleType::Scavenger, 0.0f },
			{ ParticleType::Membrane, 200.0f },
			{ ParticleType::Nucleus, 300.0f },
			{ ParticleType::Connector, 5.0f },
			{ ParticleType::Food, 0.0f },
			{ ParticleType::Waste, 0.0f }
		};
	}

	static unordered_map<ParticleType, float> connector()
	{
		return unordered_map<ParticleType, float>
		{
			{ ParticleType::Predator, 5.0f },
			{ ParticleType::Prey, 5.0f },
			{ ParticleType::Scavenger, 5.0f },
			{ ParticleType::Membrane, 5.0f },
			{ ParticleType::Nucleus, 5.0f },
			{ ParticleType::Connector, 5.0f },
			{ ParticleType::Food, 0.0f },
			{ ParticleType::Waste, 0.0f }
		};
	}

	static unordered_map<ParticleType, float> food()
	{
		return unordered_map<ParticleType, float>
		{
			{ ParticleType::Predator, 0.0f },
			{ ParticleType::Prey, 60.0f },
			{ ParticleType::Scavenger, 0.0f },
			{ ParticleType::Membrane, 40.0f },
			{ ParticleType::Nucleus, 60.0f },
			{ ParticleType::Connector, 30.0f },
			{ ParticleType::Food, 0.0f },
			{ ParticleType::Waste, 0.0f }
		};
	}

	static unordered_map<ParticleType, float> waste()
	{
		return unordered_map<ParticleType, float>
		{
			{ ParticleType::Predator, -5.0f },
			{ ParticleType::Prey, -5.0f },
			{ ParticleType::Scavenger, 30.0f },
			{ ParticleType::Membrane, -5.0f },
			{ ParticleType::Nucleus, -5.0f },
			{ ParticleType::Connector, -5.0f },
			{ ParticleType::Food, 0.0f },
			{ ParticleType::Waste, 0.0f }
		};
	}
};