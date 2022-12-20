#include "Config.h"

Config* Config::CreateDefault() {
	Config* config = new Config();

	config->sim_step = 1;

	return config;
}

void Config::Present() {

}

void Config::AddDef(ProductDefinition* def) {

}