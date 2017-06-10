
#include "vrpn_Configure.h"
#include "vrpn_Analog.h"
#include "vrpn_Tracker.h"

#include <vector>

#include "uvrpn_exports.hpp"

struct VRPN_Remote;

void VRPN_Remote_Callback(void *userdata, const vrpn_TRACKERCB t);


struct VRPN_Sensor {
    quad_t _rotation;
    double _position;
};

struct VRPN_Remote {

    vrpn_Tracker_Remote* _remote;
    bool _hasUpdates;
    std::vector<VRPN_Sensor> _sensors;

    VRPN_Remote(const char* url)
        : _remote(new vrpn_Tracker_Remote(url))
        , _hasUpdates(false)
    {
        _remote->register_change_handler(this, VRPN_Remote_Callback);
    }

    void update() {
        while(_hasUpdates) {
            _hasUpdates = false;
            _remote->mainloop();
        }
    }

    void set(const vrpn_TRACKERCB t) {
        if ((t.sensor + 1) >= _sensors.size()) {
            _sensors.resize(t.sensor);
        }

        VRPN_Sensor &sensor = _sensors[t.sensor];
    }

    ~VRPN_Remote() {
        delete _remote;
    }
};

//
// Wrappers
//
UVRPN_PINVOKE_EXPORT
void* uvrpn_tracker_create(const char* url) {
    return new VRPN_Remote(url);
}

UVRPN_PINVOKE_EXPORT
void uvrpn_tracker_update(void* tracker) {
    VRPN_Remote* t = static_cast<VRPN_Remote*>(tracker);
    t->update();
}

UVRPN_PINVOKE_EXPORT
void uvrpn_tracker_destroy(void** tracker) {
    VRPN_Remote* t = static_cast<VRPN_Remote*>(*tracker);
    if (t) {
        delete t;
        t = 0L;
    }
}


//
// Callback
//
void VRPN_Remote_Callback(void *userdata, const vrpn_TRACKERCB t)
{
    VRPN_Remote* r = static_cast<VRPN_Remote*>(userdata);
    if (r) {
        r->_hasUpdates = true;
        r->set(t);
    }



}
