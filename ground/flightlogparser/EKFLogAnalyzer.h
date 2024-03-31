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
#include <cmath>
#include "filterstates.h"
#include <ekfconfiguration.h>
#include <ekfstatevariance.h>
#include <homelocation.h>

namespace santypilot_gcs {
namespace flightlogparser {

class EKFLogAnalyzer: public LogAnalyzer {
public:
	// input data type
	using DataType = std::map<std::string, 
		  std::vector<std::pair<size_t, double>>>;

	struct LocalData {
		EKFConfigurationData ekfConfiguration;
		HomeLocationData     homeLocation;
		bool    usePos;
		int32_t init_stage;
		// stateEstimation work;
		bool  inited;
		bool  navOnly;
		float magLockAlpha;
	};
	struct SensorData {
	};

	// 1 filter() replay bug 
	// 2 show states
	// 3 evaluate bug occurs: do some warning mechanism 
	// 4 mock by step
	// 5 maybe which matrix init too big or calc not recursive
	virtual void analyze() {
		// 1. filter data
		DataType _data;
		// 2. call filter functions 
		// & evaluate states

		// 3. evaluate intermediate variables
	    return;
	}
private:
	void init() {
		EKFConfigurationInitialize();
		EKFConfigurationGet(&this->ekfConfiguration);
	}
	// check for isnan or close to zero
	static inline bool invalid_var(float data) {
		if (std::isnan(data) || std::isinf(data)) {
			return true;
		}
		if (data < 1e-15f) { 
			// var should not be close to zero. 
			// And not negative either.
			return true;
		}
		return false;
	}
	// do filter StateEstimation/filterekf.c
	FilterStates::DataFields fields;
}; // EKFLogAnalyzer
} // flightlogparser
} // santypilot_gcs

#endif // _EKF_LOG_ANALYZER_H
