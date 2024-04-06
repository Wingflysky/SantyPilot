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

extern "C" {
#include "libraries/inc/CoordinateConversions.h"
#include "libraries/math/mathmisc.h"
#include "libraries/inc/insgps.h"
}

namespace santypilot_gcs {
namespace flightlogparser {
using RElem = EKFConfiguration::RElem;
using QElem = EKFConfiguration::QElem;

class EKFLogAnalyzer: public LogAnalyzer {
public:
	// input data type
	using DataType = std::map<std::string, 
		  std::vector<std::pair<size_t, double>>>;

	struct LocalData {
		int32_t init_stage;
		bool  inited;
		bool  navOnly;
		float magLockAlpha;
	};
	struct SensorData {};

	// 1 filter() replay bug 
	// 2 show states
	// 3 evaluate bug occurs: do some warning mechanism 
	// 4 mock by step
	// 5 maybe which matrix init too big or calc not recursive
	virtual void analyze() {
		// 1. filter data
		if (!_inited) {
			// init vars
			_config_data = _config.getData();
			_location_data = _homelocation.getData();
			float magnorm[3] = { _location_data.Be[0], 
				_location_data.Be[1], _location_data.Be[2] };
			// print_diag(magnorm, 3);

			vector_normalizef(magnorm, 3);
			const float down[3] = { 0, 0, 1 };
			float cross[3];
			CrossProduct(down, magnorm, cross);
			_inited = true;
			// init algo
            INSGPSInit();
			INSSetArmed(false); // debug not armed state
			INSSetMagNorth(_location_data.Be);

			// set variance
            float Be2 = pow(_location_data.Be[0], 2) + 
				pow(_location_data.Be[1], 2) + pow(_location_data.Be[2], 2);

			float mag_r[3] = { _config_data.R[RElem::R_MAGX] / Be2,
							  _config_data.R[RElem::R_MAGY] / Be2,
							  _config_data.R[RElem::R_MAGZ] / Be2 };
			float acc_q[3] = { _config_data.Q[QElem::Q_ACCELX],
							   _config_data.Q[QElem::Q_ACCELY],
							   _config_data.Q[QElem::Q_ACCELZ] };
			float gyro_q[3] = { _config_data.Q[QElem::Q_GYROX],
							    _config_data.Q[QElem::Q_GYROY],
							    _config_data.Q[QElem::Q_GYROZ] };
			float gyro_biasq[3] = { _config_data.Q[QElem::Q_GYRODRIFTX],
								   _config_data.Q[QElem::Q_GYRODRIFTY],
								   _config_data.Q[QElem::Q_GYRODRIFTZ] };
            INSSetMagVar(mag_r);
            INSSetAccelVar(acc_q);
            INSSetGyroVar(gyro_q);
            INSSetGyroBiasVar(gyro_biasq);
            INSSetBaroVar(_config_data.R[RElem::R_BAROZ]);
		}
		// 2. call filter functions 
		// & evaluate states
		/*
		print_diag(_location_data.Be, 3);
		print_diag(_config_data.P, 13);
		print_diag(_config_data.Q, 9);
		print_diag(_config_data.R, 10);
		*/
		size_t data_len = _data["dT"].size();
		for (auto i = 0; i < data_len; i++) {
			float gyro[3] = {
				_data["gx"][i].second, 
				_data["gy"][i].second,
			    _data["gz"][i].second};
			float acc[3] = {
			    _data["ax"][i].second,
				_data["ay"][i].second,
				_data["az"][i].second};
			float dT = _data["dT"][i].second;

			INSStatePrediction(gyro, acc, dT);
		}
		// INSCovariancePrediction(dT);
        // INSCorrection(this->work.mag, this->work.pos, 
		//		this->work.vel, this->work.baro[0], sensors);

		// 3. evaluate intermediate variables
	    return;
	}
private:
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
	// x: 13 * 1 p3, v3, q4, gb3
	// u: 6 * 1 g3, a3
	// y: 10 * 1 p3, v3, mag3, baro1
	// x,u -> x
	// P: 13 * 13
	// Q: 9 * 9
	// R: 10 * 10
	// P = FPF^T + GQG^T
	// K = PH^T(HPH^T + R)
	// x = x + K(y - h(x,u))
	// P = (I - KH)P
	// F 13 * 13 
	// G 13 * 9
	// H 10 * 13
	// K 13 * 10

	void print_matrix(float* data, const std::vector<size_t>& dim) {
	    for (auto i = 0; i < dim.size(); i++) {
			for (auto j = 0; j < dim[i]; j++) {
				std::cout << data[i] << " ";
			}
			std::cout << std::endl;
		}
	}
	void print_diag(float* data, const size_t dim) {
	    for (auto i = 0; i < dim; i++) {
			for (auto j = 0; j < i; j++) {
				std::cout << " ";
			}
			std::cout << data[i] << std::endl;
		}
		std::cout << std::endl;
	}
	// do filter StateEstimation/filterekf.c
	bool _inited = false;
	EKFConfiguration _config;
	EKFConfiguration::DataFields _config_data;
	HomeLocation _homelocation;
	HomeLocation::DataFields _location_data;
}; // EKFLogAnalyzer
} // flightlogparser
} // santypilot_gcs

#endif // _EKF_LOG_ANALYZER_H
