#include "ConfigLib.h"
using namespace std;

namespace ConfigLib {
	std::list<pair<char*, char*>> Config::configMap;
	char* Config::delimitter;
	char* Config::configName;

	Config::Config(char * name) {
		Config::configName = name;
		Config::delimitter = DEFAULT_DELIMITTER; //Default delimitter
	}
	Config::Config(char * name, char * delimitter) {
		Config::configName = name;
		Config::delimitter = delimitter;
		configMap = list<pair<char*, char*>>();
	}

	Config::~Config() {
		for (list<pair<char*, char*>>::iterator iter = configMap.begin(); iter != configMap.end(); iter++) {
			free(iter->first);
			free(iter->second);
		}
	}
	double Config::getDouble(char * key) {
		char * val = getCleanValue(key);
		if (val == NULL)
			return 0;
		float d;
		sscanf(val, "%lf", &d);
		return d;
	}

	float Config::getFloat(char * key) {
		char * val = getCleanValue(key);
		if (val == NULL)
			return 0;
		float f;
		sscanf(val, "%f", &f);
		return f;
	}

	int Config::getInt(char * key) {
		char * val = getCleanValue(key);
		if (val == NULL)
			return 0;
		int i;
		sscanf(val, "%d", &i);
		return i;
	}

	long Config::getLong(char * key) {
		char * val = getCleanValue(key);
		if (val == NULL)
			return 0;
		int i;
		sscanf(val, "%ld", &i);
		return i;
	}

	char * Config::getString(char * key) {
		return getCleanValue(key);
	}

	bool Config::getBool(char * key) {
		char * value = Config::getCleanValue(key);
		if (strcmp(value, "true") == 0)
			return true;
		return false;
	}

	void Config::setDouble(char * key, double value) {
		char val[MAXBUF];
		sprintf(val, "%lf", value);
		setCleanValue(key, val);
	}

	void Config::setFloat(char * key, float value) {
		char val[MAXBUF];
		sprintf(val, "%f", value);
		setCleanValue(key, val);
	}

	void Config::setInt(char * key, int value) {
		char val[MAXBUF];
		sprintf(val, "%d", value);
		setCleanValue(key, val);
	}

	void Config::setLong(char * key, long value) {
		char val[MAXBUF];
		sprintf(val, "%ld", value);
		setCleanValue(key, val);
	}

	void Config::setString(char * key, char * value) {
		setCleanValue(key, value);
	}

	void Config::setBool(char * key, bool value) {
		if (value == true)
			Config::setCleanValue(key, "true");
		else
			Config::setCleanValue(key, "false");
	}

	void Config::loadConfig() {
		FILE * configFile;
		configFile = fopen(configName, "r");
		if (configFile != NULL) {
			char line[MAXBUF];

			while (fgets(line, sizeof(line), configFile)) {
				char * key = (char *) malloc(MAXBUF);
				char * value = (char *)malloc(MAXBUF);
				strcpy(key, strtok(line, delimitter));
				strcpy(value, strtok(NULL, "\n"));
				configMap.push_back(make_pair(key, value));
			}
			fclose(configFile);
		} else {
			printf("Could not open file\n");
		}
	}

	void Config::saveConfig() {
		FILE * configFile;
		configFile = fopen(configName, "w");
		if (configFile != NULL) {
			for (list<pair<char*,char*>>::iterator iterator = configMap.begin(); iterator != configMap.end(); iterator++) {
				fprintf(configFile, "%s%s%s\n", iterator->first, delimitter, iterator->second);
			}
			fclose(configFile);
		} else {
			printf("Could not open file\n");
		}
	}
	char * Config::getCleanValue(char * key) {
		for (list<pair<char*, char*>>::iterator iter = configMap.begin(); iter != configMap.end(); iter++) {
			if (strcmp(key, iter->first) == 0)
				return iter->second;
		}
		printf("Cannot find key\n");
		return NULL;
	}
	void Config::setCleanValue(char * key, char* value) {
		for (list<pair<char*, char*>>::iterator iter = configMap.begin(); iter != configMap.end(); iter++) {
			if (strcmp(key, iter->first) == 0) {
				strcpy(iter->second, value);
				return;
			}
		}

		char * keyAlloc = (char *)malloc(MAXBUF);
		char * valueAlloc = (char *)malloc(MAXBUF);
		strcpy(keyAlloc, key);
		strcpy(valueAlloc, value);
		configMap.push_back(make_pair(keyAlloc, valueAlloc));
	}
	void Config::printValues() {
		printf("Printing values\n");
		for (list<pair<char*, char*>>::iterator iter = configMap.begin(); iter != configMap.end(); iter++) {
			printf("%s%s%s\n", iter->first, delimitter, iter->second);
		}
	}
	void Config::removeKey(char* key) {
		pair<char*, char*> toRemove;
		for (list<pair<char*, char*>>::iterator iter = configMap.begin(); iter != configMap.end(); iter++) {
			if (strcmp(iter->first, key) == 0)
				toRemove = make_pair(iter->first, iter->second);
		}
		free(toRemove.first);
		free(toRemove.second);
		configMap.remove(toRemove);

	}

}