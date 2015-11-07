#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>

#define _CRT_SECURE_NO_WARNINGS
#define MAXBUF 1024
#define DEFAULT_DELIMITTER "="

namespace ConfigLib {
	class Config {
	public:
		Config(char*);
		Config(char * name, char * delimitter);
		static double getDouble(char*);
		static bool getBool(char*);
		static char * getString(char*);
		static int getInt(char*);
		static long getLong(char*);
		static float getFloat(char*);
		static void setDouble(char*, double);
		static void setBool(char*, bool);
		static void setString(char*, char*);
		static void setInt(char*, int);
		static void setLong(char*, long);
		static void setFloat(char*, float);
		static void loadConfig();
		static void saveConfig();
		static std::list<std::pair<char*, char*>> configMap;
		static char* delimitter;
		static char* configName;
		static void removeKey(char*);
		static void printValues();
		~Config();
	private:
		static char* getCleanValue(char *);
		static void setCleanValue(char *, char*);
	};

}

