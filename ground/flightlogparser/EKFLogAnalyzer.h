/**
 * @file: EKFLogAnalyzer.h
 * @brief: class decl for EKF LogEntry Analyze
 * @author: zhangxin@santypilot
 * @date: 2024-3-17
 */
#ifndef _EKF_LOG_ANALYZER_H
#define _EKF_LOG_ANALYZER_H

#include "LogAnalyzer.h"
#include <iostream>
#include "filterstates.h"

namespace santypilot_gcs {
namespace flightlogparser {

class EKFLogAnalyzer: public LogAnalyzer {
public:
	struct SensorData {
	};
	virtual void parse(const std::vector<std::string>& tokens,
			std::map<std::string, std::string>& refer) {
		size_t idx = 0;
		for (; idx < tokens.size(); idx++) {
			if (tokens[idx] == "Data:") {
			    break;
			}
		}
		if (idx == tokens.size()) {
		    return; // not found
		}
		auto& name = tokens[idx];
		if (name !=  "FILTERSTATES") {
		    return;
		}
		// key: [ value ] unit
		idx++;
		for (; idx < tokens.size();) {
			const auto& unit = refer[tokens[idx]];
		}
	}

	virtual void analyze(const std::vector<ExtendedDebugLogEntry*>& logs) {
		// 1. filter data
		for (auto& log: logs) {
			std::string data;// = log->getLogData();
			if (data.empty()) { // filter invalid ones
			    continue;
			}
			std::cout << data << std::endl;
			FilterStates::DataFields filter_states;
			// filter_states
		}

		// 2. process specific field data and plot
		// call filter functions
	    return;
	}
protected:
	bool parse(const std::string& raw) {
		return true;
	}
private:
	FilterStates::DataFields fields;
}; // EKFLogAnalyzer
} // flightlogparser
} // santypilot_gcs

#endif // _EKF_LOG_ANALYZER_H
