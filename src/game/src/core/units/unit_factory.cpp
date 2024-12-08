#include "unit_factory.h";


const unordered_map<UNIT, UNIT_CLASS> unit_factory::unit_class_mapping = {
	{UNIT::CANNON, UNIT_CLASS::ATTACK},
	{UNIT::CATAPULT, UNIT_CLASS::ATTACK},
	{UNIT::BASE_UNIT, UNIT_CLASS::ATTACK}
};


const unordered_map<UNIT, uint_fast8_t> unit_factory::attack_range_mapping = {
	{UNIT::CANNON, 4},
	{UNIT::CANNON, 8},
};
