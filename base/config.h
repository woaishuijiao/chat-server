#ifndef CONFIG_H
#define CONFIG_H

#include <memory>
#include <string>
#include <sstream>
#include <boost/lexical_cast.hpp>

namespace jiong {

class ConfigVarBase {
public:
	typedef std::shared_ptr<ConfigVarBase> ptr;
	ConfigVarBase(const std::string& name, const std::string& description = "") 
		: m_name(name),
		m_description(description) {
	}
	virtual ~ConfigVarBase() {}

	const std::string& getName() const { return m_name; }
	const std::string& getDescriotion() const { return m_description; }

	virtual std::string toString() = 0;
	virtual bool fromString(const std::string& val) = 0;
protected:
	std::string m_name;
	std::string m_description;
};

template<class T>
class ConfigVar : public ConfigVarBase {
public:
	typedef std::shared_ptr<ConfigVar> ptr;

	ConfigVar(const std::string& name, const T& default_value,
			const std::string& description = "") 
		: ConfigVarBase(name, description),
		m_val(default_value) {
	}

	std::string toString() override {
	}
	bool fromString(const std::string& val) override {
	}
private:
	T m_val;
};

}

#endif
