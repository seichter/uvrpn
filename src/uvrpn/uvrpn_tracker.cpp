/**
 * uvrpn - a minimal wrapper for VRPN in Unity
 *
 * Copyright (c) 2013-2018 Hartmut Seichter
 *
 * This file is part of uvrpn and licensed under the terms of the MIT License
 *
 */
#include "vrpn_Configure.h"
#include "vrpn_Analog.h"
#include "vrpn_Tracker.h"

#include "uvrpn_exports.hpp"

#include <memory>
#include <vector>


struct VRPN_Tracker_Remote;

void VRPN_Remote_Callback(void *userdata, const vrpn_TRACKERCB t);

/**
 * @brief The VRPN_Remote struct
 *
 */
struct VRPN_Tracker_Remote {

	using DataType = _vrpn_TRACKERCB;

    std::unique_ptr<vrpn_Tracker_Remote> _remote;

	bool _hasUpdates  = false;

	std::vector<DataType> _sensors;

	size_t _updateCount = 0;

	VRPN_Tracker_Remote(const char* url)
		: _remote(new vrpn_Tracker_Remote(url))
    {
        // register a change hander
        _remote->register_change_handler(this, VRPN_Remote_Callback);
    }

    void update() {
        do {
            // reset hasUpdates ...
            _hasUpdates = false;
            // call loop
            _remote->mainloop();
            // check if there were actually some updates
        } while(_hasUpdates);
    }

	void get(DataType* s,size_t num) {
        // just to make sure we have a sensor here
        if (s && num < _sensors.size()) {
			*s = _sensors[num];
        }
    }

	void set(const DataType t) {

        _updateCount++;

		auto N = static_cast<size_t>(t.sensor + 1);

		// resize internal sensor representation
		if (N >= _sensors.size()) {
			_sensors.resize(N);
        }

		_sensors[static_cast<size_t>(t.sensor)] = t;

		this->_hasUpdates = true;
    }

    size_t sensorCount() const {
        return _sensors.size();
    }

	size_t updateCount() const {
        return _updateCount;
    }

	~VRPN_Tracker_Remote() {
        _remote->unregister_change_handler(this, VRPN_Remote_Callback);
    }
};

//
// Wrappers
//
UVRPN_PINVOKE_EXPORT
void* uvrpn_tracker_create(const char* url) {
	return new VRPN_Tracker_Remote(url);
}

UVRPN_PINVOKE_EXPORT
void uvrpn_tracker_update(void* tracker) {
	VRPN_Tracker_Remote* t = static_cast<VRPN_Tracker_Remote*>(tracker);
    t->update();
}

UVRPN_PINVOKE_EXPORT
void uvrpn_tracker_get_sensor(void* tracker,VRPN_Tracker_Remote::DataType *s,size_t num) {
	VRPN_Tracker_Remote* t = static_cast<VRPN_Tracker_Remote*>(tracker);
    t->get(s,num);
}

UVRPN_PINVOKE_EXPORT
size_t uvrpn_tracker_get_sensor_count(void* tracker) {
	VRPN_Tracker_Remote* t = static_cast<VRPN_Tracker_Remote*>(tracker);
    return t->sensorCount();
}

UVRPN_PINVOKE_EXPORT
size_t uvrpn_tracker_get_update_count(void* tracker) {
	VRPN_Tracker_Remote* t = static_cast<VRPN_Tracker_Remote*>(tracker);
    return t->updateCount();
}

UVRPN_PINVOKE_EXPORT
void uvrpn_tracker_destroy(void* tracker) {
	VRPN_Tracker_Remote* t = static_cast<VRPN_Tracker_Remote*>(tracker);
    if (t) {
        delete t;
		t = nullptr;
    }
}


//
// Callback
//
void VRPN_CALLBACK VRPN_Remote_Callback(void *userdata, const vrpn_TRACKERCB t)
{
	VRPN_Tracker_Remote* r = static_cast<VRPN_Tracker_Remote*>(userdata);
	if (r) {
        r->set(t);
    }
}
