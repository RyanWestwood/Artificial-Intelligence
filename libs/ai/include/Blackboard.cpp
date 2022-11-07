#include "Blackboard.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

namespace ai {

	void Blackboard::Initialize(std::string filename)
	{
		m_Filename = filename;
		ReadFile();
		PrintBoard();
	}

	FloatPtr Blackboard::GetFloat(std::string name, float default_value)
	{
		if(m_Floats.find(name) == m_Floats.end()) {
			m_Floats.emplace(name, std::make_shared<float>(default_value));
		}
		return m_Floats[name];
	}

	BoolPtr Blackboard::GetBool(std::string name, bool default_value)
	{
		if (m_Bools.find(name) == m_Bools.end()) {
			m_Bools.emplace(name, std::make_shared<bool>(default_value));
		}
		return m_Bools[name];
	}

	void Blackboard::ReadFile()
	{
		std::vector<std::string> row;
		std::string line, word;

		std::fstream file(m_Filename, std::ios::in);
		if (file.is_open())
		{
			while (std::getline(file, line))
			{
				row.clear();
				std::stringstream str(line);

				while (getline(str, word, ',')) {
					row.push_back(word);
				}
				if (row[0] == "float") {
					FloatPtr value = std::make_shared<float>(std::stof(row[2]));
					m_Floats.emplace(row[1], value);
				}
				if (row[0] == "bool") {
					bool value = row[2] == "true" ? true : false;
					BoolPtr value2 = std::make_shared<bool>(value);
					m_Bools.emplace(row[1], value2);
				}
			}
		}
		else {
			std::cout << "Could not open the file - " << m_Filename << "\n";
		}
	}

	void Blackboard::WriteFile()
	{

	}

	void Blackboard::PrintBoard()
	{
		std::cout << "Float dictionary: \n";
		for (const auto& element : m_Floats)
		{
			std::cout << element.first << " " << *element.second << "\n";
		}
		std::cout << "Bool dictionary: \n";
		for (const auto& element : m_Bools)
		{
			std::cout << element.first << " " << *element.second << "\n";
		}
	}

	BlackboardPtr CreateBlackboard(std::string filename)
	{
		BlackboardPtr value = std::make_shared<Blackboard>();
		value->Initialize(filename);
		return value;
	}

} // namespace ai