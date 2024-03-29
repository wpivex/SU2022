#pragma once

class Intakeable {
public:
    virtual void setVelocity(float velocity) = 0;
    void stop() { setVelocity(0); }
    virtual void setIndexer(bool on) {};
};