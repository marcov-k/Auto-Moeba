#include "Saver.h"
#include "FileUtils.h"
#include "../Particles/Particle.h"
#include <filesystem>
#include <fstream>

#include "../ParticleHandler.h"
#include "raylib.h"

void Saver::save_state(const Camera2D& camera)
{
	auto init_dir = get_initial_directory();
	auto file_path = prompt_file(ExplorerMode::Save, L"NewAutoMoebaSave", init_dir);
	if (file_path == L"") throw NoSaveFileException("No save file was selected.");

	std::ofstream stream(file_path);
	if (!stream.is_open()) throw FileOpenFailedException("Failed to open save file.");

	FileUtils::write_int32(stream, magic_number);
	FileUtils::write_vector2(stream, camera.target);
	FileUtils::write_float(stream, camera.zoom);
	FileUtils::write_size_t(stream, ParticleHandler::particles.size());
	for (auto& particle : ParticleHandler::particles)
	{
		particle->write_particle(stream, particle->get_id());
	}

	stream.close();
}

void Saver::load_state(Camera2D& camera)
{
	auto init_dir = get_initial_directory();
	auto file_path = prompt_file(ExplorerMode::Open, L"", init_dir);
	if (file_path == L"") throw NoSaveFileException("No save file was selected.");

	std::ifstream stream(file_path);
	if (!stream.is_open()) throw FileOpenFailedException("Failed to open save file.");

	int magic = FileUtils::read_int32(stream);
	if (magic != magic_number) throw InvalidFileException("Invalid file type opened.");

	camera.target = FileUtils::read_vector2(stream);
	camera.zoom = FileUtils::read_float(stream);

	ParticleHandler::clear_all();

	size_t particle_count = FileUtils::read_size_t(stream);
	for (size_t i = 0; i < particle_count; ++i)
	{
		Particle::create_from_data(stream);
	}

	stream.close();
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