/**
 * @file: LogAnalyzer.h
 * @brief: base class for LogEntry Analyze
 * @author: zhangxin@santypilot
 * @date: 2024-3-17
 */
#ifndef _LOG_ANALYZER_H
#define _LOG_ANALYZER_H

#include "ExtendedDebugLogEntry.h"
#include "uavobjectparser.h" // ObjectInfo
#include <QList>
#include <vector>

namespace santypilot_gcs {
namespace flightlogparser {

class LogAnalyzer {
public:
	virtual bool init(const std::map<std::string, std::string>& obj_fields) {
		_obj_fields = obj_fields;
	}

	virtual void analyze(
		const std::vector<ExtendedDebugLogEntry*>&) = 0;

	virtual void parse() {}

	void process(const QList<ObjectInfo *>& info,
		std::vector<ExtendedDebugLogEntry*>& logs) {
		std::map<std::string, size_t> field_2_idx;
		std::map<std::string, std::string> field_2_unit;
		for (auto i = 0; i < info.count(); i++) {
			if (info.at(i) == nullptr) {
			    continue;
			}
			auto& field = info.at(i)->name;
		    field_2_idx[field.toStdString()] = i;
			// map field to unit string
		}
		for (auto* entry: logs) {
			/*
		    auto data = entry->getLogData();
			if (data.empty()) {
			    continue;
			}
			auto tokens = split(data, ' ');
			std::cout << tokens.size() << "----" << std::endl;
			*/
		}
	}
private:
	std::vector<std::string> split(const std::string& raw, const char& c) {
		std::vector<std::string> ret;
		if (raw.empty()) {
		    return ret;
		}
		size_t l = 0, r = 0;
		while (true) {
			r = raw.find_first_of(c);
			ret.push_back(raw.substr(l, r - 1));
			if (r == std::string::npos) {
				return ret;
			}
			l = r + 1;
		}
	}
	std::map<std::string, std::string> _obj_fields;
}; // LogAnalyzer 
} // fliglogparser
} // santypilot_gcs

#endif // _LOG_ANALYZER_H
