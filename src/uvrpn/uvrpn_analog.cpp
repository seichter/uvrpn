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
#include "vrpn_Button.h"

#include <memory>
#include "uvrpn_exports.hpp"

void VRPN_Analog_Callback(void *userdata, const vrpn_ANALOGCB info);

struct vrpn_Analog_Wrapper {

	std::unique_ptr<vrpn_Analog_Remote> _remote;
	vrpn_ANALOGCB _data;

	vrpn_Analog_Wrapper(const char* url)
		: _remote(new vrpn_Analog_Remote(url))
	{
		// register a change hander
		_remote->register_change_handler(this, VRPN_Analog_Callback);
	}

	void set(const vrpn_ANALOGCB t) {
		// copy data
		_data = t;
	}

	void get() {
	}
};



void VRPN_Analog_Callback(void *userdata, const vrpn_ANALOGCB info)
{
	reinterpret_cast<vrpn_Analog_Wrapper*>(userdata)->set(info);
}

//#include "vrpn_Configure.h"
//#include "vrpn_Analog.h"
//#include "vrpn_Tracker.h"


//#include <memory>
//#include <vector>


//vrpn_ANALOGCB

//struct VRPN_Remote;

//void VRPN_Remote_Callback(void *userdata, const vrpn_TRACKERCB t);

//struct vrpn_Analog {
//    vrpn_float64 _position[3];
//    vrpn_float64 _rotation[4];
//};

//struct VRPN_Remote {

//    std::unique_ptr<vrpn_Tracker_Remote> _remote;

//    bool _hasUpdates;
//    std::vector<VRPN_Sensor> _sensors;

//    int _updateCount = 0;

//    VRPN_Remote(const char* url)
//        : _remote(new vrpn_Tracker_Remote(url))
//        , _hasUpdates(false)
//    {
//        // register a change hander
//        _remote->register_change_handler(this, VRPN_Remote_Callback);
//    }

//    void update() {

//        do {
//            // reset hasUpdates ...
//            _hasUpdates = false;
//            // call loop
//            _remote->mainloop();
//            // check if there were actually some updates
//        } while(_hasUpdates);
//    }

//    void get(VRPN_Sensor* s,size_t num) {
//        // just to make sure we have a sensor here
//        if (s && num < _sensors.size()) {
//            s->_position[0] = _sensors[num]._position[0];
//            s->_position[1] = _sensors[num]._position[1];
//            s->_position[2] = _sensors[num]._position[2];

//            s->_rotation[0] = _sensors[num]._rotation[0];
//            s->_rotation[1] = _sensors[num]._rotation[1];
//            s->_rotation[2] = _sensors[num]._rotation[2];
//            s->_rotation[3] = _sensors[num]._rotation[3];
//        }
//    }

//    void set(const vrpn_TRACKERCB t) {

//        _updateCount++;

//        if ((t.sensor + 1) >= _sensors.size()) {
//            _sensors.resize(t.sensor + 1);
//        }

//        VRPN_Sensor &sensor = _sensors[t.sensor];

//        // copy internal data
//        // position in order x,y,z
//        sensor._position[0] = t.pos[0];
//        sensor._position[1] = t.pos[1];
//        sensor._position[2] = t.pos[2];

//        // rotation as quaternion in order x,y,z,w
//        sensor._rotation[0] = t.quat[0];
//        sensor._rotation[1] = t.quat[1];
//        sensor._rotation[2] = t.quat[2];
//        sensor._rotation[3] = t.quat[3];
//    }

//    size_t sensorCount() const {
//        return _sensors.size();
//    }

//    int updateCount() const {
//        return _updateCount;
//    }

//    ~VRPN_Remote() {
//        _remote->unregister_change_handler(this, VRPN_Remote_Callback);
//    }
//};

////
//// Wrappers
////
//UVRPN_PINVOKE_EXPORT
//void* uvrpn_tracker_create(const char* url) {
//    return new VRPN_Remote(url);
//}

//UVRPN_PINVOKE_EXPORT
//void uvrpn_tracker_update(void* tracker) {
//    VRPN_Remote* t = static_cast<VRPN_Remote*>(tracker);
//    t->update();
//}

//UVRPN_PINVOKE_EXPORT
//void uvrpn_tracker_get_sensor(void* tracker,VRPN_Sensor *s,size_t num) {
//    VRPN_Remote* t = static_cast<VRPN_Remote*>(tracker);
//    t->get(s,num);
//}

//UVRPN_PINVOKE_EXPORT
//size_t uvrpn_tracker_get_sensor_count(void* tracker) {
//    VRPN_Remote* t = static_cast<VRPN_Remote*>(tracker);
//    return t->sensorCount();
//}

//UVRPN_PINVOKE_EXPORT
//int uvrpn_tracker_get_update_count(void* tracker) {
//    VRPN_Remote* t = static_cast<VRPN_Remote*>(tracker);
//    return t->updateCount();
//}

//UVRPN_PINVOKE_EXPORT
//void uvrpn_tracker_destroy(void* tracker) {
//    VRPN_Remote* t = static_cast<VRPN_Remote*>(tracker);
//    if (t) {
//        delete t;
//        t = 0L;
//    }
//}


//
// Callback
//
void VRPN_CALLBACK VRPN_Remote_Callback(void *userdata, const vrpn_ANALOGCB t)
{
//    vrpn_AN* r = static_cast<VRPN_Remote*>(userdata);
//    if (r) {
//        r->_hasUpdates = true;
//        r->set(t);
//    }
}
