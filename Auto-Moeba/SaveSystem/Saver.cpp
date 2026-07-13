#include "Saver.h"
#include "FileUtils.h"
#include "../Particles/Particle.h"
#include <filesystem>
#include <fstream>

#include "FileUtils.h"
#include "../ParticleHandler.h"
#include "raylib.h"

bool Saver::save_state(Camera2D& camera)
{
	auto init_dir = get_initial_directory();
	auto file_path = prompt_file(ExplorerMode::Save, L"NewAutoMoebaSave", init_dir);

	std::ofstream stream(file_path);
	if (!stream.is_open()) return false;

	FileUtils::write_int32(stream, magic_number);
	FileUtils::write_vector2(stream, camera.target);
	FileUtils::write_size_t(stream, ParticleHandler::particles.size());
	for (auto& particle : ParticleHandler::particles)
	{
		particle->write_particle(stream, particle->get_id());
	}

	stream.close();
	return true;
}

bool Saver::load_state(Camera2D& camera)
{
	auto init_dir = get_initial_directory();
	auto file_path = prompt_file(ExplorerMode::Open, L"", init_dir);

	std::ifstream stream(file_path);
	if (!stream.is_open()) return false;

	int magic = FileUtils::read_int32(stream);
	if (magic != magic_number) return false;

	camera.target = FileUtils::read_vector2(stream);

	ParticleHandler::clear_all();

	size_t particle_count = FileUtils::read_size_t(stream);
	for (size_t i = 0; i < particle_count; ++i)
	{
		Particle::create_from_data(stream);
	}

	stream.close();
	return true;
}

std::wstring Saver::get_initial_directory()
{
	auto init_dir = get_executable_directory() + directory_name;
	if (!std::filesystem::exists(init_dir))
	{
		std::filesystem::create_directories(init_dir);
	}
	return init_dir;
}